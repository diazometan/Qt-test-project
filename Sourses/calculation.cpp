#include "mainwindow.h"
#include "ui_mainwindow.h"

double MainWindow::first_part(QVector<double> rf, QVector<double> fuel, QVector<double> decay,
                              QVector<double> doza, double t)
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

double MainWindow::second_part_min(QVector<double> e_grd, QVector<double> h_grd, QVector<double> rf,
                                   QVector<double> decay, QVector<double> fuel, double t)
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
        j++;
    }
    i = 0;
    j = 0;
    while (i < rf.size())
    {
        sum_2 += h_grd[j] * fuel[i] * exp(-(decay[i] * (t - TIME))) * rf[i] / sum;
        i++;
        j++;
    }
    a_1 = GC / sum_1;
    a_2 = GC / sum_2;
    if (a_1 < a_2)
        return (a_1);
    else
        return (a_2);
}

double MainWindow::calculation(QVector<double> rf, QVector<double> fuel, QVector<double> decay, QVector<double> doza,
                               QVector<double> e_grd, QVector<double> h_grd, double t)
{
   double first;
   double second;

   first = first_part(rf, fuel, decay, doza, t);
   second = second_part_min(e_grd, h_grd, rf, decay, fuel, t);
   return (first * second);
}
