#include "userselectionwindow.h"
#include "ui_userselectionwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDir>
#include <QResizeEvent>
#include <QListWidgetItem>
#include <QIcon>
#include <QPainter>
#include <QFont>

UserSelectionWindow::UserSelectionWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserSelectionWindow)
    , m_selectedUser(nullptr)
{
    ui->setupUi(this);
    
    // Убираем пунктирную рамку фокуса
    ui->userListWidget->setFocusPolicy(Qt::NoFocus);
    
    updateBackground();
    
    connect(ui->selectButton, &QPushButton::clicked, this, &UserSelectionWindow::onSelectButtonClicked);
    connect(ui->newUserButton, &QPushButton::clicked, this, &UserSelectionWindow::onNewUserButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &UserSelectionWindow::onBackButtonClicked);
    connect(ui->deleteUserButton, &QPushButton::clicked, this, &UserSelectionWindow::onDeleteUserButtonClicked);
    connect(ui->userListWidget, &QListWidget::itemSelectionChanged, this, &UserSelectionWindow::onUserListSelectionChanged);
    
    onUserListSelectionChanged();
}

UserSelectionWindow::~UserSelectionWindow()
{
    delete ui;
}

void UserSelectionWindow::setUsers(const QList<User*>& users)
{
    m_users = users;
    updateUserList();
}

void UserSelectionWindow::updateUserList()
{
    ui->userListWidget->clear();
    for (int i = 0; i < m_users.size(); ++i) {
        User* user = m_users[i];
        QString itemText = user->getName();
        QListWidgetItem* item = new QListWidgetItem(itemText);
        
        // Создаем стандартную иконку аватара
        QPixmap avatarPixmap(56, 56);
        avatarPixmap.fill(Qt::transparent);
        QPainter painter(&avatarPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Рисуем круглый аватар с градиентом
        QBrush brush(QColor(100, 150, 200));
        painter.setBrush(brush);
        painter.setPen(QPen(QColor(70, 120, 170), 2));
        painter.drawEllipse(2, 2, 52, 52);
        
        // Добавляем инициал пользователя
        painter.setPen(QPen(Qt::white, 1));
        QFont font = painter.font();
        font.setBold(true);
        font.setPointSize(24);
        painter.setFont(font);
        if (!itemText.isEmpty()) {
            QString initial = itemText.left(1).toUpper();
            painter.drawText(avatarPixmap.rect(), Qt::AlignCenter, initial);
        }
        
        item->setIcon(QIcon(avatarPixmap));
        // Храним индекс пользователя вместо указателя
        item->setData(Qt::UserRole, i);
        ui->userListWidget->addItem(item);
    }
}

void UserSelectionWindow::onUserListSelectionChanged()
{
    QListWidgetItem* currentItem = ui->userListWidget->currentItem();
    bool hasSelection = currentItem != nullptr;
    ui->selectButton->setEnabled(hasSelection);
    ui->deleteUserButton->setEnabled(hasSelection);
}

void UserSelectionWindow::onSelectButtonClicked()
{
    QListWidgetItem* currentItem = ui->userListWidget->currentItem();
    if (currentItem) {
        int index = currentItem->data(Qt::UserRole).toInt();
        if (index >= 0 && index < m_users.size()) {
            m_selectedUser = m_users[index];
            emit userSelected(m_selectedUser);
        }
    }
}

void UserSelectionWindow::onNewUserButtonClicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Новый пользователь", "Введите имя пользователя:",
                                         QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        User* newUser = new User(name);
        m_users.append(newUser);
        updateUserList();
        emit newUserCreated(newUser);
    }
}

void UserSelectionWindow::onBackButtonClicked()
{
    emit backButtonClicked();
}

void UserSelectionWindow::onDeleteUserButtonClicked()
{
    QListWidgetItem* currentItem = ui->userListWidget->currentItem();
    if (currentItem) {
        int index = currentItem->data(Qt::UserRole).toInt();
        if (index >= 0 && index < m_users.size()) {
            User* userToDelete = m_users[index];
            int ret = QMessageBox::question(this, "Удаление пользователя",
                                            QString("Вы уверены, что хотите удалить пользователя '%1'?").arg(userToDelete->getName()),
                                            QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                m_users.removeAt(index);
                emit userDeleted(userToDelete);
                delete userToDelete;
                updateUserList();
                onUserListSelectionChanged();
            }
        }
    }
}

void UserSelectionWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void UserSelectionWindow::updateBackground()
{
    QString backgroundPath = "../FantasyPets/img/back2.jpg";
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

