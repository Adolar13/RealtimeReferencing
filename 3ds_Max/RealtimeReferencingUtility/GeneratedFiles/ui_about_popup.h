/********************************************************************************
** Form generated from reading UI file 'about_popup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_POPUP_H
#define UI_ABOUT_POPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_about_popup
{
public:
    QPlainTextEdit *aboutText;
    QPushButton *okButton;

    void setupUi(QWidget *about_popup)
    {
        if (about_popup->objectName().isEmpty())
            about_popup->setObjectName(QStringLiteral("about_popup"));
        about_popup->setWindowModality(Qt::ApplicationModal);
        about_popup->setEnabled(true);
        about_popup->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(about_popup->sizePolicy().hasHeightForWidth());
        about_popup->setSizePolicy(sizePolicy);
        aboutText = new QPlainTextEdit(about_popup);
        aboutText->setObjectName(QStringLiteral("aboutText"));
        aboutText->setEnabled(true);
        aboutText->setGeometry(QRect(20, 30, 361, 211));
        aboutText->setAcceptDrops(false);
        aboutText->setFrameShadow(QFrame::Raised);
        aboutText->setTabChangesFocus(false);
        aboutText->setUndoRedoEnabled(false);
        aboutText->setReadOnly(true);
        aboutText->setBackgroundVisible(false);
        okButton = new QPushButton(about_popup);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(160, 260, 75, 23));
        sizePolicy.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy);

        retranslateUi(about_popup);

        QMetaObject::connectSlotsByName(about_popup);
    } // setupUi

    void retranslateUi(QWidget *about_popup)
    {
        about_popup->setWindowTitle(QApplication::translate("about_popup", "About Realtime Referencing", Q_NULLPTR));
        aboutText->setPlainText(QApplication::translate("about_popup", "Realtime Referencing Plugin\n"
"\n"
"Dieses Programm ist w\303\244hrend der Abschlussarbeit von Paul Wolff im Bachelorstudiengang Medieninformatik an der Hochschule f\303\274r Technik und Wirtschaft Dresden entstanden.\n"
"\n"
"Der Titel der Arbeit lautet \"Ergr\303\274ndung von M\303\266glichkeiten der Echtzeitreferenzierung in 3DS Max zu 3D Szenen anderer Garfiksysteme und exemplarische Implementierung eines Prototyps.\".\n"
"\n"
"(C) Paul Wolff 2017", Q_NULLPTR));
        okButton->setText(QApplication::translate("about_popup", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class about_popup: public Ui_about_popup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_POPUP_H
