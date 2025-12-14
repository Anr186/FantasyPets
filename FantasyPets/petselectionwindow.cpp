#include "petselectionwindow.h"
#include "ui_petselectionwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QScrollArea>
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include <QDateTime>
#include <QMouseEvent>
#include <QFrame>
#include <QPalette>
#include <QDir>
#include <QResizeEvent>
#include <QListWidget>
#include <QSpinBox>
#include <QFileDialog>
PetSelectionWindow::PetSelectionWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PetSelectionWindow)
    , m_user(nullptr)
    , m_selectedPet(nullptr)
{
    ui->setupUi(this);
    
    connect(ui->selectButton, &QPushButton::clicked, this, &PetSelectionWindow::onSelectButtonClicked);
    connect(ui->newPetButton, &QPushButton::clicked, this, &PetSelectionWindow::onNewPetButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &PetSelectionWindow::onBackButtonClicked);
    connect(ui->deletePetButton, &QPushButton::clicked, this, &PetSelectionWindow::onDeletePetButtonClicked);
    
    setupStandardPets();
    onPetListSelectionChanged();
    
    updateBackground();
}

PetSelectionWindow::~PetSelectionWindow()
{
    delete ui;
}

void PetSelectionWindow::setUser(User* user)
{
    m_user = user;
    updatePetList();
}

void PetSelectionWindow::updatePetList()
{
    clearPetCards();
    if (m_user) {
        QWidget* container = ui->petScrollArea->widget();
        if (container) {
            QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(container->layout());
            if (layout) {
                for (Pet* pet : m_user->getPets()) {
                    QWidget* card = createPetCard(pet);
                    layout->addWidget(card);
                    m_petCards.append(card);
                }
            }
        }
    }
    onPetListSelectionChanged();
}

void PetSelectionWindow::clearPetCards()
{
    QWidget* container = ui->petScrollArea->widget();
    if (container) {
        QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(container->layout());
        if (layout) {
            while (layout->count() > 0) {
                QLayoutItem* item = layout->takeAt(0);
                if (item->widget()) {
                    item->widget()->deleteLater();
                }
                delete item;
            }
        }
    }
    m_petCards.clear();
    m_selectedPet = nullptr;
}

