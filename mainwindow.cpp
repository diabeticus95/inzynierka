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
#include <QMessageBox>

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
	lensWvl = lambda;
	lensSam = probkowanie;
	lensF = f;
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
			this->ui->push_deleteAllZern->setEnabled(true);
	}
}


void MainWindow::on_push_deleteAllZern_clicked()
{
	this->ui->list_Zernik->clear();
	zernikList.clear();
	this->ui->listDeleter->setEnabled(false);
	this->ui->push_generateZern->setEnabled(false);
	this->ui->push_deleteAllZern->setEnabled(false);
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
	mergedMap = std::make_unique<Bitmap>(soczewka->returnBitmap()->row_count,soczewka->returnBitmap()->col_count);
	mergedMap->mergeMaps(toMerge);
	QString nazwaStr = this->ui->lineEdit_nazwaZern->text();
	nazwaStr.append(".bmp");
	QByteArray ba = nazwaStr.toLatin1();
	char *nazwa = ba.data();
	mergedMap->generateImage(nazwa);
	this->ui->push_FFT->setEnabled(true);
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



void MainWindow::on_actionO_programie_triggered()
{
	QMessageBox::about(0,"LEns GENerator based on Diffraction & Aberrations.","Opracowany na Wydziale Fizyki Politechniki Warszawskiej\nAutor: Patryk Kowalski\nOpiekun naukowy: Dr inż Agnieszka Siemion\n\nProgram jest narzędziem umożliwiajacym generację soczewek dyfrakcyjnych z aberracjami, oraz symulowanie ich funkcji rozmycia punktu.\nZostał opracowany w ramach pracy inżynierskiej\nKontakt z autorem: patryk95kowalski@gmail.com");
 }

void MainWindow::on_push_FFT_clicked()
{

	if (this->ui->radioAmp->isChecked()){
		Bitmap fftMap = fft(*mergedMap, lensF*lensSam,lensWvl*lensSam, sqrt);
		QString nazwaStr = this->ui->lineEdit_nazwaZern->text() + "AmpPSF";
		nazwaStr.append(".bmp");
		QByteArray ba = nazwaStr.toLatin1();
		char *nazwa = ba.data();
		fftMap.generateImage(nazwa);}
	else if (this->ui->radioLog->isChecked()){
		Bitmap fftMap = fft(*mergedMap, lensF*lensSam,lensWvl*lensSam, log);
		QString nazwaStr = this->ui->lineEdit_nazwaZern->text() + "LogPSF";
		nazwaStr.append(".bmp");
		QByteArray ba = nazwaStr.toLatin1();
		char *nazwa = ba.data();
		fftMap.generateImage(nazwa);}
}
