#ifndef LOGINDATABASE_W_H
#define LOGINDATABASE_W_H

#include <QDialog>
#include <QSqlDatabase>
#include <QCloseEvent>
#include <QMessageBox>
namespace Ui {
class LoginDatabase_w;
}

class LoginDatabase_w : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDatabase_w(QWidget *parent = 0);
    ~LoginDatabase_w();
    QSqlDatabase * getDb();
    bool isConnectDb;
private slots:

    void on_ip1_e_textEdited(const QString &arg1);

    void on_ip2_e_textEdited(const QString &arg1);

    void on_ip3_e_textEdited(const QString &arg1);

    void on_ip4_e_textEdited(const QString &arg1);

    void on_user_name_e_textEdited(const QString &arg1);

    void on_passwd_e_textEdited(const QString &arg1);

    void on_ok_b_released();

    void on_cancel_b_released();

private:
    Ui::LoginDatabase_w *ui;
    QSqlDatabase db;
    void okEnable();

};

#endif // LOGINDATABASE_W_H
