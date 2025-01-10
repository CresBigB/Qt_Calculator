#include "ProgrammerPage.h"

ProgrammerPageWidget::ProgrammerPageWidget(QWidget* parent)
{
	ui.setupUi(this);
	ui.btn_point->setEnabled(false);
	ui.radioButton_DEC->click();
	changeMode(Mode::DEC);
	signalsConnect();
}

void ProgrammerPageWidget::showNumber(const int number) const
{
	ui.showHEX->setText(QString::number(number, 16));
	ui.showDEC->setText(QString::number(number, 10));
	ui.showOCT->setText(QString::number(number, 8));
	ui.showBIN->setText(QString::number(number, 2));
}

ProgrammerPageWidget::Mode ProgrammerPageWidget::getCurrentMode() const
{
	return currentMode;
}

void ProgrammerPageWidget::changeMode(const Mode mode)
{
	switch (mode)
	{
	case Mode::HEX:
		currentMode = Mode::HEX;
		ui.btn_A->setEnabled(true);
		ui.btn_B->setEnabled(true);
		ui.btn_C->setEnabled(true);
		ui.btn_D->setEnabled(true);
		ui.btn_E->setEnabled(true);
		ui.btn_F->setEnabled(true);
		ui.btn_1->setEnabled(true);
		ui.btn_2->setEnabled(true);
		ui.btn_3->setEnabled(true);
		ui.btn_4->setEnabled(true);
		ui.btn_5->setEnabled(true);
		ui.btn_6->setEnabled(true);
		ui.btn_7->setEnabled(true);
		ui.btn_8->setEnabled(true);
		ui.btn_9->setEnabled(true);
		break;
	case Mode::DEC:
		currentMode = Mode::DEC;
		ui.btn_A->setEnabled(false);
		ui.btn_B->setEnabled(false);
		ui.btn_C->setEnabled(false);
		ui.btn_D->setEnabled(false);
		ui.btn_E->setEnabled(false);
		ui.btn_F->setEnabled(false);
		ui.btn_1->setEnabled(true);
		ui.btn_2->setEnabled(true);
		ui.btn_3->setEnabled(true);
		ui.btn_4->setEnabled(true);
		ui.btn_5->setEnabled(true);
		ui.btn_6->setEnabled(true);
		ui.btn_7->setEnabled(true);
		ui.btn_8->setEnabled(true);
		ui.btn_9->setEnabled(true);
		break;
	case Mode::OCT:
		currentMode = Mode::OCT;
		ui.btn_A->setEnabled(false);
		ui.btn_B->setEnabled(false);
		ui.btn_C->setEnabled(false);
		ui.btn_D->setEnabled(false);
		ui.btn_E->setEnabled(false);
		ui.btn_F->setEnabled(false);
		ui.btn_1->setEnabled(true);
		ui.btn_2->setEnabled(true);
		ui.btn_3->setEnabled(true);
		ui.btn_4->setEnabled(true);
		ui.btn_5->setEnabled(true);
		ui.btn_6->setEnabled(true);
		ui.btn_7->setEnabled(true);
		ui.btn_8->setEnabled(false);
		ui.btn_9->setEnabled(false);
		break;
	case Mode::BIN:
		currentMode = Mode::BIN;
		ui.btn_A->setEnabled(false);
		ui.btn_B->setEnabled(false);
		ui.btn_C->setEnabled(false);
		ui.btn_D->setEnabled(false);
		ui.btn_E->setEnabled(false);
		ui.btn_F->setEnabled(false);
		ui.btn_2->setEnabled(false);
		ui.btn_3->setEnabled(false);
		ui.btn_4->setEnabled(false);
		ui.btn_5->setEnabled(false);
		ui.btn_6->setEnabled(false);
		ui.btn_7->setEnabled(false);
		ui.btn_8->setEnabled(false);
		ui.btn_9->setEnabled(false);
		break;
	}
}

void ProgrammerPageWidget::signalsConnect()
{
	connect(ui.btn_1, &QPushButton::clicked, this, [this] {emit inputNum(1); });
	connect(ui.btn_2, &QPushButton::clicked, this, [this] {emit inputNum(2); });
	connect(ui.btn_3, &QPushButton::clicked, this, [this] {emit inputNum(3); });
	connect(ui.btn_4, &QPushButton::clicked, this, [this] {emit inputNum(4); });
	connect(ui.btn_5, &QPushButton::clicked, this, [this] {emit inputNum(5); });
	connect(ui.btn_6, &QPushButton::clicked, this, [this] {emit inputNum(6); });
	connect(ui.btn_7, &QPushButton::clicked, this, [this] {emit inputNum(7); });
	connect(ui.btn_8, &QPushButton::clicked, this, [this] {emit inputNum(8); });
	connect(ui.btn_9, &QPushButton::clicked, this, [this] {emit inputNum(9); });
	connect(ui.btn_0, &QPushButton::clicked, this, [this] {emit inputNum(0); });
	connect(ui.btn_A, &QPushButton::clicked, this, [this] {emit inputNum('A'); });
	connect(ui.btn_B, &QPushButton::clicked, this, [this] {emit inputNum('B'); });
	connect(ui.btn_C, &QPushButton::clicked, this, [this] {emit inputNum('C'); });
	connect(ui.btn_D, &QPushButton::clicked, this, [this] {emit inputNum('D'); });
	connect(ui.btn_E, &QPushButton::clicked, this, [this] {emit inputNum('E'); });
	connect(ui.btn_F, &QPushButton::clicked, this, [this] {emit inputNum('F'); });

	connect(ui.btnAdd, &QPushButton::clicked, this, [this] {emit inputOperator("+"); });
	connect(ui.btnMinus, &QPushButton::clicked, this, [this] {emit inputOperator("-"); });
	connect(ui.btnMultiply, &QPushButton::clicked, this, [this] {emit inputOperator("x"); });
	connect(ui.btnExcept, &QPushButton::clicked, this, [this] {emit inputOperator("÷"); });
	connect(ui.btnAND, &QPushButton::clicked, this, [this] {emit inputOperator("AND"); });
	connect(ui.btnOR, &QPushButton::clicked, this, [this] {emit inputOperator("OR"); });
	connect(ui.btnNOT, &QPushButton::clicked, this, [this] {emit inputOperator("NOT"); });
	connect(ui.btnXOR, &QPushButton::clicked, this, [this] {emit inputOperator("XOR"); });
	connect(ui.btnMoveLeft, &QPushButton::clicked, this, [this] {emit inputOperator("<<"); });
	connect(ui.btnMoveRight, &QPushButton::clicked, this, [this] {emit inputOperator(">>"); });


	connect(ui.btnBackSpace, &QPushButton::clicked, this, [this] {emit backSpace(); });
	connect(ui.btnClean, &QPushButton::clicked, this, [this] {emit clean(); });
	connect(ui.btnEvaluate, &QPushButton::clicked, this, [this] {emit evaluate(); });
	connect(ui.btnChangePlusMinus, &QPushButton::clicked, this, [this] {emit changePlusMinus(); });

	connect(ui.radioButton_HEX, &QRadioButton::toggled, this, [this] {changeMode(Mode::HEX); emit clean(); });
	connect(ui.radioButton_OCT, &QRadioButton::toggled, this, [this] {changeMode(Mode::OCT); emit clean(); });
	connect(ui.radioButton_DEC, &QRadioButton::toggled, this, [this] {changeMode(Mode::DEC); emit clean(); });
	connect(ui.radioButton_BIN, &QRadioButton::toggled, this, [this] {changeMode(Mode::BIN); emit clean(); });
}

