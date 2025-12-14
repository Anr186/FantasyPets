#include "savemanager.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStandardPaths>
#include <QApplication>
#include <QDebug>

SaveManager& SaveManager::getInstance()
{
    static SaveManager instance;
    return instance;
}

void SaveManager::ensureSaveDirectory()
{
    if (m_savePath.isEmpty()) {
        // Сохраняем в директории приложения
        QString appDir = QApplication::applicationDirPath();
        m_savePath = appDir + "/saves";
        
        QDir dir;
        if (!dir.exists(m_savePath)) {
            dir.mkpath(m_savePath);
        }
    }
}

QString SaveManager::getSavePath() const
{
    return m_savePath;
}

void SaveManager::saveUsers(const QList<User*>& users)
{
    ensureSaveDirectory();
    
    QJsonObject root;
    QJsonArray usersArray;
    
    for (User* user : users) {
        usersArray.append(user->toJson());
    }
    
    root["users"] = usersArray;
    
    QJsonDocument doc(root);
    QString filePath = m_savePath + "/users.json";
    
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        qDebug() << "Users saved to" << filePath;
    } else {
        qDebug() << "Failed to save users to" << filePath;
    }
}

QList<User*> SaveManager::loadUsers()
{
    ensureSaveDirectory();
    
    QList<User*> users;
    QString filePath = m_savePath + "/users.json";
    
    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "Save file does not exist:" << filePath;
        return users;
    }
    
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();
        
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject root = doc.object();
            QJsonArray usersArray = root["users"].toArray();
            
            for (const QJsonValue& value : usersArray) {
                User* user = User::fromJson(value.toObject());
                if (user) {
                    users.append(user);
                }
            }
        }
    } else {
        qDebug() << "Failed to load users from" << filePath;
    }
    
    return users;
}


