#pragma once
#include "Headers.h"
#include "MainWindow.h"

class Calculate :public QObject
{
	Q_OBJECT
public:
	static Calculate* instance()
	{
		if (_instance == nullptr)
			_instance = new Calculate;
		return _instance;
	}
	~Calculate() override;

private:
	Calculate();
	QString formatExpression(const QString& expression) const;
	void mainWindowSignalConnect();
	QString evaluate() const;
	void showNumberAndExpression() const;

private:
	static Calculate* _instance;

	QString currentNumber;
	QString currentExpression;
	MainWindow* mainWindow;
};