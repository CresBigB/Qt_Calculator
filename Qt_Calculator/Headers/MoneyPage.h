#pragma once
#include "Headers.h"

#include "ui_MoneyPage.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MoneyPage;
}
QT_END_NAMESPACE

class MoneyPageWidget :public QWidget
{
	Q_OBJECT
public:
	MoneyPageWidget(QWidget* parent = nullptr);
	void reTranslate(const QString& fileName);

private:
	Ui::MoneyPage ui;
};