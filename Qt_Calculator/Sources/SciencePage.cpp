#include "SciencePage.h"

#include "ui_SciencePage.h"

SciencePageWidget::SciencePageWidget(QWidget* parent) :QWidget(parent)
{
	ui.setupUi(this);
	signalConnect();
}

void SciencePageWidget::changeMode(const Mode mode) const
{
	switch (mode)
	{
	case Mode::Standard:
		ui.btnTan->setEnabled(false);
		ui.btnSin->setEnabled(false);
		ui.btnCos->setEnabled(false);
		ui.btnExponent->setEnabled(false);
		ui.btnLog->setEnabled(false);
		ui.btnLn->setEnabled(false);
		ui.btnRadicalSign->setEnabled(false);
		ui.btnLeftBrackets->setEnabled(false);
		ui.btnRightBrackets->setEnabled(false);
		break;
	case Mode::Science:
		ui.btnTan->setEnabled(true);
		ui.btnSin->setEnabled(true);
		ui.btnCos->setEnabled(true);
		ui.btnExponent->setEnabled(true);
		ui.btnLog->setEnabled(true);
		ui.btnLn->setEnabled(true);
		ui.btnRadicalSign->setEnabled(true);
		ui.btnLeftBrackets->setEnabled(true);
		ui.btnRightBrackets->setEnabled(true);
		break;
	}
}


void SciencePageWidget::signalConnect()
{
	connect(ui.btn_1, &QPushButton::clicked, this, [this] {emit inputNumber(1); });
	connect(ui.btn_2, &QPushButton::clicked, this, [this] {emit inputNumber(2); });
	connect(ui.btn_3, &QPushButton::clicked, this, [this] {emit inputNumber(3); });
	connect(ui.btn_4, &QPushButton::clicked, this, [this] {emit inputNumber(4); });
	connect(ui.btn_5, &QPushButton::clicked, this, [this] {emit inputNumber(5); });
	connect(ui.btn_6, &QPushButton::clicked, this, [this] {emit inputNumber(6); });
	connect(ui.btn_7, &QPushButton::clicked, this, [this] {emit inputNumber(7); });
	connect(ui.btn_8, &QPushButton::clicked, this, [this] {emit inputNumber(8); });
	connect(ui.btn_9, &QPushButton::clicked, this, [this] {emit inputNumber(9); });
	connect(ui.btn_0, &QPushButton::clicked, this, [this] {emit inputNumber(0); });

	connect(ui.btnAdd, &QPushButton::clicked, this, [this] {emit inputOperator("+"); });
	connect(ui.btnMinus, &QPushButton::clicked, this, [this] {emit inputOperator("-"); });
	connect(ui.btnMultiply, &QPushButton::clicked, this, [this] {emit inputOperator("x"); });
	connect(ui.btnExcept, &QPushButton::clicked, this, [this] {emit inputOperator("÷"); });
	connect(ui.btnMod, &QPushButton::clicked, this, [this] {emit inputOperator("Mod"); });
	connect(ui.btnSin, &QPushButton::clicked, this, [this] {emit inputOperator("sin"); });
	connect(ui.btnCos, &QPushButton::clicked, this, [this] {emit inputOperator("cos"); });
	connect(ui.btnTan, &QPushButton::clicked, this, [this] {emit inputOperator("tan"); });
	connect(ui.btnExponent, &QPushButton::clicked, this, [this] {emit inputOperator("^"); });
	connect(ui.btnLog, &QPushButton::clicked, this, [this] {emit inputOperator("log"); });
	connect(ui.btnLn, &QPushButton::clicked, this, [this] {emit inputOperator("ln"); });
	connect(ui.btnRadicalSign, &QPushButton::clicked, this, [this] {emit inputOperator("√一"); });
	connect(ui.btnLeftBrackets, &QPushButton::clicked, this, [this] {emit inputOperator("("); });
	connect(ui.btnRightBrackets, &QPushButton::clicked, this, [this] {emit inputOperator(")"); });

	connect(ui.btnBackSpace, &QPushButton::clicked, this, [this] {emit backSpace(); });
	connect(ui.btnClear, &QPushButton::clicked, this, [this] {emit clean(); });
	connect(ui.btnEvaluate, &QPushButton::clicked, this, [this] {emit evaluate(); });
	connect(ui.btnPoint, &QPushButton::clicked, this, [this] {emit inputNumber(-1); });
	connect(ui.btnChangePlusMinus, &QPushButton::clicked, this, [this] {emit changePlusMinus(); });

}
