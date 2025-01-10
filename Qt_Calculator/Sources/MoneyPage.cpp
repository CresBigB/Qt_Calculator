#include "MoneyPage.h"

MoneyPageWidget::MoneyPageWidget(QWidget* parent)
{
	ui.setupUi(this);
	ui.inputDollar->setValidator(new QDoubleValidator(ui.inputDollar));
	ui.inputRMB->setValidator(new QDoubleValidator(ui.inputRMB));
	connect(ui.inputDollar, &QLineEdit::textChanged, this, [this](const QString& text)
		{
			ui.inputRMB->setText(QString::number(text.toDouble() * 7.33));
		});

	connect(ui.inputRMB, &QLineEdit::textChanged, this, [this](const QString& text)
		{
			ui.inputDollar->setText(QString::number(text.toDouble() / 7.33));
		});
}

void MoneyPageWidget::reTranslate(const QString& fileName)
{
	QTranslator* translator = new QTranslator(this);
	if (translator->load(fileName))
		ui.retranslateUi(this);
}
