/********************************************************************************
** Form generated from reading UI file 'petselectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PETSELECTIONWINDOW_H
#define UI_PETSELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PetSelectionWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QScrollArea *petScrollArea;
    QWidget *petCardsContainer;
    QHBoxLayout *petCardsLayout;
    QSpacerItem *spacerBeforeButtons;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *leftSpacer;
    QPushButton *selectButton;
    QSpacerItem *buttonSpacer1;
    QPushButton *newPetButton;
    QSpacerItem *buttonSpacer2;
    QPushButton *deletePetButton;
    QSpacerItem *buttonSpacer3;
    QPushButton *backButton;
    QSpacerItem *rightSpacer;
    QSpacerItem *bottomSpacer;

    void setupUi(QMainWindow *PetSelectionWindow)
    {
        if (PetSelectionWindow->objectName().isEmpty())
            PetSelectionWindow->setObjectName(QString::fromUtf8("PetSelectionWindow"));
        PetSelectionWindow->resize(900, 650);
        centralWidget = new QWidget(PetSelectionWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        topSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(topSpacer);

        titleLabel = new QLabel(centralWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        font.setWeight(99);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        petScrollArea = new QScrollArea(centralWidget);
        petScrollArea->setObjectName(QString::fromUtf8("petScrollArea"));
        petScrollArea->setWidgetResizable(true);
        petScrollArea->setMinimumSize(QSize(0, 300));
        petCardsContainer = new QWidget();
        petCardsContainer->setObjectName(QString::fromUtf8("petCardsContainer"));
        petCardsContainer->setGeometry(QRect(0, 0, 680, 280));
        petCardsLayout = new QHBoxLayout(petCardsContainer);
        petCardsLayout->setSpacing(15);
        petCardsLayout->setObjectName(QString::fromUtf8("petCardsLayout"));
        petCardsLayout->setContentsMargins(10, 10, 10, 10);
        petScrollArea->setWidget(petCardsContainer);

        verticalLayout->addWidget(petScrollArea);

        spacerBeforeButtons = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(spacerBeforeButtons);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(leftSpacer);

        selectButton = new QPushButton(centralWidget);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setEnabled(false);
        selectButton->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(selectButton);

        buttonSpacer1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(buttonSpacer1);

        newPetButton = new QPushButton(centralWidget);
        newPetButton->setObjectName(QString::fromUtf8("newPetButton"));
        newPetButton->setMinimumSize(QSize(160, 40));

        horizontalLayout->addWidget(newPetButton);

        buttonSpacer2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(buttonSpacer2);

        deletePetButton = new QPushButton(centralWidget);
        deletePetButton->setObjectName(QString::fromUtf8("deletePetButton"));
        deletePetButton->setEnabled(false);
        deletePetButton->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(deletePetButton);

        buttonSpacer3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(buttonSpacer3);

        backButton = new QPushButton(centralWidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(backButton);

        rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(rightSpacer);


        verticalLayout->addLayout(horizontalLayout);

        bottomSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(bottomSpacer);

        PetSelectionWindow->setCentralWidget(centralWidget);

        retranslateUi(PetSelectionWindow);

        QMetaObject::connectSlotsByName(PetSelectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PetSelectionWindow)
    {
        PetSelectionWindow->setWindowTitle(QApplication::translate("PetSelectionWindow", "\320\222\321\213\320\261\320\276\321\200 \320\277\320\270\321\202\320\276\320\274\321\206\320\260", nullptr));
        titleLabel->setStyleSheet(QApplication::translate("PetSelectionWindow", "QLabel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"        stop:0 #9966ff, stop:0.5 #aa88ff, stop:1 #cc99ff);\n"
"    color: #000000;\n"
"    font-weight: 900;\n"
"    border: 3px solid #aa88ff;\n"
"    border-radius: 5px;\n"
"    padding: 8px 20px;\n"
"    font-size: 18px;\n"
"}", nullptr));
        titleLabel->setText(QApplication::translate("PetSelectionWindow", "\320\222\321\213\320\261\320\276\321\200 \320\277\320\270\321\202\320\276\320\274\321\206\320\260", nullptr));
        selectButton->setText(QApplication::translate("PetSelectionWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        selectButton->setStyleSheet(QApplication::translate("PetSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00ff88, stop:0.5 #00cc66, stop:1 #009944);\n"
"    color: #ffffff;\n"
"    border: 2px solid #00ffcc;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00ffaa, stop:0.5 #00ff88, stop:1 #00cc66);\n"
"    border: 2px solid #00ffff;\n"
"}\n"
"QPushButton:pressed:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00cc66, stop:0.5 #009944, stop:1 #006633);\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #444444;\n"
"    color: #888888;\n"
"    border: 2px solid #666666;\n"
"}", nullptr));
        newPetButton->setText(QApplication::translate("PetSelectionWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\277\320\270\321\202\320\276\320\274\321\206\320\260", nullptr));
        newPetButton->setStyleSheet(QApplication::translate("PetSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00ffcc, stop:0.5 #00cc99, stop:1 #009966);\n"
"    color: #ffffff;\n"
"    border: 2px solid #00ffff;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00ffff, stop:0.5 #00ffcc, stop:1 #00cc99);\n"
"    border: 2px solid #00ffff;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #00cc99, stop:0.5 #009966, stop:1 #006644);\n"
"}", nullptr));
        deletePetButton->setText(QApplication::translate("PetSelectionWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        deletePetButton->setStyleSheet(QApplication::translate("PetSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #ff0066, stop:0.5 #cc0044, stop:1 #990033);\n"
"    color: #ffffff;\n"
"    border: 2px solid #ff00aa;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #ff0088, stop:0.5 #ff0066, stop:1 #cc0044);\n"
"    border: 2px solid #ff00ff;\n"
"}\n"
"QPushButton:pressed:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #cc0044, stop:0.5 #990033, stop:1 #660022);\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #444444;\n"
"    color: #888888;\n"
"    border: 2px solid #666666;\n"
"}", nullptr));
        backButton->setText(QApplication::translate("PetSelectionWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        backButton->setStyleSheet(QApplication::translate("PetSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #9966ff, stop:0.5 #7744cc, stop:1 #552299);\n"
"    color: #ffffff;\n"
"    border: 2px solid #aa88ff;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #aa88ff, stop:0.5 #9966ff, stop:1 #7744cc);\n"
"    border: 2px solid #cc99ff;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #7744cc, stop:0.5 #552299, stop:1 #331166);\n"
"}", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PetSelectionWindow: public Ui_PetSelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PETSELECTIONWINDOW_H
