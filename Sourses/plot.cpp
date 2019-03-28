#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::addPoint(double x, double y)
{
	qv_x.append(x);
	qv_y.append(y);
}

void MainWindow::addPointtoLine(double x, double y)
{
	v_x.append(x);
	v_y.append(y);
}

void MainWindow::addConstPlot(double x, double y)
{
	const_x.append(x);
	const_y.append(y);
}

void MainWindow::clearData()
{
	qv_x.clear();
	qv_y.clear();
}

void MainWindow::plot()
{
	ui->plot->graph(0)->setData(qv_x, qv_y);
	ui->plot->graph(1)->setData(v_x, v_y);
	ui->plot->graph(2)->setData(const_x, const_y);
	ui->plot->replot();
	ui->plot->update();
}

void MainWindow::creatPlot(QVector<double> fuel, QVector<double> decay, QVector<double> rf,
                           QVector<double> doza, QVector<double> e_grd, QVector<double> h_grd)
{
	double t;
	double step;
    QString str;

	t = 0.1;
    step = 1.0;
	while (t <= 100.0001)
    {
        addPointtoLine(t, calculation(rf, fuel, decay, doza, e_grd, h_grd, 86400 * t));
        addConstPlot(t, 1000);
		if (t == 1.0 || t == 10.0 || t == 100.0)
		{
			t *= 10.0;
			step *= 10.0;
		}
		else
			t += 0.5 * step;
	}
}

void MainWindow::initPlot()
{
	ui->plot->addGraph();
	ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
	ui->plot->graph(0)->setLineStyle((QCPGraph::lsNone));
	ui->plot->addGraph();
	ui->plot->graph(1)->setPen(QPen(Qt::darkMagenta));
	ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QPen(Qt::red));
}
