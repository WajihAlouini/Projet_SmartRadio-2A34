#include "ardouino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
ardouino::ardouino()

{
data="";
arduino_port_name="";
arduino_is_available =false;
Serial=new QSerialPort;
}
QString ardouino::getardouino_port_name()
{
  return  arduino_port_name ;
}
int ardouino::connect_ardouino()
{
    foreach(const QSerialPortInfo& serial_port_info,QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {

          if(serial_port_info.vendorIdentifier() ==ardouino_uno_vendor_id && serial_port_info.productIdentifier()==ardouino_uno_vendor_id)

           {

            arduino_is_available=true;
            arduino_port_name =serial_port_info.portName();
          }
        }

    }
    qDebug()<<"arduino port name:"<<arduino_port_name;
    if( arduino_is_available)
    {
         Serial->setPortName( arduino_port_name);
       if(Serial->open(QSerialPort::ReadWrite))
       {
           Serial->setBaudRate(QSerialPort::Baud9600);
           Serial->setDataBits(QSerialPort::Data8);
           Serial->setParity(QSerialPort::NoParity);
           Serial->setStopBits(QSerialPort::OneStop);
           Serial->setFlowControl(QSerialPort::NoFlowControl);
           return 0;

       }
return 1;
    }
    return -1;
}
int ardouino::close_ardouino()
{
    if(Serial->isOpen())
    {
        Serial->close();
        return 0;
    }

    return 1;
}
QByteArray ardouino::read_from_ardouino()
{
    if(Serial->isReadable()){
         data=Serial->readAll(); //rÃ©cupÃ©rer les donnÃ©es reÃ§ues

         return data;
    }
 }


int ardouino::write_to_ardouino( QByteArray d)

{

    if(Serial->isWritable()){
        Serial->write(d);  // envoyer des donnÃ©s vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}
QSerialPort* ardouino::getserial(){return  Serial;}
