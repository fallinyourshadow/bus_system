#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>

#include "logindatabase_w.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    LoginDatabase_w * loginDb_w;

private slots:
    void on_buttonbus_clicked();

    void on_buttonok_clicked();

private:
    Ui::Widget *ui;

    QString busid;
    int cout;
    QSqlDatabase *db;
};

#endif // WIDGET_H
