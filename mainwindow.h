#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "win_qextserialport.h" // ����ͷ�ļ�
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
    Win_QextSerialPort *myCom; // ��������
    MyThread thread; // ��������
private slots:
    void SPI_Translate(QByteArray &); // ��SPI����λȷ��
    void readMyCom(); // ���������ں���
    void autoScroll();
    void on_openMyComBtn_clicked();
    void on_closeMyComBtn_clicked();
    void on_sendMsgBtn_clicked();
    void on_startTestButton_clicked();
    void on_resetButton_clicked();
    void on_saveCfgButton_clicked();
    void on_readCfgButton_clicked();
};

/* ��ʱ�࣬�߳���ʱ */
class SleeperThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};


#endif // MAINWINDOW_H
