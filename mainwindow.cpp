#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Add->setVisible(false);
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

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText((QString()));
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
    }
    setWindowTitle((filename));
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText((text));
    file.close();
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

void MainWindow::on_actionPrint_triggered()
{
    int x_1;
    int x_2;
    int y_1;
    int y_2;
    QString str_x_1;
    QString str_y_1;
    QString str_x_2;
    QString str_y_2;

    str_x_1 = ui->line_range_x_1->text();
    str_y_1 = ui->line_range_y_1->text();
    str_x_2 = ui->line_range_x_2->text();
    str_y_2 = ui->line_range_y_2->text();
    x_1 = str_x_1.toInt();
    y_1 = str_y_1.toInt();
    x_2 = str_x_2.toInt();
    y_2 = str_y_2.toInt();
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(x_1, x_2);
    ui->plot->yAxis->setRange(y_1, y_2);
    ui->plot->replot();
    ui->plot->update();

    ui->Add->setVisible(true);
}
