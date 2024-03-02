#ifndef SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_CREDITCALC_H
#define SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_CREDITCALC_H

#include <QDialog>

#include "../controller/controller.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {
class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(Controller *controller, QWidget *parent = nullptr);
  void InitializeUIValues();
  ~CreditCalc();

 private slots:
  void on_calculate_clicked();

 private:
  Ui::CreditCalc *ui;
  Controller *controller;
  void ClearUIFields();
  void UpdateListWidget();
};
}  // namespace s21

#endif  // SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_CREDITCALC_H
