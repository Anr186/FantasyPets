/********************************************************************************
** Form generated from reading UI file 'userselectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSELECTIONWINDOW_H
#define UI_USERSELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserSelectionWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *topSpacer;
    QLabel *titleLabel;
    QSpacerItem *spacerBeforeList;
    QHBoxLayout *listLayout;
    QSpacerItem *horizontalSpacer;
    QListWidget *userListWidget;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *spacerBeforeButtons;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *leftSpacer;
    QPushButton *selectButton;
    QSpacerItem *buttonSpacer1;
    QPushButton *newUserButton;
    QSpacerItem *buttonSpacer2;
    QPushButton *deleteUserButton;
    QSpacerItem *buttonSpacer3;
    QPushButton *backButton;
    QSpacerItem *rightSpacer;
    QSpacerItem *bottomSpacer;

    void setupUi(QMainWindow *UserSelectionWindow)
    {
        if (UserSelectionWindow->objectName().isEmpty())
            UserSelectionWindow->setObjectName(QString::fromUtf8("UserSelectionWindow"));
        UserSelectionWindow->resize(700, 504);
        centralWidget = new QWidget(UserSelectionWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(topSpacer);

        titleLabel = new QLabel(centralWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        spacerBeforeList = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(spacerBeforeList);

        listLayout = new QHBoxLayout();
        listLayout->setObjectName(QString::fromUtf8("listLayout"));
        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        listLayout->addItem(horizontalSpacer);

        userListWidget = new QListWidget(centralWidget);
        userListWidget->setObjectName(QString::fromUtf8("userListWidget"));
        userListWidget->setMinimumSize(QSize(0, 220));
        userListWidget->setMaximumSize(QSize(750, 220));

        listLayout->addWidget(userListWidget);

        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        listLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(listLayout);

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

        newUserButton = new QPushButton(centralWidget);
        newUserButton->setObjectName(QString::fromUtf8("newUserButton"));
        newUserButton->setMinimumSize(QSize(160, 40));

        horizontalLayout->addWidget(newUserButton);

        buttonSpacer2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(buttonSpacer2);

        deleteUserButton = new QPushButton(centralWidget);
        deleteUserButton->setObjectName(QString::fromUtf8("deleteUserButton"));
        deleteUserButton->setEnabled(false);
        deleteUserButton->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(deleteUserButton);

        buttonSpacer3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(buttonSpacer3);

        backButton = new QPushButton(centralWidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(backButton);

        rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(rightSpacer);


        verticalLayout->addLayout(horizontalLayout);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(bottomSpacer);

        UserSelectionWindow->setCentralWidget(centralWidget);

        retranslateUi(UserSelectionWindow);

        QMetaObject::connectSlotsByName(UserSelectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserSelectionWindow)
    {
        UserSelectionWindow->setWindowTitle(QApplication::translate("UserSelectionWindow", "\320\222\321\213\320\261\320\276\321\200 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        titleLabel->setStyleSheet(QApplication::translate("UserSelectionWindow", "QLabel {\n"
"    color: #ffffff;\n"
"    font-weight: bold;\n"
"    border: 2px solid #ffffff;\n"
"    border-radius: 5px;\n"
"    padding: 5px 15px;\n"
"    background-color: rgba(45, 80, 22, 0.3);\n"
"}", nullptr));
        titleLabel->setText(QApplication::translate("UserSelectionWindow", "\320\222\321\213\320\261\320\276\321\200 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        userListWidget->setStyleSheet(QApplication::translate("UserSelectionWindow", "QListWidget {\n"
"    background-color: rgba(240, 250, 230, 0.95);\n"
"    border: 2px solid #2d5016;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    outline: none;\n"
"}\n"
"QListWidget::item {\n"
"    background-color: rgba(240, 230, 210, 0.8);\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"    margin: 2px;\n"
"    outline: none;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    min-height: 45px;\n"
"}\n"
"QListWidget::item:selected {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #5a8c3a, stop:1 #2d5016);\n"
"    color: white;\n"
"    border: 1px solid #1a3009;\n"
"    outline: none;\n"
"}\n"
"QListWidget::item:selected:focus {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #5a8c3a, stop:1 #2d5016);\n"
"    color: white;\n"
"    border: 2px solid #1a3009;\n"
"    outline: none;\n"
"}\n"
"QListWidget::item:hover {\n"
"    background-color: rgba(90, 140, 58, 0.3);\n"
"    outline: none"
                        ";\n"
"}\n"
"QListWidget:focus {\n"
"    outline: none;\n"
"    border: 2px solid #2d5016;\n"
"}", nullptr));
        selectButton->setStyleSheet(QApplication::translate("UserSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #4a7c2a, stop:0.5 #2d5016, stop:1 #1a3009);\n"
"    color: white;\n"
"    border: 2px solid #1a3009;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #5a8c3a, stop:0.5 #3d7026, stop:1 #2d5016);\n"
"    border: 2px solid #2d5016;\n"
"}\n"
"QPushButton:pressed:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #2d5016, stop:0.5 #1a3009, stop:1 #0f1a05);\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #888888;\n"
"    color: #cccccc;\n"
"    border: 2px solid #666666;\n"
"}", nullptr));
        selectButton->setText(QApplication::translate("UserSelectionWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        newUserButton->setStyleSheet(QApplication::translate("UserSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #6b9c4a, stop:0.5 #4a7c2a, stop:1 #2d5016);\n"
"    color: white;\n"
"    border: 2px solid #2d5016;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #7bac5a, stop:0.5 #5a8c3a, stop:1 #3d7026);\n"
"    border: 2px solid #3d7026;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #4a7c2a, stop:0.5 #2d5016, stop:1 #1a3009);\n"
"}", nullptr));
        newUserButton->setText(QApplication::translate("UserSelectionWindow", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        deleteUserButton->setStyleSheet(QApplication::translate("UserSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #8b3a3a, stop:0.5 #6b2a2a, stop:1 #4a1a1a);\n"
"    color: white;\n"
"    border: 2px solid #4a1a1a;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #9b4a4a, stop:0.5 #7b3a3a, stop:1 #5a2a2a);\n"
"    border: 2px solid #5a2a2a;\n"
"}\n"
"QPushButton:pressed:enabled {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #6b2a2a, stop:0.5 #4a1a1a, stop:1 #2a0a0a);\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #888888;\n"
"    color: #cccccc;\n"
"    border: 2px solid #666666;\n"
"}", nullptr));
        deleteUserButton->setText(QApplication::translate("UserSelectionWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        backButton->setStyleSheet(QApplication::translate("UserSelectionWindow", "QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #7a6b4a, stop:0.5 #5a4a2a, stop:1 #3a2a1a);\n"
"    color: white;\n"
"    border: 2px solid #3a2a1a;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #8a7b5a, stop:0.5 #6a5a3a, stop:1 #4a3a2a);\n"
"    border: 2px solid #4a3a2a;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #5a4a2a, stop:0.5 #3a2a1a, stop:1 #2a1a0a);\n"
"}", nullptr));
        backButton->setText(QApplication::translate("UserSelectionWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserSelectionWindow: public Ui_UserSelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSELECTIONWINDOW_H
