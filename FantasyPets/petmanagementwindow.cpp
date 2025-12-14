#include "petmanagementwindow.h"
#include "ui_petmanagementwindow.h"
#include "action.h"
#include "pettype.h"
#include <QMessageBox>
#include <QPixmap>
#include <QProgressBar>
#include <QPalette>
#include <QBrush>
#include <QDir>
#include <QResizeEvent>
#include <QGraphicsDropShadowEffect>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QTimer>

PetManagementWindow::PetManagementWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PetManagementWindow)
    , m_pet(nullptr)
    , m_lastBackgroundSize(0, 0)
    , m_lastPetType(PetType::Custom)
    , m_lastRoomNumber(-1)
    , m_roomsButton(nullptr)
{
    ui->setupUi(this);
    
    m_updateTimer = new QTimer(static_cast<QWidget*>(this));
    connect(m_updateTimer, &QTimer::timeout, this, &PetManagementWindow::updatePetStatus);
    m_updateTimer->start(5000); // Обновление каждые 5 секунд
    
    connect(ui->feedButton, &QPushButton::clicked, this, &PetManagementWindow::onFeedButtonClicked);
    connect(ui->playButton, &QPushButton::clicked, this, &PetManagementWindow::onPlayButtonClicked);
    connect(ui->sleepButton, &QPushButton::clicked, this, &PetManagementWindow::onSleepButtonClicked);
    connect(ui->undoButton, &QPushButton::clicked, this, &PetManagementWindow::onUndoButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &PetManagementWindow::onBackButtonClicked);
    
    // Создаем кнопку для покупки комнат программно
    m_roomsButton = new QPushButton("Комнаты", static_cast<QWidget*>(this));
    m_roomsButton->setMaximumSize(150, 45);
    m_roomsButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #9966ff, stop:0.5 #7744cc, stop:1 #5522aa);"
        "    color: #ffffff;"
        "    border: 2px solid #aa88ff;"
        "    border-radius: 5px;"
        "    padding: 5px 15px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #aa88ff, stop:0.5 #9966ff, stop:1 #7744cc);"
        "}"
    );
    connect(m_roomsButton, &QPushButton::clicked, this, &PetManagementWindow::onRoomsButtonClicked);
}

PetManagementWindow::~PetManagementWindow()
{
    if (m_pet) {
        m_pet->detachObserver(static_cast<PetObserver*>(this));
    }
    // Очищаем историю действий
    while (!m_actionHistory.isEmpty()) {
        delete m_actionHistory.pop();
    }
    delete ui;
}

void PetManagementWindow::setPet(Pet* pet)
{
    if (m_pet) {
        m_pet->detachObserver(static_cast<PetObserver*>(this));
    }
    
    m_pet = pet;
    
    if (m_pet) {
        m_pet->attachObserver(static_cast<PetObserver*>(this));
        updateUI();
        updateBackground();
        
        // Размещаем кнопку комнат рядом с кнопкой "Назад"
        if (m_roomsButton && ui->backButton) {
            QWidget* backButtonParent = ui->backButton->parentWidget();
            if (backButtonParent) {
                QLayout* backButtonLayout = backButtonParent->layout();
                if (backButtonLayout) {
                    QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(backButtonLayout);
                    if (hLayout) {
                        // Вставляем кнопку перед кнопкой "Назад"
                        int backButtonIndex = hLayout->indexOf(ui->backButton);
                        if (backButtonIndex >= 0) {
                            hLayout->insertWidget(backButtonIndex, m_roomsButton);
                        } else {
                            hLayout->addWidget(m_roomsButton);
                        }
                    }
                }
            }
        }
    }
}

void PetManagementWindow::onPetChanged(Pet* pet)
{
    if (pet == m_pet) {
        updateUI();
        emit petChanged(pet);
    }
}

void PetManagementWindow::updatePetStatus()
{
    if (m_pet) {
        m_pet->update();
    }
}

