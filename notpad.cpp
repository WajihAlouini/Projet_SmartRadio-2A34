#include "notpad.h"
#include "ui_notpad.h"

notpad::notpad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notpad)
{
    ui->setupUi(this);
}

notpad::~notpad()
{
    delete ui;
}
