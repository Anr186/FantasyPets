#include "pettype.h"
#include <QPainter>
#include <QFont>

PetType::PetType(StandardType type, const QString& name, const QString& description)
    : m_type(type)
    , m_babyAvaPath("")
    , m_bigAvaPath("")
    , m_babyImagePath("")
    , m_bigImagePath("")
{
    if (type == Custom) {
        m_name = name.isEmpty() ? "Custom Pet" : name;
        m_description = description;
        // Создаем простую иконку для кастомного питомца
        m_icon = QPixmap(64, 64);
        m_icon.fill(Qt::transparent);
        QPainter painter(&m_icon);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(QColor(100, 150, 200)));
        painter.drawEllipse(10, 10, 44, 44);
    } else {
        m_name = getStandardTypeName(type);
        m_description = getStandardTypeDescription(type);
        m_icon = getStandardTypeIcon(type);
    }
}

QString PetType::getStandardTypeName(StandardType type)
{
    switch (type) {
        case Dragon: return "Дракон";
        case Griffin: return "Грифон";
        case Unicorn: return "Единорог";
        default: return "Неизвестный";
    }
}

QString PetType::getStandardTypeDescription(StandardType type)
{
    switch (type) {
        case Dragon:
            return "Могущественный дракон с огненным дыханием. Любит играть и требует много внимания.";
        case Griffin:
            return "Благородный грифон - смесь орла и льва. Очень активный и игривый питомец.";
        case Unicorn:
            return "Волшебный единорог с магическим рогом. Нежный и дружелюбный, но требует заботы.";
        default:
            return "";
    }
}

QPixmap PetType::getStandardTypeIcon(StandardType type)
{
    QPixmap icon(64, 64);
    icon.fill(Qt::transparent);
    QPainter painter(&icon);
    painter.setRenderHint(QPainter::Antialiasing);
    
    switch (type) {
        case Dragon: {
            // Рисуем дракона (красный)
            painter.setBrush(QBrush(QColor(220, 50, 50)));
            painter.drawEllipse(15, 20, 34, 24); // тело
            painter.drawEllipse(20, 10, 12, 12); // голова
            painter.setBrush(QBrush(QColor(255, 100, 100)));
            painter.drawEllipse(22, 12, 8, 8); // глаз
            break;
        }
        case Griffin: {
            // Рисуем грифона (золотой)
            painter.setBrush(QBrush(QColor(200, 150, 50)));
            painter.drawEllipse(15, 25, 34, 20); // тело льва
            painter.setBrush(QBrush(QColor(150, 100, 50)));
            painter.drawEllipse(20, 10, 20, 18); // голова орла
            painter.setBrush(QBrush(QColor(255, 200, 100)));
            painter.drawEllipse(25, 13, 6, 6); // глаз
            break;
        }
        case Unicorn: {
            // Рисуем единорога (белый с радугой)
            painter.setBrush(QBrush(QColor(255, 255, 255)));
            painter.drawEllipse(15, 20, 34, 24); // тело
            painter.drawEllipse(20, 10, 18, 18); // голова
            // Рог
            QPolygon horn;
            horn << QPoint(29, 10) << QPoint(27, 5) << QPoint(31, 5);
            painter.setBrush(QBrush(QColor(200, 150, 255)));
            painter.drawPolygon(horn);
            painter.setBrush(QBrush(QColor(100, 150, 255)));
            painter.drawEllipse(25, 13, 6, 6); // глаз
            break;
        }
        default:
            break;
    }
    
    return icon;
}


