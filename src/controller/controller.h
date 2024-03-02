#ifndef SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_CONTROLLER_H
#define SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_CONTROLLER_H

#include <QObject>
#include <cmath>
#include <string>

#include "../model/calc_model.h"
#include "../view/qcustomplot.h"

class Ui_MainWindow;

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(Ui_MainWindow* ui, MyCalc* model);
  void ProcessCalculation(std::string& input_string, std::string& x_line,
                          std::string& output_string);
  double CalculateToDouble(std::string& input_string, std::string& x_line);
  void RemoveLastCharacter();
  void FillGraphValues(std::string& input_string, double x_max, double x_min,
                       double y_max, double y_min);
  const std::vector<double>& get_XData() const;
  const std::vector<double>& get_YData() const;
  void ClearXData();
  void ClearYData();
  bool ValidateInputFields(const std::string& amount, const std::string& rate,
                           const std::string& term) const;
  void CalculateCredit(const std::string& amount_std,
                       const std::string& rate_std, const std::string& term_std,
                       bool annuity) const;
  const std::string& get_overpayment_str() const;
  const std::string& get_total_payment_str() const;
  const std::vector<std::string>& get_monthly_payments() const;

 public slots:
  void InputLine(const std::string symbols);
  std::string GetInputString() const;
  void ClearStrings();

 private:
  Ui_MainWindow* ui;           // Указатель на UI
  MyCalc* model;               // Указатель на model
  std::string input_string_;   // строка для ввода
  std::string x_line_;         // строка x
  std::string output_string_;  // строка вывода
};
}  // namespace s21

#endif  // SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_CONTROLLER_H
