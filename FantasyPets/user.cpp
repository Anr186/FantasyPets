#include "user.h"
#include <QJsonObject>
#include <QJsonArray>

User::User(const QString& name)
    : m_name(name)
{
}

void User::addPet(Pet* pet)
{
    if (pet && !m_pets.contains(pet)) {
        m_pets.append(pet);
    }
}

void User::removePet(Pet* pet)
{
    m_pets.removeAll(pet);
}

Pet* User::getPet(int index) const
{
    if (index >= 0 && index < m_pets.size()) {
        return m_pets[index];
    }
    return nullptr;
}

QJsonObject User::toJson() const
{
    QJsonObject obj;
    obj["name"] = m_name;
    
    QJsonArray petsArray;
    for (Pet* pet : m_pets) {
        petsArray.append(pet->toJson());
    }
    obj["pets"] = petsArray;
    
    return obj;
}

User* User::fromJson(const QJsonObject& json)
{
    QString name = json["name"].toString();
    User* user = new User(name);
    
    QJsonArray petsArray = json["pets"].toArray();
    for (const QJsonValue& value : petsArray) {
        Pet* pet = Pet::fromJson(value.toObject());
        if (pet) {
            user->addPet(pet);
        }
    }
    
    return user;
}


