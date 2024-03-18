#ifndef REHEARSALWIDGET_H
#define REHEARSALWIDGET_H

#include <QWidget>
#include "ufunbase.h"
#include <mitkStandaloneDataStorage.h>

namespace Ui {
class RehearsalWidget;
}

class RehearsalWidget : public uFunBase
{
    Q_OBJECT

public:
    explicit RehearsalWidget(QWidget *parent = nullptr);
    ~RehearsalWidget();
private:
    Ui::RehearsalWidget *ui;
    mitk::StandaloneDataStorage::Pointer m_dataStorage;
};

#endif // REHEARSALWIDGET_H
