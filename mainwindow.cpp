#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdatetime.h>
#include <qlineedit.h>
#include <QFileDialog>
#include <QMessageBox>
#include "string.h"

using namespace std;

char array2char(unsigned long long SPI_LUT, unsigned char BIT);

/* SPI位长放置设置 */
#define SPI_SIZE_BIT1 5
#define SPI_SIZE_BIT2 6

/* SPI超始化设置 */
#define SPI_START 8

/* SPI所在位置定义 */
#define SPI_63 (SPI_START+63)
#define SPI_62 (SPI_START+62)
#define SPI_61 (SPI_START+61)
#define SPI_60 (SPI_START+60)
#define SPI_59 (SPI_START+59)
#define SPI_58 (SPI_START+58)
#define SPI_57 (SPI_START+57)
#define SPI_56 (SPI_START+56)
#define SPI_55 (SPI_START+55)
#define SPI_54 (SPI_START+54)
#define SPI_53 (SPI_START+53)
#define SPI_52 (SPI_START+52)
#define SPI_51 (SPI_START+51)
#define SPI_50 (SPI_START+50)
#define SPI_49 (SPI_START+49)
#define SPI_48 (SPI_START+48)
#define SPI_47 (SPI_START+47)
#define SPI_46 (SPI_START+46)
#define SPI_45 (SPI_START+45)
#define SPI_44 (SPI_START+44)
#define SPI_43 (SPI_START+43)
#define SPI_42 (SPI_START+42)
#define SPI_41 (SPI_START+41)
#define SPI_40 (SPI_START+40)
#define SPI_39 (SPI_START+39)
#define SPI_38 (SPI_START+38)
#define SPI_37 (SPI_START+37)
#define SPI_36 (SPI_START+36)
#define SPI_35 (SPI_START+35)
#define SPI_34 (SPI_START+34)
#define SPI_33 (SPI_START+33)
#define SPI_32 (SPI_START+32)
#define SPI_31 (SPI_START+31)
#define SPI_30 (SPI_START+30)
#define SPI_29 (SPI_START+29)
#define SPI_28 (SPI_START+28)
#define SPI_27 (SPI_START+27)
#define SPI_26 (SPI_START+26)
#define SPI_25 (SPI_START+25)
#define SPI_24 (SPI_START+24)
#define SPI_23 (SPI_START+23)
#define SPI_22 (SPI_START+22)
#define SPI_21 (SPI_START+21)
#define SPI_20 (SPI_START+20)
#define SPI_19 (SPI_START+19)
#define SPI_18 (SPI_START+18)
#define SPI_17 (SPI_START+17)
#define SPI_16 (SPI_START+16)
#define SPI_15 (SPI_START+15)
#define SPI_14 (SPI_START+14)
#define SPI_13 (SPI_START+13)
#define SPI_12 (SPI_START+12)
#define SPI_11 (SPI_START+11)
#define SPI_10 (SPI_START+10)
#define SPI_9 (SPI_START+9)
#define SPI_8 (SPI_START+8)
#define SPI_7 (SPI_START+7)
#define SPI_6 (SPI_START+6)
#define SPI_5 (SPI_START+5)
#define SPI_4 (SPI_START+4)
#define SPI_3 (SPI_START+3)
#define SPI_2 (SPI_START+2)
#define SPI_1 (SPI_START+1)
#define SPI_0 (SPI_START+0)

// START OF WHAT YOU NEED TO EDIT:
/* Start of define macro----------------------------------------------------------------------------------------------------- */
#define SPI_SIZE 63 // SPI的bit长度

/* SPI各位定义 */
#define RL1 SPI_0
#define RL2 SPI_1
#define RS1 SPI_2
#define RS2 SPI_3
#define RS3 SPI_4
#define RS4 SPI_5
#define RS5 SPI_6
#define SP31 SPI_7
#define SP32 SPI_8
#define SP21 SPI_9
#define SP22 SPI_10
#define SP11 SPI_11
#define SP12 SPI_12
#define SP4 SPI_13
#define SP3 SPI_14
#define SP2 SPI_15
#define SP1 SPI_16
#define DCOC2 SPI_17
#define DCOC1 SPI_18
/* ----------------------------------------------------------------------------------------------------- End of define macro*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->closeMyComBtn->setEnabled(false); // 开始“关闭串口”按钮不可用
    ui->sendMsgBtn->setEnabled(false); // 开始“发送数据”按钮不可用
    ui->startTestButton->setEnabled(false); // 开始测试不可用
    ui->resetButton->setEnabled(false); // 开始测试不可用

    /* Start of Combo Box Set----------------------------------------------------------------------------------------------------- */
    /* 在这里设置你的Combo Box的“可编辑性”与“输入范围” */
    QRegExp rx("^[0-9]{1,10}$"); // 这个10就是最大长度
    QValidator *validator = new QRegExpValidator(rx,0);

    /* Combo Box“可编辑性”设置 */
    /* 示例：ui->gainSetBox->setEditable(true); // 设置增益输入为可编辑 */
    ui->gainSetBox->setEditable(true);

    /* 设置Combo Box的“输入范围” */
    /* 示例：ui->gainSetBox->lineEdit()->setValidator(validator); */
    ui->gainSetBox->lineEdit()->setValidator(validator);

    /* 设置LineEdit的"输入范围" */
    QRegExp regx("[!-&---a-zA-Z0-9]+$");
    QValidator *validatorgx = new QRegExpValidator(regx, 0 );
    ui->sendMsgLineEdit->setValidator( validatorgx );

    /* -----------------------------------------------------------------------------------------------------End of Combo Box Set */
}


