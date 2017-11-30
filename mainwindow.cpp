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
	double f = this->ui->doubleSpinBox_ogniskowa->value();
	int size =  this->ui->spinBox_size->value();
	double probkowanie =  (double)1000000/this->ui->spinBox_sampling->value();
	double lambda =  this->ui->doubleSpinBox_wavelenght->value() * 0.000000001;
	if(this->ui->checkBox_paraxial->isChecked() == true)
		soczewka = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::paraxial_formula);
	else
		soczewka = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::non_paraxial_formula);
	QString nazwaStr = this->ui->lineEdit_nazwaPliku->text();
	nazwaStr.append(".bmp");
	QByteArray ba = nazwaStr.toLatin1();
	char *nazwa = ba.data();
	soczewka->returnBitmap()->generateImage(nazwa);
	this->ui->push_addToVector->setEnabled(true);
	this->ui->button_genLens->setEnabled(false);
}
void MainWindow::on_push_deleteLens_clicked()
{
	soczewka.reset(nullptr);
	this->ui->push_addToVector->setEnabled(false);
	if (zernikList.size() == 0){
		this->ui->push_generateZern->setEnabled(false);
	}
	this->ui->button_genLens->setEnabled(true);
}

void MainWindow::on_push_addToVector_clicked()
{
	std::unique_ptr<DiffractiveStructure> zernik = std::make_unique<Zernike>(soczewka->returnBitmap()->row_count,
																			 soczewka->returnBitmap()->row_count,
																			 this->ui->ZernCoeffSpinbox->value(),
																			 zernFuncs[this->ui->boxZernike->currentIndex()]);
	zernikList.push_back(std::move(zernik));
	QString string = this->ui->ZernCoeffSpinbox->textFromValue(this->ui->ZernCoeffSpinbox->value()) + " " + this->ui->boxZernike->currentText();
	this->ui->list_Zernik->addItem(string);
	this->ui->push_generateZern->setEnabled(true);
	this->ui->listDeleter->setEnabled(true);
}

void MainWindow::on_listDeleter_clicked()
{
	int index = this->ui->list_Zernik->currentIndex().row();
	this->ui->list_Zernik->takeItem(index);
	zernikList.erase(zernikList.begin()+index);
	if (zernikList.size() == 0){
		this->ui->listDeleter->setEnabled(false);
		this->ui->push_generateZern->setEnabled(false);
	}
}
void MainWindow::on_push_miniMapZern_clicked()
{
	int size = 256;
	char nazwa[] = "tmp/zernTMP.bmp";
	std::unique_ptr<DiffractiveStructure> zernik = std::make_unique<Zernike>(size,size,
																			 this->ui->ZernCoeffSpinbox->value(),
																			 zernFuncs[this->ui->boxZernike->currentIndex()]);
	zernik->returnBitmap()->generateImage(nazwa);
	QPixmap pixmap("tmp/zernTMP.bmp");
	this->ui->label_ZernPic->setPixmap(pixmap);
}

void MainWindow::on_push_generateZern_clicked()
{
	for (const auto& zern : zernikList){
		toMerge.push_back(zern.get());
	}
	toMerge.push_back(soczewka.get());
	Bitmap merczLens(soczewka->returnBitmap()->row_count,soczewka->returnBitmap()->row_count);
	merczLens.mergeMaps(toMerge);
	QString nazwaStr = this->ui->lineEdit_nazwaZern->text();
	nazwaStr.append(".bmp");
	QByteArray ba = nazwaStr.toLatin1();
	char *nazwa = ba.data();
	merczLens.generateImage(nazwa);
}


void MainWindow::on_push_miniMap_clicked()
{
	double f = this->ui->doubleSpinBox_ogniskowa->value();
	int size =  256;
	double probkowanie =  (double)1000000/this->ui->spinBox_sampling->value();
	double lambda =  this->ui->doubleSpinBox_wavelenght->value() * 0.000000001;
	std::unique_ptr<DiffractiveStructure> soczewkaMINI;
	if(this->ui->checkBox_paraxial->isChecked() == true)
		soczewkaMINI = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::paraxial_formula);
	else
		soczewkaMINI = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::non_paraxial_formula);
	char nazwa[] = "tmp/lensTMP.bmp";
	soczewkaMINI->returnBitmap()->generateImage(nazwa);
	QPixmap pixmap("tmp/lensTMP.bmp");
	this->ui->label_LensPic->setPixmap(pixmap);
//	label.setMask(pixmap.mask());
//	label.show();
}





