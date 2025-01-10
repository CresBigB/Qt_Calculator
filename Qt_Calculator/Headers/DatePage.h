#pragma once
#include "Headers.h"

#include "ui_DatePage.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class DatePage;
}
QT_END_NAMESPACE

class DatePageWidget :public QWidget
{
	Q_OBJECT
public:
	enum class Mode :qint8 { Add, Minus };
	DatePageWidget(QWidget* parent = nullptr);
	void changeMode(const Mode mode);
	void reTranslate(const QString& fileName);

	void evaluate() const;

private:
	void add() const;
	void minus() const;

private:
	Mode currentMode = Mode::Add;
	Ui::DatePage ui;
};