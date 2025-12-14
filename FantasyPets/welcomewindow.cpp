#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include <QPixmap>
#include <QPalette>
#include <QDir>
#include <QResizeEvent>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
    connect(ui->playButton, &QPushButton::clicked, this, &WelcomeWindow::playButtonClicked);
    
    updateBackground();
}

void WelcomeWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void WelcomeWindow::updateBackground()
{
    // Устанавливаем фон
    QString backgroundPath = "../FantasyPets/img/back1.jpg";
    QPixmap background(backgroundPath);
    
    if (!background.isNull()) {
        // Масштабируем изображение под размер окна
        background = background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(background));
        this->setPalette(palette);
        this->setAutoFillBackground(true);
    }
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

