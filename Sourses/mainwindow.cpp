#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowTitle("OIL1");
	ui->Add->setVisible(false);
	ui->Calc->setVisible(false);
	connect(ui->Add, SIGNAL (released()), this, SLOT (on_actionPrint_triggered()));
	init_plot();
}

MainWindow::~MainWindow()
{
	delete ui;
}
