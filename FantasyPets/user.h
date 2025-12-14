#ifndef USER_H
#define USER_H

#include "pet.h"
#include <QString>
#include <QList>
#include <QJsonObject>

class User
{
public:
    User(const QString& name);
    
    QString getName() const { return m_name; }
    QList<Pet*>& getPets() { return m_pets; }
    const QList<Pet*>& getPets() const { return m_pets; }
    
    void addPet(Pet* pet);
    void removePet(Pet* pet);
    Pet* getPet(int index) const;
    int getPetCount() const { return m_pets.size(); }
    
    // Сохранение/загрузка
    QJsonObject toJson() const;
    static User* fromJson(const QJsonObject& json);

private:
    QString m_name;
    QList<Pet*> m_pets;
};

#endif // USER_H

