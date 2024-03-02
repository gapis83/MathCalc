#include "calc_model.h"

void s21::MyCalc::ResultCalculationProcess(std::string& input_string,
                                           std::string& x_line,
                                           std::string& output_string) {
  set_input_string(input_string);
  try {
    double result = ExpressionCalculate(x_line);
    if (result == static_cast<int>(result)) {
      output_string = std::to_string(static_cast<int>(result));
    } else {
      std::ostringstream oss;
      oss.precision(7);
      oss << std::fixed << result;
      output_string = oss.str();
    }
  } catch (const std::runtime_error& e) {
    output_string = e.what();
  }
}

double s21::MyCalc::ExpressionCalculate(const std::string& x_line) {
  S21CorrectString(x_line);
  if (S21Verifying()) {
    throw std::runtime_error("Incorrect String");
  } else {
    S21Parser();
    CopyQueueToStack();
  }
  double result = 0.0;
  if (ExpressionProcessor.empty()) {
    result = ResultStack.top().value;
  }
  return result;
}

double s21::MyCalc::CalculateResult(std::string& input_string,
                                    std::string& x_line) {
  set_input_string(input_string);
  try {
    return ExpressionCalculate(x_line);
  } catch (const std::runtime_error&) {
    return std::numeric_limits<double>::quiet_NaN();
  }
}

void s21::MyCalc::S21CorrectString(const std::string& x_line) {
  std::string corrected_string;
  bool prev_char_is_open_parenthesis = false;
  for (size_t i = 0; i < input_string_.length(); ++i) {
    char current_char = input_string_[i];
    if (current_char == '=' || i > 254) {
      corrected_string += current_char;
      break;
    }
    if (current_char == ' ') {
      continue;
    } else if (current_char == '-' || current_char == '+') {
      if (i == 0 || prev_char_is_open_parenthesis) {
        corrected_string += "(0" + std::string(1, current_char) + "1)*";
      } else {
        corrected_string += current_char;
      }
    } else if (current_char == 'x') {
      if (x_line[0] == '-') {
        corrected_string += "((0-1)*" + x_line.substr(1) + ")";
      } else {
        corrected_string += "(" + x_line + ")";
      }
    } else {
      corrected_string += current_char;
    }
    prev_char_is_open_parenthesis = (current_char == '(');
  }
  input_string_ = corrected_string;
}

void s21::MyCalc::set_input_string(const std::string& input) {
  input_string_ = input;
}

bool s21::MyCalc::S21Verifying() const {
  bool error = false;
  int bracket_balance = 0;
  for (size_t array_index = 0; array_index < input_string_.length();
       ++array_index) {
    if (error) break;
    char array_symbol = input_string_[array_index];
    if ((array_symbol == '(') || array_symbol == ')') {
      error = S21Brackets(array_index, bracket_balance);
    } else if (IsDigitOrDot(array_index)) {
      error = S21CheckNum(array_index);
    } else if ((array_symbol > ')' && array_symbol < '/') ||
               array_symbol == '^') {
      error = S21Signs(array_index);
    } else if ((array_symbol < '(' || array_symbol > '9') && (!error)) {
      error = S21Symbols(array_index);
      if (!error) {
        if ((array_symbol == '=') && (!IsPreviousNumber(array_index))) {
          return true;
        }
      }
    }
  }
  if ((ContainsE() && IsValidExponentialString()) || (S21FirstSymbol()) ||
      (bracket_balance != 0)) {
    error = true;
  }
  if (input_string_.back() != '=') error = true;
  return error;
}

bool s21::MyCalc::S21CheckNum(size_t element_index) const {
  std::string number = "";
  for (; IsDigitOrDot(element_index); ++element_index) {
    number += input_string_[element_index];
  }
  size_t pos = 0;
  std::stod(number, &pos);
  if (pos != number.length()) {
    return true;
  }
  return false;
}

bool s21::MyCalc::S21FirstSymbol() const {
  if (input_string_[0] == SIGNS[2] || input_string_[0] == SIGNS[3] ||
      input_string_[0] == SIGNS[4]) {
    return true;
  } else {
    return false;
  }
}