QWidget* PetSelectionWindow::createPetCard(Pet* pet)
{
    QWidget* container = ui->petScrollArea->widget();
    QFrame* card = new QFrame(container);
    card->setFixedSize(150, 200);
    card->setFrameShape(QFrame::Box);
    card->setLineWidth(2);
    card->setStyleSheet(QString(
        "QFrame {"
        "    background-color: rgba(240, 250, 230, 0.9);"
        "    border: 2px solid #4a7c2a;"
        "    border-radius: 10px;"
        "}"
        "QFrame:hover {"
        "    border: 3px solid #2d5016;"
        "    background-color: rgba(240, 250, 230, 1.0);"
        "}"
    ));
    card->setCursor(Qt::PointingHandCursor);
    
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(0, 0, 0, 0);
    cardLayout->setSpacing(0);
    
    // Область с изображением (фон)
    QLabel* imageLabel = new QLabel(card);
    imageLabel->setFixedHeight(150);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setScaledContents(true);
    
    // Загружаем изображение фона для карточки по типу животного
    QString typeName;
    PetType::StandardType type = pet->getType().getType();
    switch (type) {
        case PetType::Dragon:
            typeName = "Dragon";
            break;
        case PetType::Griffin:
            typeName = "Griffin";
            break;
        case PetType::Unicorn:
            typeName = "Unicorn";
            break;
        case PetType::Custom:
            typeName = "Custom";
            break;
    }
    
    // Проверяем возраст: если >= 10 часов, используем большие картинки
    QDateTime birthDate = pet->getBirthDate();
    qint64 ageInSeconds = birthDate.secsTo(QDateTime::currentDateTime());
    bool useBigImage = (ageInSeconds >= 36000); // 2 часа = 7200 секунд
    
    QString imagePath;
    QPixmap backgroundImage;
    
    // Для кастомного питомца используем сохраненные пути
    if (type == PetType::Custom) {
        if (useBigImage) {
            imagePath = pet->getType().getBigAvaPath();
        } else {
            imagePath = pet->getType().getBabyAvaPath();
        }
        if (!imagePath.isEmpty()) {
            backgroundImage = QPixmap(imagePath);
        }
    }
    
    // Если изображение не загружено (не кастомный или путь пустой), используем стандартные пути
    if (backgroundImage.isNull()) {
        QString fileName;
        if (useBigImage) {
            // Для больших картинок используем формат Type-big-ava.jpg
            if (type == PetType::Dragon) {
                fileName = "Dragon-big-ava.jpg";
            } else {
                fileName = typeName + "-big-ava.jpg";
            }
        } else {
            fileName = typeName + "-ava.jpg";
        }
        imagePath = "../FantasyPets/img/" + fileName;
        backgroundImage = QPixmap(imagePath);
        
        if (backgroundImage.isNull()) {
            // Пробуем альтернативный путь
            imagePath = QDir::currentPath() + "/img/" + fileName;
            backgroundImage = QPixmap(imagePath);
        }
    }
    
    if (backgroundImage.isNull()) {
        // Если изображение не найдено, используем иконку питомца
        QPixmap petIcon = pet->getType().getIcon();
        if (!petIcon.isNull()) {
            QPixmap scaledIcon = petIcon.scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            
            // Создаем фон для карточки
            QPixmap background(150, 150);
            background.fill(QColor(200, 220, 180));
            
            QPainter painter(&background);
            painter.setRenderHint(QPainter::Antialiasing);
            
            // Рисуем градиентный фон
            QLinearGradient gradient(0, 0, 0, 150);
            gradient.setColorAt(0, QColor(220, 240, 200));
            gradient.setColorAt(1, QColor(180, 200, 160));
            painter.fillRect(background.rect(), gradient);
            
            // Рисуем иконку по центру
            int x = (150 - scaledIcon.width()) / 2;
            int y = (150 - scaledIcon.height()) / 2;
            painter.drawPixmap(x, y, scaledIcon);
            
            imageLabel->setPixmap(background);
        } else {
            imageLabel->setStyleSheet("background-color: #c8dcb4;");
        }
    } else {
        // Масштабируем изображение под размер карточки
        QPixmap scaledBackground = backgroundImage.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        imageLabel->setPixmap(scaledBackground);
    }
    
    cardLayout->addWidget(imageLabel);
    
    // Имя питомца внизу
    QLabel* nameLabel = new QLabel(pet->getName(), card);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet(QString(
        "QLabel {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #cc99ff, stop:0.5 #aa88ff, stop:1 #9966ff);"
        "    color: #000000;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    padding: 3px;"
        "    border: 2px solid #ddbbff;"
        "    border-bottom-left-radius: 8px;"
        "    border-bottom-right-radius: 8px;"
        "}"
    ));
    nameLabel->setFixedHeight(35);
    
    cardLayout->addWidget(nameLabel);
    
    // Обработчик клика - храним индекс питомца
    int petIndex = m_petCards.size();
    card->installEventFilter(this);
    card->setProperty("petIndex", petIndex);
    
    return card;
}

void PetSelectionWindow::setupStandardPets()
{
    // Добавляем стандартные типы в список для создания
    // Это будет использоваться в диалоге создания
}

void PetSelectionWindow::onPetListSelectionChanged()
{
    bool hasSelection = m_selectedPet != nullptr;
    ui->selectButton->setEnabled(hasSelection);
    ui->deletePetButton->setEnabled(hasSelection);
}

void PetSelectionWindow::onSelectButtonClicked()
{
    if (m_selectedPet) {
        emit petSelected(m_selectedPet);
    }
}

