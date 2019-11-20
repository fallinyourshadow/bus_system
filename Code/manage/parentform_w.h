#ifndef PARENTFORM_W_H
#define PARENTFORM_W_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
namespace Ui {
class ParentForm_w;
}

class ParentForm_w : public QDialog
{
    Q_OBJECT

public:
    explicit ParentForm_w(QSqlDatabase *DB,QWidget *parent = 0);
    ~ParentForm_w();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    //void on_Button_ok_clicked();

private:
    Ui::ParentForm_w *ui;
    QSqlDatabase *db;
    QSqlTableModel *model;
};

#endif // PARENTFORM_W_H
