#ifndef PETTYPE_H
#define PETTYPE_H

#include <QString>
#include <QPixmap>

class PetType
{
public:
    enum StandardType {
        Dragon,
        Griffin,
        Unicorn,
        Custom
    };
    
    PetType(StandardType type, const QString& name = "", const QString& description = "");
    
    StandardType getType() const { return m_type; }
    QString getName() const { return m_name; }
    QString getDescription() const { return m_description; }
    QPixmap getIcon() const { return m_icon; }
    
    // Пути к изображениям для кастомного питомца
    QString getBabyAvaPath() const { return m_babyAvaPath; }
    QString getBigAvaPath() const { return m_bigAvaPath; }
    QString getBabyImagePath() const { return m_babyImagePath; }
    QString getBigImagePath() const { return m_bigImagePath; }
    
    void setIcon(const QPixmap& icon) { m_icon = icon; }
    void setName(const QString& name) { m_name = name; }
    void setDescription(const QString& description) { m_description = description; }
    void setBabyAvaPath(const QString& path) { m_babyAvaPath = path; }
    void setBigAvaPath(const QString& path) { m_bigAvaPath = path; }
    void setBabyImagePath(const QString& path) { m_babyImagePath = path; }
    void setBigImagePath(const QString& path) { m_bigImagePath = path; }
    
    static QString getStandardTypeName(StandardType type);
    static QString getStandardTypeDescription(StandardType type);
    static QPixmap getStandardTypeIcon(StandardType type);

private:
    StandardType m_type;
    QString m_name;
    QString m_description;
    QPixmap m_icon;
    
    // Пути к изображениям для кастомного питомца
    QString m_babyAvaPath;    // Аватарка baby для экрана выбора
    QString m_bigAvaPath;     // Аватарка big для экрана выбора
    QString m_babyImagePath;  // Картинка baby для экрана управления
    QString m_bigImagePath;   // Картинка big для экрана управления
};

#endif // PETTYPE_H


