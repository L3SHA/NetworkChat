/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pbSendMsg;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pbConnect;
    QLineEdit *leHost;
    QLineEdit *leName;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spPort;
    QListWidget *lwUsers;
    QListWidget *lwLog;
    QPlainTextEdit *pteMessage;
    QPushButton *pbDisconnect;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1280, 720);
        pbSendMsg = new QPushButton(Dialog);
        pbSendMsg->setObjectName(QStringLiteral("pbSendMsg"));
        pbSendMsg->setGeometry(QRect(570, 410, 75, 23));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(480, 90, 46, 13));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(400, 350, 46, 13));
        pbConnect = new QPushButton(Dialog);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));
        pbConnect->setGeometry(QRect(860, 490, 75, 23));
        leHost = new QLineEdit(Dialog);
        leHost->setObjectName(QStringLiteral("leHost"));
        leHost->setGeometry(QRect(840, 340, 113, 20));
        leName = new QLineEdit(Dialog);
        leName->setObjectName(QStringLiteral("leName"));
        leName->setGeometry(QRect(840, 440, 113, 20));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(800, 340, 31, 16));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(800, 390, 21, 16));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(800, 440, 31, 16));
        spPort = new QSpinBox(Dialog);
        spPort->setObjectName(QStringLiteral("spPort"));
        spPort->setGeometry(QRect(840, 390, 111, 22));
        lwUsers = new QListWidget(Dialog);
        lwUsers->setObjectName(QStringLiteral("lwUsers"));
        lwUsers->setGeometry(QRect(460, 120, 256, 192));
        lwLog = new QListWidget(Dialog);
        lwLog->setObjectName(QStringLiteral("lwLog"));
        lwLog->setGeometry(QRect(730, 120, 256, 192));
        pteMessage = new QPlainTextEdit(Dialog);
        pteMessage->setObjectName(QStringLiteral("pteMessage"));
        pteMessage->setGeometry(QRect(460, 340, 251, 41));
        pbDisconnect = new QPushButton(Dialog);
        pbDisconnect->setObjectName(QStringLiteral("pbDisconnect"));
        pbDisconnect->setGeometry(QRect(860, 540, 75, 23));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        pbSendMsg->setText(QApplication::translate("Dialog", "Send", 0));
        label->setText(QApplication::translate("Dialog", "Users", 0));
        label_2->setText(QApplication::translate("Dialog", "Message", 0));
        pbConnect->setText(QApplication::translate("Dialog", "Connect", 0));
        label_3->setText(QApplication::translate("Dialog", "Host", 0));
        label_4->setText(QApplication::translate("Dialog", "Port", 0));
        label_5->setText(QApplication::translate("Dialog", "Name", 0));
        pbDisconnect->setText(QApplication::translate("Dialog", "Disconnect", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
