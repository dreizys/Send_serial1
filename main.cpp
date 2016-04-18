#include "dialog.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    //w.setFixedSize(560,160);
    w.setWindowTitle("RGB LED CONTROLLER");
    w.show();

    return a.exec();
}
