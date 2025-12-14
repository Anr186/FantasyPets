#ifndef ACTION_H
#define ACTION_H

#include "pet.h"
#include <QString>

// Command pattern
class Action
{
public:
    virtual ~Action() = default;
    virtual bool execute(Pet* pet) = 0;
    virtual void undo(Pet* pet) = 0;
    virtual QString getDescription() const = 0;
    virtual int getCost() const { return 0; }
};

// Конкретные действия
class FeedAction : public Action
{
public:
    FeedAction(int foodValue = 20, int cost = 5);
    bool execute(Pet* pet) override;
    void undo(Pet* pet) override;
    QString getDescription() const override { return "Кормить"; }
    int getCost() const override { return m_cost; }

private:
    int m_foodValue;
    int m_cost;
    int m_previousHunger;
};

class PlayAction : public Action
{
public:
    PlayAction(int moodIncrease = 15, int coinsReward = 10);
    bool execute(Pet* pet) override;
    void undo(Pet* pet) override;
    QString getDescription() const override { return "Играть"; }
    int getCost() const override { return 0; }

private:
    int m_moodIncrease;
    int m_coinsReward;
    int m_previousMood;
    int m_previousCoins;
};

class SleepAction : public Action
{
public:
    SleepAction(int sleepIncrease = 30);
    bool execute(Pet* pet) override;
    void undo(Pet* pet) override;
    QString getDescription() const override { return "Уложить спать"; }
    int getCost() const override { return 0; }

private:
    int m_sleepIncrease;
    int m_previousSleep;
};

#endif // ACTION_H


