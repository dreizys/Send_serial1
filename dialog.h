#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_green_Slider_valueChanged(int value);

    void on_red_Slider_valueChanged(int value);

    void on_Bn_show_Port_clicked();

    void updateRGB(QString);

    void on_checkBox_stateChanged(int arg1);

    void updateLED(QString command);


private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // DIALOG_H
