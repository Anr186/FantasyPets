#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();
    
protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void playButtonClicked();

private:
    Ui::WelcomeWindow *ui;
    void updateBackground();
};

#endif // WELCOMEWINDOW_H

