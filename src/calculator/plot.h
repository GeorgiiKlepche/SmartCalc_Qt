#include <QWidget>

extern "C" {
#include "s21_calc.h"
}

namespace Ui {
class Plot;
}

class Plot : public QWidget {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  void paintGraph(QString Y1, double X1, double xMax, double yMax, double xMin,
                  double yMin, double step);
  ~Plot();

 private slots:

 private:
  Ui::Plot *ui;
};
