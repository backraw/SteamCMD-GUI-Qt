#!/usr/bin/env python3

# =============================================================================
# >> IMPORTS
# =============================================================================
import sys
assert sys.version_info >= (3, 4)  # TODO: put this below the other imports?

import os

from bs4 import BeautifulSoup

from contextlib import suppress

from json import dump as json_dump
from json import load as json_load

from urllib.request import urlopen


# =============================================================================
# >> CONSTANTS
# =============================================================================
VALVE_SERVERS_LIST_URL = 'https://developer.valvesoftware.com/wiki/Dedicated_Servers_List'
SERVERLIST_JSON = os.path.join(os.path.expanduser('~'), '.config', 'steamcmd-gui-qt', 'serverlist.json')


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerList(dict):
    """Dict class used to interact with and update the settings.json file with Steam AppID information."""

    def __init__(self):
        """Constructor: Read the settings.json file if it exists."""
        # Read <SERVERLIST_JSON> file if it exists
        if os.path.isfile(SERVERLIST_JSON):
            with open(SERVERLIST_JSON) as f:
                super().__init__(json_load(f))
        else:
            super().__init__()

    def dump(self):
        """Write the contents of this dict to file."""
        s = dict([key, self[key]] for key in sorted(self))

        with open(SERVERLIST_JSON, 'w') as f:
            json_dump(s, f, indent=4)
            f.write('\n')

    def parse(self):
        """Parse <VALVE_SERVERS_LIST_URL>."""
        # Parse <VALVE_SERVERS_LIST_URL> via BeautifulSoup
        html = BeautifulSoup(urlopen(VALVE_SERVERS_LIST_URL).read(), 'lxml')

        # Get the game server contents list
        content = html.find('div', id='mw-content-text')

        # Clean up....
        if self:
            self.clear()

        # Update the server list...
        for title in content.find_all('h2')[1:-1]:

            # Only parse Linux dedicated servers
            if 'Linux' not in title.span.get_text():
                continue

            # Get the table containing the servers
            table = title.next_sibling.next_sibling

            # Get the first table row defining a game server
            tr = table.next_element.next_element.next_sibling.next_sibling

            while tr is not None:
                with suppress(AttributeError):
                    # Get the table data element containing the server's name
                    td_name = tr.next_element.next_element

                    # Get the server's name
                    name = [x for x in td_name.get_text().split() if x]

                    if 'Dedicated' in name:
                        name.remove('Dedicated')

                    while name[-1].lower() in ('server', 'server]', '-', 'linux'):
                        name.pop()

                    # Create a new section for this dedicated server
                    server = self[' '.join(name)] = dict()

                    # Parse this server's information
                    td = self._parse_td(td_name, server, 'appid')
                    td = self._parse_td(td, server, 'steamcmd')
                    td = self._parse_td(td, server, 'steamclient')
                    self._parse_td(td, server, 'anonymous')

                # Parse the next table row
                try:
                    tr = tr.next_sibling

                except AttributeError:

                    # If the try-call resulted in an error, we are finished with this table
                    tr = None

    def _parse_td(self, td, server, key):
        """Parse the table data information from <td> into <server[key]>."""
        # Get the table data element containing the information
        td = td.next_sibling.next_element

        # Get its text
        text = td.get_text()

        # If there's no text, then it equals <false>
        if not text:
            text = False

        # Else, parse the right type...
        else:
            if text.isdigit():
                text = int(text)
            else:
                text = True

        # Put the parsed text into <server[key]>
        server[key] = text

        # Return the new table data element
        return td


# =============================================================================
# >> MAIN
# =============================================================================
if __name__ == '__main__':
    # Create a Settings object
    serverlist = ServerList()

    # Parse <VALVE_SERVERS_LIST_URL>
    serverlist.parse()

    # Dump the new settings file
    serverlist.dump()
