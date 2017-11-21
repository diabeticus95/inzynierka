#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include "bmp/EasyBMP.h"
#include "Bitmap.h"
#include "Lens.h"
#include "Zernike.h"
#include <vector>
#include <iostream>
#include <QByteArray>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	for (int i = 0; i < 21; i++){
			ui->boxZernike->addItem("Z "+QString::number(i));
	}

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_button_genLens_clicked()
{
	double f = this->ui->textEdit_ogniskowa->toPlainText().toDouble();
	int size =  this->ui->textEdit_size->toPlainText().toInt();
	double probkowanie =  (double)1000000/this->ui->textEdit_sampling->toPlainText().toDouble();
	double lambda =  this->ui->textEdit_lambda->toPlainText().toDouble() * 0.000000001;
	this->soczewka = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::paraxial_formula);
	QString nazwaStr = this->ui->lineEdit_nazwa->text();
	nazwaStr.append(".bmp");
	QByteArray ba = nazwaStr.toLatin1();
	char *nazwa = ba.data();
	soczewka->returnBitmap()->generateImage(nazwa);
}

void MainWindow::on_push_addToVector_clicked()
{
	std::unique_ptr<DiffractiveStructure> zernik = std::make_unique<Zernike>(soczewka->returnBitmap()->row_count,
																			 soczewka->returnBitmap()->row_count,
																			 this->ui->lineZernCoeff->text().toDouble(),
																			 zernFuncs[this->ui->boxZernike->currentIndex()]);
	toMerge.push_back(zernik.get());
}

void MainWindow::on_push_generateZern_clicked()
{
	toMerge.push_back(soczewka.get());
	Bitmap merczLens(soczewka->returnBitmap()->row_count,soczewka->returnBitmap()->row_count);
/*	merczLens.mergeMaps(toMerge);
	QString nazwaStr = this->ui->lineEdit_nazwaZern->text();
	nazwaStr.append(".bmp");
	QByteArray ba = nazwaStr.toLatin1();
	char *nazwa = ba.data();
	merczLens.generateImage(nazwa);
*/
}
