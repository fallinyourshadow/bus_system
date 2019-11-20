/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *buttonbus;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *buttonok;
    QTextBrowser *text_display;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(708, 582);
        buttonbus = new QPushButton(Widget);
        buttonbus->setObjectName(QStringLiteral("buttonbus"));
        buttonbus->setGeometry(QRect(280, 490, 93, 28));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(200, 220, 251, 41));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 220, 141, 31));
        buttonok = new QPushButton(Widget);
        buttonok->setObjectName(QStringLiteral("buttonok"));
        buttonok->setGeometry(QRect(490, 220, 93, 28));
        text_display = new QTextBrowser(Widget);
        text_display->setObjectName(QStringLiteral("text_display"));
        text_display->setGeometry(QRect(200, 280, 256, 192));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        buttonbus->setText(QApplication::translate("Widget", "\345\242\236\351\225\277", 0));
        label->setText(QApplication::translate("Widget", "\350\276\223\345\205\245\345\205\254\344\272\244ID", 0));
        buttonok->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
