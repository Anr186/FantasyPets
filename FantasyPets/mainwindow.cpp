#include "mainwindow.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_welcomeWindow(nullptr)
    , m_userSelectionWindow(nullptr)
    , m_petSelectionWindow(nullptr)
    , m_petManagementWindow(nullptr)
    , m_currentUser(nullptr)
    , m_currentPet(nullptr)
{
    // MainWindow используется только как контейнер для управления окнами
    // Не показываем его напрямую
    hide();
    
    // Создаем окна
    m_welcomeWindow = new WelcomeWindow(this);
    m_userSelectionWindow = new UserSelectionWindow(this);
    m_petSelectionWindow = new PetSelectionWindow(this);
    m_petManagementWindow = new PetManagementWindow(this);
    
    // Загружаем пользователей
    loadUsers();
    m_userSelectionWindow->setUsers(m_users);
    
    // Подключаем сигналы
    connect(m_welcomeWindow, &WelcomeWindow::playButtonClicked, this, &MainWindow::showUserSelection);
    connect(m_userSelectionWindow, &UserSelectionWindow::userSelected, this, &MainWindow::onUserSelected);
    connect(m_userSelectionWindow, &UserSelectionWindow::newUserCreated, this, [this](User* user) {
        if (!m_users.contains(user)) {
            m_users.append(user);
        }
        m_userSelectionWindow->setUsers(m_users);
        saveUsers();
    });
    connect(m_userSelectionWindow, &UserSelectionWindow::backButtonClicked, this, &MainWindow::showWelcomeScreen);
    connect(m_userSelectionWindow, &UserSelectionWindow::userDeleted, this, [this](User* user) {
        m_users.removeAll(user);
        saveUsers();
    });
    
    connect(m_petSelectionWindow, &PetSelectionWindow::petSelected, this, &MainWindow::onPetSelected);
    connect(m_petSelectionWindow, &PetSelectionWindow::newPetCreated, this, [this](Pet* pet) {
        if (m_currentUser) {
            saveUsers();
        }
    });
    connect(m_petSelectionWindow, &PetSelectionWindow::petDeleted, this, [this](Pet* pet) {
        saveUsers();
    });
    connect(m_petSelectionWindow, &PetSelectionWindow::backButtonClicked, this, &MainWindow::showUserSelection);
    
    connect(m_petManagementWindow, &PetManagementWindow::backButtonClicked, this, &MainWindow::showPetSelection);
    connect(m_petManagementWindow, &PetManagementWindow::petChanged, this, [this](Pet* pet) {
        saveUsers();
    });
    
    // Показываем приветственный экран
    showWelcomeScreen();
}

MainWindow::~MainWindow()
{
    saveUsers();
    // Очищаем память
    for (User* user : m_users) {
        delete user;
    }
}

void MainWindow::showWelcomeScreen()
{
    showWindow(m_welcomeWindow);
}

void MainWindow::showUserSelection()
{
    m_userSelectionWindow->setUsers(m_users);
    showWindow(m_userSelectionWindow);
}

void MainWindow::showPetSelection()
{
    if (m_currentUser) {
        m_petSelectionWindow->setUser(m_currentUser);
        showWindow(m_petSelectionWindow);
    }
}

void MainWindow::showPetManagement()
{
    if (m_currentPet) {
        m_petManagementWindow->setPet(m_currentPet);
        showWindow(m_petManagementWindow);
    }
}

void MainWindow::onUserSelected(User* user)
{
    m_currentUser = user;
    showPetSelection();
}

void MainWindow::onPetSelected(Pet* pet)
{
    m_currentPet = pet;
    showPetManagement();
}

void MainWindow::saveAndClose()
{
    saveUsers();
    close();
}

void MainWindow::loadUsers()
{
    m_users = SaveManager::getInstance().loadUsers();
}

void MainWindow::saveUsers()
{
    SaveManager::getInstance().saveUsers(m_users);
}

void MainWindow::showWindow(QMainWindow* window)
{
    // Скрываем все окна
    m_welcomeWindow->hide();
    m_userSelectionWindow->hide();
    m_petSelectionWindow->hide();
    m_petManagementWindow->hide();
    
    // Показываем нужное окно
    if (window) {
        window->show();
        // При первом показе устанавливаем размер и позицию
        if (!window->isVisible() || window->geometry().isEmpty()) {
            window->resize(800, 600);
            window->move(100, 100);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    saveUsers();
    event->accept();
}
