#include "mainwindow.h"
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
	CreateDirectoryA("tmp", NULL);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
