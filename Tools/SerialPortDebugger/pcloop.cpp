#include "pcloop.h"
#include "ui_pcloop.h"

#include <QDebug>

PCLoop::PCLoop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PCLoop)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    ui->label->setText("Waiting to star test");
}

PCLoop::~PCLoop()
{
    delete ui;
}

void PCLoop::on_pushButton_clicked()
{
    if(ui->progressBar->value()==0)
    {
        if(port != 0)
        {
            if(!port->isOpen())
                if(!port->open(QIODevice::ReadWrite))
                    ui->label->setText("Error, can not open the port you selected.");

            ui->label->setText(" If your Serial port's Tx light is flashing,\n Please Link RX and TX,\n or cancle to change an other port");
            ui->progressBar->setValue(10);
            port->disconnect();
            connect(port,SIGNAL(readyRead()),this,SLOT(check()));
            QTimer::singleShot(200,this,SLOT(sendData()));
        }
        else
            ui->label->setText("Error, invalid port, please select an other");
    }
    //ui->label->setText("Connect Rx and Tx");
}

void PCLoop::sendData()
{
    //qDebug()<<"~!~!@";
    if(port->isOpen())
    {
        if(ui->progressBar->value() == 10)
        {
            port->write("PCLoop Test");
            QTimer::singleShot(200,this,SLOT(sendData()));
        }
    }
    else
        ui->label->setText("Error can not send data, brocken USB-TTL uint or system fault.");
}

void PCLoop::check()
{
    if(port->readAll().contains("PCLoop Test"))
    {
        ui->progressBar->setValue(100);
        ui->label->setText("Successed,PCLoop test passed!");
    }
}

QSerialPort *PCLoop::getPort() const
{
    return port;
}

void PCLoop::setPort(QSerialPort *value)
{
    port = value;
}
