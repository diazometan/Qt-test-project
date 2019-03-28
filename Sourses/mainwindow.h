#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>

#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QSqlDriver>

#include <QVector>

#define WF 3
#define UC 3.6E+9
#define GC 0.1
#define TIME 1800

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void addPoint(double x, double y);
	void addPointtoLine(double x, double y);
	void addConstPlot(double x, double y);
	void clearData();
	void plot();

	double calculation(QVector<double> rf, QVector<double> fuel, QVector<double> decay, QVector<double> doza,
					   QVector<double> e_grd, QVector<double> h_grd, double t);
	double firstPart(QVector<double> rf, QVector<double> fuel, QVector<double> decay,
					  QVector<double> doza, double t);
	double secondPartMin(QVector<double> e_grd, QVector<double> h_grd, QVector<double> rf, QVector<double> decay,
						   QVector<double> fuel, double t);
	[[ noreturn ]] void printErrorQuery(QSqlQuery query);
	[[ noreturn ]] void printErrorOpen(QSqlDatabase sdb);

	void readDataBase(QVector<double>& fuel, QVector<double>& decay, QVector<double>& rf,
						QVector<double>& doza, QVector<double>& e_grd, QVector<double>& h_grd);
	void creatPlot();
	void initPlot();

private slots:
	void on_actionNew_triggered();

	void on_actionOpen_triggered();

	void on_Add_clicked();

	void on_Clear_clicked();

	void on_actionPrint_triggered();

	void on_Calc_clicked();

private:
	Ui::MainWindow *ui;

	QString currentFile = "";

	QVector<double> qv_x, qv_y;
	QVector<double> v_x, v_y;
	QVector<double> const_x, const_y;
};

#endif // MAINWINDOW_H
