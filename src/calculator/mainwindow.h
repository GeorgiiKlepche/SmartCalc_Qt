#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "credit.h"
#include "depocit.h"
#include "plot.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  Plot plot;
  depocit dep;
  Credit cred;
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void button_click();
  void buttonDot_click();
  void buttonBr_click();
  void buttonAC_click();
  void buttonEQ_click();
  void buttonPlot_click();
  void buttonCredit_click();
  void buttonDeposit_click();

  void on_MainWindow_destroyed();
};
#endif  // MAINWINDOW_H
