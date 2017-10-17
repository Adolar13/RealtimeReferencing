/********************************************************************************
** Form generated from reading UI file 'ref_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REF_MENU_H
#define UI_REF_MENU_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RefMenuRollup
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *createNodeButton;
    QPushButton *removeNodeButton;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *pathEdit;
    QPushButton *pathButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *updateButton;
    QCheckBox *autoUpdateCheck;
    QPushButton *testButton;

    void setupUi(QWidget *RefMenuRollup)
    {
        if (RefMenuRollup->objectName().isEmpty())
            RefMenuRollup->setObjectName(QStringLiteral("RefMenuRollup"));
        RefMenuRollup->setWindowModality(Qt::NonModal);
        RefMenuRollup->resize(316, 371);
        RefMenuRollup->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        gridLayoutWidget = new QWidget(RefMenuRollup);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 100, 207, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(40);
        gridLayout->setContentsMargins(20, 20, 20, 20);
        createNodeButton = new QPushButton(gridLayoutWidget);
        createNodeButton->setObjectName(QStringLiteral("createNodeButton"));

        gridLayout->addWidget(createNodeButton, 0, 0, 1, 1);

        removeNodeButton = new QPushButton(gridLayoutWidget);
        removeNodeButton->setObjectName(QStringLiteral("removeNodeButton"));
        removeNodeButton->setEnabled(false);
        removeNodeButton->setCheckable(false);
        removeNodeButton->setAutoDefault(false);

        gridLayout->addWidget(removeNodeButton, 1, 0, 1, 1);

        groupBox = new QGroupBox(RefMenuRollup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 234, 56));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pathEdit = new QLineEdit(groupBox);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));
        pathEdit->setFrame(false);
        pathEdit->setReadOnly(true);
        pathEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(pathEdit);

        pathButton = new QPushButton(groupBox);
        pathButton->setObjectName(QStringLiteral("pathButton"));

        horizontalLayout->addWidget(pathButton);

        horizontalLayoutWidget = new QWidget(RefMenuRollup);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 270, 211, 55));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        updateButton = new QPushButton(horizontalLayoutWidget);
        updateButton->setObjectName(QStringLiteral("updateButton"));
        updateButton->setEnabled(false);

        horizontalLayout_2->addWidget(updateButton);

        autoUpdateCheck = new QCheckBox(horizontalLayoutWidget);
        autoUpdateCheck->setObjectName(QStringLiteral("autoUpdateCheck"));
        autoUpdateCheck->setEnabled(false);

        horizontalLayout_2->addWidget(autoUpdateCheck);

        testButton = new QPushButton(RefMenuRollup);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setGeometry(QRect(230, 340, 75, 23));

        retranslateUi(RefMenuRollup);

        removeNodeButton->setDefault(false);


        QMetaObject::connectSlotsByName(RefMenuRollup);
    } // setupUi

    void retranslateUi(QWidget *RefMenuRollup)
    {
        RefMenuRollup->setWindowTitle(QApplication::translate("RefMenuRollup", "Form", Q_NULLPTR));
        createNodeButton->setText(QApplication::translate("RefMenuRollup", "Create Reference Node", Q_NULLPTR));
        removeNodeButton->setText(QApplication::translate("RefMenuRollup", "Remove Reference Node", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("RefMenuRollup", "Reference Path", Q_NULLPTR));
        pathEdit->setText(QApplication::translate("RefMenuRollup", "C:/Temp", Q_NULLPTR));
        pathButton->setText(QApplication::translate("RefMenuRollup", "Select", Q_NULLPTR));
        updateButton->setText(QApplication::translate("RefMenuRollup", "Update", Q_NULLPTR));
        autoUpdateCheck->setText(QApplication::translate("RefMenuRollup", "Auto Update", Q_NULLPTR));
        testButton->setText(QApplication::translate("RefMenuRollup", "TEST", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RefMenuRollup: public Ui_RefMenuRollup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REF_MENU_H
