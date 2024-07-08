#include "credit.h"

#include <math.h>

#include <QIntValidator>
#include <QMessageBox>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->sum->setValidator(new QDoubleValidator(this));
  ui->procent->setValidator(new QDoubleValidator(this));
  ui->term->setValidator(new QIntValidator(this));
  connect(ui->diffType, SIGNAL(clicked()), this, SLOT(onDiffClicked()));
  connect(ui->annType, SIGNAL(clicked()), this, SLOT(onAnnClicked()));
}

Credit::~Credit() { delete ui; }

void Credit::clearOutput() {
  ui->output->setText("");
  ui->cr_pereplata->setText("");
  ui->total_cr->setText("");
}

void Credit::onDiffClicked() {
  if (ui->procent->text().isEmpty() || ui->sum->text().isEmpty() ||
      ui->term->text().isEmpty()) {
    clearOutput();
    QMessageBox::critical(this, "Ошибка",
                          "Пожалуйста, заполните все обязательные поля.");
  } else if (ui->sum->text().toDouble() < 1000 ||
             ui->sum->text().toDouble() > 150000000) {
    clearOutput();
    QMessageBox::critical(this, "Ошибка",
                          "Пожалуйста, введите сумму от 1 000 до 150 000 000 "
                          "₽.");
  } else {
    QString resultPayment = "", resultOverpayment = "";
    QString resultTotalCredit = "";
    clearOutput();
    double interestAmount, monthlyPayment = 0, totalPayment = 0;

    QString initialAmountStr = ui->sum->text();
    double initialAmount = initialAmountStr.toDouble();

    QString interestRateStr = ui->procent->text();
    double interestRate = interestRateStr.toDouble();

    int creditTerm = ui->term->text().toInt();
    int totalMonths = creditTerm * 12;
    double loanBody = initialAmount / totalMonths;
    double originalLoanAmount = initialAmount;

    while (totalMonths != 0) {
      interestAmount = initialAmount * (interestRate / 100) / 12;
      initialAmount -= loanBody;
      monthlyPayment = interestAmount + loanBody;
      totalPayment += monthlyPayment;
      resultPayment = QString::number(monthlyPayment);
      ui->output->setText(ui->output->text() + resultPayment + " Руб " + "\n");
      totalMonths--;
    }

    resultTotalCredit = QString::number(totalPayment);
    ui->total_cr->setText(resultTotalCredit + " Руб");
    double overpayment = totalPayment - originalLoanAmount;
    resultOverpayment = QString::number(overpayment);
    ui->cr_pereplata->setText(resultOverpayment + " Руб");
  }
}

void Credit::onAnnClicked() {
  if (ui->procent->text().isEmpty() || ui->sum->text().isEmpty() ||
      ui->term->text().isEmpty()) {
    clearOutput();
    QMessageBox::critical(this, "Ошибка",
                          "Пожалуйста, заполните все обязательные поля.");
  } else if (ui->sum->text().toDouble() < 1000 ||
             ui->sum->text().toDouble() > 150000000) {
    clearOutput();
    QMessageBox::critical(this, "Ошибка",
                          "Пожалуйста, введите сумму от 1 000 до 150 000 000 "
                          "₽.");
  } else {
    QString resultPayment = "", resultOverpayment = "";
    QString resultTotalCredit = "";
    clearOutput();

    QString initialAmountStr = ui->sum->text();
    double initialAmount = initialAmountStr.toDouble();

    QString interestRateStr = ui->procent->text();
    double interestRate = interestRateStr.toDouble();

    int creditTerm = ui->term->text().toInt();
    int totalMonths = creditTerm * 12;
    double monthlyInterestRate = interestRate / 100 / 12;

    double annuityFactor =
        monthlyInterestRate / (1 - pow(1 + monthlyInterestRate, -totalMonths));
    double monthlyPayment = initialAmount * annuityFactor;
    double totalPayment = monthlyPayment * totalMonths;

    resultPayment = QString::number(monthlyPayment);
    ui->output->setText(resultPayment + " Руб");

    resultTotalCredit = QString::number(totalPayment);
    ui->total_cr->setText(resultTotalCredit + " Руб");

    double overpayment = totalPayment - initialAmount;
    resultOverpayment = QString::number(overpayment);
    ui->cr_pereplata->setText(resultOverpayment + " Руб");
  }
}
