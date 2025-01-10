#include "Headers.h"
#include "MainWindow.h"
#include "SciencePage.h"
#include "Calculate.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	Calculate* calculate = Calculate::instance();

	QString string = "A8";

	//MainWindow window;
	//window.show();
	//QString s = "123123123123";
	//s.replace("123", "111");


	return QApplication::exec();
}

#include "main.moc"