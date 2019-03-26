#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Add->setVisible(false);
    ui->Calc->setVisible(false);
    connect(ui->Add, SIGNAL (released()), this, SLOT (on_actionPrint_triggered()));
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle((QCPGraph::lsNone));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->plot->replot();
    ui->plot->update();
}

QVector<double> MainWindow::base_one()
{
    QSqlDatabase sdb;
    QVector<double> tmp(38, 0);
    int i = 0;

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../test/database.db3");
    if (!sdb.open())
    {
          qDebug() << "Open bug" << sdb.lastError().text();
          return (tmp);
    }
    QSqlQuery query;
    if (!query.exec("SELECT Radio, Fuel FROM Inventory"))
    {
        qDebug() << "Error with query" << query.lastError();
        return (tmp);
    }
    while (query.next() || i < tmp.size())
    {
        tmp[i] = query.value(1).toDouble();
        i++;
    }
    return (tmp);
}

QVector<double> MainWindow::base_two()
{
    QSqlDatabase sdb;
    QVector<double> tmp(38, 0);
    int i = 0;

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../test/database_1.db3");
    if (!sdb.open())
    {
          qDebug() << "Open bug" << sdb.lastError().text();
          return (tmp);
    }
    QSqlQuery query;
    if (!query.exec("SELECT Radio, Half_life, Decay FROM Half_life"))
    {
        qDebug() << "Error with query" << query.lastError();
        return (tmp);
    }
    while (query.next() || i < tmp.size())
    {
        tmp[i] = query.value(2).toDouble();
        i++;
    }
    return (tmp);
}

QVector<double> MainWindow::base_three()
{
    QSqlDatabase sdb;
    QVector<double> tmp(38, 0);
    int i = 0;

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../test/database_3.db3");
    if (!sdb.open())
    {
          qDebug() << "Open bug" << sdb.lastError().text();
          return (tmp);
    }
    QSqlQuery query;
    if (!query.exec("SELECT Radio, Doza FROM Ambient"))
    {
        qDebug() << "Error with query" << query.lastError();
        return (tmp);
    }
    while (query.next() || i < tmp.size())
    {
        tmp[i] = query.value(1).toDouble();
        i++;
    }
    return (tmp);
}

QVector<double> MainWindow::base_four()
{
    QSqlDatabase sdb;
    QVector<double> tmp(76, 0);
    int i = 0;

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../test/database_4.db3");
    if (!sdb.open())
    {
          qDebug() << "Open bug" << sdb.lastError().text();
          return (tmp);
    }
    QSqlQuery query;
    if (!query.exec("SELECT Radio, E_grd, H_grd FROM Conversion"))
    {
        qDebug() << "Error with query" << query.lastError();
        return (tmp);
    }
    while (query.next() || i < tmp.size())
    {
        tmp[i] = query.value(1).toDouble();
        i++;
        tmp[i] = query.value(2).toDouble();
        i++;
    }
    return (tmp);
}

double MainWindow::calculation(QVector<double> rf, QVector<double> fuel, QVector<double> decay, QVector<double> doza, QVector<double> e_grd, double t)
{
   double first;
   double second;

   first = first_part(rf, fuel, decay, doza, t);
   second = second_part_min(e_grd, rf, decay, fuel, t);
   return (first * second);
}

double MainWindow::first_part(QVector<double> rf, QVector<double> fuel, QVector<double> decay, QVector<double> doza, double t)
{
    double sum;
    double first;
    int i;

    i = 0;
    sum = 0.0;
    first = 0.0;
    while (i < rf.size())
    {
        sum += fuel[i] * exp(-(decay[i] * (t - TIME))) * rf[i];
        i++;
    }
    i = 0;
    while (i < rf.size())
    {
        first += (fuel[i] * exp(-(decay[i] * (t - TIME))) * rf[i]) / sum * doza[i];
        i++;
    }
    first *= (WF * UC);
    return (first);
}

double MainWindow::second_part_min(QVector<double> e_grd, QVector<double> rf, QVector<double> decay, QVector<double> fuel, double t)
{
    double a_1;
    double a_2;
    double sum_1;
    double sum_2;
    double sum;
    int i;
    int j;

    i = 0;
    j = 0;
    sum_1 = 0.0;
    sum_2 = 0.0;
    sum = 0.0;
    while (i < rf.size())
    {
        sum += fuel[i] * exp(-(decay[i] * (t - TIME))) * rf[i];
        i++;
    }
    i = 0;
    while (i < rf.size())
    {
        sum_1 += e_grd[j] * fuel[i] * exp(-(decay[i] * (t - TIME))) * rf[i] / sum;
        i++;
        j += 2;
    }
    i = 0;
    j = 1;
    while (i < rf.size())
    {
        sum_2 += e_grd[j] * fuel[i] * exp(-(decay[i] * (t - TIME))) * rf[i] / sum;
        i++;
        j += 2;
    }
    a_1 = GC / sum_1;
    a_2 = GC / sum_2;
    if (a_1 < a_2)
        return (a_1);
    else
        return (a_2);
}

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
    QString str;
    double t;
    double day;
    double ret;

    fuel = base_one();
    decay = base_two();
    doza = base_three();
    e_grd = base_four();
    str = ui->time->text();
    day = str.toDouble();
    t = 86400.0 * day;
    /*foreach(auto e, e_grd)
    {
        str += QString::number(e);
        str += "\n";
    }
    ui->textEdit->insertPlainText(str);*/
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return ;
    }
    QSqlDatabase sdb;
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(currentFile);
    if (!sdb.open())
    {
          qDebug() << sdb.lastError().text();
          return ;
    }
    QSqlQuery query;
    if (!query.exec("SELECT Radio, RF FROM Mix"))
    {
        qDebug() << "Error" << query.lastError();
        return ;
    }
    while (query.next())
        rf.append(query.value(1).toDouble());
    file.close();
    ret = calculation(rf, fuel, decay, doza, e_grd, t);
    str = QString::number(ret);
    ui->textEdit->setText(str);
    ui->Calc->setVisible(true);
    on_actionPrint_triggered();
    addPoint(day, ret);
    plot();
}

void MainWindow::on_actionPrint_triggered()
{
    ui->plot->xAxis->setLabel("Time after shutdown t[days]");
    ui->plot->yAxis->setLabel("OIL1(t, mix) [mSv/h]");
    ui->plot->xAxis->setRange(0.1, 100.0);
    ui->plot->yAxis->setRange(100, 10000);
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
    QString str;
    QFile file(currentFile);
    double t;
    double day;
    double ret;

    fuel = base_one();
    decay = base_two();
    doza = base_three();
    e_grd = base_four();
    str = ui->time->text();
    day = str.toDouble();
    t = 86400.0 * day;
    ui->textEdit->setText("KEK\n");
    QSqlDatabase sdb;
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(currentFile);
    if (!sdb.open())
    {
          qDebug() << sdb.lastError().text();
          return ;
    }
    QSqlQuery query;
    if (!query.exec("SELECT Radio, RF FROM Mix"))
    {
        qDebug() << "Error" << query.lastError();
        return ;
    }
    while (query.next())
        rf.append(query.value(1).toDouble());
    file.close();
    ret = calculation(rf, fuel, decay, doza, e_grd, t);
    str = QString::number(ret);
    ui->textEdit->setText(str);
    addPoint(day, ret);
    plot();
}