void MainWindow::on_startTestButton_clicked()
{
    int tmpIndex;
    tmpIndex = ui->tabWidget->currentIndex(); // 获取当前Tab页面值，从0开始。

    /* Start of UART output----------------------------------------------------------------------------------------------------- */
    /* 要输出的字符数组，示例：QByteArray writeByte; */
    QByteArray writeByte;

    writeByte[0] = '$';
    writeByte[1] = 'S';
    writeByte[2] = 'P';
    writeByte[3] = 'I';
    writeByte[4] = '-';
    writeByte[5] = (int)(SPI_SIZE/10) + '0';
    writeByte[6] = SPI_SIZE%10+'0';
    writeByte[7] = '-';

    switch(tmpIndex){ // 只有当在参数设置Tab时才输出数据
    case 0:
        qDebug() << QString("Start of parameter test --"); // Debug

        SPI_Translate(writeByte); // 根据Combox Box来设置SPI的各位。

        if(writeByte.size()<(SPI_SIZE+SPI_START)){ // 自动补位
            int intTmp = writeByte.size();
            for(int i = intTmp; i<SPI_SIZE+SPI_START;i++)
                writeByte[i] = '0';
        }

        writeByte[writeByte.size()] = '#'; // 自动补结尾标识
        qDebug() << QString("The length of QByteArray:");
        qDebug() << writeByte.size(); // 用于获取并输出QByteArray的长度
        qDebug() << QString("The string to output");
        qDebug() << writeByte; // 用出显示要打印到串口的数据

        qDebug() << QString("-- End of parameter tesT"); // Debug

        myCom->write(writeByte);
        break;
    default:
        qDebug() << QString("Warning: No this Tab！");
        break;
    } // end of switch(tmpIndex)
    /* -----------------------------------------------------------------------------------------------------Start of UART output */
}

/* Start of SPI_Translate----------------------------------------------------------------------------------------------------- */
unsigned long long int SPI_LUT[61] = {
    0x00041,
    0x02041,
    0x02042,
    0x02040,
    0x02061,
    0x02062,
    0x06041,
    0x06042,
    0x06040,
    0x06061,
    0x06062,
    0x1E041,
    0x1E042,
    0x1E040,
    0x1E061,
    0x1E062,
    0x1E041,
    0x1E042,
    0x1E040,
    0x1E061,
    0x1E062,
    0x1E841,
    0x1E842,
    0x1E840,
    0x1E861,
    0x1E862,
    0x1EA41,
    0x1EA42,
    0x1EA40,
    0x1EA61,
    0x1EA62,
    0x1FA41,
    0x1FA42,
    0x1FA40,
    0x1FA61,
    0x1FA62,
    0x1FE41,
    0x1FE42,
    0x1FE40,
    0x1FE61,
    0x1FE62,
    0x1FEC1,
    0x1FEC2,
    0x1FEC0,
    0x1FEE1,
    0x1FEE2,
    0x1FFC1,
    0x1FFC2,
    0x1FFC0,
    0x1FFE1,
    0x1FFE2,
    0x1FFE0,
    0x1FFF1,
    0x1FFF2,
    0x1FFF0,
    0x1FFF9,
    0x1FFFA,
    0x1FFF8,
    0x1FFFD,
    0x1FFFE,
    0x1FFFC
};

