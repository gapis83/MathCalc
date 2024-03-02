#ifndef SRC_CALC_MODEL_H
#define SRC_CALC_MODEL_H

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <unordered_map>

const int kIncrementBy1 = 1;
const int kIncrementBy2 = 2;
const int kIncrementBy3 = 3;
#define NUMBERS "1234567890."
#define FUNCTIONS "mcstal"
#define K_NOTUSE "bfhjkp,"
#define SIGNS "+-*/^()"

enum ElementType { NUMBER, OPERATOR, FUNCTION };

struct RpnElement {
  ElementType type;
  double value;
  std::string operation;
  int priority;

  RpnElement(ElementType t, double val, const std::string& op, int prio)
      : type(t), value(val), operation(op), priority(prio) {}
  RpnElement(double val) : type(NUMBER), value(val), priority(0) {}
  RpnElement(const std::string& operation, int prio)
      : type(OPERATOR), operation(operation), priority(prio) {}
  RpnElement(const std::string& function_str)
      : type(FUNCTION), operation(function_str), priority(4) {}
};

namespace s21 {
class MyCalc {
 public:
  using StackType = std::stack<RpnElement>;
  using QueueType = std::queue<RpnElement>;

  void set_input_string(const std::string& input);
  void ResultCalculationProcess(std::string& input_string, std::string& x_line,
                                std::string& output_string);
  double ExpressionCalculate(const std::string& x_line);
  double CalculateResult(std::string& input_string, std::string& x_line);
  void CalculateGraphData(std::string& input_string, double x_max, double x_min,
                          double y_max, double y_min);
  const std::vector<double>& get_XData() const;
  const std::vector<double>& get_YData() const;
  void ClearVectorXData();
  void ClearVectorYData();
  bool ValidateUserInput(const std::string& amount, const std::string& rate,
                         const std::string& term) const;
  void CalculateLoanParameters(const std::string& amount,
                               const std::string& rate, const std::string& term,
                               bool annuity);
  const std::string& get_overpayment_str() const;
  const std::string& get_total_payment() const;
  const std::vector<std::string>& get_monthly_payments() const;

 private:
  std::string input_string_;
  std::string overpayment_str_;
  std::string total_payment_;
  std::vector<std::string> monthly_payments_;

  std::unordered_map<std::string, int> function_increments = {
      {"mod", kIncrementBy2},   {"sin(", kIncrementBy2},
      {"sqrt(", kIncrementBy3}, {"cos(", kIncrementBy2},
      {"tan(", kIncrementBy2},  {"log(", kIncrementBy2},
      {"ln(", kIncrementBy1}};

  std::unordered_map<std::string, std::function<double(double, double)>>
      binary_operations = {
          {"+", [](double a, double b) { return a + b; }},
          {"-", [](double a, double b) { return a - b; }},
          {"*", [](double a, double b) { return a * b; }},
          {"/", [](double a, double b) { return a / b; }},
          {"^", [](double a, double b) { return std::pow(a, b); }},
          {"mod", [](double a, double b) { return std::fmod(a, b); }}};

  std::unordered_map<std::string, std::function<double(double)>>
      unary_operations = {{"sin", [](double a) { return std::sin(a); }},
                          {"cos", [](double a) { return std::cos(a); }},
                          {"tan", [](double a) { return std::tan(a); }},
                          {"asin", [](double a) { return std::asin(a); }},
                          {"acos", [](double a) { return std::acos(a); }},
                          {"atan", [](double a) { return std::atan(a); }},
                          {"sqrt", [](double a) { return std::sqrt(a); }},
                          {"log", [](double a) { return std::log10(a); }},
                          {"ln", [](double a) { return std::log(a); }}};

  std::queue<RpnElement> ExpressionProcessor;
  std::stack<RpnElement> ResultStack;
  std::stack<RpnElement> StackTmpOperators;
  std::vector<double> XData_;
  std::vector<double> YData_;

  void S21CorrectString(const std::string& x_line);
  bool S21Verifying() const;
  bool S21FirstSymbol() const;
  bool S21Brackets(size_t element_index, int& bracket_balance) const;
  bool CloseBracket(size_t element_index) const;
  bool IsPreviousNumber(size_t element_index) const;
  bool S21Signs(size_t element_index) const;
  bool ContainsE() const;
  bool IsValidExponentialString() const;
  bool S21Symbols(size_t& element_index) const;
  bool IsOutOfRange(char current_char) const;
  bool IsSpecialFunction(size_t& element_index) const;
  bool S21CheckMod(size_t element_index) const;
  bool S21CheckNum(size_t element_index) const;
  int S21CheckFunction(size_t arrays_index) const;
  int S21Parser();
  int NumLexeme(size_t element_index, QueueType& ExpressionProcessor);
  int SignLexeme(size_t element_index);
  int SignFunc(size_t element_index);
  bool IsCharE(size_t element_index) const;
  bool IsDigitOrDot(size_t element_index) const;
  bool IsLexemeCharacter(size_t element_index) const;
  void ConvertToRPN(RpnElement& element);
  void MoveOperatorToPostfix();
  void S21Calculation();
  double CalculateBinaryOperation(double a, double b,
                                  const std::string& operation);
  double CalculateUnaryOperation(double a, const std::string& operation);
  void CopyQueueToStack();
  bool IsValidNumber(const std::string& expression, bool is_double) const;
  void CalculateAnnuityCreditconst(const std::string& amount,
                                   const std::string& rate,
                                   const std::string& term);
  void CalculateDifferentiatedCredit(const std::string& amount,
                                     const std::string& rate,
                                     const std::string& term);
  double RoundTo2Decimals(double value);
  std::string FormatDoubleToString(double value);
};
}  // namespace s21

#endif  // SRC_CALC_MODEL_H