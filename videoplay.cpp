#include "videoplay.h"
#include "ui_videoplay.h"

videoplay::videoplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoplay)
{
    ui->setupUi(this);
}

videoplay::~videoplay()
{
    delete ui;
}
