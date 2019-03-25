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

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_Add_clicked();

    void on_Clear_clicked();

    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;

    QString currentFile = "";

    QVector<double> qv_x, qv_y;
};

#endif // MAINWINDOW_H
