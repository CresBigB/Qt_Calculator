#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
{
	ui = new Ui::MainWindow;
	ui->setupUi(this);
	ui->scrollAreaLayout->setAlignment(Qt::AlignTop);
	QSettings setting("Calculate");
	restoreState(setting.value("windowState").toByteArray());
	SciencePageSignalsConnect();
	ProgrammerPageSignalsConnect();
	actionSignalConnect();
	whiteTheme();
}

MainWindow::~MainWindow()
{
	// 保存当前的布局
	QSettings settings("Calculate");
	settings.setValue("windowState", saveState());
}

void MainWindow::changePage(const Page page) const
{
	switch (page)
	{
	case Page::Standard:
		ui->stackedWidget->setCurrentIndex(0);
		qobject_cast<SciencePageWidget*>(ui->stackedWidget->currentWidget())->changeMode(SciencePageWidget::Mode::Standard);
		ui->historyWidget->show();
		ui->expression->show();
		break;
	case Page::Science:
		ui->stackedWidget->setCurrentIndex(0);
		qobject_cast<SciencePageWidget*>(ui->stackedWidget->currentWidget())->changeMode(SciencePageWidget::Mode::Science);
		ui->historyWidget->show();
		ui->expression->show();
		break;
	case Page::Programmer:
		ui->stackedWidget->setCurrentIndex(1);
		ui->historyWidget->show();
		ui->expression->show();
		break;
	case Page::Date:
		ui->stackedWidget->setCurrentIndex(2);
		ui->historyWidget->hide();
		ui->expression->hide();
		break;
	case Page::Money:
		ui->stackedWidget->setCurrentIndex(3);
		ui->historyWidget->hide();
		ui->expression->hide();
		break;
	}
}

void MainWindow::changeTheme(const Theme theme)
{
	switch (theme)
	{
	case Theme::Black:
		blackTheme();
		break;
	case Theme::White:
		whiteTheme();
		break;
	}
}

void MainWindow::changeLanguage(const Language language)
{
	QTranslator* translator = new QTranslator(this);
	QString file;
	switch (language)
	{
	case Language::Chinese:
		file = ":/new/prefix1/Translator/zh_cn.qm";
		break;
	case Language::English:
		file = ":/new/prefix1/Translator/en.qm";
		break;
	}
	if (!translator->load(file))
	{
		QMessageBox::critical(this, "错误", "翻译文件加载失败");
		return;
	}
	qApp->installTranslator(translator);
	ui->retranslateUi(this);
	ui->datePage->reTranslate(file);
	ui->moneyPage->reTranslate(file);
}

void MainWindow::addHistory(const QString& history)
{
	auto label = new QLabel(this);
	label->setText(history);
	ui->scrollAreaLayout->addWidget(label);
}

void MainWindow::showNumber(const QString& number) const
{
	ui->showNumber->setText(number);
	if (ui->stackedWidget->currentIndex() == 1)
	{
		auto page = qobject_cast<ProgrammerPageWidget*>(ui->stackedWidget->currentWidget());
		switch (page->getCurrentMode())
		{
		case ProgrammerPageWidget::Mode::HEX:
			page->showNumber(number.toInt(nullptr, 16));
			break;
		case ProgrammerPageWidget::Mode::DEC:
			page->showNumber(number.toInt());
			break;
		case ProgrammerPageWidget::Mode::OCT:
			page->showNumber(number.toInt(nullptr, 8));
			break;
		case ProgrammerPageWidget::Mode::BIN:
			page->showNumber(number.toInt(nullptr, 2));
			break;
		}
	}
}

void MainWindow::showExpression(const QString& expression) const
{
	ui->showExpression->setText(expression);
}

void MainWindow::SciencePageSignalsConnect()
{
	connect(ui->sciencePage, &SciencePageWidget::inputNumber, this, [this](const int num) {emit inputNumber(num); });
	connect(ui->sciencePage, &SciencePageWidget::inputOperator, this, [this](const QString& _operator) {emit inputOperator(_operator); });
	connect(ui->sciencePage, &SciencePageWidget::evaluate, this, [this] {emit evaluate(); });
	connect(ui->sciencePage, &SciencePageWidget::backSpace, this, [this] {emit backSpace(); });
	connect(ui->sciencePage, &SciencePageWidget::clean, this, [this] {emit clean(); });
	connect(ui->sciencePage, &SciencePageWidget::changePlusMinus, this, [this] {emit changePlusMinus(); });
}

void MainWindow::ProgrammerPageSignalsConnect()
{
	connect(ui->programmerPage, &ProgrammerPageWidget::inputNum, this, [this](const int num) {emit inputNumber(num); });
	connect(ui->programmerPage, &ProgrammerPageWidget::inputOperator, this, [this](const QString& _operator) {emit inputOperator(_operator); });
	connect(ui->programmerPage, &ProgrammerPageWidget::evaluate, this, [this] {emit evaluate(); });
	connect(ui->programmerPage, &ProgrammerPageWidget::backSpace, this, [this] {emit backSpace(); });
	connect(ui->programmerPage, &ProgrammerPageWidget::clean, this, [this] {emit clean(); });
	connect(ui->programmerPage, &ProgrammerPageWidget::changePlusMinus, this, [this] {emit changePlusMinus(); });
}

void MainWindow::actionSignalConnect()
{
	connect(ui->standardMode, &QAction::triggered, this, [this] {changePage(Page::Standard); });
	connect(ui->scienceMode, &QAction::triggered, this, [this] {changePage(Page::Science); });
	connect(ui->programmerMode, &QAction::triggered, this, [this] {changePage(Page::Programmer); });
	connect(ui->date, &QAction::triggered, this, [this] {changePage(Page::Date); });
	connect(ui->money, &QAction::triggered, this, [this] {changePage(Page::Money); });
	connect(ui->whiteTheme, &QAction::triggered, this, [this] {whiteTheme(); });
	connect(ui->blackTheme, &QAction::triggered, this, [this] {blackTheme(); });
	connect(ui->actionEnglish, &QAction::triggered, this, [this] {changeLanguage(Language::English); });
	connect(ui->actionChinese, &QAction::triggered, this, [this] {changeLanguage(Language::Chinese); });
}

void MainWindow::blackTheme()
{
	QFile file(":/new/prefix1/black.css");
	if (file.open(QIODeviceBase::ReadOnly))
	{
		QTextStream stream(&file);
		QString style = stream.readAll();
		this->setStyleSheet(style);
	}
	else
		QMessageBox::critical(this, tr("错误"), tr("无法加载改样式"));
}

void MainWindow::whiteTheme()
{
	QFile file(":/new/prefix1/white.css");
	if (file.open(QIODeviceBase::ReadOnly))
	{
		QTextStream stream(&file);
		QString style = stream.readAll();
		this->setStyleSheet(style);
	}
	else
		QMessageBox::critical(this, tr("错误"), tr("无法加载改样式"));

}
