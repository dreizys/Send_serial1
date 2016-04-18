#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)

{
    ui->setupUi(this);
    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";


   // qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();

    /*foreach (const QSerialPortInfo &seriaPortInfo, QSerialPortInfo::availablePorts() ){
        qDebug() << "Has vendor ID: " << seriaPortInfo.hasVendorIdentifier();
        if(seriaPortInfo.hasVendorIdentifier()){
            qDebug() << " Vendor ID: " << seriaPortInfo.vendorIdentifier();
            qDebug() << "port name is : " << seriaPortInfo.portName();
            arduino_port_name = seriaPortInfo.portName();
        }*/


    foreach (const QSerialPortInfo &seriaPortInfo, QSerialPortInfo::availablePorts() ){
               if(seriaPortInfo.hasVendorIdentifier()){
                //qDebug() << " Vendor ID: " << seriaPortInfo.vendorIdentifier();
                //qDebug() << "port name is : " << seriaPortInfo.portName();
                arduino_port_name = seriaPortInfo.portName();
                ui->comboBox->addItem(arduino_port_name);
                arduino_is_available = true;
    }
 }
    if(arduino_is_available){
        //open & configure the serial port
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);


    }
    else{
        //give error message
        QMessageBox::warning(this, "Port error", "Couldn't find the arduino");
    }

   /* for(int i = 0; i < 10; i++)
       {
           ui->comboBox->addItem("item " + QString::number(i)); //testing qcombobox
       }*/
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void Dialog::on_green_Slider_valueChanged(int value)
{
ui->green_value_label->setText(QString("%1").arg(value));
Dialog::updateRGB(QString("%1").arg(value));

//qDebug << value;
}

void Dialog::on_red_Slider_valueChanged(int value)
{
ui->red_value_label->setText(QString("%1").arg(value));
Dialog::updateRGB(QString("%1").arg(value));
//qDebug << value;
}

void Dialog::updateRGB(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    } else{
        qDebug() << "couldn't write to serial!";
    }
}

void Dialog::updateLED(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    } else{
        qDebug() << "couldn't write to serial!";
    }
}

void Dialog::on_Bn_show_Port_clicked()
{

        QMessageBox::information(this, "Item Selection",
                                 ui->comboBox->currentText());

    ui->lb_Port->setText(QString(arduino_port_name));
}


void Dialog::on_checkBox_stateChanged(int arg1)
{

          //  QMessageBox* msg = new QMessageBox(this->parentWidget());
          //  msg->setWindowTitle("Hello !");

            if(arg1)
            {
              //msg->setText("CheckBox is Checked !");
                Dialog::updateLED("1");
                QMessageBox::information(this, "CheckBox", "Checked");
            }
            else
            {
              //msg->setText("CheckBox is Unchecked !");
                Dialog::updateLED("0");
                QMessageBox::information(this, "CheckBox", "Unchecked");
            }
           // msg->show();

}