void PetSelectionWindow::onNewPetButtonClicked()
{
    if (!m_user) return;
    
    QDialog dialog(this);
    dialog.setWindowTitle("Создать питомца");
    dialog.setMinimumWidth(350);
    dialog.setMaximumWidth(400);
    dialog.setFixedHeight(800);
    
    // Стилизация диалога в неоновом стиле
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
        "    outline: none;"
        "}"
        "QListWidget::item {"
        "    padding: 5px;"
        "    border-radius: 3px;"
        "    margin: 2px;"
        "}"
        "QListWidget::item:selected {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #9966ff, stop:1 #7744cc);"
        "    color: #000000;"
        "    font-weight: bold;"
        "    outline: none;"
        "}"
        "QListWidget::item:selected:focus {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #9966ff, stop:1 #7744cc);"
        "    color: #000000;"
        "    outline: none;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: rgba(153, 102, 255, 0.3);"
        "}"
        "QLineEdit, QTextEdit {"
        "    background-color: #2a1a3e;"
        "    border: 2px solid #9966ff;"
        "    border-radius: 5px;"
        "    color: #ffffff;"
        "    padding: 5px;"
        "    font-size: 11px;"
        "}"
        "QLineEdit:focus, QTextEdit:focus {"
        "    border: 2px solid #aa88ff;"
        "    background-color: #3a2a4e;"
        "}"
        "QSpinBox {"
        "    background-color: #2a1a3e;"
        "    border: 2px solid #9966ff;"
        "    border-radius: 5px;"
        "    color: #ffffff;"
        "    padding: 5px;"
        "    font-size: 11px;"
        "}"
        "QSpinBox:focus {"
        "    border: 2px solid #aa88ff;"
        "    background-color: #3a2a4e;"
        "}"
        "QSpinBox::up-button, QSpinBox::down-button {"
        "    background-color: #9966ff;"
        "    border: 1px solid #aa88ff;"
        "    border-radius: 3px;"
        "    width: 20px;"
        "}"
        "QSpinBox::up-button:hover, QSpinBox::down-button:hover {"
        "    background-color: #aa88ff;"
        "}"
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #00ffcc, stop:0.5 #00cc99, stop:1 #009966);"
        "    color: #000000;"
        "    border: 2px solid #00ffff;"
        "    border-radius: 5px;"
        "    padding: 5px 15px;"
        "    font-weight: bold;"
        "    font-size: 11px;"
        "    min-width: 60px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #00ffff, stop:0.5 #00ffcc, stop:1 #00cc99);"
        "    border: 2px solid #00ffff;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #00cc99, stop:0.5 #009966, stop:1 #006644);"
        "}"
    ));
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->setSpacing(10);
    layout->setContentsMargins(15, 15, 15, 15);
    
    // Выбор типа питомца
    QLabel* typeLabel = new QLabel("Тип питомца:", &dialog);
    layout->addWidget(typeLabel);
    
    QListWidget* typeList = new QListWidget(&dialog);
    typeList->addItem("Дракон");
    typeList->addItem("Грифон");
    typeList->addItem("Единорог");
    typeList->addItem("Свой питомец");
    typeList->setCurrentRow(0);
    typeList->setFixedHeight(150);
    typeList->setFocusPolicy(Qt::NoFocus);
    typeList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(typeList);
    
    // Имя
    QLabel* nameLabel = new QLabel("Имя:", &dialog);
    nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(nameLabel);
    QLineEdit* nameEdit = new QLineEdit(&dialog);
    nameEdit->setPlaceholderText("Введите имя питомца");
    nameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(nameEdit);
    
    // Описание (только для кастомного)
    QLabel* descLabel = new QLabel("Описание (только для своего питомца):", &dialog);
    descLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(descLabel);
    QTextEdit* descEdit = new QTextEdit(&dialog);
    descEdit->setFixedHeight(80);
    descEdit->setPlaceholderText("Опишите вашего питомца");
    descEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(descEdit);
    
    // Скорость изменения потребностей (только для кастомного)
    QLabel* hungerSpeedLabel = new QLabel("Скорость изменения голода (1-5):", &dialog);
    hungerSpeedLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(hungerSpeedLabel);
    QSpinBox* hungerSpeedSpin = new QSpinBox(&dialog);
    hungerSpeedSpin->setMinimum(1);
    hungerSpeedSpin->setMaximum(5);
    hungerSpeedSpin->setValue(1);
    hungerSpeedSpin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(hungerSpeedSpin);
    
    QLabel* sleepSpeedLabel = new QLabel("Скорость изменения сна (1-5):", &dialog);
    sleepSpeedLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(sleepSpeedLabel);
    QSpinBox* sleepSpeedSpin = new QSpinBox(&dialog);
    sleepSpeedSpin->setMinimum(1);
    sleepSpeedSpin->setMaximum(5);
    sleepSpeedSpin->setValue(1);
    sleepSpeedSpin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(sleepSpeedSpin);
    
    // Выбор изображений для кастомного питомца
    QLabel* babyAvaLabel = new QLabel("Аватарка малыша (для экрана выбора):", &dialog);
    babyAvaLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(babyAvaLabel);
    QHBoxLayout* babyAvaLayout = new QHBoxLayout();
    QLineEdit* babyAvaPathEdit = new QLineEdit(&dialog);
    babyAvaPathEdit->setPlaceholderText("Выберите изображение...");
    babyAvaPathEdit->setReadOnly(true);
    QPushButton* babyAvaButton = new QPushButton("Выбрать...", &dialog);
    connect(babyAvaButton, &QPushButton::clicked, [&dialog, babyAvaPathEdit]() {
        QString fileName = QFileDialog::getOpenFileName(&dialog, "Выберите аватарку малыша", "", "Изображения (*.jpg *.jpeg *.png *.bmp)");
        if (!fileName.isEmpty()) {
            babyAvaPathEdit->setText(fileName);
        }
    });
    babyAvaLayout->addWidget(babyAvaPathEdit);
    babyAvaLayout->addWidget(babyAvaButton);
    layout->addLayout(babyAvaLayout);
    
    QLabel* bigAvaLabel = new QLabel("Аватарка взрослого (для экрана выбора):", &dialog);
    bigAvaLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(bigAvaLabel);
    QHBoxLayout* bigAvaLayout = new QHBoxLayout();
    QLineEdit* bigAvaPathEdit = new QLineEdit(&dialog);
    bigAvaPathEdit->setPlaceholderText("Выберите изображение...");
    bigAvaPathEdit->setReadOnly(true);
    QPushButton* bigAvaButton = new QPushButton("Выбрать...", &dialog);
    connect(bigAvaButton, &QPushButton::clicked, [&dialog, bigAvaPathEdit]() {
        QString fileName = QFileDialog::getOpenFileName(&dialog, "Выберите аватарку взрослого", "", "Изображения (*.jpg *.jpeg *.png *.bmp)");
        if (!fileName.isEmpty()) {
            bigAvaPathEdit->setText(fileName);
        }
    });
    bigAvaLayout->addWidget(bigAvaPathEdit);
    bigAvaLayout->addWidget(bigAvaButton);
    layout->addLayout(bigAvaLayout);
    
    QLabel* babyImageLabel = new QLabel("Картинка малыша (для экрана управления):", &dialog);
    babyImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(babyImageLabel);
    QHBoxLayout* babyImageLayout = new QHBoxLayout();
    QLineEdit* babyImagePathEdit = new QLineEdit(&dialog);
    babyImagePathEdit->setPlaceholderText("Выберите изображение...");
    babyImagePathEdit->setReadOnly(true);
    QPushButton* babyImageButton = new QPushButton("Выбрать...", &dialog);
    connect(babyImageButton, &QPushButton::clicked, [&dialog, babyImagePathEdit]() {
        QString fileName = QFileDialog::getOpenFileName(&dialog, "Выберите картинку малыша", "", "Изображения (*.jpg *.jpeg *.png *.bmp)");
        if (!fileName.isEmpty()) {
            babyImagePathEdit->setText(fileName);
        }
    });
    babyImageLayout->addWidget(babyImagePathEdit);
    babyImageLayout->addWidget(babyImageButton);
    layout->addLayout(babyImageLayout);
    
    QLabel* bigImageLabel = new QLabel("Картинка взрослого (для экрана управления):", &dialog);
    bigImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(bigImageLabel);
    QHBoxLayout* bigImageLayout = new QHBoxLayout();
    QLineEdit* bigImagePathEdit = new QLineEdit(&dialog);
    bigImagePathEdit->setPlaceholderText("Выберите изображение...");
    bigImagePathEdit->setReadOnly(true);
    QPushButton* bigImageButton = new QPushButton("Выбрать...", &dialog);
    connect(bigImageButton, &QPushButton::clicked, [&dialog, bigImagePathEdit]() {
        QString fileName = QFileDialog::getOpenFileName(&dialog, "Выберите картинку взрослого", "", "Изображения (*.jpg *.jpeg *.png *.bmp)");
        if (!fileName.isEmpty()) {
            bigImagePathEdit->setText(fileName);
        }
    });
    bigImageLayout->addWidget(bigImagePathEdit);
    bigImageLayout->addWidget(bigImageButton);
    layout->addLayout(bigImageLayout);
    
    // Добавляем растяжку, чтобы элементы не сдвигались вверх
    layout->addStretch();
    
    // Кнопки
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Ok)->setText("OK");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    // Показываем/скрываем описание, скорости и изображения в зависимости от выбора
    auto updateDescVisibility = [descLabel, descEdit, hungerSpeedLabel, hungerSpeedSpin, sleepSpeedLabel, sleepSpeedSpin,
                                  babyAvaLabel, babyAvaPathEdit, babyAvaButton, bigAvaLabel, bigAvaPathEdit, bigAvaButton,
                                  babyImageLabel, babyImagePathEdit, babyImageButton, bigImageLabel, bigImagePathEdit, bigImageButton, typeList]() {
        bool isCustom = typeList->currentRow() == 3;
        descLabel->setVisible(isCustom);
        descEdit->setVisible(isCustom);
        hungerSpeedLabel->setVisible(isCustom);
        hungerSpeedSpin->setVisible(isCustom);
        sleepSpeedLabel->setVisible(isCustom);
        sleepSpeedSpin->setVisible(isCustom);
        babyAvaLabel->setVisible(isCustom);
        babyAvaPathEdit->setVisible(isCustom);
        babyAvaButton->setVisible(isCustom);
        bigAvaLabel->setVisible(isCustom);
        bigAvaPathEdit->setVisible(isCustom);
        bigAvaButton->setVisible(isCustom);
        babyImageLabel->setVisible(isCustom);
        babyImagePathEdit->setVisible(isCustom);
        babyImageButton->setVisible(isCustom);
        bigImageLabel->setVisible(isCustom);
        bigImagePathEdit->setVisible(isCustom);
        bigImageButton->setVisible(isCustom);
    };
    connect(typeList, &QListWidget::currentRowChanged, this, updateDescVisibility);
    updateDescVisibility();
    
    if (dialog.exec() == QDialog::Accepted) {
        QString name = nameEdit->text().trimmed();
        if (name.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Имя питомца не может быть пустым!");
            return;
        }
        
        int typeIndex = typeList->currentRow();
        PetType::StandardType type;
        QString description;
        int hungerDecayRate = 1;
        int sleepDecayRate = 1;
        
        if (typeIndex == 0) {
            // Дракон: быстрая скорость изменения потребностей
            type = PetType::Dragon;
            hungerDecayRate = 4;
            sleepDecayRate = 4;
        } else if (typeIndex == 1) {
            // Гриффон: средняя скорость изменения потребностей
            type = PetType::Griffin;
            hungerDecayRate = 3;
            sleepDecayRate = 3;
        } else if (typeIndex == 2) {
            // Единорог: медленная скорость изменения потребностей
            type = PetType::Unicorn;
            hungerDecayRate = 2;
            sleepDecayRate = 2;
        } else {
            // Кастомный: пользователь выбирает скорость и изображения
            type = PetType::Custom;
            description = descEdit->toPlainText().trimmed();
            hungerDecayRate = hungerSpeedSpin->value();
            sleepDecayRate = sleepSpeedSpin->value();
        }
        
        PetType petType(type, type == PetType::Custom ? name : "", description);
        
        // Устанавливаем пути к изображениям для кастомного питомца
        if (type == PetType::Custom) {
            petType.setBabyAvaPath(babyAvaPathEdit->text());
            petType.setBigAvaPath(bigAvaPathEdit->text());
            petType.setBabyImagePath(babyImagePathEdit->text());
            petType.setBigImagePath(bigImagePathEdit->text());
        }
        
        Pet* newPet = new Pet(name, petType, hungerDecayRate, sleepDecayRate);
        m_user->addPet(newPet);
        updatePetList();
        emit newPetCreated(newPet);
    }
}

