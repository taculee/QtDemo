#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "windows.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void stop();

protected:
    void run();

private:
    volatile bool stopped;

signals:

public slots:

};

#endif // MYTHREAD_H
