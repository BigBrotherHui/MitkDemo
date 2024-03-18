#ifndef SYSTEMTOOLBAR_H
#define SYSTEMTOOLBAR_H
#include "SystemConfigWidget.h"
#include <QPointer>
#include <QWidget>
class QMenu;
class QAction;
namespace Ui {
class SystemToolBar;
}
//class SystemConfigDialog;
class SystemToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit SystemToolBar(QWidget *parent = nullptr);
    ~SystemToolBar();

private slots:
    void slot_systemConfig();

    void on_pushButton_screenshot_clicked();

    void on_pushButton_exit_clicked();

    void slot_userManager();
private:
    Ui::SystemToolBar *ui;
    QMenu* m_menu;
    QAction* m_actionUserManager;
    QAction* m_actionSystemConfig;
    QPointer<SystemConfigWidget> dialog{ nullptr };
};

#endif // SYSTEMTOOLBAR_H