bool s21::MyCalc::S21Brackets(size_t element_index,
                              int& bracket_balance) const {
  char current_symbol = input_string_[element_index];
  bool error = false;
  if (current_symbol == ')') {
    --bracket_balance;
    if (CloseBracket(element_index)) error = true;
  } else {
    ++bracket_balance;
    if (element_index < input_string_.length() - 1) {
      char next_symbol = input_string_[element_index + 1];
      if (next_symbol == '*' || next_symbol == '/' || next_symbol == '.')
        error = true;
    }
    if (element_index > 0) {
      if (IsDigitOrDot(element_index - 1)) {
        error = true;
      }
    }
  }
  if (bracket_balance < 0) error = true;
  return error;
}

bool s21::MyCalc::CloseBracket(size_t element_index) const {
  if (element_index == 0) return true;
  char previous = input_string_[element_index - 1];
  if (previous != ')' && (!IsDigitOrDot(element_index - 1))) {
    return true;
  } else {
    return false;
  }
}

bool s21::MyCalc::IsPreviousNumber(size_t element_index) const {
  if (element_index == 0) {
    return false;
  }
  for (size_t i = element_index - 1; i != SIZE_MAX; --i) {
    char current_char = input_string_[i];
    if (std::isdigit(current_char) || current_char == '.') {
      return true;
    }
    if (current_char != ')') {
      return false;
    }
  }
  return false;
}

bool s21::MyCalc::S21Signs(size_t element_index) const {
  if ((input_string_[element_index + 1] > ')' &&
       input_string_[element_index + 1] < '0') ||
      input_string_[element_index + 1] == '^') {
    return true;
  }
  return false;
}

bool s21::MyCalc::ContainsE() const {
  for (char c : input_string_) {
    if (c == 'e' || c == 'E') {
      return true;
    }
  }
  return false;
}

bool s21::MyCalc::IsValidExponentialString() const {
  const std::regex pattern("[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+");
  std::smatch match;
  int exponential_count = 0;
  int e_count = 0;
  std::string::const_iterator search_start = input_string_.cbegin();
  while (
      std::regex_search(search_start, input_string_.cend(), match, pattern)) {
    search_start = match.suffix().first;
    exponential_count++;
  }
  for (char c : input_string_) {
    if (c == 'e' || c == 'E') {
      e_count++;
    }
  }
  return exponential_count != e_count;
}

bool s21::MyCalc::S21Symbols(size_t& element_index) const {
  char current_char = input_string_[element_index];
  if (IsOutOfRange(current_char) && current_char != '=') {
    return true;
  }
  if (IsSpecialFunction(element_index)) {
    return true;
  }
  return false;
}

bool s21::MyCalc::IsSpecialFunction(size_t& element_index) const {
  char current_char = input_string_[element_index];
  if (current_char == FUNCTIONS[0]) {
    if (S21CheckMod(element_index)) {
      return true;
    }
  }
  if (strchr(FUNCTIONS, current_char) != nullptr) {
    if (current_char == FUNCTIONS[4]) {
      element_index += kIncrementBy1;
    }
    int new_index = S21CheckFunction(element_index);
    if (new_index < 0) {
      return true;
    } else {
      element_index = new_index;
    }
  }
  return false;
}

bool s21::MyCalc::IsOutOfRange(char current_char) const {
  return (current_char < 40) || (current_char > 57 && current_char < 94) ||
         (current_char > 94 && current_char < 97) || (current_char > 116);
}

bool s21::MyCalc::S21CheckMod(size_t element_index) const {
  if (element_index == 0) return true;
  char prev_char = input_string_[element_index - kIncrementBy1];
  if ((strchr(SIGNS, prev_char) && prev_char != ')') || (prev_char == '.')) {
    return true;
  }
  char next_char = input_string_[element_index + kIncrementBy3];
  if ((strchr(SIGNS, next_char) && next_char != '(') || (next_char == '.')) {
    return true;
  }
  return false;
}

int s21::MyCalc::S21CheckFunction(size_t arrays_index) const {
  for (const auto& entry : function_increments) {
    const std::string& targetFunction = entry.first;
    int increment = entry.second;
    std::string substr =
        input_string_.substr(arrays_index, targetFunction.length());
    if (substr == targetFunction) {
      return arrays_index + increment;
    }
  }
  return -1;
}

