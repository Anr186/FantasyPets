#ifndef USERSELECTIONWINDOW_H
#define USERSELECTIONWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class UserSelectionWindow;
}

class UserSelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSelectionWindow(QWidget *parent = nullptr);
    ~UserSelectionWindow();
    
    void setUsers(const QList<User*>& users);
    User* getSelectedUser() const { return m_selectedUser; }

signals:
    void userSelected(User* user);
    void newUserCreated(User* user);
    void userDeleted(User* user);
    void backButtonClicked();

private slots:
    void onUserListSelectionChanged();
    void onSelectButtonClicked();
    void onNewUserButtonClicked();
    void onBackButtonClicked();
    void onDeleteUserButtonClicked();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::UserSelectionWindow *ui;
    QList<User*> m_users;
    User* m_selectedUser;
    void updateUserList();
    void updateBackground();
};

#endif // USERSELECTIONWINDOW_H

