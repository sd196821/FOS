#ifndef FOS_SPD_H
#define FOS_SPD_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

class Ports
{
public:
    Ports();
    ~Ports();
    QSerialPort* getPort(int number);
    int getAvailablePortNumber() const;

    void refresh();

private:
    static const int MaxPorts = 20;
    QSerialPort **port;
    int availablePortNumber;
};



namespace Ui {
class FOS_SPD;
}

class FOS_SPD : public QMainWindow
{
    Q_OBJECT

public:
    explicit FOS_SPD(QWidget *parent = 0);
    ~FOS_SPD();

private slots:
    void on_comboBox_PortName_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();
private slots:
    void monitor();
    void on_pushButton_2_clicked();
    void on_pushButton_Refresh_clicked();

private:
    Ui::FOS_SPD *ui;
    Ports *ports;
    QSerialPort *currentPort;
};



#endif // FOS_SPD_H
