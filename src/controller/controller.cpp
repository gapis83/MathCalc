#include "controller.h"

s21::Controller::Controller(Ui_MainWindow* ui, s21::MyCalc* model)
    : ui(ui), model(model) {}

void s21::Controller::ProcessCalculation(std::string& input_string,
                                         std::string& x_line,
                                         std::string& output_string) {
  model->ResultCalculationProcess(input_string, x_line, output_string);
}

double s21::Controller::CalculateToDouble(std::string& input_string,
                                          std::string& x_line) {
  return model->CalculateResult(input_string, x_line);
}

void s21::Controller::InputLine(const std::string symbols) {
  input_string_ += symbols;
}

namespace s21 {
std::string Controller::GetInputString() const { return input_string_; }
}  // namespace s21

void s21::Controller::ClearStrings() {
  input_string_.clear();
  output_string_.clear();
}

void s21::Controller::RemoveLastCharacter() {
  if (!input_string_.empty()) {
    input_string_.pop_back();
  }
}

void s21::Controller::FillGraphValues(std::string& input_string, double x_max,
                                      double x_min, double y_max,
                                      double y_min) {
  model->CalculateGraphData(input_string, x_max, x_min, y_max, y_min);
}

namespace s21 {
const std::vector<double>& Controller::get_XData() const {
  return model->get_XData();
}
}  // namespace s21

namespace s21 {
const std::vector<double>& Controller::get_YData() const {
  return model->get_YData();
}
}  // namespace s21

void s21::Controller::ClearXData() { model->ClearVectorXData(); }

void s21::Controller::ClearYData() { model->ClearVectorYData(); }

bool s21::Controller::ValidateInputFields(const std::string& amount,
                                          const std::string& rate,
                                          const std::string& term) const {
  return model->ValidateUserInput(amount, rate, term);
}

void s21::Controller::CalculateCredit(const std::string& amount_std,
                                      const std::string& rate_std,
                                      const std::string& term_std,
                                      bool annuity) const {
  model->CalculateLoanParameters(amount_std, rate_std, term_std, annuity);
}

namespace s21 {
const std::string& Controller::get_overpayment_str() const {
  return model->get_overpayment_str();
}
}  // namespace s21

namespace s21 {
const std::string& Controller::get_total_payment_str() const {
  return model->get_total_payment();
}
}  // namespace s21

namespace s21 {
const std::vector<std::string>& Controller::get_monthly_payments() const {
  return model->get_monthly_payments();
}
}  // namespace s21
