#include "pet.h"
#include "petobserver.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>
#include <QDebug>

Pet::Pet(const QString& name, const PetType& type, int hungerDecayRate, int sleepDecayRate)
    : m_name(name)
    , m_type(type)
    , m_birthDate(QDateTime::currentDateTime())
    , m_hunger("Голод", 100)
    , m_sleep("Сон", 100)
    , m_mood("Настроение", 100)
    , m_health("Здоровье", 100)
    , m_coins(0)
    , m_hungerDecayRate(hungerDecayRate)
    , m_sleepDecayRate(sleepDecayRate)
    , m_currentRoom(0)
{
}

Pet::~Pet()
{
    m_observers.clear();
}

int Pet::getAge() const
{
    return m_birthDate.daysTo(QDateTime::currentDateTime());
}

void Pet::addCoins(int amount)
{
    m_coins += amount;
    notifyObservers();
}

bool Pet::spendCoins(int amount)
{
    if (m_coins >= amount) {
        m_coins -= amount;
        notifyObservers();
        return true;
    }
    return false;
}

bool Pet::buyRoom(int roomNumber, int cost)
{
    if (roomNumber <= 0) return false; // Комната 0 - базовая, её покупать не нужно
    if (hasRoom(roomNumber)) return false; // Комната уже куплена
    if (m_coins < cost) return false; // Недостаточно монет
    
    if (spendCoins(cost)) {
        m_boughtRooms.append(roomNumber);
        notifyObservers();
        return true;
    }
    return false;
}

void Pet::setCurrentRoom(int roomNumber)
{
    if (roomNumber == 0 || hasRoom(roomNumber)) {
        m_currentRoom = roomNumber;
        notifyObservers();
    }
}

bool Pet::hasRoom(int roomNumber) const
{
    return m_boughtRooms.contains(roomNumber);
}

void Pet::update()
{
    updateNeeds();
    notifyObservers();
}

void Pet::updateNeeds()
{
    // Голод уменьшается со временем
    m_hunger.decrease(m_hungerDecayRate);
    
    // Сон уменьшается со временем
    m_sleep.decrease(m_sleepDecayRate);
    
    // Настроение зависит от других потребностей
    if (m_hunger.isCritical() || m_sleep.isCritical()) {
        m_mood.decrease(2);
    } else if (m_hunger.isLow() || m_sleep.isLow()) {
        m_mood.decrease(1);
    } else {
        m_mood.increase(1);
    }
    
    // Здоровье зависит от критических потребностей
    if (m_hunger.isCritical() || m_sleep.isCritical() || m_mood.isCritical()) {
        m_health.decrease(1);
    } else if (m_health.getValue() < 100) {
        m_health.increase(1);
    }
}

void Pet::attachObserver(PetObserver* observer)
{
    if (observer && !m_observers.contains(observer)) {
        m_observers.append(observer);
    }
}

void Pet::detachObserver(PetObserver* observer)
{
    m_observers.removeAll(observer);
}

void Pet::notifyObservers()
{
    for (PetObserver* observer : m_observers) {
        observer->onPetChanged(this);
    }
}

QString Pet::getAvatarPath() const
{
    int age = getAge();
    QString basePath = ":/avatars/";
    
    if (age < 3) {
        return basePath + "baby_" + QString::number(static_cast<int>(m_type.getType()));
    } else if (age < 7) {
        return basePath + "young_" + QString::number(static_cast<int>(m_type.getType()));
    } else {
        return basePath + "adult_" + QString::number(static_cast<int>(m_type.getType()));
    }
}

QJsonObject Pet::toJson() const
{
    QJsonObject obj;
    obj["name"] = m_name;
    obj["type"] = static_cast<int>(m_type.getType());
    obj["typeName"] = m_type.getName();
    obj["typeDescription"] = m_type.getDescription();
    // Сохраняем пути к изображениям для кастомного питомца
    if (m_type.getType() == PetType::Custom) {
        obj["babyAvaPath"] = m_type.getBabyAvaPath();
        obj["bigAvaPath"] = m_type.getBigAvaPath();
        obj["babyImagePath"] = m_type.getBabyImagePath();
        obj["bigImagePath"] = m_type.getBigImagePath();
    }
    
    // Сохраняем информацию о комнатах
    QJsonArray boughtRoomsArray;
    for (int room : m_boughtRooms) {
        boughtRoomsArray.append(room);
    }
    obj["boughtRooms"] = boughtRoomsArray;
    obj["currentRoom"] = m_currentRoom;
    obj["birthDate"] = m_birthDate.toString(Qt::ISODate);
    obj["coins"] = m_coins;
    obj["hunger"] = m_hunger.getValue();
    obj["sleep"] = m_sleep.getValue();
    obj["mood"] = m_mood.getValue();
    obj["health"] = m_health.getValue();
    obj["hungerDecayRate"] = m_hungerDecayRate;
    obj["sleepDecayRate"] = m_sleepDecayRate;
    return obj;
}

Pet* Pet::fromJson(const QJsonObject& json)
{
    QString name = json["name"].toString();
    PetType::StandardType type = static_cast<PetType::StandardType>(json["type"].toInt());
    
    QString typeName = json["typeName"].toString();
    QString typeDescription = json["typeDescription"].toString();
    
    PetType petType(type == PetType::Custom ? PetType::Custom : type,
                    type == PetType::Custom ? typeName : "",
                    type == PetType::Custom ? typeDescription : "");
    
    // Загружаем пути к изображениям для кастомного питомца
    if (type == PetType::Custom) {
        petType.setBabyAvaPath(json["babyAvaPath"].toString());
        petType.setBigAvaPath(json["bigAvaPath"].toString());
        petType.setBabyImagePath(json["babyImagePath"].toString());
        petType.setBigImagePath(json["bigImagePath"].toString());
    }
    
    int hungerDecay = json["hungerDecayRate"].toInt(1);
    int sleepDecay = json["sleepDecayRate"].toInt(1);
    
    Pet* pet = new Pet(name, petType, hungerDecay, sleepDecay);
    
    pet->m_birthDate = QDateTime::fromString(json["birthDate"].toString(), Qt::ISODate);
    pet->m_coins = json["coins"].toInt();
    pet->m_hunger.setValue(json["hunger"].toInt());
    pet->m_sleep.setValue(json["sleep"].toInt());
    pet->m_mood.setValue(json["mood"].toInt());
    pet->m_health.setValue(json["health"].toInt());
    
    // Загружаем информацию о комнатах
    if (json.contains("boughtRooms")) {
        QJsonArray boughtRoomsArray = json["boughtRooms"].toArray();
        for (const QJsonValue& value : boughtRoomsArray) {
            pet->m_boughtRooms.append(value.toInt());
        }
    }
    pet->m_currentRoom = json["currentRoom"].toInt(0);
    
    return pet;
}

