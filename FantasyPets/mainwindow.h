#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "welcomewindow.h"
#include "userselectionwindow.h"
#include "petselectionwindow.h"
#include "petmanagementwindow.h"
#include "savemanager.h"
#include "user.h"
#include <QList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showWelcomeScreen();
    void showUserSelection();
    void showPetSelection();
    void showPetManagement();
    void onUserSelected(User* user);
    void onPetSelected(Pet* pet);
    void saveAndClose();

private:
    WelcomeWindow* m_welcomeWindow;
    UserSelectionWindow* m_userSelectionWindow;
    PetSelectionWindow* m_petSelectionWindow;
    PetManagementWindow* m_petManagementWindow;
    
    QList<User*> m_users;
    User* m_currentUser;
    Pet* m_currentPet;
    
    void loadUsers();
    void saveUsers();
    void showWindow(QMainWindow* window);
    
protected:
    void closeEvent(QCloseEvent* event) override;
};

#endif // MAINWINDOW_H
