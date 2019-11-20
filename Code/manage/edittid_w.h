#ifndef EDITTID_W_H
#define EDITTID_W_H

#include <QDialog>
#include <QStringList>
namespace Ui {
class EditTid_w;
}

class EditTid_w : public QDialog
{
    Q_OBJECT

public:
    explicit EditTid_w(QStringList *, QWidget *parent = 0);
    ~EditTid_w();

private slots:

    void on_cancel_b_clicked();

    void on_ok_b_clicked();

private:
    QStringList * tid_list;
    Ui::EditTid_w *ui;
};

#endif // EDITTID_W_H
