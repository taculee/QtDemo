#include <QTextCodec>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "windows.h"
#include <qdatetime.h> // ������ʱ


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); // ʹ����ɴ�������
    MainWindow w;
    w.show();

    return a.exec();
}
