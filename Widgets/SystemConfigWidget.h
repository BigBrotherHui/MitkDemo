#pragma once

#include <QDialog>
#include <QPushButton>
#include "ui_SystemConfigWidget.h"
#include "SystemControler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SystemConfigWidgetClass; };
QT_END_NAMESPACE

class SystemConfigWidget : public QDialog
{
	Q_OBJECT

public:
	SystemConfigWidget(QWidget *parent = nullptr);
	~SystemConfigWidget();


private slots:
	void on_pushButton();

	void on_pushButton2();

	void on_pushButton3();
private:
	Ui::SystemConfigWidgetClass *ui;
};
