#pragma once
#include "Headers.h"

#include "ui_ProgrammerPage.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class ProgrammerPage;
}
QT_END_NAMESPACE


class ProgrammerPageWidget :public QWidget
{
	Q_OBJECT
public:
	enum class  Mode :qint8 { HEX, DEC, OCT, BIN };
	ProgrammerPageWidget(QWidget* parent = nullptr);

public:
	void showNumber(const int number) const;
	[[nodiscard]] Mode getCurrentMode() const;

signals:
	void modeChange(const Mode mode);
	void inputNum(const int num);
	void inputOperator(const QString& _operator);
	void changePlusMinus();
	void backSpace();
	void evaluate();
	void clean();

public:
	void changeMode(const Mode mode);

private:
	void signalsConnect();

private:
	Mode currentMode = Mode::DEC;
	Ui::ProgrammerPage ui;
};