void PetManagementWindow::updateUI()
{
    if (!m_pet) return;
    
    // Обновляем информацию о питомце
    ui->petNameLabel->setText(m_pet->getName());
    ui->petTypeLabel->setText(m_pet->getType().getName());
    
    // Вычисляем возраст в днях и часах
    QDateTime birthDate = m_pet->getBirthDate();
    QDateTime currentDate = QDateTime::currentDateTime();
    qint64 seconds = birthDate.secsTo(currentDate);
    int days = seconds / 86400; // 86400 секунд в дне
    int hours = (seconds % 86400) / 3600; // Оставшиеся часы
    
    QString ageText;
    if (days > 0) {
        if (hours > 0) {
            ageText = QString("Возраст: %1 дн. %2 ч.").arg(days).arg(hours);
        } else {
            ageText = QString("Возраст: %1 дн.").arg(days);
        }
    } else {
        ageText = QString("Возраст: %1 ч.").arg(hours);
    }
    ui->ageLabel->setText(ageText);
    
    ui->coinsLabel->setText(QString("Монеты: %1🪙").arg(m_pet->getCoins()));
    
    // Обновляем прогресс-бары потребностей
    ui->hungerProgressBar->setValue(m_pet->getHunger()->getValue());
    ui->hungerProgressBar->setFormat(QString("%1%").arg(m_pet->getHunger()->getValue()));
    
    ui->sleepProgressBar->setValue(m_pet->getSleep()->getValue());
    ui->sleepProgressBar->setFormat(QString("%1%").arg(m_pet->getSleep()->getValue()));
    
    ui->moodProgressBar->setValue(m_pet->getMood()->getValue());
    ui->moodProgressBar->setFormat(QString("%1%").arg(m_pet->getMood()->getValue()));
    
    ui->healthProgressBar->setValue(m_pet->getHealth()->getValue());
    ui->healthProgressBar->setFormat(QString("%1%").arg(m_pet->getHealth()->getValue()));
    
    // Обновляем формат для всех прогресс-баров (проценты внутри)
    ui->hungerProgressBar->setFormat(QString("%1%").arg(m_pet->getHunger()->getValue()));
    ui->sleepProgressBar->setFormat(QString("%1%").arg(m_pet->getSleep()->getValue()));
    ui->moodProgressBar->setFormat(QString("%1%").arg(m_pet->getMood()->getValue()));
    
    // Цветовая индикация будет применяться в applyPetStyle()
    
    // Иконка питомца
    PetType::StandardType petType = m_pet->getType().getType();
    QString iconPath;
    
    // Проверяем возраст: если >= 10 часов, используем большие картинки
    // Используем уже вычисленную переменную seconds
    bool useBigImage = (seconds >= 36000); // 10 часов = 36000 секунд
    
    if (petType == PetType::Dragon) {
        QString fileName = useBigImage ? "Dragon-big.jpg" : "Dragon-baby.jpg";
        iconPath = "../FantasyPets/img/" + fileName;
        QPixmap icon(iconPath);
        if (icon.isNull()) {
            iconPath = QDir::currentPath() + "/img/" + fileName;
            icon = QPixmap(iconPath);
        }
        if (!icon.isNull()) {
            int maxWidth = 250;
            QSize originalSize = icon.size();
            if (originalSize.width() > maxWidth) {
                QPixmap scaledIcon = icon.scaled(maxWidth, 10000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->petIconLabel->setPixmap(scaledIcon);
            } else {
                ui->petIconLabel->setPixmap(icon);
            }
        }
    } else if (petType == PetType::Griffin) {
        QString fileName = useBigImage ? "Griffin-big.jpg" : "Griffin-baby.jpg";
        iconPath = "../FantasyPets/img/" + fileName;
        QPixmap icon(iconPath);
        if (icon.isNull()) {
            iconPath = QDir::currentPath() + "/img/" + fileName;
            icon = QPixmap(iconPath);
        }
        if (!icon.isNull()) {
            int maxWidth = 250;
            QSize originalSize = icon.size();
            if (originalSize.width() > maxWidth) {
                QPixmap scaledIcon = icon.scaled(maxWidth, 10000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->petIconLabel->setPixmap(scaledIcon);
            } else {
                ui->petIconLabel->setPixmap(icon);
            }
        }
    } else if (petType == PetType::Unicorn) {
        QString fileName = useBigImage ? "Unicorn-big.jpg" : "Unicorn-baby.jpg";
        iconPath = "../FantasyPets/img/" + fileName;
        QPixmap icon(iconPath);
        if (icon.isNull()) {
            iconPath = QDir::currentPath() + "/img/" + fileName;
            icon = QPixmap(iconPath);
        }
        if (!icon.isNull()) {
            int maxWidth = 250;
            QSize originalSize = icon.size();
            if (originalSize.width() > maxWidth) {
                QPixmap scaledIcon = icon.scaled(maxWidth, 10000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->petIconLabel->setPixmap(scaledIcon);
            } else {
                ui->petIconLabel->setPixmap(icon);
            }
        }
    } else if (petType == PetType::Custom) {
        // Для кастомного питомца используем сохраненные пути
        QString customImagePath;
        if (useBigImage) {
            customImagePath = m_pet->getType().getBigImagePath();
        } else {
            customImagePath = m_pet->getType().getBabyImagePath();
        }
        
        QPixmap icon;
        if (!customImagePath.isEmpty()) {
            icon = QPixmap(customImagePath);
        }
        
        // Если кастомный путь не задан или не загрузился, пробуем стандартные пути
        if (icon.isNull()) {
            QString fileName = useBigImage ? "Custom-big.jpg" : "Custom-baby.jpg";
            iconPath = "../FantasyPets/img/" + fileName;
            icon = QPixmap(iconPath);
            if (icon.isNull()) {
                iconPath = QDir::currentPath() + "/img/" + fileName;
                icon = QPixmap(iconPath);
            }
        } else {
            iconPath = customImagePath;
        }
        
        if (!icon.isNull()) {
            int maxWidth = 250;
            QSize originalSize = icon.size();
            if (originalSize.width() > maxWidth) {
                QPixmap scaledIcon = icon.scaled(maxWidth, 10000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->petIconLabel->setPixmap(scaledIcon);
            } else {
                ui->petIconLabel->setPixmap(icon);
            }
        }
    } else {
        QPixmap icon = m_pet->getType().getIcon();
        if (!icon.isNull()) {
            ui->petIconLabel->setPixmap(icon.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    
    // Кнопка отмены
    ui->undoButton->setEnabled(!m_actionHistory.isEmpty());
    
    // Применяем стили в зависимости от типа питомца
    applyPetStyle();
    
    // Обновляем фон после применения стилей, чтобы он не пропадал
    updateBackground();
}

void PetManagementWindow::onFeedButtonClicked()
{
    if (!m_pet) return;
    
    FeedAction* action = new FeedAction(20, 5);
    executeAction(action);
}

void PetManagementWindow::onPlayButtonClicked()
{
    if (!m_pet) return;
    
    PlayAction* action = new PlayAction(15, 10);
    executeAction(action);
}

void PetManagementWindow::onSleepButtonClicked()
{
    if (!m_pet) return;
    
    SleepAction* action = new SleepAction(30);
    executeAction(action);
}

void PetManagementWindow::onUndoButtonClicked()
{
    if (m_actionHistory.isEmpty() || !m_pet) return;
    
    Action* lastAction = m_actionHistory.pop();
    lastAction->undo(m_pet);
    delete lastAction;
    
    updateUI();
}

void PetManagementWindow::onBackButtonClicked()
{
    emit backButtonClicked();
}

void PetManagementWindow::onRoomsButtonClicked()
{
    if (!m_pet) return;
    
    QDialog dialog(static_cast<QWidget*>(this));
    dialog.setWindowTitle("Комнаты");
    dialog.setMinimumWidth(400);
    dialog.setFixedHeight(500);
    
    // Стилизация диалога
    dialog.setStyleSheet(QString(
        "QDialog {"
        "    background-color: #1a0a2e;"
        "}"
        "QLabel {"
        "    color: #00ffff;"
        "    font-weight: bold;"
        "    font-size: 12px;"
        "}"
        "QListWidget {"
        "    background-color: #2a1a3e;"
        "    border: 2px solid #9966ff;"
        "    border-radius: 5px;"
        "    color: #ffffff;"
        "    padding: 5px;"
        "}"
        "QListWidget::item {"
        "    padding: 10px;"
        "    border-radius: 3px;"
        "    margin: 2px;"
        "    outline: none;"
        "}"
        "QListWidget::item:selected {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #9966ff, stop:1 #7744cc);"
        "    color: #000000;"
        "    font-weight: bold;"
        "    outline: none;"
        "}"
        "QListWidget::item:focus {"
        "    outline: none;"
        "}"
        "QListWidget::item:selected:focus {"
        "    outline: none;"
        "}"
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #00ffcc, stop:0.5 #00cc99, stop:1 #009966);"
        "    color: #000000;"
        "    border: 2px solid #00ffff;"
        "    border-radius: 5px;"
        "    padding: 5px 15px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #00ffff, stop:0.5 #00ffcc, stop:1 #00cc99);"
        "}"
        "QPushButton:disabled {"
        "    background: #555555;"
        "    color: #888888;"
        "    border: 2px solid #666666;"
        "}"
    ));
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->setSpacing(10);
    layout->setContentsMargins(15, 15, 15, 15);
    
    QLabel* titleLabel = new QLabel("Выберите комнату:", &dialog);
    layout->addWidget(titleLabel);
    
    QListWidget* roomsList = new QListWidget(&dialog);
    roomsList->setFocusPolicy(Qt::NoFocus); // Убираем пунктирную обводку фокуса
    
    // Добавляем базовую комнату (всегда доступна)
    QListWidgetItem* baseRoomItem = new QListWidgetItem("Базовая комната (бесплатно)", roomsList);
    baseRoomItem->setData(Qt::UserRole, 0);
    if (m_pet->getCurrentRoom() == 0) {
        baseRoomItem->setSelected(true);
    }
    roomsList->addItem(baseRoomItem);
    
    // Добавляем одну дополнительную комнату
    int roomNumber = 1;
    bool isBought = m_pet->hasRoom(roomNumber);
    int cost = 100; // Стоимость дополнительной комнаты
    
    QString roomText;
    if (isBought) {
        roomText = QString("Дополнительная комната (куплена)");
    } else {
        roomText = QString("Дополнительная комната (%1 монет)").arg(cost);
    }
    
    QListWidgetItem* roomItem = new QListWidgetItem(roomText, roomsList);
    roomItem->setData(Qt::UserRole, roomNumber);
    roomItem->setData(Qt::UserRole + 1, cost);
    roomItem->setData(Qt::UserRole + 2, isBought);
    
    if (m_pet->getCurrentRoom() == roomNumber) {
        roomItem->setSelected(true);
    }
    
    if (!isBought && m_pet->getCoins() < cost) {
        roomItem->setForeground(QBrush(QColor(150, 150, 150)));
    }
    
    roomsList->addItem(roomItem);
    
    roomsList->setCurrentRow(m_pet->getCurrentRoom());
    layout->addWidget(roomsList);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* buyButton = new QPushButton("Купить", &dialog);
    QPushButton* selectButton = new QPushButton("Выбрать", &dialog);
    QPushButton* closeButton = new QPushButton("Закрыть", &dialog);
    
    buttonLayout->addWidget(buyButton);
    buttonLayout->addWidget(selectButton);
    buttonLayout->addWidget(closeButton);
    layout->addLayout(buttonLayout);
    
    // Обновляем состояние кнопок при выборе комнаты
    auto updateButtons = [buyButton, selectButton, roomsList, this]() {
        QListWidgetItem* currentItem = roomsList->currentItem();
        if (!currentItem) return;
        
        int roomNumber = currentItem->data(Qt::UserRole).toInt();
        bool isBought = currentItem->data(Qt::UserRole + 2).toBool();
        int cost = currentItem->data(Qt::UserRole + 1).toInt();
        
        if (roomNumber == 0) {
            buyButton->setEnabled(false);
            selectButton->setEnabled(true);
        } else if (isBought) {
            buyButton->setEnabled(false);
            selectButton->setEnabled(m_pet->getCurrentRoom() != roomNumber);
        } else {
            buyButton->setEnabled(m_pet->getCoins() >= cost);
            selectButton->setEnabled(false);
        }
    };
    
    connect(roomsList, &QListWidget::currentRowChanged, updateButtons);
    updateButtons();
    
    connect(buyButton, &QPushButton::clicked, [&dialog, roomsList, this, updateButtons]() {
        QListWidgetItem* currentItem = roomsList->currentItem();
        if (!currentItem) return;
        
        int roomNumber = currentItem->data(Qt::UserRole).toInt();
        int cost = currentItem->data(Qt::UserRole + 1).toInt();
        bool isBought = currentItem->data(Qt::UserRole + 2).toBool();
        
        if (roomNumber == 0 || isBought) return;
        
        if (m_pet->buyRoom(roomNumber, cost)) {
            currentItem->setText("Дополнительная комната (куплена)");
            currentItem->setData(Qt::UserRole + 2, true);
            currentItem->setForeground(QBrush(QColor(255, 255, 255)));
            updateButtons();
            updateUI();
            QMessageBox::information(&dialog, "Успех", "Дополнительная комната успешно куплена!");
        } else {
            QMessageBox::warning(&dialog, "Ошибка", "Недостаточно монет для покупки этой комнаты!");
        }
    });
    
    connect(selectButton, &QPushButton::clicked, [&dialog, roomsList, this]() {
        QListWidgetItem* currentItem = roomsList->currentItem();
        if (!currentItem) return;
        
        int roomNumber = currentItem->data(Qt::UserRole).toInt();
        bool isBought = currentItem->data(Qt::UserRole + 2).toBool();
        
        if (roomNumber == 0 || isBought) {
            m_pet->setCurrentRoom(roomNumber);
            updateBackground();
            QString roomName = (roomNumber == 0) ? "базовая" : "дополнительная";
            QMessageBox::information(&dialog, "Успех", QString("%1 комната выбрана!").arg(roomName));
            dialog.accept();
        }
    });
    
    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    
    dialog.exec();
}

void PetManagementWindow::executeAction(Action* action)
{
    if (!action || !m_pet) {
        delete action;
        return;
    }
    
    if (action->execute(m_pet)) {
        m_actionHistory.push(action);
        updateUI();
        // Ограничиваем размер истории (максимум 10 действий)
        if (m_actionHistory.size() > 10) {
            Action* oldAction = m_actionHistory.first();
            m_actionHistory.removeFirst();
            delete oldAction;
        }
    } else {
        QString errorMsg = QString("Не удалось выполнить действие: %1").arg(action->getDescription());
        if (action->getCost() > 0 && m_pet->getCoins() < action->getCost()) {
            errorMsg += QString("\nНедостаточно монет! Нужно: %1, есть: %2").arg(action->getCost()).arg(m_pet->getCoins());
        }
        QMessageBox::warning(static_cast<QWidget*>(this), "Ошибка", errorMsg);
        delete action;
    }
}

void PetManagementWindow::updateBackground()
{
    if (!m_pet) return;
    
    QWidget* centralWidget = this->centralWidget();
    if (!centralWidget) return;
    
    QSize widgetSize = centralWidget->size();
    if (widgetSize.width() <= 0 || widgetSize.height() <= 0) {
        return; // Размер еще не установлен
    }
    
    PetType::StandardType petType = m_pet->getType().getType();
    int currentRoom = m_pet->getCurrentRoom();
    
    // Определяем путь к фону в зависимости от типа питомца и выбранной комнаты
    QString backgroundFileName;
    if (currentRoom > 0) {
        // Используем дополнительную комнату
        switch (petType) {
            case PetType::Dragon:
                backgroundFileName = "dragon-back1-dop.jpg";
                break;
            case PetType::Griffin:
                backgroundFileName = "griffin-back1-dop.jpg";
                break;
            case PetType::Unicorn:
                backgroundFileName = "unicorn-back1-dop.jpg";
                break;
            case PetType::Custom:
            default:
                backgroundFileName = "custom-back1-dop.jpg";
                break;
        }
    } else {
        // Используем базовую комнату
        switch (petType) {
            case PetType::Dragon:
                backgroundFileName = "dragon-back.jpg";
                break;
            case PetType::Griffin:
                backgroundFileName = "griffin-back.jpg";
                break;
            case PetType::Unicorn:
                backgroundFileName = "unicorn-back.jpg";
                break;
            case PetType::Custom:
            default:
                backgroundFileName = "custom-back.jpg";
                break;
        }
    }
    
    // Загружаем исходное изображение только если изменился тип питомца, комната или оно еще не загружено
    if (m_cachedBackground.isNull() || m_lastPetType != petType || m_lastRoomNumber != currentRoom) {
        QString backgroundPath = "../FantasyPets/img/" + backgroundFileName;
        m_cachedBackground = QPixmap(backgroundPath);
        
        if (m_cachedBackground.isNull()) {
            backgroundPath = QDir::currentPath() + "/img/" + backgroundFileName;
            m_cachedBackground = QPixmap(backgroundPath);
        }
        
        // Если дополнительная комната не найдена, используем базовую
        if (m_cachedBackground.isNull() && currentRoom > 0) {
            switch (petType) {
                case PetType::Dragon:
                    backgroundFileName = "dragon-back.jpg";
                    break;
                case PetType::Griffin:
                    backgroundFileName = "griffin-back.jpg";
                    break;
                case PetType::Unicorn:
                    backgroundFileName = "unicorn-back.jpg";
                    break;
                case PetType::Custom:
                default:
                    backgroundFileName = "custom-back.jpg";
                    break;
            }
            backgroundPath = "../FantasyPets/img/" + backgroundFileName;
            m_cachedBackground = QPixmap(backgroundPath);
            if (m_cachedBackground.isNull()) {
                backgroundPath = QDir::currentPath() + "/img/" + backgroundFileName;
                m_cachedBackground = QPixmap(backgroundPath);
            }
        }
        
        m_lastPetType = petType;
        m_lastRoomNumber = currentRoom;
        m_scaledBackground = QPixmap(); // Сбрасываем кэш масштабированного изображения
        m_lastBackgroundSize = QSize(0, 0); // Сбрасываем размер для принудительного пересчета
    }
    
    if (!m_cachedBackground.isNull()) {
        // Масштабируем только если изменился размер виджета или тип питомца
        if (m_lastBackgroundSize != widgetSize || m_scaledBackground.isNull()) {
            m_scaledBackground = m_cachedBackground.scaled(widgetSize, Qt::IgnoreAspectRatio, Qt::FastTransformation);
            m_lastBackgroundSize = widgetSize;
        }
        
        // Устанавливаем фон через палитру
        QPalette palette = centralWidget->palette();
        palette.setBrush(QPalette::Window, QBrush(m_scaledBackground));
        centralWidget->setPalette(palette);
        centralWidget->setAutoFillBackground(true);
    }
}

void PetManagementWindow::applyPetStyle()
{
    if (!m_pet) return;
    
    PetType::StandardType petType = m_pet->getType().getType();
    
    if (petType == PetType::Dragon) {
        // Огненная тема для дракона
        QString dragonStyle = QString(
            // Общий стиль для меток (контрастные цвета с оранжевым)
            "QLabel {"
            "    color: #ffffff;"
            "    font-weight: bold;"
            "    background: transparent;"
            "}"
            "QLabel#petNameLabel {"
            "    color: #ffffff;"
            "    font-size: 32px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.8);"
            "    padding: 8px 20px;"
            "    border-radius: 12px;"
            "    border: 3px solid #ff8c42;"
            "}"
            "QLabel#petTypeLabel {"
            "    color: #ffffff;"
            "    font-size: 18px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#ageLabel {"
            "    color: #ffffff;"
            "    font-size: 20px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.8);"
            "    padding: 5px 15px;"
            "    border-radius: 10px;"
            "    border: 3px solid #ffaa66;"
            "}"
            "QLabel#coinsLabel {"
            "    color: #ffffff;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            // Подписи для прогресс-баров (длинные и тонкие)
            "QLabel#hungerLabel, QLabel#sleepLabel, QLabel#moodLabel, QLabel#healthLabel {"
            "    color: #ffffff;"
            "    font-weight: 900;"
            "    font-size: 14px;"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a90e2, stop:0.5 #357abd, stop:1 #2a5f8f);"
            "    padding: 2px 20px;"
            "    border-radius: 5px;"
            "    border: 3px solid #5ba3f5;"
            "    min-width: 120px;"
            "    max-width: 120px;"
            "}"
            // Подписи для кнопок
            "QLabel#feedButtonLabel, QLabel#playButtonLabel, QLabel#sleepButtonLabel, QLabel#undoButtonLabel {"
            "    color: #ffffff;"
            "    font-weight: 900;"
            "    font-size: 12px;"
            "    background-color: rgba(0, 0, 0, 0.4);"
            "    padding: 2px 20px;"
            "    border-radius: 3px;"
            "    border: 2px solid #ff4500;"
            "    min-width: 120px;"
            "    max-width: 120px;"
            "}"
            // Прогресс-бары как обводка кнопок с процентами внутри
            "QProgressBar {"
            "    border: none;"
            "    border-radius: 30px;"
            "    text-align: center;"
            "    font-weight: 900;"
            "    font-size: 24px;"
            "    color: #ffffff;"
            "    background-color: transparent;"
            "    min-width: 160px;"
            "    min-height: 60px;"
            "    max-width: 160px;"
            "    max-height: 60px;"
            "}"
            "QProgressBar::chunk {"
            "    background: transparent;"
            "}"
            // Рамка для картинки
            "QFrame#petImageFrame {"
            "    border: 5px solid #ff4500;"
            "    border-radius: 15px;"
            "    background-color: rgba(26, 10, 46, 0.3);"
            "}"
            // Имя и возраст поверх картинки
            "QLabel#petNameLabel {"
            "    color: #ff4500;"
            "    font-size: 32px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 5px 15px;"
            "    border-radius: 10px;"
            "}"
            "QLabel#ageLabel {"
            "    color: #ffaa66;"
            "    font-size: 20px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 8px;"
            "}"
            // Увеличенные круглые кнопки с огненной темой
            "QPushButton#feedButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ff8c5a, stop:0.5 #ff6b3d, stop:1 #e55a2b);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#feedButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffa070, stop:0.5 #ff8c5a, stop:1 #ff6b3d);"
            "}"
            "QPushButton#feedButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #e55a2b, stop:0.5 #cc4a1f, stop:1 #b33a13);"
            "}"
            "QPushButton#playButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffb380, stop:0.5 #ff9966, stop:1 #ff7f4d);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#playButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffcc99, stop:0.5 #ffb380, stop:1 #ff9966);"
            "}"
            "QPushButton#playButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ff7f4d, stop:0.5 #ff6b3d, stop:1 #e55a2b);"
            "}"
            "QPushButton#sleepButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #d9771a, stop:0.5 #b86515, stop:1 #995310);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#sleepButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ff9933, stop:0.5 #d9771a, stop:1 #b86515);"
            "}"
            "QPushButton#sleepButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #995310, stop:0.5 #7a420c, stop:1 #5b3109);"
            "}"
            "QPushButton#undoButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #7a7a7a, stop:0.5 #666666, stop:1 #525252);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#undoButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8e8e8e, stop:0.5 #7a7a7a, stop:1 #666666);"
            "    border: 3px solid #aaaaaa;"
            "}"
            "QPushButton#undoButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #525252, stop:0.5 #3d3d3d, stop:1 #292929);"
            "}"
            "QPushButton#undoButton:disabled {"
            "    background: #333333;"
            "    color: #666666;"
            "    border: 3px solid #444444;"
            "}"
            "QPushButton#backButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8b4513, stop:0.5 #654321, stop:1 #4a2c1a);"
            "    color: #ffffff;"
            "    border: 3px solid #a0522d;"
            "    border-radius: 10px;"
            "    padding: 10px 25px;"
            "    font-weight: bold;"
            "    font-size: 14px;"
            "    min-width: 120px;"
            "    min-height: 40px;"
            "    max-width: 150px;"
            "    max-height: 45px;"
            "}"
            "QPushButton#backButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #a0522d, stop:0.5 #8b4513, stop:1 #654321);"
            "    border: 3px solid #cd853f;"
            "}"
            "QPushButton#backButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a2c1a, stop:0.5 #3d2414, stop:1 #2d1a0f);"
            "}"
        );
        
        this->setStyleSheet(dragonStyle);
        
        // Добавляем обводку для текста кнопок
        auto addTextOutline = [](QPushButton* button) {
            QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(button);
            shadow->setBlurRadius(3);
            shadow->setXOffset(0);
            shadow->setYOffset(0);
            shadow->setColor(QColor(0, 0, 0, 200));
            button->setGraphicsEffect(shadow);
        };
        
        addTextOutline(ui->feedButton);
        addTextOutline(ui->playButton);
        addTextOutline(ui->sleepButton);
        addTextOutline(ui->undoButton);
        
        // Обновляем цвета прогресс-баров в зависимости от значений
        auto setDragonProgressBarColor = [](QProgressBar* bar, int value) {
            QString chunkStyle;
            QString borderColor;
            if (value < 20) {
                borderColor = "#990000";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #cc0000, stop:0.5 #ff0000, stop:1 #ff3333);"
                            "    border-radius: 28px;"
                            "}";
            } else if (value < 50) {
                borderColor = "#cc4400";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ff6600, stop:0.5 #ff8800, stop:1 #ffaa00);"
                            "    border-radius: 28px;"
                            "}";
            } else {
                borderColor = "#cc3300";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ff6b35, stop:0.5 #ff8c42, stop:1 #ffaa66);"
                            "    border-radius: 28px;"
                            "}";
            }
            QString barStyle = QString("QProgressBar { background-color: %1; border: 2px solid %1; padding: 2px; }").arg(borderColor);
            bar->setStyleSheet(bar->styleSheet() + barStyle + chunkStyle);
        };
        
        setDragonProgressBarColor(ui->hungerProgressBar, m_pet->getHunger()->getValue());
        setDragonProgressBarColor(ui->sleepProgressBar, m_pet->getSleep()->getValue());
        setDragonProgressBarColor(ui->moodProgressBar, m_pet->getMood()->getValue());
        setDragonProgressBarColor(ui->healthProgressBar, m_pet->getHealth()->getValue());
    } else if (petType == PetType::Griffin) {
        // Золотая тема для гриффона
        QString griffinStyle = QString(
            "QLabel {"
            "    color: #ffffff;"
            "    font-weight: bold;"
            "    background: transparent;"
            "}"
            "QLabel#petNameLabel {"
            "    color: #ffd700;"
            "    font-size: 32px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 5px 15px;"
            "    border-radius: 10px;"
            "    border: 3px solid #ffd700;"
            "}"
            "QLabel#petTypeLabel {"
            "    color: #ffffff;"
            "    font-size: 18px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#ageLabel {"
            "    color: #ffed4e;"
            "    font-size: 20px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 8px;"
            "    border: 3px solid #ffd700;"
            "}"
            "QLabel#coinsLabel {"
            "    color: #ffffff;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#hungerLabel, QLabel#sleepLabel, QLabel#moodLabel, QLabel#healthLabel {"
            "    color: #ffffff;"
            "    font-weight: 900;"
            "    font-size: 14px;"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a90e2, stop:0.5 #357abd, stop:1 #2a5f8f);"
            "    padding: 2px 20px;"
            "    border-radius: 5px;"
            "    border: 3px solid #5ba3f5;"
            "    min-width: 120px;"
            "    max-width: 120px;"
            "}"
            "QProgressBar {"
            "    border: none;"
            "    border-radius: 30px;"
            "    text-align: center;"
            "    font-weight: 900;"
            "    font-size: 24px;"
            "    color: #ffffff;"
            "    background-color: transparent;"
            "    min-width: 160px;"
            "    min-height: 60px;"
            "    max-width: 160px;"
            "    max-height: 60px;"
            "}"
            "QProgressBar::chunk {"
            "    background: transparent;"
            "}"
            "QFrame#petImageFrame {"
            "    border: 5px solid #ffd700;"
            "    border-radius: 15px;"
            "    background-color: rgba(26, 10, 46, 0.3);"
            "}"
            "QPushButton#feedButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffd700, stop:0.5 #ffb300, stop:1 #cc8f00);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#feedButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffed4e, stop:0.5 #ffd700, stop:1 #ffb300);"
            "}"
            "QPushButton#feedButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #cc8f00, stop:0.5 #b37f00, stop:1 #996f00);"
            "}"
            "QPushButton#playButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffb84d, stop:0.5 #ffa500, stop:1 #cc8400);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#playButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffcc66, stop:0.5 #ffb84d, stop:1 #ffa500);"
            "}"
            "QPushButton#playButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #cc8400, stop:0.5 #b37400, stop:1 #996400);"
            "}"
            "QPushButton#sleepButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #d4af37, stop:0.5 #b8941f, stop:1 #9a7a0f);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#sleepButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #e6c547, stop:0.5 #d4af37, stop:1 #b8941f);"
            "}"
            "QPushButton#sleepButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #9a7a0f, stop:0.5 #7a5f0a, stop:1 #5a4507);"
            "}"
            "QPushButton#undoButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #7a7a7a, stop:0.5 #666666, stop:1 #525252);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#undoButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8e8e8e, stop:0.5 #7a7a7a, stop:1 #666666);"
            "    border: 3px solid #aaaaaa;"
            "}"
            "QPushButton#undoButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #525252, stop:0.5 #3d3d3d, stop:1 #292929);"
            "}"
            "QPushButton#undoButton:disabled {"
            "    background: #333333;"
            "    color: #666666;"
            "    border: 3px solid #444444;"
            "}"
            "QPushButton#backButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8b4513, stop:0.5 #654321, stop:1 #4a2c1a);"
            "    color: #ffffff;"
            "    border: 3px solid #a0522d;"
            "    border-radius: 10px;"
            "    padding: 10px 25px;"
            "    font-weight: bold;"
            "    font-size: 14px;"
            "    min-width: 120px;"
            "    min-height: 40px;"
            "    max-width: 150px;"
            "    max-height: 45px;"
            "}"
            "QPushButton#backButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #a0522d, stop:0.5 #8b4513, stop:1 #654321);"
            "    border: 3px solid #cd853f;"
            "}"
            "QPushButton#backButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a2c1a, stop:0.5 #3d2414, stop:1 #2d1a0f);"
            "}"
        );
        
        this->setStyleSheet(griffinStyle);
        
        // Добавляем обводку для текста кнопок
        auto addTextOutline = [](QPushButton* button) {
            QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(button);
            shadow->setBlurRadius(3);
            shadow->setXOffset(0);
            shadow->setYOffset(0);
            shadow->setColor(QColor(0, 0, 0, 200));
            button->setGraphicsEffect(shadow);
        };
        
        addTextOutline(ui->feedButton);
        addTextOutline(ui->playButton);
        addTextOutline(ui->sleepButton);
        addTextOutline(ui->undoButton);
        
        // Обновляем цвета прогресс-баров для гриффона
        auto setGriffinProgressBarColor = [](QProgressBar* bar, int value) {
            QString chunkStyle;
            QString borderColor;
            if (value < 20) {
                borderColor = "#990000";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #cc0000, stop:0.5 #ff0000, stop:1 #ff3333);"
                            "    border-radius: 28px;"
                            "}";
            } else if (value < 50) {
                borderColor = "#cc7700";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ff9900, stop:0.5 #ffaa00, stop:1 #ffbb00);"
                            "    border-radius: 28px;"
                            "}";
            } else {
                borderColor = "#cc9900";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ffd700, stop:0.5 #ffed4e, stop:1 #ffff66);"
                            "    border-radius: 28px;"
                            "}";
            }
            QString barStyle = QString("QProgressBar { background-color: %1; border: 2px solid %1; padding: 2px; }").arg(borderColor);
            bar->setStyleSheet(bar->styleSheet() + barStyle + chunkStyle);
        };
        
        setGriffinProgressBarColor(ui->hungerProgressBar, m_pet->getHunger()->getValue());
        setGriffinProgressBarColor(ui->sleepProgressBar, m_pet->getSleep()->getValue());
        setGriffinProgressBarColor(ui->moodProgressBar, m_pet->getMood()->getValue());
        setGriffinProgressBarColor(ui->healthProgressBar, m_pet->getHealth()->getValue());
    } else if (petType == PetType::Unicorn) {
        // Магическая тема для единорога
        QString unicornStyle = QString(
            "QLabel {"
            "    color: #ffffff;"
            "    font-weight: bold;"
            "    background: transparent;"
            "}"
            "QLabel#petNameLabel {"
            "    color: #dda0dd;"
            "    font-size: 32px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 5px 15px;"
            "    border-radius: 10px;"
            "    border: 3px solid #ba55d3;"
            "}"
            "QLabel#petTypeLabel {"
            "    color: #ffffff;"
            "    font-size: 18px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#ageLabel {"
            "    color: #ffb6c1;"
            "    font-size: 20px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 8px;"
            "    border: 3px solid #dda0dd;"
            "}"
            "QLabel#coinsLabel {"
            "    color: #ffffff;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#hungerLabel, QLabel#sleepLabel, QLabel#moodLabel, QLabel#healthLabel {"
            "    color: #ffffff;"
            "    font-weight: 900;"
            "    font-size: 14px;"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a90e2, stop:0.5 #357abd, stop:1 #2a5f8f);"
            "    padding: 2px 20px;"
            "    border-radius: 5px;"
            "    border: 3px solid #5ba3f5;"
            "    min-width: 120px;"
            "    max-width: 120px;"
            "}"
            "QProgressBar {"
            "    border: none;"
            "    border-radius: 30px;"
            "    text-align: center;"
            "    font-weight: 900;"
            "    font-size: 24px;"
            "    color: #ffffff;"
            "    background-color: transparent;"
            "    min-width: 160px;"
            "    min-height: 60px;"
            "    max-width: 160px;"
            "    max-height: 60px;"
            "}"
            "QProgressBar::chunk {"
            "    background: transparent;"
            "}"
            "QFrame#petImageFrame {"
            "    border: 5px solid #ba55d3;"
            "    border-radius: 15px;"
            "    background-color: rgba(26, 10, 46, 0.3);"
            "}"
            "QPushButton#feedButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #dda0dd, stop:0.5 #ba55d3, stop:1 #9370db);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#feedButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #e6b3e6, stop:0.5 #dda0dd, stop:1 #ba55d3);"
            "}"
            "QPushButton#feedButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #9370db, stop:0.5 #7b5fb3, stop:1 #634d8b);"
            "}"
            "QPushButton#playButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffb6c1, stop:0.5 #ff91a4, stop:1 #cc7285);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#playButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffc0cb, stop:0.5 #ffb6c1, stop:1 #ff91a4);"
            "}"
            "QPushButton#playButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #cc7285, stop:0.5 #b35a6a, stop:1 #994250);"
            "}"
            "QPushButton#sleepButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #b19cd9, stop:0.5 #9370db, stop:1 #7b5fb3);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#sleepButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #c4a8e3, stop:0.5 #b19cd9, stop:1 #9370db);"
            "}"
            "QPushButton#sleepButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #7b5fb3, stop:0.5 #634d8b, stop:1 #4a3a66);"
            "}"
            "QPushButton#undoButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #7a7a7a, stop:0.5 #666666, stop:1 #525252);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#undoButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8e8e8e, stop:0.5 #7a7a7a, stop:1 #666666);"
            "    border: 3px solid #aaaaaa;"
            "}"
            "QPushButton#undoButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #525252, stop:0.5 #3d3d3d, stop:1 #292929);"
            "}"
            "QPushButton#undoButton:disabled {"
            "    background: #333333;"
            "    color: #666666;"
            "    border: 3px solid #444444;"
            "}"
            "QPushButton#backButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8b4513, stop:0.5 #654321, stop:1 #4a2c1a);"
            "    color: #ffffff;"
            "    border: 3px solid #a0522d;"
            "    border-radius: 10px;"
            "    padding: 10px 25px;"
            "    font-weight: bold;"
            "    font-size: 14px;"
            "    min-width: 120px;"
            "    min-height: 40px;"
            "    max-width: 150px;"
            "    max-height: 45px;"
            "}"
            "QPushButton#backButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #a0522d, stop:0.5 #8b4513, stop:1 #654321);"
            "    border: 3px solid #cd853f;"
            "}"
            "QPushButton#backButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a2c1a, stop:0.5 #3d2414, stop:1 #2d1a0f);"
            "}"
        );
        
        this->setStyleSheet(unicornStyle);
        
        // Добавляем обводку для текста кнопок
        auto addTextOutline = [](QPushButton* button) {
            QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(button);
            shadow->setBlurRadius(3);
            shadow->setXOffset(0);
            shadow->setYOffset(0);
            shadow->setColor(QColor(0, 0, 0, 200));
            button->setGraphicsEffect(shadow);
        };
        
        addTextOutline(ui->feedButton);
        addTextOutline(ui->playButton);
        addTextOutline(ui->sleepButton);
        addTextOutline(ui->undoButton);
        
        // Обновляем цвета прогресс-баров для единорога
        auto setUnicornProgressBarColor = [](QProgressBar* bar, int value) {
            QString chunkStyle;
            QString borderColor;
            if (value < 20) {
                borderColor = "#990000";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #cc0000, stop:0.5 #ff0000, stop:1 #ff3333);"
                            "    border-radius: 28px;"
                            "}";
            } else if (value < 50) {
                borderColor = "#cc4a7a";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ff69b4, stop:0.5 #ff91a4, stop:1 #ffb6c1);"
                            "    border-radius: 28px;"
                            "}";
            } else {
                borderColor = "#8b3fa3";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ba55d3, stop:0.5 #dda0dd, stop:1 #e6b3e6);"
                            "    border-radius: 28px;"
                            "}";
            }
            QString barStyle = QString("QProgressBar { background-color: %1; border: 2px solid %1; padding: 2px; }").arg(borderColor);
            bar->setStyleSheet(bar->styleSheet() + barStyle + chunkStyle);
        };
        
        setUnicornProgressBarColor(ui->hungerProgressBar, m_pet->getHunger()->getValue());
        setUnicornProgressBarColor(ui->sleepProgressBar, m_pet->getSleep()->getValue());
        setUnicornProgressBarColor(ui->moodProgressBar, m_pet->getMood()->getValue());
        setUnicornProgressBarColor(ui->healthProgressBar, m_pet->getHealth()->getValue());
    } else if (petType == PetType::Custom) {
        // Тропическая тема для кастомного персонажа
        QString customStyle = QString(
            "QLabel {"
            "    color: #ffffff;"
            "    font-weight: bold;"
            "    background: transparent;"
            "}"
            "QLabel#petNameLabel {"
            "    color: #ffd700;"
            "    font-size: 32px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 5px 15px;"
            "    border-radius: 10px;"
            "    border: 3px solid #40e0d0;"
            "}"
            "QLabel#petTypeLabel {"
            "    color: #ffffff;"
            "    font-size: 18px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#ageLabel {"
            "    color: #ffe4b5;"
            "    font-size: 20px;"
            "    font-weight: 900;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 8px;"
            "    border: 3px solid #ffd700;"
            "}"
            "QLabel#coinsLabel {"
            "    color: #ffffff;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "    background-color: rgba(0, 0, 0, 0.6);"
            "    padding: 3px 10px;"
            "    border-radius: 5px;"
            "}"
            "QLabel#hungerLabel, QLabel#sleepLabel, QLabel#moodLabel, QLabel#healthLabel {"
            "    color: #ffffff;"
            "    font-weight: 900;"
            "    font-size: 14px;"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a90e2, stop:0.5 #357abd, stop:1 #2a5f8f);"
            "    padding: 2px 20px;"
            "    border-radius: 5px;"
            "    border: 3px solid #5ba3f5;"
            "    min-width: 120px;"
            "    max-width: 120px;"
            "}"
            "QProgressBar {"
            "    border: none;"
            "    border-radius: 30px;"
            "    text-align: center;"
            "    font-weight: 900;"
            "    font-size: 24px;"
            "    color: #ffffff;"
            "    background-color: transparent;"
            "    min-width: 160px;"
            "    min-height: 60px;"
            "    max-width: 160px;"
            "    max-height: 60px;"
            "}"
            "QProgressBar::chunk {"
            "    background: transparent;"
            "}"
            "QFrame#petImageFrame {"
            "    border: 5px solid #40e0d0;"
            "    border-radius: 15px;"
            "    background-color: rgba(26, 10, 46, 0.3);"
            "}"
            "QPushButton#feedButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #40e0d0, stop:0.5 #20b2aa, stop:1 #008b8b);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#feedButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #60f0f0, stop:0.5 #40e0d0, stop:1 #20b2aa);"
            "}"
            "QPushButton#feedButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #008b8b, stop:0.5 #006b6b, stop:1 #004b4b);"
            "}"
            "QPushButton#playButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffd700, stop:0.5 #ffa500, stop:1 #ff8c00);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#playButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffed4e, stop:0.5 #ffd700, stop:1 #ffa500);"
            "}"
            "QPushButton#playButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ff8c00, stop:0.5 #cc7000, stop:1 #995400);"
            "}"
            "QPushButton#sleepButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #ffe4b5, stop:0.5 #f5deb3, stop:1 #deb887);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#sleepButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #fff4e0, stop:0.5 #ffe4b5, stop:1 #f5deb3);"
            "}"
            "QPushButton#sleepButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #deb887, stop:0.5 #c9a66b, stop:1 #b0884f);"
            "}"
            "QPushButton#undoButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #7a7a7a, stop:0.5 #666666, stop:1 #525252);"
            "    color: #ffffff;"
            "    border: none;"
            "    border-radius: 50px;"
            "    font-weight: 900;"
            "    font-size: 18px;"
            "    min-width: 100px;"
            "    min-height: 100px;"
            "    max-width: 100px;"
            "    max-height: 100px;"
            "    text-align: center;"
            "}"
            "QPushButton#undoButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8e8e8e, stop:0.5 #7a7a7a, stop:1 #666666);"
            "    border: 3px solid #aaaaaa;"
            "}"
            "QPushButton#undoButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #525252, stop:0.5 #3d3d3d, stop:1 #292929);"
            "}"
            "QPushButton#undoButton:disabled {"
            "    background: #333333;"
            "    color: #666666;"
            "    border: 3px solid #444444;"
            "}"
            "QPushButton#backButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #8b4513, stop:0.5 #654321, stop:1 #4a2c1a);"
            "    color: #ffffff;"
            "    border: 3px solid #a0522d;"
            "    border-radius: 10px;"
            "    padding: 10px 25px;"
            "    font-weight: bold;"
            "    font-size: 14px;"
            "    min-width: 120px;"
            "    min-height: 40px;"
            "    max-width: 150px;"
            "    max-height: 45px;"
            "}"
            "QPushButton#backButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #a0522d, stop:0.5 #8b4513, stop:1 #654321);"
            "    border: 3px solid #cd853f;"
            "}"
            "QPushButton#backButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #4a2c1a, stop:0.5 #3d2414, stop:1 #2d1a0f);"
            "}"
        );
        
        this->setStyleSheet(customStyle);
        
        // Добавляем обводку для текста кнопок
        auto addTextOutline = [](QPushButton* button) {
            QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(button);
            shadow->setBlurRadius(3);
            shadow->setXOffset(0);
            shadow->setYOffset(0);
            shadow->setColor(QColor(0, 0, 0, 200));
            button->setGraphicsEffect(shadow);
        };
        
        addTextOutline(ui->feedButton);
        addTextOutline(ui->playButton);
        addTextOutline(ui->sleepButton);
        addTextOutline(ui->undoButton);
        
        // Обновляем цвета прогресс-баров для кастомного персонажа
        auto setCustomProgressBarColor = [](QProgressBar* bar, int value) {
            QString chunkStyle;
            QString borderColor;
            if (value < 20) {
                borderColor = "#990000";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #cc0000, stop:0.5 #ff0000, stop:1 #ff3333);"
                            "    border-radius: 28px;"
                            "}";
            } else if (value < 50) {
                borderColor = "#cc8844";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #ffa07a, stop:0.5 #ffb6c1, stop:1 #ffe4b5);"
                            "    border-radius: 28px;"
                            "}";
            } else {
                borderColor = "#20a2aa";
                chunkStyle = "QProgressBar::chunk {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "        stop:0 #40e0d0, stop:0.5 #87ceeb, stop:1 #add8e6);"
                            "    border-radius: 28px;"
                            "}";
            }
            QString barStyle = QString("QProgressBar { background-color: %1; border: 2px solid %1; padding: 2px; }").arg(borderColor);
            bar->setStyleSheet(bar->styleSheet() + barStyle + chunkStyle);
        };
        
        setCustomProgressBarColor(ui->hungerProgressBar, m_pet->getHunger()->getValue());
        setCustomProgressBarColor(ui->sleepProgressBar, m_pet->getSleep()->getValue());
        setCustomProgressBarColor(ui->moodProgressBar, m_pet->getMood()->getValue());
        setCustomProgressBarColor(ui->healthProgressBar, m_pet->getHealth()->getValue());
    }
}

void PetManagementWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