int s21::MyCalc::S21Parser() {
  for (size_t element_index = 0; element_index < input_string_.length();
       ++element_index) {
    char current_char = input_string_[element_index];
    if (IsDigitOrDot(element_index)) {
      element_index = NumLexeme(element_index, ExpressionProcessor);
    }
    if (std::strchr(SIGNS, current_char) != nullptr) {
      element_index = SignLexeme(element_index);
    }
    if (std::strchr(FUNCTIONS, current_char) != nullptr) {
      element_index = SignFunc(element_index);
    }
    if (current_char == 61) {
      break;
    }
  }
  return 0;
}

int s21::MyCalc::NumLexeme(size_t element_index,
                           QueueType& ExpressionProcessor) {
  std::string lexeme(1, input_string_[element_index]);
  ++element_index;
  while (element_index < input_string_.length() &&
         IsLexemeCharacter(element_index)) {
    lexeme.push_back(input_string_[element_index]);
    ++element_index;
  }
  --element_index;
  double parsed_number = std::stod(lexeme);
  ExpressionProcessor.push({parsed_number});
  return element_index;
}
int s21::MyCalc::SignLexeme(size_t element_index) {
  char current_char = input_string_[element_index];
  int priority = 0;
  std::string op_str;
  switch (current_char) {
    case '+':
      priority = 1;
      op_str = "+";
      break;
    case '-':
      priority = 1;
      op_str = "-";
      break;
    case '*':
      priority = 2;
      op_str = "*";
      break;
    case '/':
      priority = 2;
      op_str = "/";
      break;
    case '^':
      priority = 3;
      op_str = "^";
      break;
    case '(':
      priority = 5;
      op_str = "(";
      break;
    case ')':
      priority = 5;
      op_str = ")";
      break;
    default:
      break;
  }
  RpnElement element(op_str, priority);
  ConvertToRPN(element);
  return element_index;
}

int s21::MyCalc::SignFunc(size_t element_index) {
  char current_char = input_string_[element_index];
  char next_char = input_string_[element_index + 1];
  int increment = kIncrementBy2;
  RpnElement element("", 0);
  switch (current_char) {
    case FUNCTIONS[0]:
      element = RpnElement("mod", 2);
      break;
    case FUNCTIONS[1]:
      element = RpnElement("cos");
      break;
    case FUNCTIONS[2]:
      if (next_char == 'i') {
        element = RpnElement("sin");
      } else {
        increment = kIncrementBy3;
        element = RpnElement{ElementType::FUNCTION, 0.0, "sqrt", 3};
      }
      break;
    case FUNCTIONS[3]:
      element = RpnElement("tan");
      break;
    case FUNCTIONS[4]:
      increment = kIncrementBy3;
      if (next_char == FUNCTIONS[1]) {
        element = RpnElement("acos");
      } else if (next_char == FUNCTIONS[2]) {
        element = RpnElement("asin");
      } else {
        element = RpnElement("atan");
      }
      increment = kIncrementBy3;
      break;
    case FUNCTIONS[5]:
      if (next_char == 'n') {
        element = RpnElement("ln");
        increment = kIncrementBy1;
      } else {
        element = RpnElement("log");
      }
      break;
  }
  ConvertToRPN(element);
  return element_index + increment;
}

bool s21::MyCalc::IsCharE(size_t element_index) const {
  if (element_index > 0 && (input_string_[element_index] == 'e' ||
                            (input_string_[element_index] == 'E'))) {
    return true;
  }
  return false;
}

bool s21::MyCalc::IsDigitOrDot(size_t element_index) const {
  char current_char = input_string_[element_index];
  return (std::strchr(NUMBERS, current_char) != nullptr);
}

bool s21::MyCalc::IsLexemeCharacter(size_t element_index) const {
  char current_char = input_string_[element_index];
  return (IsDigitOrDot(element_index) || IsCharE(element_index)) ||
         ((current_char == SIGNS[0] || current_char == SIGNS[1]) &&
          IsCharE(element_index - 1));
}

