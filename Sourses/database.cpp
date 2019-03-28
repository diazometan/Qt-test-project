#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::readDataBase(QVector<double>& fuel, QVector<double>& decay, QVector<double>& rf,
						QVector<double>& doza, QVector<double> e_grd, QVector<double>& h_grd)
{
	QSqlDatabase sdb;
	sdb = QSqlDatabase::addDatabase("QSQLITE");
	sdb.setDatabaseName(currentFile);
	if (!sdb.open())
		print_error_open(sdb);

	QSqlQuery query;
	QSqlQuery query_1;
	QSqlQuery query_2;
	QSqlQuery query_3;
	QSqlQuery query_4;

	if (!query.exec("SELECT Radio, RF FROM Mix"))
		printErrorQuery(query);
	while (query.next())
		rf.append(query.value(1).toDouble());
	if (!query_1.exec("SELECT Radio, Fuel FROM Inventory"))
		printErrorQuery(query_1);
	while (query_1.next())
		fuel.append(query_1.value(1).toDouble());
	if (!query_2.exec("SELECT Radio, Half_life, Decay FROM Half_life"))
		printErrorQuery(query_2);
	while (query_2.next())
		decay.append(query_2.value(2).toDouble());
	if (!query_3.exec("SELECT Radio, Doza FROM Ambient"))
		printErrorQuery(query_3);
	while (query_3.next())
		doza.append(query_3.value(1).toDouble());
	if (!query_4.exec("SELECT Radio, E_grd, H_grd FROM Conversion"))
		printErrorQuery(query_4);
	while (query_4.next())
	{
		e_grd.append(query_4.value(1).toDouble());
		h_grd.append(query_4.value(2).toDouble());
	}
}
