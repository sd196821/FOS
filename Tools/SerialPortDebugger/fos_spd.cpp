#include "fos_spd.h"
#include "ui_fos_spd.h"
#include "pcloop.h"

#include <QDebug>

FOS_SPD::FOS_SPD(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FOS_SPD)
{
    currentPort = 0;
    ui->setupUi(this);
    ports = new Ports();
    ui->comboBox_PortName->addItem("Selet your port");
    for(int i = 0; i < ports->getAvailablePortNumber(); ++i)
    {
        if(ports->getPort(i) != 0)
            ui->comboBox_PortName->addItem(ports->getPort(i)->portName());
    }
}

FOS_SPD::~FOS_SPD()
{
    delete ui;
}

Ports::Ports()
{
    availablePortNumber = QSerialPortInfo::availablePorts().length();

    qDebug()<<availablePortNumber;

    port = new QSerialPort*[availablePortNumber];
    for(int i = 0; i < availablePortNumber; ++i)
    {
        port[i] = new QSerialPort(QSerialPortInfo::availablePorts()[i]);
        qDebug()<<port[i]->portName();
    }
}

Ports::~Ports()
{
    for(int i = 0; i < availablePortNumber; ++i)
        delete port[i];
}

QSerialPort *Ports::getPort(int number)
{
    if((number < availablePortNumber)&& (number >= 0))
        return port[number];
    else
        return 0;
}

int Ports::getAvailablePortNumber() const
{
    return availablePortNumber;
}

void FOS_SPD::on_comboBox_PortName_currentIndexChanged(int index)
{
    if(currentPort != 0)
    {
        if(currentPort->isOpen())
            currentPort->close();
        this->disconnect(currentPort);
    }
    currentPort = ports->getPort(index-1);
    if(currentPort != 0)
    {
        connect(currentPort,SIGNAL(readyRead()),this,SLOT(monitor()));
        currentPort->setBaudRate(ui->lineEdit->text().toInt());
        currentPort->setDataBits(QSerialPort::Data8);
        currentPort->setParity(QSerialPort::NoParity);
        currentPort->setFlowControl(QSerialPort::NoFlowControl);
        currentPort->setStopBits(QSerialPort::OneStop);
        if(currentPort->open(QIODevice::ReadWrite))
            ui->textBrowser->append("Open Success!");
        else
            ui->textBrowser->append("Fail to open");
    }
}

void FOS_SPD::on_lineEdit_textChanged(const QString &arg1)
{
    currentPort->setBaudRate(arg1.toInt());
}

void FOS_SPD::on_pushButton_clicked()
{
    currentPort->write(ui->textBrowser_2->toPlainText().toLocal8Bit());
}

void FOS_SPD::monitor()
{
    ui->textBrowser->append(currentPort->readAll());
}

void FOS_SPD::on_pushButton_2_clicked()
{
    PCLoop dialog;
    dialog.setPort(currentPort);
    dialog.exec();
    connect(currentPort,SIGNAL(readyRead()),this,SLOT(monitor()));
    qDebug()<<"Quit";
}