void s21::MyCalc::ConvertToRPN(RpnElement& element) {
  if (element.operation != ")") {
    if (StackTmpOperators.empty() ||
        element.priority > StackTmpOperators.top().priority ||
        StackTmpOperators.top().operation == "(") {
      StackTmpOperators.push(element);
    } else if ((element.priority < StackTmpOperators.top().priority) ||
               (element.priority == StackTmpOperators.top().priority)) {
      if (element.priority == 3 && StackTmpOperators.top().priority == 3) {
        StackTmpOperators.push(element);
      } else {
        MoveOperatorToPostfix();
        ConvertToRPN(element);
      }
    } else {
      ExpressionProcessor.push(element);
    }
  } else {
    while (!StackTmpOperators.empty() &&
           StackTmpOperators.top().operation != "(") {
      MoveOperatorToPostfix();
    }
    if (!StackTmpOperators.empty() && StackTmpOperators.top().operation == "(")
      StackTmpOperators.pop();
  }
}

void s21::MyCalc::MoveOperatorToPostfix() {
  RpnElement top_operator = StackTmpOperators.top();
  StackTmpOperators.pop();
  ExpressionProcessor.push(top_operator);
}

void s21::MyCalc::CopyQueueToStack() {
  if (!StackTmpOperators.empty()) {
    while (!StackTmpOperators.empty()) {
      MoveOperatorToPostfix();
    }
  }
  while (!ExpressionProcessor.empty()) {
    if (ExpressionProcessor.front().type == NUMBER) {
      RpnElement element = ExpressionProcessor.front();
      ExpressionProcessor.pop();
      ResultStack.push(element);
    } else {
      S21Calculation();
    }
  }
}

void s21::MyCalc::S21Calculation() {
  double operand_2 = ResultStack.top().value;
  double result = 0.0;
  if (ExpressionProcessor.front().type == OPERATOR) {
    ResultStack.pop();
    double operand_1 = ResultStack.top().value;
    result = CalculateBinaryOperation(operand_1, operand_2,
                                      ExpressionProcessor.front().operation);
  } else {
    result = CalculateUnaryOperation(operand_2,
                                     ExpressionProcessor.front().operation);
  }
  ExpressionProcessor.pop();
  ResultStack.top().value = result;
}

double s21::MyCalc::CalculateBinaryOperation(double a, double b,
                                             const std::string& operation) {
  auto it = binary_operations.find(operation);
  if (it != binary_operations.end()) {
    return it->second(a, b);
  }
  return 0;
}

double s21::MyCalc::CalculateUnaryOperation(double a,
                                            const std::string& operation) {
  auto it = unary_operations.find(operation);
  if (it != unary_operations.end()) {
    return it->second(a);
  }
  return 0;
}

void s21::MyCalc::CalculateGraphData(std::string& input_string, double x_max,
                                     double x_min, double y_max, double y_min) {
  int kGraph_Points = 100000;
  if (x_min < x_max && y_min < y_max && (!input_string.empty())) {
    double step = (std::abs(x_max) + std::abs(x_min)) / kGraph_Points;
    for (double i = x_min; i < x_max; i += step) {
      std::string line_x = std::to_string(i);
      input_string += "=";
      double y_value = CalculateResult(input_string, line_x);
      this->XData_.push_back(i);
      this->YData_.push_back(y_value);
    }
  } else {
    this->XData_.clear();
    this->YData_.clear();
  }
}

namespace s21 {
const std::vector<double>& MyCalc::get_XData() const { return XData_; }
}  // namespace s21

namespace s21 {
const std::vector<double>& MyCalc::get_YData() const { return YData_; }
}  // namespace s21

void s21::MyCalc::ClearVectorXData() { XData_.clear(); }

void s21::MyCalc::ClearVectorYData() { YData_.clear(); }

bool s21::MyCalc::ValidateUserInput(const std::string& amount,
                                    const std::string& rate,
                                    const std::string& term) const {
  if (!IsValidNumber(amount, true) || !IsValidNumber(rate, true) ||
      !IsValidNumber(term, false)) {
    return false;
  } else {
    return true;
  }
}

