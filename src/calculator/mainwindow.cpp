#include "mainwindow.h"

#include <QIntValidator>
#include <QTextStream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->lineX->setValidator(new QDoubleValidator(this));
  ui->lineXmin->setValidator(new QDoubleValidator(this));
  ui->lineXmax->setValidator(new QDoubleValidator(this));
  ui->lineYmin->setValidator(new QDoubleValidator(this));
  ui->lineYmax->setValidator(new QDoubleValidator(this));
  ui->lineStep->setValidator(new QDoubleValidator(this));

  ui->label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  connect(ui->button0, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button1, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button2, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button3, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button4, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button5, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button6, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button7, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button8, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->button9, SIGNAL(clicked()), this, SLOT(button_click()));

  connect(ui->buttonTan, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonAtan, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonCos, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonAcos, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonSin, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonAsin, SIGNAL(clicked()), this, SLOT(button_click()));

  connect(ui->buttonLog, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonLn, SIGNAL(clicked()), this, SLOT(button_click()));

  connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonSub, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonMult, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonDiv, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonMod, SIGNAL(clicked()), this, SLOT(button_click()));

  connect(ui->buttonPow, SIGNAL(clicked()), this, SLOT(button_click()));
    connect(ui->buttonSqrt, SIGNAL(clicked()), this, SLOT(button_click()));
  connect(ui->buttonX, SIGNAL(clicked()), this, SLOT(button_click()));

  connect(ui->buttonDot, SIGNAL(clicked()), this, SLOT(buttonDot_click()));
  connect(ui->buttonLBr, SIGNAL(clicked()), this, SLOT(buttonBr_click()));
  connect(ui->buttonRBr, SIGNAL(clicked()), this, SLOT(buttonBr_click()));
  connect(ui->buttonAC, SIGNAL(clicked()), this, SLOT(buttonAC_click()));
  connect(ui->buttonEQ, SIGNAL(clicked()), this, SLOT(buttonEQ_click()));
  connect(ui->buttonCredit, SIGNAL(clicked()), this,
          SLOT(buttonCredit_click()));
  connect(ui->buttonDeposit, SIGNAL(clicked()), this,
          SLOT(buttonDeposit_click()));

  connect(ui->buttonPlot, SIGNAL(clicked()), this, SLOT(buttonPlot_click()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::button_click() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (button != nullptr) {
    if (ui->label->text() == "0") {
      ui->label->setText(button->text());
    } else {
      ui->label->setText(ui->label->text() + button->text());
    }
  }
}

void MainWindow::buttonDot_click() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  ui->label->setText(ui->label->text() + button->text());
  if (ui->label->text() == '.') {
    ui->label->setText("0.");
  }
}

void MainWindow::buttonBr_click() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  QString text_label = ui->label->text();
  int flag_Lbr = std::count(text_label.begin(), text_label.end(), '(');
  int flag_Rbr = std::count(text_label.begin(), text_label.end(), ')');
  int flag_br = flag_Lbr - flag_Rbr;
  if (button == ui->buttonLBr) {
    ui->label->setText(ui->label->text() + button->text());
    flag_br++;
  } else if (button == ui->buttonRBr) {
    if (flag_br > 0) {
      flag_br--;
      ui->label->setText(ui->label->text() + button->text());
    }
  }
}

void MainWindow::buttonAC_click() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (button != nullptr) {
    ui->label->setText("");
  }
}

// проверка вывода в Си коде после конвертации
/*
extern "C" void processCString(const char* cstr) {
    printf("Received C-string: %s\n", cstr);
}
*/

void MainWindow::buttonEQ_click() {
  double result = 0.0;
  char* Cstr_temp = ui->label->text().toLocal8Bit().data();
  double qt_x = ui->lineX->text().toDouble();
  // processCString(str_temp);
  if (!validation(Cstr_temp)) {
    result = evaluateExpression(Cstr_temp, qt_x);
    QString str_total = QString::number(result);
    ui->label->setText(str_total);
  } else {
    ui->label->setText("Error");
  }
}

void MainWindow::buttonPlot_click() {
  double xMin = ui->lineXmin->text().toDouble();
  double xMax = ui->lineXmax->text().toDouble();
  double yMin = ui->lineYmin->text().toDouble();
  double yMax = ui->lineYmax->text().toDouble();
  double step = ui->lineStep->text().toDouble();

  if (!plotValid(xMax, xMin, yMax, yMin)) {
    double valueX = ui->lineX->text().toDouble();
    char* Cstr_temp =
        ui->label->text().toLocal8Bit().data();  // Qstring in *str
    // processCString(Cstr_temp);
    if (!validation(Cstr_temp)) {
      plot.show();
      plot.paintGraph((ui->label->text()), valueX, xMax, yMax, xMin, yMin,
                      step);
    }
  }
}

void MainWindow::buttonCredit_click() { cred.show(); }

void MainWindow::buttonDeposit_click() { dep.show(); }

void MainWindow::on_MainWindow_destroyed() { this->close(); }
