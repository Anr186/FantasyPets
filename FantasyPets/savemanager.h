#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "user.h"
#include <QString>
#include <QList>
#include <QJsonObject>

class SaveManager
{
public:
    static SaveManager& getInstance();
    
    void saveUsers(const QList<User*>& users);
    QList<User*> loadUsers();
    
    QString getSavePath() const;

private:
    SaveManager() = default;
    ~SaveManager() = default;
    SaveManager(const SaveManager&) = delete;
    SaveManager& operator=(const SaveManager&) = delete;
    
    QString m_savePath;
    void ensureSaveDirectory();
};

#endif // SAVEMANAGER_H


