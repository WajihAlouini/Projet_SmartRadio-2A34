#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <QMainWindow>

namespace Ui {
class temp_sensor;
}

class temp_sensor : public QMainWindow
{
    Q_OBJECT

public:
    explicit temp_sensor(QWidget *parent = nullptr);
    ~temp_sensor();

private:
    Ui::temp_sensor *ui;
};

#endif // TEMP_SENSOR_H
