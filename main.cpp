#include <QTextCodec>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "windows.h"
#include <qdatetime.h> // 用于延时


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); // 使程序可处理中文
    MainWindow w;
    w.show();

    return a.exec();
}
