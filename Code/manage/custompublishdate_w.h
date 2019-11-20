#ifndef CUSTOMPUBLISHDATE_W_H
#define CUSTOMPUBLISHDATE_W_H

#include <QDialog>

namespace Ui {
class CustomPublishDate_w;
}

class CustomPublishDate_w : public QDialog
{
    Q_OBJECT

public:
    explicit CustomPublishDate_w(QString * ,QWidget *parent = 0);
    ~CustomPublishDate_w();

private slots:


    void on_mon_e_textEdited(const QString &arg1);

    void on_day_e_textEdited(const QString &arg1);

    void on_ok_b_clicked();

    void on_pushButton_2_clicked();

    void on_year_e_textEdited(const QString &arg1);

private:
    QString *publish_date;
    Ui::CustomPublishDate_w *ui;
};

#endif // CUSTOMPUBLISHDATE_W_H
