#ifndef PET_H
#define PET_H

#include "need.h"
#include "pettype.h"
#include <QString>
#include <QDateTime>
#include <QList>
#include <QJsonObject>

// Forward declaration для Observer
class PetObserver;

class Pet
{
public:
    Pet(const QString& name, const PetType& type, int hungerDecayRate = 1, int sleepDecayRate = 1);
    ~Pet();
    
    QString getName() const { return m_name; }
    PetType getType() const { return m_type; }
    int getAge() const; // Возраст в днях
    QDateTime getBirthDate() const { return m_birthDate; } // Дата рождения
    int getCoins() const { return m_coins; }
    
    Need* getHunger() { return &m_hunger; }
    Need* getSleep() { return &m_sleep; }
    Need* getMood() { return &m_mood; }
    Need* getHealth() { return &m_health; }
    
    void addCoins(int amount);
    bool spendCoins(int amount);
    
    // Механизм комнат
    bool buyRoom(int roomNumber, int cost);
    void setCurrentRoom(int roomNumber);
    int getCurrentRoom() const { return m_currentRoom; }
    QList<int> getBoughtRooms() const { return m_boughtRooms; }
    bool hasRoom(int roomNumber) const;
    
    // Обновление состояния питомца (вызывается по таймеру)
    void update();
    
    // Observer pattern
    void attachObserver(PetObserver* observer);
    void detachObserver(PetObserver* observer);
    void notifyObservers();
    
    // Сохранение/загрузка
    QJsonObject toJson() const;
    static Pet* fromJson(const QJsonObject& json);
    
    friend class User; // Для доступа к приватным членам при загрузке

private:
    QString m_name;
    PetType m_type;
    QDateTime m_birthDate;
    
    Need m_hunger;
    Need m_sleep;
    Need m_mood;
    Need m_health;
    
    int m_coins;
    int m_hungerDecayRate;
    int m_sleepDecayRate;
    
    // Механизм комнат
    QList<int> m_boughtRooms;  // Список купленных комнат
    int m_currentRoom;         // Текущая выбранная комната (0 = базовая, 1+ = дополнительные)
    
    QList<PetObserver*> m_observers;
    
    void updateNeeds();
    QString getAvatarPath() const; // Путь к аватару в зависимости от возраста
};

#endif // PET_H

