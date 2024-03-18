#include "SystemConfigWidget.h"

SystemConfigWidget::SystemConfigWidget(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::SystemConfigWidgetClass())
{
	ui->setupUi(this);


	connect(ui->pushButton, &QPushButton::clicked, this, &SystemConfigWidget::on_pushButton);
	connect(ui->pushButton2, &QPushButton::clicked, this, &SystemConfigWidget::on_pushButton2);
	connect(ui->pushButton3, &QPushButton::clicked, this, &SystemConfigWidget::on_pushButton3);
}

SystemConfigWidget::~SystemConfigWidget()
{
	delete ui;
}

void SystemConfigWidget::on_pushButton()
{
	SystemControler::getInstance()->getRobotControler()->setMotorPower(1);
}

void SystemConfigWidget::on_pushButton2()
{

}

void SystemConfigWidget::on_pushButton3()
{

}