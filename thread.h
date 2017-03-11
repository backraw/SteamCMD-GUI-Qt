#ifndef THREAD_H
#define THREAD_H

#include <QObject>


namespace steamcmd {

/**
 * @brief steamcmd::Thread:
 * Base class for application thread objects.
 *
 * A subclass must implement the methods start() and run().
 */
class Thread : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief c'tor
     *
     * @param parent A pointer to the QOgject parent (always 0)
     */
    explicit Thread(QObject *parent = 0);

    /**
     * @brief Virtual method:
     * To be implemented by subclasses.
     *
     * The subclass shall call startWithSignal() with the appropriate signal in this method.
     *
     * @param receiver A pointer to a QObject instance which contains the slot to signal to
     * @param slot The receiver's slot member function
     */
    virtual void start(const QObject *receiver, const char *slot) = 0;

public slots:
    /**
     * @brief Virtual method:
     * To be implemented by subclasses.
     *
     * The subclass shall implement the running behavior in this method.
     */
    virtual void run() = 0;

protected:
    /**
     * @brief Call run() on a new QThread instance:
     * <ol>
     *   <li>Create a new QThread instance on the heap</li>
     *   <li>Connect signals and slots</li>
     *   <li>Call the thread's start() method</li>
     * </ol>
     *
     * @param signal The signal to listen to
     * @param receiver A pointer to a QObject instance which contains the slot to signal to
     * @param slot The receiver's slot member function
     */
    void startWithSignal(const char *signal, const QObject *receiver, const char *slot);
};

} // namespace steamcmd

#endif // THREAD_H
