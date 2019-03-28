#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::print_error_query(QSqlQuery query)
{
	qDebug() << "Error" << query.lastError();
	exit (1);
}

void MainWindow::print_error_open(QSqlDatabase sdb)
{
	qDebug() << sdb.lastError().text();
	exit (1);
}
