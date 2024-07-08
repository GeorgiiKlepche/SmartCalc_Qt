#include "depocit.h"

#include <QIntValidator>
#include <QMessageBox>
#include <cmath>

#include "ui_depocit.h"

depocit::depocit(QWidget *parent) : QMainWindow(parent), ui(new Ui::depocit) {
  ui->setupUi(this);
  ui->sum->setValidator(new QDoubleValidator(this));
  ui->procent->setValidator(new QDoubleValidator(this));
  ui->taxRate->setValidator(new QIntValidator(this));
  ui->term->setValidator(new QIntValidator(this));

  connect(ui->calculateButton, SIGNAL(clicked()), this, SLOT(calculate()));
}

depocit::~depocit() { delete ui; }

void depocit::calculate() {
  QString sumText = ui->sum->text();
  QString procentText = ui->procent->text();
  QString termText = ui->term->text();
  QString taxText = ui->taxRate->text();

  if (sumText.isEmpty() || procentText.isEmpty() || termText.isEmpty() ||
      termText.isEmpty() || taxText.isEmpty()) {
    QMessageBox::critical(this, "Ошибка",
                          "Пожалуйста, заполните все обязательные поля.");
  } else {
    double initialAmount = sumText.toDouble();
    double interestRate = procentText.toDouble();
    double taxRate = taxText.toDouble();
    int period = termText.toInt();
    int capitalizationPeriods = ui->taxRate->text().toInt();
    if (initialAmount <= 0 || interestRate <= 0 || interestRate <= 0 ||
        period <= 0) {
      QMessageBox::critical(this, "Ошибка",
                            "Пожалуйста, заполните все обязательные поля.");
    } else if (initialAmount < 1000) {
      QMessageBox::critical(this, "Ошибка",
                            "Пожалуйста, введите сумму больше 1000.");
    } else {
      std::vector<double> deposits = parseNumbers(ui->deposits->text());
      std::vector<double> withdrawals = parseNumbers(ui->withdrawals->text());

      double interestAmount = calculateInterest(initialAmount, interestRate,
                                                period, capitalizationPeriods);
      double taxAmount = calculateTax(interestAmount, taxRate);
      double finalAmount = calculateFinalAmount(
          initialAmount, interestAmount, taxAmount, deposits, withdrawals);

      ui->interestAmountOutput->setText(QString::number(interestAmount));
      ui->taxAmountOutput->setText(QString::number(taxAmount));
      ui->finalAmountOutput->setText(QString::number(finalAmount));
    }
  }
}

double depocit::calculateInterest(double initialAmount, double interestRate,
                                  int period, int capitalizationPeriods) {
  return initialAmount *
             std::pow(1 + (interestRate / 100) / capitalizationPeriods,
                      period * capitalizationPeriods) -
         initialAmount;
}

double depocit::calculateTax(double interestAmount, double taxRate) {
  return interestAmount * (taxRate / 100);
}

double depocit::calculateFinalAmount(double initialAmount,
                                     double interestAmount, double taxAmount,
                                     const std::vector<double> &deposits,
                                     const std::vector<double> &withdrawals) {
  double finalAmount = initialAmount + interestAmount - taxAmount;

  for (double deposit : deposits) {
    finalAmount += deposit;
  }

  for (double withdrawal : withdrawals) {
    finalAmount -= withdrawal;
  }

  return finalAmount;
}

double depocit::calculateTotalInterest(double initialAmount,
                                       double interestRate, int period,
                                       int capitalizationPeriods,
                                       double taxRate) {
  double totalInterest = calculateInterest(initialAmount, interestRate, period,
                                           capitalizationPeriods);

  if (capitalizationPeriods == 0) {
    totalInterest -= calculateTax(totalInterest, taxRate);
  } else {
    double accumulatedAmount = initialAmount;

    for (int i = 1; i <= period * capitalizationPeriods; ++i) {
      accumulatedAmount +=
          accumulatedAmount * (interestRate / 100) / capitalizationPeriods;

      if (i % capitalizationPeriods == 0) {
        double interestEarned = accumulatedAmount - initialAmount;
        double taxAmount = calculateTax(interestEarned, taxRate);
        totalInterest += interestEarned - taxAmount;
      }
    }
  }

  return totalInterest;
}
std::vector<double> depocit::parseNumbers(const QString &input) {
  QStringList parts = input.split(' ');
  std::vector<double> numbers;
  for (const QString &part : parts) {
    numbers.push_back(part.toDouble());
  }
  return numbers;
}
