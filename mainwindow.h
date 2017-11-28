#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <vector>
#include "DiffractiveStructure.h"
#include "Zernike.h"
#include "Lens.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_button_genLens_clicked();

	void on_push_addToVector_clicked();

	void on_push_generateZern_clicked();

	void on_push_miniMap_clicked();

	void on_push_miniMapZern_clicked();

private:
	Ui::MainWindow *ui;
	std::unique_ptr<DiffractiveStructure> soczewka;
	std::vector<DiffractiveStructure*> toMerge;
	typedef double(*zernFunc)(double, double);
	zernFunc zernFuncs[21] = {Zernike::Z0, Zernike::Z1, Zernike::Z2, Zernike::Z3, Zernike::Z4, Zernike::Z5, Zernike::Z6, Zernike::Z7, Zernike::Z8, Zernike::Z9, Zernike::Z10, Zernike::Z11, Zernike::Z12, Zernike::Z13, Zernike::Z14, Zernike::Z15, Zernike::Z16, Zernike::Z17, Zernike::Z18, Zernike::Z19, Zernike::Z20};
	std::vector<std::unique_ptr<DiffractiveStructure>> zernikList;
};

#endif // MAINWINDOW_H
