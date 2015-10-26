#ifndef FOS_SPD_H
#define FOS_SPD_H

#include <QMainWindow>

namespace Ui {
class FOS_SPD;
}

class FOS_SPD : public QMainWindow
{
    Q_OBJECT

public:
    explicit FOS_SPD(QWidget *parent = 0);
    ~FOS_SPD();

private:
    Ui::FOS_SPD *ui;
};

#endif // FOS_SPD_H
