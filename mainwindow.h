
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/qobjectdefs.h>
#include <QtWidgets/QMainWindow>

class QWidget;
class QCloseEvent;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class CaseManage;
class CaseManageControl;
class NavigationWidget;
class NavigationWidgetControl;
class PreOperationDesignControl;
class RehearsalWidget;
class RehearsalWidgetControl;
class StdMultiWidget;
class SubToolBar;
class MainToolBar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum CenterWidget {
        CenterWidget_CaseManage,
        CenterWidget_NavigationWidget,
        CenterWidget_RehearWidget,
        CenterWidget_StdMultiWidget
    };
    enum ControlWidget {
        ControlWidget_CaseManageControl,
        ControlWidget_NavigationWidgetControl,
        ControlWidget_PreOperationDesignControl,
        ControlWidget_RehearsalWidgetControl
    };
    enum ToolBarWidget {
        ToolBarWidget_MainToolBar,
        ToolBarWidget_SubToolBar
    };
    Q_INVOKABLE explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void f_Init();
    void setPatientInfo(QString t);
    //void setMarkerVisible(bool v);
    void SetCurrentCenterWidget(CenterWidget index);
    void SetCurrentControlWidget(ControlWidget index);
    void SetCurrentToolBar(ToolBarWidget index);

    QWidget* GetCenterWidget(CenterWidget index);
    QWidget* GetControlWidget(ControlWidget index);
    QWidget* GetToolBarWidget(ToolBarWidget index);
protected:
    virtual void closeEvent(QCloseEvent* e) override;
private slots:
    void slot_timeout();
private:
    Ui::MainWindow *ui;
    QTimer* mTimer;
    CaseManage* m_caseManage;
    NavigationWidget* m_navigationWidget;
    RehearsalWidget* m_rehearsalWidget;
    StdMultiWidget* m_stdMultiWidget;

    CaseManageControl* m_caseManageControl;
    NavigationWidgetControl* m_navigationWidgetControl;
    PreOperationDesignControl* m_preOperationDesignControl;
    RehearsalWidgetControl* m_rehearsalWidgetControl;

    SubToolBar* m_subToolBar;
    MainToolBar* m_mainToolBar;

    std::map<CenterWidget, QWidget*> m_centerWidgetMap;
    std::map<ControlWidget, QWidget*> m_controlWidgetMap;
    std::map<ToolBarWidget, QWidget*> m_toolBarWidgetMap;
    const QString robotConnect = "QLabel { min-width: 48px; min-height: 48px; border-image:url(:/res/robot_connect.png) 1 1 1 1 stretch stretch; } QToolTip { ; }";
	const QString robotDisconnect = "QLabel { min-width: 48px; min-height: 48px; border-image:url(:/res/robot_disconnect.png) 1 1 1 1 stretch stretch; } QToolTip { ; }";
};
#endif // MAINWINDOW_H
