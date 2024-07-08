#include "plot.h"

#include "ui_plot.h"

Plot::Plot(QWidget *parent) : QWidget(parent), ui(new Ui::Plot) {
  ui->setupUi(this);
}

Plot::~Plot() { delete ui; }

void Plot::paintGraph(QString Y1, double X1, double xMax, double yMax,
                      double xMin, double yMin, double step) {
  char *Cstr_temp = Y1.toLocal8Bit().data();  // Qstring in *str
  double xBegin = xMin, xEnd = xMax, h = step, Y;
  QVector<double> x, y;
  ui->widget->clearGraphs();
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);

  for (X1 = xBegin; X1 <= xEnd; X1 += h) {
    Y = evaluateExpression(Cstr_temp, X1);
    x.push_back(X1);
    y.push_back(Y);
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}
