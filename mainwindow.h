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
    void clearData();
    void plot();

    QVector<double> base_one();
    QVector<double> base_two();
    QVector<double> base_three();
    QVector<double> base_four();

    double calculation(QVector<double> rf, QVector<double> fuel, QVector<double> decay, QVector<double> doza, QVector<double> e_grd, double t);
    double first_part(QVector<double> rf, QVector<double> fuel, QVector<double> decay, QVector<double> doza, double t);
    double second_part_min(QVector<double> e_grd, QVector<double> rf, QVector<double> decay, QVector<double> fuel, double t);

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
};

#endif // MAINWINDOW_H
