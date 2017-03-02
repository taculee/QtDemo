#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "win_qextserialport.h" // 加入头文件
#include "mythread.h"
#include <QDebug>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Win_QextSerialPort *myCom; // 声明对象
    MyThread thread; // 声明对象
private slots:
    void SPI_Translate(QByteArray &); // 对SPI进行位确定
    void readMyCom(); // 声明读串口函数
    void autoScroll();
    void on_openMyComBtn_clicked();
    void on_closeMyComBtn_clicked();
    void on_sendMsgBtn_clicked();
    void on_startTestButton_clicked();
    void on_resetButton_clicked();
    void on_saveCfgButton_clicked();
    void on_readCfgButton_clicked();
};

/* 延时类，线程延时 */
class SleeperThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};


#endif // MAINWINDOW_H