void MainWindow::SPI_Translate(QByteArray &writeByte){
    /* C++标准string类型数据，示例：string strGain; */
    string strGain;
    string strDcoc1;
    string strDcoc2;
    /* Qt扩展类，示例：QString qstrGain; */
    QString qstrGain;
    QString qstrDcoc1;
    QString qstrDcoc2;

    /* 获取Combo Box数据，示例：qstrGain = ui->gainSetBox->currentText(); // 获取Combo Box的数值
                             strGain = qstrGain.toStdString(); // 转化为标准string */
    qstrGain = ui->gainSetBox->currentText();
    qstrDcoc1 = ui->dcoc1Box->currentText();
    qstrDcoc2 = ui->dcoc2Box->currentText();

    strGain = qstrGain.toStdString(); // 化为C++标准string，易于学过C++的人进行处理
    strDcoc1 = qstrDcoc1.toStdString();
    strDcoc2 = qstrDcoc2.toStdString();

    int dB = atoi(strGain.c_str());
    qDebug() << QString("dB:");
    qDebug() << dB;

    /* array2char是把SPI_LUT[dB]中的RL1位转换为char型再赋给writeByte */
    writeByte[RL1] = array2char(SPI_LUT[dB], RL1);
    writeByte[RL2] = array2char(SPI_LUT[dB], RL2);
    writeByte[RS1] = array2char(SPI_LUT[dB], RS1);
    writeByte[RS2] = array2char(SPI_LUT[dB], RS2);
    writeByte[RS3] = array2char(SPI_LUT[dB], RS3);
    writeByte[RS4] = array2char(SPI_LUT[dB], RS4);
    writeByte[RS5] = array2char(SPI_LUT[dB], RS5);
    writeByte[SP31] = array2char(SPI_LUT[dB], SP31);
    writeByte[SP32] = array2char(SPI_LUT[dB], SP32);
    writeByte[SP21] = array2char(SPI_LUT[dB], SP21);
    writeByte[SP22] = array2char(SPI_LUT[dB], SP22);
    writeByte[SP11] = array2char(SPI_LUT[dB], SP11);
    writeByte[SP12] = array2char(SPI_LUT[dB], SP12);
    writeByte[SP4] = array2char(SPI_LUT[dB], SP4);
    writeByte[SP3] = array2char(SPI_LUT[dB], SP3);
    writeByte[SP2] = array2char(SPI_LUT[dB], SP2);
    writeByte[SP1] = array2char(SPI_LUT[dB], SP1);

    /* 转换部分 */
    switch(strDcoc1[0]){
    case '0':
        writeByte[DCOC1] = '0';
        break;
    case '1':
        writeByte[DCOC1] = '1';
        break;
    }

    switch(strDcoc2[0]){
    case '0':
        writeByte[DCOC2] = '0';
        break;
    case '1':
        writeByte[DCOC2] = '1';
        break;
    }

}
/* -----------------------------------------------------------------------------------------------------Start of SPI_Translate */

char array2char(unsigned long long SPI_LUT, unsigned char BIT){
    unsigned long long int llintTmp;
    char charTmp;

    BIT -= SPI_START;
    llintTmp = (SPI_LUT>>BIT)&0x01;
    charTmp = (char)llintTmp + '0';
    return charTmp;
}

void MainWindow::on_resetButton_clicked()
{
    QByteArray writeByte;
    writeByte[0] = '$';
    writeByte[1] = 'R';
    writeByte[2] = 'S';
    writeByte[3] = 'T';
    writeByte[4] = '!';
    myCom->write(writeByte);
    qDebug() << QString("reset --"); // Debug
    qDebug() << writeByte;
    qDebug() << QString("-- reset"); // Debug

    ui->receiveMsgTextBrowser->clear();
    ui->sendMsgLineEdit->clear();
}

void MainWindow::on_saveCfgButton_clicked()
{


    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("保存设置文件"),
                                                    "",
                                                    tr("Config Files (*.txt)")); // 打开文件对话框并获取文件路径信息

    if (!fileName.isNull())
    {
        QDateTime curTime;
        QString strCurTime=curTime.currentDateTime().toString("yyyy-MM-dd HH-mm-ss"); // 保存设置文件的时间信息
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) // 只写、结束符修正、清空
        {
            QMessageBox::warning(this,"Waining!","File can't open.",QMessageBox::Yes); // 打开错误提示并结束
        }
        else{
            QTextStream cfgStream(&file);
            cfgStream<<strCurTime<<"\n";

             /* Start of Combo Box Index Save----------------------------------------------------------------------------------------------------- */
            int gainIndex;
            int dcoc1Index;
            int dcoc2Index;

            /* 获取Combo Box当前索引 */
            gainIndex = ui->gainSetBox->currentIndex();
            dcoc1Index = ui->dcoc1Box->currentIndex();
            dcoc2Index = ui->dcoc2Box->currentIndex();

            /* 将Combo Box当前索引写入文件，每个Combo Box占一行 */
            cfgStream<<QString::number(gainIndex)<<"\n";
            cfgStream<<QString::number(dcoc1Index)<<"\n";
            cfgStream<<QString::number(dcoc2Index)<<"\n";
            /* -----------------------------------------------------------------------------------------------------End of Combo Box Index Save */

            file.close();
        }
    }
}