bool s21::MyCalc::IsValidNumber(const std::string& expression,
                                bool is_double) const {
  if (expression.empty() && (is_double)) {
    return false;
  }
  bool error = true;
  for (size_t i = 0; i < expression.length(); ++i) {
    if (std::strchr(NUMBERS, expression[i]) == nullptr) {
      error = false;
      break;
    }
  }
  if (error) {
    size_t pos;
    if (is_double) {
      double value = std::stod(expression, &pos);
      if ((pos != expression.length()) || value < 0) {
        error = false;
      }
    } else {
      int value = std::stoi(expression, &pos);
      if ((pos != expression.length()) || value < 0) {
        error = false;
      }
    }
  }
  return error;
}

void s21::MyCalc::CalculateLoanParameters(const std::string& amount,
                                          const std::string& rate,
                                          const std::string& term,
                                          bool annuity) {
  monthly_payments_.clear();
  overpayment_str_.clear();
  total_payment_.clear();
  if (annuity) {
    CalculateAnnuityCreditconst(amount, rate, term);
  } else {
    CalculateDifferentiatedCredit(amount, rate, term);
  }
}

void s21::MyCalc::CalculateAnnuityCreditconst(const std::string& amount,
                                              const std::string& rate,
                                              const std::string& term) {
  std::string monthly_interest_rate = rate + "/12/100";
  std::string monthly_payment = amount + "*(" + monthly_interest_rate +
                                "/(1-(1+" + monthly_interest_rate + ")^(-" +
                                term + ")))=";
  std::string x_line = "0.0";
  set_input_string(monthly_payment);
  double num_monthly_payment = ExpressionCalculate(x_line);
  num_monthly_payment = RoundTo2Decimals(num_monthly_payment);
  std::string result_monthly_payment =
      FormatDoubleToString(num_monthly_payment);
  monthly_payments_.push_back("Ежемесячный платёж: " + result_monthly_payment);
  double num_total_pay = num_monthly_payment * std::stod(term);
  total_payment_ = FormatDoubleToString(num_total_pay);
  double num_overpayment = num_total_pay - std::stod(amount);
  num_overpayment = RoundTo2Decimals(num_overpayment);
  overpayment_str_ = FormatDoubleToString(num_overpayment);
}

void s21::MyCalc::CalculateDifferentiatedCredit(const std::string& amount,
                                                const std::string& rate,
                                                const std::string& term) {
  double monthly_rate = (std::stod(rate) / 100.0) / 12.0;
  double amount_double = std::stod(amount);
  double principal_payment = amount_double / std::stod(term);
  principal_payment = RoundTo2Decimals(principal_payment);
  double remaining_loan = amount_double;
  int max_mount = std::stoi(term);
  double total_pay = 0.0;
  for (int month = 1; month <= max_mount; ++month) {
    double interest_payment = remaining_loan * monthly_rate;
    interest_payment = RoundTo2Decimals(interest_payment);
    double monthly_payment = principal_payment + interest_payment;
    remaining_loan -= principal_payment;
    remaining_loan = RoundTo2Decimals(remaining_loan);
    total_pay += monthly_payment;
    std::string current_payment =
        std::to_string(month) + ": " + FormatDoubleToString(monthly_payment);
    monthly_payments_.push_back(current_payment);
  }
  total_payment_ = FormatDoubleToString(total_pay);
  overpayment_str_ = FormatDoubleToString(total_pay - amount_double);
}

namespace s21 {
const std::string& MyCalc::get_overpayment_str() const {
  return overpayment_str_;
}
}  // namespace s21

namespace s21 {
const std::string& MyCalc::get_total_payment() const { return total_payment_; }
}  // namespace s21

namespace s21 {
const std::vector<std::string>& MyCalc::get_monthly_payments() const {
  return monthly_payments_;
}
}  // namespace s21

double s21::MyCalc::RoundTo2Decimals(double value) {
  return std::round(value * 100) / 100;
}

namespace s21 {
std::string MyCalc::FormatDoubleToString(double value) {
  std::string str_value = std::to_string(value);
  str_value.erase(str_value.find_last_not_of('0') + 1, std::string::npos);
  if (str_value.back() == '.') str_value.pop_back();
  return str_value;
}
}  // namespace s21