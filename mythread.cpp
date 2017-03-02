#include "mythread.h"
#include <QDebug>
#include "string.h"

using namespace std;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
}

void MyThread::run()
{
    while (!stopped) {
    }
    stopped = false;
}

void MyThread::stop()
{
    stopped = true;
}
