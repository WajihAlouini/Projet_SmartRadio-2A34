#include "temp_sensor.h"
#include "ui_temp_sensor.h"

temp_sensor::temp_sensor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::temp_sensor)
{
    ui->setupUi(this);
    ui->lcdNumber->display("...............");
}

temp_sensor::~temp_sensor()
{
    delete ui;
}
