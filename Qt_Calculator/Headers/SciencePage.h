#pragma once

#include "Headers.h"

#include "ui_SciencePage.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
	class SciencePage;
}
QT_BEGIN_NAMESPACE

class SciencePageWidget :public QWidget
{
	Q_OBJECT
public:
	enum class Mode :qint8 { Standard, Science };
	SciencePageWidget(QWidget* parent = nullptr);

signals:
	void inputNumber(const int num);
	void inputOperator(const QString& _operator);
	void changePlusMinus();
	void backSpace();
	void clean();
	void evaluate();

public:
	void changeMode(const Mode mode) const;

private:
	void signalConnect();

private:
	Ui::SciencePage ui;
};