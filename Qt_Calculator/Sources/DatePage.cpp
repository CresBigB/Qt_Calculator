#include "DatePage.h"

DatePageWidget::DatePageWidget(QWidget* parent)
{
	ui.setupUi(this);
	ui.dateEdit->setDate(QDate::currentDate());
	ui.radioButton_Add->click();
	changeMode(Mode::Add);

	ui.inputYear->setValidator(new QIntValidator(ui.inputYear));
	ui.inputMonth->setValidator(new QIntValidator(ui.inputMonth));
	ui.inputDay->setValidator(new QIntValidator(ui.inputDay));

	connect(ui.dateEdit, &QDateEdit::dateChanged, this, [this] {this->evaluate(); });
	connect(ui.radioButton_Add, &QRadioButton::clicked, this, [this] {this->changeMode(Mode::Add); });
	connect(ui.radioButton_Minus, &QRadioButton::clicked, this, [this] {this->changeMode(Mode::Minus); });
	connect(ui.inputDay, &QLineEdit::textChanged, this, [this] {evaluate(); });
	connect(ui.inputMonth, &QLineEdit::textChanged, this, [this] {evaluate(); });
	connect(ui.inputYear, &QLineEdit::textChanged, this, [this] {evaluate(); });
}

void DatePageWidget::changeMode(const Mode mode)
{
	currentMode = mode;
	evaluate();
}

void DatePageWidget::reTranslate(const QString& fileName)
{
	QTranslator* translator = new QTranslator(this);
	if (translator->load(fileName))
		ui.retranslateUi(this);
}

void DatePageWidget::evaluate() const
{
	if (currentMode == Mode::Add)
		add();
	else
		minus();
}


void DatePageWidget::add() const
{
	auto currentDate = ui.dateEdit->date();
	currentDate = currentDate.addYears(ui.inputYear->text().toInt());
	currentDate = currentDate.addMonths(ui.inputMonth->text().toInt());
	currentDate = currentDate.addDays(ui.inputDay->text().toInt());
	ui.showResult->setText(currentDate.toString(Qt::ISODateWithMs));
}

void DatePageWidget::minus() const
{
	auto currentDate = ui.dateEdit->date();
	currentDate = currentDate.addYears(ui.inputYear->text().toInt() * -1);
	currentDate = currentDate.addMonths(ui.inputMonth->text().toInt() * -1);
	currentDate = currentDate.addDays(ui.inputDay->text().toInt() * -1);
	ui.showResult->setText(currentDate.toString(Qt::ISODateWithMs));
}

