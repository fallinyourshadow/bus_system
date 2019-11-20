/********************************************************************************
** Form generated from reading UI file 'logindatabase_w.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDATABASE_W_H
#define UI_LOGINDATABASE_W_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDatabase_w
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *ip_l_2;
    QLabel *user_l_2;
    QLabel *passwd_l_2;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *ip2_e;
    QLineEdit *ip3_e;
    QLineEdit *passwd_e;
    QLineEdit *ip1_e;
    QLineEdit *ip4_e;
    QLabel *label_6;
    QLineEdit *user_name_e;
    QPushButton *ok_b;
    QPushButton *cancel_b;

    void setupUi(QDialog *LoginDatabase_w)
    {
        if (LoginDatabase_w->objectName().isEmpty())
            LoginDatabase_w->setObjectName(QStringLiteral("LoginDatabase_w"));
        LoginDatabase_w->resize(688, 256);
        LoginDatabase_w->setMinimumSize(QSize(0, 0));
        LoginDatabase_w->setBaseSize(QSize(0, 0));
        widget = new QWidget(LoginDatabase_w);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 627, 193));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ip_l_2 = new QLabel(widget);
        ip_l_2->setObjectName(QStringLiteral("ip_l_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ip_l_2->sizePolicy().hasHeightForWidth());
        ip_l_2->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(22);
        ip_l_2->setFont(font);
        ip_l_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(ip_l_2);

        user_l_2 = new QLabel(widget);
        user_l_2->setObjectName(QStringLiteral("user_l_2"));
        user_l_2->setFont(font);
        user_l_2->setLayoutDirection(Qt::LeftToRight);
        user_l_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(user_l_2);

        passwd_l_2 = new QLabel(widget);
        passwd_l_2->setObjectName(QStringLiteral("passwd_l_2"));
        passwd_l_2->setFont(font);
        passwd_l_2->setLayoutDirection(Qt::LeftToRight);
        passwd_l_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(passwd_l_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font1;
        font1.setFamily(QStringLiteral("Adobe Arabic"));
        font1.setPointSize(22);
        label_4->setFont(font1);

        gridLayout_3->addWidget(label_4, 0, 3, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        gridLayout_3->addWidget(label_5, 0, 1, 1, 1);

        ip2_e = new QLineEdit(widget);
        ip2_e->setObjectName(QStringLiteral("ip2_e"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ip2_e->sizePolicy().hasHeightForWidth());
        ip2_e->setSizePolicy(sizePolicy1);
        ip2_e->setMinimumSize(QSize(0, 35));
        QFont font2;
        font2.setFamily(QStringLiteral("Adobe Arabic"));
        font2.setPointSize(24);
        ip2_e->setFont(font2);

        gridLayout_3->addWidget(ip2_e, 0, 2, 1, 1);

        ip3_e = new QLineEdit(widget);
        ip3_e->setObjectName(QStringLiteral("ip3_e"));
        sizePolicy1.setHeightForWidth(ip3_e->sizePolicy().hasHeightForWidth());
        ip3_e->setSizePolicy(sizePolicy1);
        ip3_e->setMinimumSize(QSize(0, 35));
        ip3_e->setFont(font2);

        gridLayout_3->addWidget(ip3_e, 0, 4, 1, 1);

        passwd_e = new QLineEdit(widget);
        passwd_e->setObjectName(QStringLiteral("passwd_e"));
        sizePolicy1.setHeightForWidth(passwd_e->sizePolicy().hasHeightForWidth());
        passwd_e->setSizePolicy(sizePolicy1);
        passwd_e->setMinimumSize(QSize(0, 35));
        passwd_e->setFont(font2);

        gridLayout_3->addWidget(passwd_e, 2, 0, 1, 7);

        ip1_e = new QLineEdit(widget);
        ip1_e->setObjectName(QStringLiteral("ip1_e"));
        sizePolicy1.setHeightForWidth(ip1_e->sizePolicy().hasHeightForWidth());
        ip1_e->setSizePolicy(sizePolicy1);
        ip1_e->setMinimumSize(QSize(0, 35));
        ip1_e->setFont(font2);

        gridLayout_3->addWidget(ip1_e, 0, 0, 1, 1);

        ip4_e = new QLineEdit(widget);
        ip4_e->setObjectName(QStringLiteral("ip4_e"));
        sizePolicy1.setHeightForWidth(ip4_e->sizePolicy().hasHeightForWidth());
        ip4_e->setSizePolicy(sizePolicy1);
        ip4_e->setMinimumSize(QSize(0, 35));
        ip4_e->setFont(font2);

        gridLayout_3->addWidget(ip4_e, 0, 6, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        gridLayout_3->addWidget(label_6, 0, 5, 1, 1);

        user_name_e = new QLineEdit(widget);
        user_name_e->setObjectName(QStringLiteral("user_name_e"));
        sizePolicy1.setHeightForWidth(user_name_e->sizePolicy().hasHeightForWidth());
        user_name_e->setSizePolicy(sizePolicy1);
        user_name_e->setMinimumSize(QSize(0, 35));
        user_name_e->setFont(font2);

        gridLayout_3->addWidget(user_name_e, 1, 0, 1, 7);


        horizontalLayout_2->addLayout(gridLayout_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        ok_b = new QPushButton(LoginDatabase_w);
        ok_b->setObjectName(QStringLiteral("ok_b"));
        ok_b->setGeometry(QRect(430, 220, 93, 28));
        QFont font3;
        font3.setFamily(QStringLiteral("Adobe Arabic"));
        font3.setPointSize(12);
        ok_b->setFont(font3);
        cancel_b = new QPushButton(LoginDatabase_w);
        cancel_b->setObjectName(QStringLiteral("cancel_b"));
        cancel_b->setGeometry(QRect(550, 220, 93, 28));
        cancel_b->setFont(font3);

        retranslateUi(LoginDatabase_w);

        QMetaObject::connectSlotsByName(LoginDatabase_w);
    } // setupUi

    void retranslateUi(QDialog *LoginDatabase_w)
    {
        LoginDatabase_w->setWindowTitle(QApplication::translate("LoginDatabase_w", "Dialog", 0));
        ip_l_2->setText(QApplication::translate("LoginDatabase_w", "ip:", 0));
        user_l_2->setText(QApplication::translate("LoginDatabase_w", "user:", 0));
        passwd_l_2->setText(QApplication::translate("LoginDatabase_w", "password:", 0));
        label_4->setText(QApplication::translate("LoginDatabase_w", ".", 0));
        label_5->setText(QApplication::translate("LoginDatabase_w", ".", 0));
        label_6->setText(QApplication::translate("LoginDatabase_w", ".", 0));
        ok_b->setText(QApplication::translate("LoginDatabase_w", "\350\277\236\346\216\245", 0));
        cancel_b->setText(QApplication::translate("LoginDatabase_w", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDatabase_w: public Ui_LoginDatabase_w {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDATABASE_W_H
