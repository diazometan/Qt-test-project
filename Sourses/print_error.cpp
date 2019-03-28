#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::printErrorQuery(QSqlQuery query)
{
	qDebug() << "Error" << query.lastError();
	exit (1);
}

void MainWindow::printErrorOpen(QSqlDatabase sdb)
{
	qDebug() << sdb.lastError().text();
	exit (1);
}
