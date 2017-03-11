#include <QThread>

#include "thread.h"


namespace steamcmd {

Thread::Thread(QObject *parent)
    : QObject(parent)
{
}

void Thread::startWithSignal(const char *signal, const QObject *receiver, const char *slot)
{
    // Create a new thread
    QThread *thread = new QThread();

    // Create a worker and move it to the thread
    moveToThread(thread);

    // Connect signals and slots
    QObject::connect(this, signal, receiver, slot);
    QObject::connect(thread, SIGNAL(started()), this, SLOT(run()));
    QObject::connect(this, signal, thread, SLOT(quit()));
    QObject::connect(this, signal, this, SLOT(deleteLater()));
    QObject::connect(thread, signal, thread, SLOT(deleteLater()));

    // Start the thread
    thread->start();
}

} // namespace steamcmd