void PetSelectionWindow::onBackButtonClicked()
{
    emit backButtonClicked();
}

void PetSelectionWindow::onDeletePetButtonClicked()
{
    if (!m_user || !m_selectedPet) return;
    
    int ret = QMessageBox::question(this, "Удаление питомца",
                                    QString("Вы уверены, что хотите удалить питомца '%1'?").arg(m_selectedPet->getName()),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        Pet* petToDelete = m_selectedPet;
        m_user->removePet(petToDelete);
        emit petDeleted(petToDelete);
        delete petToDelete;
        m_selectedPet = nullptr;
        updatePetList();
    }
}

void PetSelectionWindow::onCreateCustomPet()
{
    onNewPetButtonClicked();
}

bool PetSelectionWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QFrame* card = qobject_cast<QFrame*>(obj);
        if (card && card->property("petIndex").isValid() && m_user) {
            // Снимаем выделение с предыдущей карточки
            for (QWidget* w : m_petCards) {
                QFrame* prevCard = qobject_cast<QFrame*>(w);
                if (prevCard) {
                    prevCard->setStyleSheet(QString(
                        "QFrame {"
                        "    background-color: rgba(240, 250, 230, 0.9);"
                        "    border: 2px solid #4a7c2a;"
                        "    border-radius: 10px;"
                        "}"
                        "QFrame:hover {"
                        "    border: 3px solid #2d5016;"
                        "    background-color: rgba(240, 250, 230, 1.0);"
                        "}"
                    ));
                }
            }
            
            // Выделяем текущую карточку
            card->setStyleSheet(QString(
                "QFrame {"
                "    background-color: rgba(240, 250, 230, 1.0);"
                "    border: 4px solid #2d5016;"
                "    border-radius: 10px;"
                "}"
            ));
            
            // Получаем индекс питомца
            int petIndex = card->property("petIndex").toInt();
            if (petIndex >= 0 && petIndex < m_user->getPetCount()) {
                m_selectedPet = m_user->getPet(petIndex);
                onPetListSelectionChanged();
            }
            
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void PetSelectionWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void PetSelectionWindow::updateBackground()
{
    // Устанавливаем фон только для центрального виджета
    QWidget* centralWidget = this->centralWidget();
    if (!centralWidget) return;
    
    QString backgroundPath = "../FantasyPets/img/back3.jpg";
    QPixmap background(backgroundPath);
    
    if (background.isNull()) {
        backgroundPath = QDir::currentPath() + "/img/back3.jpg";
        background = QPixmap(backgroundPath);
    }
    
    if (!background.isNull()) {
        // Масштабируем изображение под размер центрального виджета
        background = background.scaled(centralWidget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(background));
        centralWidget->setPalette(palette);
        centralWidget->setAutoFillBackground(true);
    }
}

