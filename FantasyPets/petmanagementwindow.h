#ifndef PETMANAGEMENTWINDOW_H
#define PETMANAGEMENTWINDOW_H

#include <QMainWindow>
#include "pet.h"
#include "action.h"
#include "petobserver.h"
#include <QTimer>
#include <QStack>
#include <QPushButton>
#include <QPixmap>
#include <QSize>

namespace Ui {
class PetManagementWindow;
}

class PetManagementWindow : public QMainWindow, public PetObserver
{
    Q_OBJECT

public:
    explicit PetManagementWindow(QWidget *parent = nullptr);
    ~PetManagementWindow();
    
    void setPet(Pet* pet);
    
    // PetObserver interface
    void onPetChanged(Pet* pet) override;

signals:
    void backButtonClicked();
    void petChanged(Pet* pet);

private slots:
    void onFeedButtonClicked();
    void onPlayButtonClicked();
    void onSleepButtonClicked();
    void onUndoButtonClicked();
    void onBackButtonClicked();
    void onRoomsButtonClicked();
    void updatePetStatus();

private:
    Ui::PetManagementWindow *ui;
    Pet* m_pet;
    QTimer* m_updateTimer;
    QStack<Action*> m_actionHistory; // Command pattern для отмены действий
    QPixmap m_cachedBackground; // Кэш исходного изображения фона
    QPixmap m_scaledBackground; // Кэш масштабированного изображения
    QSize m_lastBackgroundSize; // Последний размер для кэширования
    PetType::StandardType m_lastPetType; // Последний тип питомца для кэширования
    int m_lastRoomNumber; // Последний номер комнаты для кэширования
    QPushButton* m_roomsButton; // Кнопка для покупки комнат
    
    void updateUI();
    void executeAction(Action* action);
    void updateBackground();
    void applyPetStyle();
    
protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // PETMANAGEMENTWINDOW_H

