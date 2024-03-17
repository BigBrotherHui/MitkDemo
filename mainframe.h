#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "ufunbase.h"

class MainWindow;
class Login;
namespace Ui {
class MainFrame;
}

class MainFrame : public uFunBase
{
    Q_OBJECT

public:

    Q_INVOKABLE explicit MainFrame(QWidget *parent = nullptr);
    ~MainFrame();
    Login *GetLogin();
private:
    Ui::MainFrame *ui;
    Login *mLogin{nullptr};
};

#endif // MAINFRAME_H
