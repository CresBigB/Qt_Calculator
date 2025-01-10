#pragma once

#include "Headers.h"

#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	enum class Page :qint8 { Standard, Science, Programmer, Date, Money };
	enum class Theme :qint8 { Black, White };
	enum class Language :qint8 { Chinese, English};

	MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

public:
	void addHistory(const QString& history);
	void showNumber(const QString& number) const;
	void showExpression(const QString& expression) const;
	void changePage(const Page page) const;
	void changeTheme(const Theme theme);
	void changeLanguage(const Language language);

signals:
	void inputNumber(const int num);
	void inputOperator(const QString& _operator);
	void changePlusMinus();
	void evaluate();
	void backSpace();
	void clean();

private:
	void SciencePageSignalsConnect();
	void ProgrammerPageSignalsConnect();
	void actionSignalConnect();
	void blackTheme();
	void whiteTheme();

private:
	Ui::MainWindow* ui;
};