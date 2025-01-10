#include "Calculate.h"

Calculate* Calculate::_instance = nullptr;

Calculate::Calculate()
{
	mainWindow = new MainWindow;
	mainWindow->show();
	mainWindowSignalConnect();
}

Calculate::~Calculate()
{
	delete mainWindow;
}

QString Calculate::formatExpression(const QString& expression) const
{
	QString temp = expression;
	temp.replace("sin", "math.sin");
	temp.replace("cos", "math.cos");
	temp.replace("tan", "math.tan");
	temp.replace("log", "math.log10");
	temp.replace("Mod", "%");
	temp.replace("ln", "math.log");
	temp.replace("√一", "math.sqrt");
	temp.replace("^", "**");
	temp.replace("AND", "&");
	temp.replace("XOR", "^");
	temp.replace("OR", "|");
	temp.replace("NOT", "~");
	temp.replace("x", "*");
	temp.replace("÷", "/");
	temp.replace("π", "3.14159265358979324");
	temp.replace("e", "2.71828182845904523");

	return temp;
}

void Calculate::mainWindowSignalConnect()
{
	connect(mainWindow, &MainWindow::inputNumber, this, [this](const int num)
		{
			if (num == -1)
			{
				if (!currentNumber.contains('.'))
					currentNumber += ".";
			}
			else if (num >= 0 && num <= 9)
				currentNumber += QString::number(num);
			else
			{
				currentNumber += static_cast<char>(num);
			}
			showNumberAndExpression();
			qOut << 2;
		});

	connect(mainWindow, &MainWindow::evaluate, this, [this]
		{
			currentExpression += currentNumber;
			auto result = evaluate();
			if (!result.isEmpty())
			{
				currentNumber = result;
				mainWindow->addHistory(currentExpression + "\n" + currentNumber);
				showNumberAndExpression();
				currentExpression.clear();
			}
		});

	connect(mainWindow, &MainWindow::clean, this, [this]
		{
			currentNumber.clear();
			currentExpression.clear();
			showNumberAndExpression();
		});

	connect(mainWindow, &MainWindow::backSpace, this, [this]
		{
			currentNumber.remove(currentNumber.size() - 1, 1);
			showNumberAndExpression();
		});

	connect(mainWindow, &MainWindow::changePlusMinus, this, [this]
		{
			if (currentNumber[0] == '-')
				currentNumber.remove(0, 1);
			else
				currentNumber.insert(0, '-');
			showNumberAndExpression();
		});

	connect(mainWindow, &MainWindow::inputOperator, this, [this](const QString& _operator)
		{
			if (_operator == "+" || _operator == "-" || _operator == "x" || _operator == "÷" ||
				_operator == "(" || _operator == ")" || _operator == "^" || _operator == "<<" || _operator == "Mod"
				|| _operator == ">>" || _operator == "AND" || _operator == "OR" || _operator == "XOR")
			{
				currentExpression += currentNumber;
				currentExpression += _operator;
			}
			else
			{
				if (currentNumber.isEmpty()) return;
				QString temp = _operator + "(%1)";
				currentExpression += temp.arg(currentNumber);
			}
			currentNumber.clear();
			showNumberAndExpression();
			qOut << "1";
		});
}

QString Calculate::evaluate() const
{
	QString pythonScriptPath = "evaluate_expression.py";

	if (!QFileInfo::exists(pythonScriptPath))
	{
		QMessageBox::critical(mainWindow, tr("错误"), "Error: Python script not found at" + pythonScriptPath);
		return {};
	}

	QProcess process;
	qOut << currentExpression << formatExpression(currentExpression);
	process.start("python", QStringList() << pythonScriptPath << formatExpression(currentExpression));
	process.waitForFinished();

	QString result = process.readAllStandardOutput().trimmed();
	QString error = process.readAllStandardError().trimmed();

	if (!result[0].isDigit() && result[0] != '-')
	{
		QMessageBox::critical(mainWindow, tr("错误"), result);
		return {};
	}
	else
		return result;
}

void Calculate::showNumberAndExpression() const
{
	if (currentNumber.isEmpty())
		mainWindow->showNumber("0");
	else
		mainWindow->showNumber(currentNumber);

	mainWindow->showExpression(currentExpression);
}
