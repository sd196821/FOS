#include "fos_spd.h"
#include "ui_fos_spd.h"

FOS_SPD::FOS_SPD(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FOS_SPD)
{
    ui->setupUi(this);
}

FOS_SPD::~FOS_SPD()
{
    delete ui;
}
