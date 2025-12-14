#include "action.h"
#include <QDebug>

FeedAction::FeedAction(int foodValue, int cost)
    : m_foodValue(foodValue), m_cost(cost), m_previousHunger(0)
{
}

bool FeedAction::execute(Pet* pet)
{
    if (!pet) return false;
    
    if (pet->getCoins() < m_cost) {
        return false; // Недостаточно монет
    }
    
    m_previousHunger = pet->getHunger()->getValue();
    pet->getHunger()->increase(m_foodValue);
    pet->spendCoins(m_cost);
    pet->notifyObservers();
    return true;
}

void FeedAction::undo(Pet* pet)
{
    if (!pet) return;
    
    pet->getHunger()->setValue(m_previousHunger);
    pet->addCoins(m_cost);
    pet->notifyObservers();
}

PlayAction::PlayAction(int moodIncrease, int coinsReward)
    : m_moodIncrease(moodIncrease), m_coinsReward(coinsReward),
      m_previousMood(0), m_previousCoins(0)
{
}

bool PlayAction::execute(Pet* pet)
{
    if (!pet) return false;
    
    m_previousMood = pet->getMood()->getValue();
    m_previousCoins = pet->getCoins();
    
    pet->getMood()->increase(m_moodIncrease);
    pet->addCoins(m_coinsReward);
    pet->notifyObservers();
    return true;
}

void PlayAction::undo(Pet* pet)
{
    if (!pet) return;
    
    pet->getMood()->setValue(m_previousMood);
    // Восстанавливаем предыдущее количество монет
    int currentCoins = pet->getCoins();
    pet->addCoins(m_previousCoins - currentCoins);
    pet->notifyObservers();
}

SleepAction::SleepAction(int sleepIncrease)
    : m_sleepIncrease(sleepIncrease), m_previousSleep(0)
{
}

bool SleepAction::execute(Pet* pet)
{
    if (!pet) return false;
    
    m_previousSleep = pet->getSleep()->getValue();
    pet->getSleep()->increase(m_sleepIncrease);
    pet->notifyObservers();
    return true;
}

void SleepAction::undo(Pet* pet)
{
    if (!pet) return;
    
    pet->getSleep()->setValue(m_previousSleep);
    pet->notifyObservers();
}

