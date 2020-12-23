#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.resize(1024, 768);
	window.setWindowTitle("Alpha Pick");
	window.show();
	
	return app.exec();
}
