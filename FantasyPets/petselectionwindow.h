#ifndef PETSELECTIONWINDOW_H
#define PETSELECTIONWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "pet.h"
#include "pettype.h"

namespace Ui {
class PetSelectionWindow;
}

class PetSelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetSelectionWindow(QWidget *parent = nullptr);
    ~PetSelectionWindow();
    
    void setUser(User* user);
    Pet* getSelectedPet() const { return m_selectedPet; }

signals:
    void petSelected(Pet* pet);
    void newPetCreated(Pet* pet);
    void petDeleted(Pet* pet);
    void backButtonClicked();

private slots:
    void onPetListSelectionChanged();
    void onSelectButtonClicked();
    void onNewPetButtonClicked();
    void onBackButtonClicked();
    void onDeletePetButtonClicked();
    void onCreateCustomPet();
    
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Ui::PetSelectionWindow *ui;
    User* m_user;
    Pet* m_selectedPet;
    QList<QWidget*> m_petCards;
    void updatePetList();
    void setupStandardPets();
    QWidget* createPetCard(Pet* pet);
    void clearPetCards();
    void updateBackground();
    
protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // PETSELECTIONWINDOW_H

