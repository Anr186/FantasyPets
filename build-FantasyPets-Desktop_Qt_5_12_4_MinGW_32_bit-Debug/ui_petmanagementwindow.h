/********************************************************************************
** Form generated from reading UI file 'petmanagementwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PETMANAGEMENTWINDOW_H
#define UI_PETMANAGEMENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PetManagementWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *topSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftButtonsLayout;
    QSpacerItem *leftTopSpacer;
    QVBoxLayout *hungerGroupLayout;
    QHBoxLayout *hungerLabelLayout;
    QSpacerItem *hungerLabelLeftSpacer;
    QLabel *hungerLabel;
    QSpacerItem *hungerLabelRightSpacer;
    QHBoxLayout *hungerProgressBarLayout;
    QSpacerItem *hungerProgressBarLeftSpacer;
    QProgressBar *hungerProgressBar;
    QSpacerItem *hungerProgressBarRightSpacer;
    QSpacerItem *hungerSpacer;
    QHBoxLayout *hungerButtonLayout;
    QSpacerItem *hungerLeftSpacer;
    QPushButton *feedButton;
    QSpacerItem *hungerRightSpacer;
    QSpacerItem *leftMiddleSpacer;
    QVBoxLayout *moodGroupLayout;
    QHBoxLayout *moodLabelLayout;
    QSpacerItem *moodLabelLeftSpacer;
    QLabel *moodLabel;
    QSpacerItem *moodLabelRightSpacer;
    QHBoxLayout *moodProgressBarLayout;
    QSpacerItem *moodProgressBarLeftSpacer;
    QProgressBar *moodProgressBar;
    QSpacerItem *moodProgressBarRightSpacer;
    QSpacerItem *moodSpacer;
    QHBoxLayout *moodButtonLayout;
    QSpacerItem *moodLeftSpacer;
    QPushButton *playButton;
    QSpacerItem *moodRightSpacer;
    QSpacerItem *leftBottomSpacer;
    QSpacerItem *leftMainSpacer;
    QFrame *petImageFrame;
    QVBoxLayout *imageLayout;
    QLabel *petNameLabel;
    QLabel *ageLabel;
    QLabel *petIconLabel;
    QLabel *petTypeLabel;
    QLabel *coinsLabel;
    QSpacerItem *rightMainSpacer;
    QVBoxLayout *rightButtonsLayout;
    QSpacerItem *rightTopSpacer;
    QVBoxLayout *sleepGroupLayout;
    QHBoxLayout *sleepLabelLayout;
    QSpacerItem *sleepLabelLeftSpacer;
    QLabel *sleepLabel;
    QSpacerItem *sleepLabelRightSpacer;
    QHBoxLayout *sleepProgressBarLayout;
    QSpacerItem *sleepProgressBarLeftSpacer;
    QProgressBar *sleepProgressBar;
    QSpacerItem *sleepProgressBarRightSpacer;
    QSpacerItem *sleepSpacer;
    QHBoxLayout *sleepButtonLayout;
    QSpacerItem *sleepLeftSpacer;
    QPushButton *sleepButton;
    QSpacerItem *sleepRightSpacer;
    QSpacerItem *rightMiddleSpacer;
    QVBoxLayout *healthGroupLayout;
    QHBoxLayout *healthLabelLayout;
    QSpacerItem *healthLabelLeftSpacer;
    QLabel *healthLabel;
    QSpacerItem *healthLabelRightSpacer;
    QHBoxLayout *healthProgressBarLayout;
    QSpacerItem *healthProgressBarLeftSpacer;
    QProgressBar *healthProgressBar;
    QSpacerItem *healthProgressBarRightSpacer;
    QSpacerItem *healthSpacer;
    QHBoxLayout *healthButtonLayout;
    QSpacerItem *healthLeftSpacer;
    QPushButton *undoButton;
    QSpacerItem *healthRightSpacer;
    QSpacerItem *rightBottomSpacer;
    QSpacerItem *bottomSpacer;
    QHBoxLayout *backButtonLayout;
    QSpacerItem *backButtonLeftSpacer;
    QPushButton *backButton;
    QSpacerItem *backButtonRightSpacer;

    void setupUi(QMainWindow *PetManagementWindow)
    {
        if (PetManagementWindow->objectName().isEmpty())
            PetManagementWindow->setObjectName(QString::fromUtf8("PetManagementWindow"));
        PetManagementWindow->resize(1000, 650);
        centralWidget = new QWidget(PetManagementWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(topSpacer);

        mainLayout = new QHBoxLayout();
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        leftButtonsLayout = new QVBoxLayout();
        leftButtonsLayout->setObjectName(QString::fromUtf8("leftButtonsLayout"));
        leftTopSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        leftButtonsLayout->addItem(leftTopSpacer);

        hungerGroupLayout = new QVBoxLayout();
        hungerGroupLayout->setObjectName(QString::fromUtf8("hungerGroupLayout"));
        hungerLabelLayout = new QHBoxLayout();
        hungerLabelLayout->setObjectName(QString::fromUtf8("hungerLabelLayout"));
        hungerLabelLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hungerLabelLayout->addItem(hungerLabelLeftSpacer);

        hungerLabel = new QLabel(centralWidget);
        hungerLabel->setObjectName(QString::fromUtf8("hungerLabel"));
        hungerLabel->setMinimumSize(QSize(120, 25));
        hungerLabel->setMaximumSize(QSize(120, 25));
        hungerLabel->setAlignment(Qt::AlignCenter);

        hungerLabelLayout->addWidget(hungerLabel);

        hungerLabelRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hungerLabelLayout->addItem(hungerLabelRightSpacer);


        hungerGroupLayout->addLayout(hungerLabelLayout);

        hungerProgressBarLayout = new QHBoxLayout();
        hungerProgressBarLayout->setObjectName(QString::fromUtf8("hungerProgressBarLayout"));
        hungerProgressBarLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hungerProgressBarLayout->addItem(hungerProgressBarLeftSpacer);

        hungerProgressBar = new QProgressBar(centralWidget);
        hungerProgressBar->setObjectName(QString::fromUtf8("hungerProgressBar"));
        hungerProgressBar->setMinimumSize(QSize(120, 25));
        hungerProgressBar->setMaximumSize(QSize(120, 25));
        hungerProgressBar->setValue(100);

        hungerProgressBarLayout->addWidget(hungerProgressBar);

        hungerProgressBarRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hungerProgressBarLayout->addItem(hungerProgressBarRightSpacer);


        hungerGroupLayout->addLayout(hungerProgressBarLayout);

        hungerSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        hungerGroupLayout->addItem(hungerSpacer);

        hungerButtonLayout = new QHBoxLayout();
        hungerButtonLayout->setObjectName(QString::fromUtf8("hungerButtonLayout"));
        hungerLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hungerButtonLayout->addItem(hungerLeftSpacer);

        feedButton = new QPushButton(centralWidget);
        feedButton->setObjectName(QString::fromUtf8("feedButton"));
        feedButton->setMinimumSize(QSize(100, 100));
        feedButton->setMaximumSize(QSize(100, 100));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        feedButton->setFont(font);

        hungerButtonLayout->addWidget(feedButton);

        hungerRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hungerButtonLayout->addItem(hungerRightSpacer);


        hungerGroupLayout->addLayout(hungerButtonLayout);


        leftButtonsLayout->addLayout(hungerGroupLayout);

        leftMiddleSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        leftButtonsLayout->addItem(leftMiddleSpacer);

        moodGroupLayout = new QVBoxLayout();
        moodGroupLayout->setObjectName(QString::fromUtf8("moodGroupLayout"));
        moodLabelLayout = new QHBoxLayout();
        moodLabelLayout->setObjectName(QString::fromUtf8("moodLabelLayout"));
        moodLabelLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        moodLabelLayout->addItem(moodLabelLeftSpacer);

        moodLabel = new QLabel(centralWidget);
        moodLabel->setObjectName(QString::fromUtf8("moodLabel"));
        moodLabel->setMinimumSize(QSize(120, 25));
        moodLabel->setMaximumSize(QSize(120, 25));
        moodLabel->setAlignment(Qt::AlignCenter);

        moodLabelLayout->addWidget(moodLabel);

        moodLabelRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        moodLabelLayout->addItem(moodLabelRightSpacer);


        moodGroupLayout->addLayout(moodLabelLayout);

        moodProgressBarLayout = new QHBoxLayout();
        moodProgressBarLayout->setObjectName(QString::fromUtf8("moodProgressBarLayout"));
        moodProgressBarLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        moodProgressBarLayout->addItem(moodProgressBarLeftSpacer);

        moodProgressBar = new QProgressBar(centralWidget);
        moodProgressBar->setObjectName(QString::fromUtf8("moodProgressBar"));
        moodProgressBar->setMinimumSize(QSize(120, 25));
        moodProgressBar->setMaximumSize(QSize(120, 25));
        moodProgressBar->setValue(100);

        moodProgressBarLayout->addWidget(moodProgressBar);

        moodProgressBarRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        moodProgressBarLayout->addItem(moodProgressBarRightSpacer);


        moodGroupLayout->addLayout(moodProgressBarLayout);

        moodSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        moodGroupLayout->addItem(moodSpacer);

        moodButtonLayout = new QHBoxLayout();
        moodButtonLayout->setObjectName(QString::fromUtf8("moodButtonLayout"));
        moodLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        moodButtonLayout->addItem(moodLeftSpacer);

        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setMinimumSize(QSize(100, 100));
        playButton->setMaximumSize(QSize(100, 100));
        playButton->setFont(font);

        moodButtonLayout->addWidget(playButton);

        moodRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        moodButtonLayout->addItem(moodRightSpacer);


        moodGroupLayout->addLayout(moodButtonLayout);


        leftButtonsLayout->addLayout(moodGroupLayout);

        leftBottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        leftButtonsLayout->addItem(leftBottomSpacer);


        mainLayout->addLayout(leftButtonsLayout);

        leftMainSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mainLayout->addItem(leftMainSpacer);

        petImageFrame = new QFrame(centralWidget);
        petImageFrame->setObjectName(QString::fromUtf8("petImageFrame"));
        petImageFrame->setFrameShape(QFrame::Box);
        petImageFrame->setFrameShadow(QFrame::Raised);
        petImageFrame->setLineWidth(5);
        imageLayout = new QVBoxLayout(petImageFrame);
        imageLayout->setObjectName(QString::fromUtf8("imageLayout"));
        petNameLabel = new QLabel(petImageFrame);
        petNameLabel->setObjectName(QString::fromUtf8("petNameLabel"));
        QFont font1;
        font1.setPointSize(32);
        font1.setBold(true);
        font1.setWeight(75);
        petNameLabel->setFont(font1);
        petNameLabel->setAlignment(Qt::AlignCenter);

        imageLayout->addWidget(petNameLabel);

        ageLabel = new QLabel(petImageFrame);
        ageLabel->setObjectName(QString::fromUtf8("ageLabel"));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setWeight(75);
        ageLabel->setFont(font2);
        ageLabel->setAlignment(Qt::AlignCenter);

        imageLayout->addWidget(ageLabel);

        petIconLabel = new QLabel(petImageFrame);
        petIconLabel->setObjectName(QString::fromUtf8("petIconLabel"));
        petIconLabel->setScaledContents(true);
        petIconLabel->setAlignment(Qt::AlignCenter);

        imageLayout->addWidget(petIconLabel);

        petTypeLabel = new QLabel(petImageFrame);
        petTypeLabel->setObjectName(QString::fromUtf8("petTypeLabel"));
        QFont font3;
        font3.setPointSize(16);
        petTypeLabel->setFont(font3);
        petTypeLabel->setAlignment(Qt::AlignCenter);

        imageLayout->addWidget(petTypeLabel);

        coinsLabel = new QLabel(petImageFrame);
        coinsLabel->setObjectName(QString::fromUtf8("coinsLabel"));
        coinsLabel->setFont(font3);
        coinsLabel->setAlignment(Qt::AlignCenter);

        imageLayout->addWidget(coinsLabel);


        mainLayout->addWidget(petImageFrame);

        rightMainSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mainLayout->addItem(rightMainSpacer);

        rightButtonsLayout = new QVBoxLayout();
        rightButtonsLayout->setObjectName(QString::fromUtf8("rightButtonsLayout"));
        rightTopSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        rightButtonsLayout->addItem(rightTopSpacer);

        sleepGroupLayout = new QVBoxLayout();
        sleepGroupLayout->setObjectName(QString::fromUtf8("sleepGroupLayout"));
        sleepLabelLayout = new QHBoxLayout();
        sleepLabelLayout->setObjectName(QString::fromUtf8("sleepLabelLayout"));
        sleepLabelLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sleepLabelLayout->addItem(sleepLabelLeftSpacer);

        sleepLabel = new QLabel(centralWidget);
        sleepLabel->setObjectName(QString::fromUtf8("sleepLabel"));
        sleepLabel->setMinimumSize(QSize(120, 25));
        sleepLabel->setMaximumSize(QSize(120, 25));
        sleepLabel->setAlignment(Qt::AlignCenter);

        sleepLabelLayout->addWidget(sleepLabel);

        sleepLabelRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sleepLabelLayout->addItem(sleepLabelRightSpacer);


        sleepGroupLayout->addLayout(sleepLabelLayout);

        sleepProgressBarLayout = new QHBoxLayout();
        sleepProgressBarLayout->setObjectName(QString::fromUtf8("sleepProgressBarLayout"));
        sleepProgressBarLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sleepProgressBarLayout->addItem(sleepProgressBarLeftSpacer);

        sleepProgressBar = new QProgressBar(centralWidget);
        sleepProgressBar->setObjectName(QString::fromUtf8("sleepProgressBar"));
        sleepProgressBar->setMinimumSize(QSize(120, 25));
        sleepProgressBar->setMaximumSize(QSize(120, 25));
        sleepProgressBar->setValue(100);

        sleepProgressBarLayout->addWidget(sleepProgressBar);

        sleepProgressBarRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sleepProgressBarLayout->addItem(sleepProgressBarRightSpacer);


        sleepGroupLayout->addLayout(sleepProgressBarLayout);

        sleepSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        sleepGroupLayout->addItem(sleepSpacer);

        sleepButtonLayout = new QHBoxLayout();
        sleepButtonLayout->setObjectName(QString::fromUtf8("sleepButtonLayout"));
        sleepLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sleepButtonLayout->addItem(sleepLeftSpacer);

        sleepButton = new QPushButton(centralWidget);
        sleepButton->setObjectName(QString::fromUtf8("sleepButton"));
        sleepButton->setMinimumSize(QSize(100, 100));
        sleepButton->setMaximumSize(QSize(100, 100));
        sleepButton->setFont(font);

        sleepButtonLayout->addWidget(sleepButton);

        sleepRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sleepButtonLayout->addItem(sleepRightSpacer);


        sleepGroupLayout->addLayout(sleepButtonLayout);


        rightButtonsLayout->addLayout(sleepGroupLayout);

        rightMiddleSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        rightButtonsLayout->addItem(rightMiddleSpacer);

        healthGroupLayout = new QVBoxLayout();
        healthGroupLayout->setObjectName(QString::fromUtf8("healthGroupLayout"));
        healthLabelLayout = new QHBoxLayout();
        healthLabelLayout->setObjectName(QString::fromUtf8("healthLabelLayout"));
        healthLabelLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        healthLabelLayout->addItem(healthLabelLeftSpacer);

        healthLabel = new QLabel(centralWidget);
        healthLabel->setObjectName(QString::fromUtf8("healthLabel"));
        healthLabel->setMinimumSize(QSize(120, 25));
        healthLabel->setMaximumSize(QSize(120, 25));
        healthLabel->setAlignment(Qt::AlignCenter);

        healthLabelLayout->addWidget(healthLabel);

        healthLabelRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        healthLabelLayout->addItem(healthLabelRightSpacer);


        healthGroupLayout->addLayout(healthLabelLayout);

        healthProgressBarLayout = new QHBoxLayout();
        healthProgressBarLayout->setObjectName(QString::fromUtf8("healthProgressBarLayout"));
        healthProgressBarLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        healthProgressBarLayout->addItem(healthProgressBarLeftSpacer);

        healthProgressBar = new QProgressBar(centralWidget);
        healthProgressBar->setObjectName(QString::fromUtf8("healthProgressBar"));
        healthProgressBar->setMinimumSize(QSize(120, 25));
        healthProgressBar->setMaximumSize(QSize(120, 25));
        healthProgressBar->setValue(100);

        healthProgressBarLayout->addWidget(healthProgressBar);

        healthProgressBarRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        healthProgressBarLayout->addItem(healthProgressBarRightSpacer);


        healthGroupLayout->addLayout(healthProgressBarLayout);

        healthSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        healthGroupLayout->addItem(healthSpacer);

        healthButtonLayout = new QHBoxLayout();
        healthButtonLayout->setObjectName(QString::fromUtf8("healthButtonLayout"));
        healthLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        healthButtonLayout->addItem(healthLeftSpacer);

        undoButton = new QPushButton(centralWidget);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));
        undoButton->setEnabled(false);
        undoButton->setMinimumSize(QSize(100, 100));
        undoButton->setMaximumSize(QSize(100, 100));
        undoButton->setFont(font);

        healthButtonLayout->addWidget(undoButton);

        healthRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        healthButtonLayout->addItem(healthRightSpacer);


        healthGroupLayout->addLayout(healthButtonLayout);


        rightButtonsLayout->addLayout(healthGroupLayout);

        rightBottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        rightButtonsLayout->addItem(rightBottomSpacer);


        mainLayout->addLayout(rightButtonsLayout);


        verticalLayout->addLayout(mainLayout);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(bottomSpacer);

        backButtonLayout = new QHBoxLayout();
        backButtonLayout->setObjectName(QString::fromUtf8("backButtonLayout"));
        backButtonLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        backButtonLayout->addItem(backButtonLeftSpacer);

        backButton = new QPushButton(centralWidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setMaximumSize(QSize(150, 45));

        backButtonLayout->addWidget(backButton);

        backButtonRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        backButtonLayout->addItem(backButtonRightSpacer);


        verticalLayout->addLayout(backButtonLayout);

        PetManagementWindow->setCentralWidget(centralWidget);

        retranslateUi(PetManagementWindow);

        QMetaObject::connectSlotsByName(PetManagementWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PetManagementWindow)
    {
        PetManagementWindow->setWindowTitle(QApplication::translate("PetManagementWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\270\321\202\320\276\320\274\321\206\320\265\320\274", nullptr));
        hungerLabel->setText(QApplication::translate("PetManagementWindow", "\320\223\320\276\320\273\320\276\320\264", nullptr));
        feedButton->setText(QApplication::translate("PetManagementWindow", "\360\237\215\226\n"
"\320\232\320\276\321\200\320\274\320\270\321\202\321\214", nullptr));
        moodLabel->setText(QApplication::translate("PetManagementWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265", nullptr));
        playButton->setText(QApplication::translate("PetManagementWindow", "\360\237\216\256\n"
"\320\230\320\263\321\200\320\260\321\202\321\214", nullptr));
        petNameLabel->setText(QApplication::translate("PetManagementWindow", "\320\230\320\274\321\217 \320\277\320\270\321\202\320\276\320\274\321\206\320\260", nullptr));
        ageLabel->setText(QApplication::translate("PetManagementWindow", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202: 0 \320\264\320\275\320\265\320\271", nullptr));
        petIconLabel->setText(QString());
        petTypeLabel->setText(QApplication::translate("PetManagementWindow", "\320\242\320\270\320\277", nullptr));
        coinsLabel->setText(QApplication::translate("PetManagementWindow", "\320\234\320\276\320\275\320\265\321\202\321\213: 0", nullptr));
        sleepLabel->setText(QApplication::translate("PetManagementWindow", "\320\241\320\276\320\275", nullptr));
        sleepButton->setText(QApplication::translate("PetManagementWindow", "\360\237\230\264\n"
"\320\237\320\276\321\201\320\277\320\260\321\202\321\214", nullptr));
        healthLabel->setText(QApplication::translate("PetManagementWindow", "\320\227\320\264\320\276\321\200\320\276\320\262\321\214\320\265", nullptr));
        undoButton->setText(QApplication::translate("PetManagementWindow", "\342\206\251\n"
"\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        backButton->setText(QApplication::translate("PetManagementWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PetManagementWindow: public Ui_PetManagementWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PETMANAGEMENTWINDOW_H
