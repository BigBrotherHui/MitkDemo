#ifndef SYSTEMTOOLBAR_H
#define SYSTEMTOOLBAR_H
#include "SystemConfigWidget.h"
#include <QWidget>
#include <QPointer>

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
    void on_pushButton_settings_clicked();

    void on_pushButton_screenshot_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::SystemToolBar *ui;

    QPointer<SystemConfigWidget> dialog{ nullptr };
};

#endif // SYSTEMTOOLBAR_H
