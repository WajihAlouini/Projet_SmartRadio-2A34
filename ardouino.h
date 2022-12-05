#ifndef ARDOUINO_H
#define ARDOUINO_H
#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
class ardouino
{
public:
    ardouino();
    int connect_ardouino();
    int close_ardouino();
    int write_to_ardouino(QByteArray);
    QByteArray read_from_ardouino();
    QSerialPort* getserial();
    QString getardouino_port_name();
private:
    QSerialPort *Serial;
    static const quint16 ardouino_uno_vendor_id=9025;
    static const quint16 ardouino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;

};

#endif // ARDOUINO_H
