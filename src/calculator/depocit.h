#ifndef DEPOCIT_H
#define DEPOCIT_H

#include <QDialog>
#include <QMainWindow>
#include <QObject>
#include <QString>
#include <vector>

namespace Ui {
class depocit;
}

class depocit : public QMainWindow {
  Q_OBJECT

 public:
  explicit depocit(QWidget *parent = nullptr);
  ~depocit();
 private slots:
  void calculate();
  double calculateTotalInterest(double initialAmount, double interestRate,
                                int period, int capitalizationPeriods,
                                double taxRate);
  std::vector<double> parseNumbers(const QString &input);
  double calculateInterest(double initialAmount, double interestRate,
                           int period, int capitalizationPeriods);
  double calculateTax(double interestAmount, double taxRate);
  double calculateFinalAmount(double initialAmount, double interestAmount,
                              double taxAmount,
                              const std::vector<double> &deposits,
                              const std::vector<double> &withdrawals);

 private:
  Ui::depocit *ui;
};

#endif  // DEPOCIT_H