void MainWindow::on_readCfgButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("打开设置文件"),
                                                    "",
                                                    tr("Config Files (*.txt)"),
                                                    0);
    if (!fileName.isNull())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"file","can't open",QMessageBox::Yes);
        }
        else{
            QTextStream cfgStream(&file);
            QString strCurTime;
            strCurTime = cfgStream.readLine();

             /* Start of Combo Box Index Read----------------------------------------------------------------------------------------------------- */
            QString qstrGain;
            QString qstrDcoc1;
            QString qstrDcoc2;

            /* 每次读取文件中的一行 */
            qstrGain = cfgStream.readLine();
            qstrDcoc1 = cfgStream.readLine();
            qstrDcoc2 = cfgStream.readLine();

            /* 设置Combo Box当前索引 */
            ui->gainSetBox->setCurrentIndex(qstrGain.toInt());
            ui->dcoc1Box->setCurrentIndex(qstrDcoc1.toInt());
            ui->dcoc2Box->setCurrentIndex(qstrDcoc2.toInt());
            /* -----------------------------------------------------------------------------------------------------End of Combo Box Index Read */
        }
    }
    else{
        QMessageBox::warning(this,"Warning! ","No setting file is read.",QMessageBox::Yes);
    }
}
// END OF WHAT YOU NEED TO EDIT.

void MainWindow::readMyCom() // 读串口函数
{
    QByteArray temp;
    int numTmp;
    numTmp = myCom->bytesAvailable(); // waitForReadyRead
    temp = myCom->read(numTmp); // 读取串口缓冲区的所有数据给临时变量temp
    ui->receiveMsgTextBrowser->insertPlainText(temp);
}

void MainWindow::autoScroll()
{
    QTextCursor cursor =  ui->receiveMsgTextBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->receiveMsgTextBrowser->setTextCursor(cursor);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openMyComBtn_clicked()
{
    QString portName = ui->portNameComboBox->currentText(); // 获取串口名
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven); // 定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom ->open(QIODevice::ReadWrite); //打开串口
    if(ui->baudRateComboBox->currentText()==tr("9600")) //根据组合框内容对串口进行设置
    myCom->setBaudRate(BAUD9600);
    else if(ui->baudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200); // 设置波特率
    if(ui->dataBitsComboBox->currentText()==tr("8"))
    myCom->setDataBits(DATA_8);
    else if(ui->dataBitsComboBox->currentText()==tr("7"))
    myCom->setDataBits(DATA_7); // 设置数据位
    if(ui->parityComboBox->currentText()==tr("无"))
    myCom->setParity(PAR_NONE);
    else if(ui->parityComboBox->currentText()==tr("奇"))
    myCom->setParity(PAR_ODD);
    else if(ui->parityComboBox->currentText()==tr("偶"))
    myCom->setParity(PAR_EVEN); // 设置奇偶校验
    if(ui->stopBitsComboBox->currentText()==tr("1"))
    myCom->setStopBits(STOP_1);
    else if(ui->stopBitsComboBox->currentText()==tr("2"))
    myCom->setStopBits(STOP_2); // 设置停止位
    myCom->setFlowControl(FLOW_OFF); //设置数据流控制，我们使用无数据流控制的默认设置
    myCom->setTimeout(500); //设置延时
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom())); // 信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
    connect(ui->receiveMsgTextBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));
    ui->openMyComBtn->setEnabled(false); // 打开串口后“打开串口”按钮不可用
    ui->closeMyComBtn->setEnabled(true); // 打开串口后“关闭串口”按钮可用
    ui->sendMsgBtn->setEnabled(true); // 打开串口后“发送数据”按钮可用
    ui->baudRateComboBox->setEnabled(false); // 设置各个组合框不可用
    ui->dataBitsComboBox->setEnabled(false);
    ui->parityComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);
    ui->portNameComboBox->setEnabled(false);
    ui->startTestButton->setEnabled(true); // 开始测试可用
    ui->resetButton->setEnabled(true); // 复位可用
}

void MainWindow::on_closeMyComBtn_clicked()
{
    myCom->close();
    ui->openMyComBtn->setEnabled(true); // 关闭串口后“打开串口”按钮可用
    ui->closeMyComBtn->setEnabled(false); // 关闭串口后“关闭串口”按钮不可用
    ui->sendMsgBtn->setEnabled(false); // 关闭串口后“发送数据”按钮不可用
    ui->baudRateComboBox->setEnabled(true); // 设置各个组合框可用
    ui->dataBitsComboBox->setEnabled(true);
    ui->parityComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
    ui->portNameComboBox->setEnabled(true);
    ui->startTestButton->setEnabled(false); // 开始测试不可用
    ui->resetButton->setEnabled(false); // 复位不可用
}

void MainWindow::on_sendMsgBtn_clicked()
{
    myCom->write(ui->sendMsgLineEdit->text().toAscii()); // 以ASCII码形式将行编辑框中的数据写入串口
    QString temp = ui->sendMsgLineEdit->text();
}

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


