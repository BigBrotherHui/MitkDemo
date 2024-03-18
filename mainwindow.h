
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "umainfunbase.h"
#include <QtCore/qobjectdefs.h>
#include <QtWidgets/QMainWindow>

class QWidget;
class QCloseEvent;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,uMainFunBase
{
    Q_OBJECT

public:
    static int typeId;
    Q_INVOKABLE explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void f_Init();
    void setPatientInfo(QString t);
    //void setMarkerVisible(bool v);
protected:
    virtual void closeEvent(QCloseEvent* e) override;

private slots:
    void slot_timeout();
private:
    Ui::MainWindow *ui;
    QTimer* mTimer;


	const QString robotConnect = "QLabel { min-width: 48px; min-height: 48px; border-image:url(:/res/robot_connect.png) 1 1 1 1 stretch stretch; } QToolTip { ; }";
	const QString robotDisconnect = "QLabel { min-width: 48px; min-height: 48px; border-image:url(:/res/robot_disconnect.png) 1 1 1 1 stretch stretch; } QToolTip { ; }";


};
#endif // MAINWINDOW_H
