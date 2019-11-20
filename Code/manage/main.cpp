#include "managewindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ManageWindow w;
    w.show();
    if(!w.loginDb_w->isConnectDb)
    {
        w.close();
        a.exit(0);
    }
    return a.exec();
}
