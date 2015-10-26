#ifndef PCLOOP_H
#define PCLOOP_H

#include <QDialog>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class PCLoop;
}

class PCLoop : public QDialog
{
    Q_OBJECT

public:
    explicit PCLoop(QWidget *parent = 0);
    ~PCLoop();

    QSerialPort *getPort() const;
    void setPort(QSerialPort *value);

private slots:
    void on_pushButton_clicked();

    void sendData();
    void check();

private:
    Ui::PCLoop *ui;
    QSerialPort *port;
};

#endif // PCLOOP_H
