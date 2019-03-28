#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_actionNew_triggered()
{
	currentFile.clear();
	ui->textEdit->setText((QString()));
}

void MainWindow::on_actionOpen_triggered()
{
	QVector<double> fuel;
	QVector<double> decay;
	QVector<double> rf;
	QVector<double> doza;
	QVector<double> e_grd;
	QVector<double> h_grd;
	QString str;

	double t;
	double day;
	double ret;

	str = ui->time->text();
	day = str.toDouble();
	t = 86400.0 * day;
	QString filename = QFileDialog::getOpenFileName(this, "Open the file");
	QFile file(filename);
	currentFile = filename;
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
		return ;
	}
    readDataBase(fuel, decay, rf, doza, e_grd, h_grd);
	file.close();
	ret = calculation(rf, fuel, decay, doza, e_grd, h_grd, t);
    str = QString::number(ret);
    ui->textEdit->setText(str);
	ui->Calc->setVisible(true);
	on_actionPrint_triggered();
	addPoint(day, ret);
    creatPlot(fuel, decay, rf, doza, e_grd, h_grd);
	plot();
}

void MainWindow::on_actionPrint_triggered()
{
	ui->plot->xAxis->setLabel("Time after shutdown t[days]");
	ui->plot->yAxis->setLabel("OIL1(t, mix) [mSv/h]");
	ui->plot->xAxis->setRange(0.1, 100.0);
	ui->plot->yAxis->setRange(100, 5000);
	ui->plot->replot();
	ui->plot->update();

	ui->Add->setVisible(true);
}

void MainWindow::on_Add_clicked()
{
	addPoint(ui->d_x->value(), ui->d_y->value());
	plot();
}

void MainWindow::on_Clear_clicked()
{
	clearData();
	plot();
}

void MainWindow::on_Calc_clicked()
{
	QVector<double> fuel;
	QVector<double> decay;
	QVector<double> rf;
	QVector<double> doza;
	QVector<double> e_grd;
	QVector<double> h_grd;
	QString str;

	QFile file(currentFile);

	double t;
	double day;
	double ret;

	str = ui->time->text();
	day = str.toDouble();
	t = 86400.0 * day;
	readDataBase(fuel, decay, rf, doza, e_grd, h_grd);
	file.close();
	ret = calculation(rf, fuel, decay, doza, e_grd, h_grd, t);
	str = QString::number(ret);
	ui->textEdit->setText(str);
	addPoint(day, ret);
	plot();
}
