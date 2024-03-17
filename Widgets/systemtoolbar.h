#ifndef SYSTEMTOOLBAR_H
#define SYSTEMTOOLBAR_H

#include <QWidget>
class QMenu;
class QAction;
namespace Ui {
class SystemToolBar;
}

class SystemToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit SystemToolBar(QWidget *parent = nullptr);
    ~SystemToolBar();

private slots:
    void on_toolButton_settings_clicked();

    void on_pushButton_screenshot_clicked();

    void on_pushButton_exit_clicked();

    void slot_userManager();
private:
    Ui::SystemToolBar *ui;
    QMenu* m_menu;
    QAction* m_actionUserManager;
};

#endif // SYSTEMTOOLBAR_H
