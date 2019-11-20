#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    if(w.failSignal)
    {
        w.close();
        a.exit();
    }
    w.show();

    return a.exec();
}
