#include <gtest/gtest.h>  // Включаем заголовочный файл Google Test

#include "calc_model.h"  // Включаем заголовочный файл для тестирования

// Пример тестов
#include <gtest/gtest.h>

TEST(CalcModelTest, AdditionTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("5.1+6.4=");
  double result1 = my_calc.ExpressionCalculate("0.0");
  EXPECT_EQ(result1, 11.5);

  my_calc.set_input_string("5.1+x=");
  double result2 = my_calc.ExpressionCalculate("6.4");
  EXPECT_DOUBLE_EQ(result2, 11.5);
}

TEST(CalcModelTest, SubtractionTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("10.5-x=");
  double result = my_calc.ExpressionCalculate("2.3");
  EXPECT_DOUBLE_EQ(result, 8.2);
}

TEST(CalcModelTest, MultiplicationTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("5.1*2.1=");
  double result = my_calc.ExpressionCalculate("0.0");
  // double expected_result = 10.71;
  // double tolerance = 0.0001;
  // requirements ASSERT_NEAR(result, expected_result, tolerance);
  EXPECT_DOUBLE_EQ(result, 10.71);

  my_calc.set_input_string("5.1*x=");
  double result2 = my_calc.ExpressionCalculate("2.1");
  EXPECT_DOUBLE_EQ(result2, 10.71);
}

TEST(CalcModelTest, DivisionTest) {
  s21::MyCalc my_calc;

  std::string division = "10.71/2.1=";
  std::string x_line = "0.0";
  double result = my_calc.CalculateResult(division, x_line);
  EXPECT_DOUBLE_EQ(result, 5.1);

  my_calc.set_input_string("10.71/x=");
  double result2 = my_calc.ExpressionCalculate("2.1");
  EXPECT_DOUBLE_EQ(result2, 5.1);
}

TEST(CalcModelTest, DivisionForNullTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("10.71/0=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_TRUE(std::isinf(result));

  my_calc.set_input_string("10.71/x=");
  double result2 = my_calc.ExpressionCalculate("0.0");
  EXPECT_TRUE(std::isinf(result2));
}

TEST(CalcModelTest, ExponentiationTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("10.71^3.1=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 1557.2106296, 0.000001);

  my_calc.set_input_string("10.2^x=");
  double result2 = my_calc.ExpressionCalculate("-1.5");
  EXPECT_NEAR(result2, 0.0306972, 0.000001);

  my_calc.set_input_string("0^x=");
  double result3 = my_calc.ExpressionCalculate("-1");
  EXPECT_TRUE(std::isinf(result3));

  my_calc.set_input_string("1^x=");
  double result4 = my_calc.ExpressionCalculate("0");
  EXPECT_NEAR(result4, 1, 0.000001);
}

TEST(CalcModelTest, ModTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("10.34mod2.4=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 0.74, 0.000001);

  my_calc.set_input_string("10.34modx=");
  double result2 = my_calc.ExpressionCalculate("-2.4");
  EXPECT_NEAR(result2, 0.74, 0.000001);
}

TEST(CalcModelTest, CosTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("cos(1.57)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 0.00079, 0.00001);

  my_calc.set_input_string("cos(x)=");
  double result2 = my_calc.ExpressionCalculate("-1.57");
  EXPECT_NEAR(result2, 0.00079, 0.00001);

  my_calc.set_input_string("cos(x)=");
  double result3 = my_calc.ExpressionCalculate("0");
  EXPECT_NEAR(result3, 1, 0.00001);
}

TEST(CalcModelTest, SinTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("sin(1.57)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 1, 0.00001);

  my_calc.set_input_string("sin(x)=");
  double result2 = my_calc.ExpressionCalculate("-1.57");
  EXPECT_NEAR(result2, -1, 0.00001);

  my_calc.set_input_string("sin(x)=");
  double result3 = my_calc.ExpressionCalculate("0");
  EXPECT_NEAR(result3, 0, 0.00001);
}

TEST(CalcModelTest, TanTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("tan(1.5)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 14.10141, 0.00001);

  my_calc.set_input_string("tan(x)=");
  double result2 = my_calc.ExpressionCalculate("-1.5");
  EXPECT_NEAR(result2, -14.1014, 0.0001);
}

TEST(CalcModelTest, AcosTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("acos(0.5)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 1.04719, 0.00001);

  my_calc.set_input_string("acos(x)=");
  double result2 = my_calc.ExpressionCalculate("-0.5");
  EXPECT_NEAR(result2, 2.09439, 0.00001);

  my_calc.set_input_string("acos(x)=");
  double result3 = my_calc.ExpressionCalculate("2");
  EXPECT_TRUE(std::isnan(result3));
}

TEST(CalcModelTest, AsinTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("asin(0.5)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 0.52359, 0.00001);

  my_calc.set_input_string("asin(x)=");
  double result2 = my_calc.ExpressionCalculate("-0.5");
  EXPECT_NEAR(result2, -0.52359, 0.00001);

  my_calc.set_input_string("asin(x)=");
  double result3 = my_calc.ExpressionCalculate("2");
  EXPECT_TRUE(std::isnan(result3));
}

TEST(CalcModelTest, AtanTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("atan(0.5)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 0.46364, 0.00001);

  my_calc.set_input_string("atan(x)=");
  double result2 = my_calc.ExpressionCalculate("-0.5");
  EXPECT_NEAR(result2, -0.46364, 0.0001);

  my_calc.set_input_string("atan(x)=");
  double result3 = my_calc.ExpressionCalculate("0");
  EXPECT_NEAR(result3, 0, 0.0001);
}

TEST(CalcModelTest, SqrtTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("sqrt(5.2)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 2.28035, 0.00001);

  my_calc.set_input_string("sqrt(x)=");
  double result2 = my_calc.ExpressionCalculate("5.2");
  EXPECT_NEAR(result2, 2.28035, 0.00001);

  my_calc.set_input_string("sqrt(x)=");
  double result3 = my_calc.ExpressionCalculate("-5.2");
  EXPECT_TRUE(std::isnan(result3));
}

TEST(CalcModelTest, LnTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("ln(5.2)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 1.64865, 0.00001);

  my_calc.set_input_string("ln(x)=");
  double result2 = my_calc.ExpressionCalculate("5.2");
  EXPECT_NEAR(result2, 1.64865, 0.00001);

  my_calc.set_input_string("ln(x)=");
  double result3 = my_calc.ExpressionCalculate("-5.2");
  EXPECT_TRUE(std::isnan(result3));
}

TEST(CalcModelTest, LogTest) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("log(5.2)=");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, 0.71600334363, 0.00001);

  my_calc.set_input_string("log(x)=");
  double result2 = my_calc.ExpressionCalculate("5.2");
  EXPECT_NEAR(result2, 0.71600334363, 0.00001);

  my_calc.set_input_string("log(x)=");
  double result3 = my_calc.ExpressionCalculate("-5.2");
  EXPECT_TRUE(std::isnan(result3));
}

TEST(CalcModelTest, ComplexExpressionTest1) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("1+x*(3+4/x   -(1+x))*x+1=");
  double result = my_calc.ExpressionCalculate("2");
  EXPECT_NEAR(result, 10, 0.00001);

  my_calc.set_input_string("-3*4+x=");
  double result2 = my_calc.ExpressionCalculate("2");
  EXPECT_NEAR(result2, -10, 0.00001);

  my_calc.set_input_string("4^3^2=");
  double result3 = my_calc.ExpressionCalculate("2");
  EXPECT_NEAR(result3, 262144, 0.00001);

  my_calc.set_input_string("sqrt(sqrt(16))=");
  double result4 = my_calc.ExpressionCalculate("2");
  EXPECT_NEAR(result4, 2, 0.00001);
}

TEST(CalcModelTest, ComplexExpressionTest2) {
  s21::MyCalc my_calc;

  my_calc.set_input_string(
      "5+(1+x)*4*cos(x*7.5-x)+sin(cos(x*5))-sqrt(x^5)+asin(0.5)+tan(50)=");
  double result = my_calc.ExpressionCalculate("2");
  EXPECT_NEAR(result, 9.7401822, 0.00001);

  my_calc.set_input_string(
      "5+(1+x)*4*cos(x*7.5-x)+sin(cos(x*5))-sqrt(xmod5)+asin(0.5)+tan(50)=");
  double result2 = my_calc.ExpressionCalculate("2");
  EXPECT_NEAR(result2, 13.9828229, 0.00001);

  my_calc.set_input_string("sqrt(4)+log(10)+ln(10)=");
  double result3 = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result3, 5.3025851, 0.00001);

  my_calc.set_input_string("asin(1/2)+acos(0)+atan(1)=");
  double result4 = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result4, 2.8797933, 0.00001);
}

TEST(CalcModelTest, ComplexExpressionTest3) {
  s21::MyCalc my_calc;

  my_calc.set_input_string("-1*(3.5+2.6)=6.1");
  double result = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result, -6.1, 0.00001);

  my_calc.set_input_string("5+(-1+3)*4=");
  double result2 = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result2, 13, 0.00001);

  my_calc.set_input_string("2e4*10^2=");
  double result3 = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result3, 2e+6, 0.00001);

  my_calc.set_input_string("2e-4*10^2=");
  double result4 = my_calc.ExpressionCalculate("0.0");
  EXPECT_NEAR(result4, 2e-2, 0.00001);
}

TEST(CalcModelTest, OutputLineTest) {
  std::string input_string_1 = "1+x=";
  std::string x_line = "2";
  std::string output_string_1;

  std::string input_string_2 = "x*5/3=";
  std::string output_string_2;

  std::string input_string_3 = "x*0.001/2=";
  std::string output_string_3;

  s21::MyCalc my_calc;
  my_calc.ResultCalculationProcess(input_string_1, x_line, output_string_1);
  my_calc.ResultCalculationProcess(input_string_2, x_line, output_string_2);
  my_calc.ResultCalculationProcess(input_string_3, x_line, output_string_3);

  EXPECT_EQ(output_string_1, "3");
  EXPECT_EQ(output_string_2, "3.3333333");
  EXPECT_EQ(output_string_3, "0.0010000");
}

TEST(CalcErrorTest, Test_1) {
  std::string input_string_1 = "7+x/=";
  std::string x_line = "2";
  std::string output_string_1;

  std::string input_string_2 = "(7+x)*2)=";
  std::string output_string_2;

  std::string input_string_3 = ")7+x(*2=";
  std::string output_string_3;

  std::string input_string_4 = "7+x(*2-3)=";
  std::string output_string_4;

  std::string input_string_5 = "x+7(2-3)=";
  std::string output_string_5;

  s21::MyCalc my_calc;
  my_calc.ResultCalculationProcess(input_string_1, x_line, output_string_1);
  my_calc.ResultCalculationProcess(input_string_2, x_line, output_string_2);
  my_calc.ResultCalculationProcess(input_string_3, x_line, output_string_3);
  my_calc.ResultCalculationProcess(input_string_4, x_line, output_string_4);
  my_calc.ResultCalculationProcess(input_string_5, x_line, output_string_5);

  EXPECT_EQ(output_string_1, "Incorrect String");
  EXPECT_EQ(output_string_2, "Incorrect String");
  EXPECT_EQ(output_string_3, "Incorrect String");
  EXPECT_EQ(output_string_4, "Incorrect String");
  EXPECT_EQ(output_string_5, "Incorrect String");
}

TEST(CalcErrorTest, Test_2) {
  std::string input_string_1 = "asit(x)=";
  std::string x_line = "2";
  std::string output_string_1;

  std::string input_string_2 = "sqrt4=";
  std::string output_string_2;

  std::string input_string_3 = "*1-3=";
  std::string output_string_3;

  std::string input_string_4 = "4*mod3=";
  std::string output_string_4;

  std::string input_string_5 = "4mod-3=";
  std::string output_string_5;

  std::string input_string_6 = "4.3.5+3=";
  std::string output_string_6;

  s21::MyCalc my_calc;
  my_calc.ResultCalculationProcess(input_string_1, x_line, output_string_1);
  my_calc.ResultCalculationProcess(input_string_2, x_line, output_string_2);
  my_calc.ResultCalculationProcess(input_string_3, x_line, output_string_3);
  my_calc.ResultCalculationProcess(input_string_4, x_line, output_string_4);
  my_calc.ResultCalculationProcess(input_string_5, x_line, output_string_5);
  my_calc.ResultCalculationProcess(input_string_6, x_line, output_string_6);

  EXPECT_EQ(output_string_1, "Incorrect String");
  EXPECT_EQ(output_string_2, "Incorrect String");
  EXPECT_EQ(output_string_3, "Incorrect String");
  EXPECT_EQ(output_string_4, "Incorrect String");
  EXPECT_EQ(output_string_5, "Incorrect String");
  EXPECT_EQ(output_string_6, "Incorrect String");
}

TEST(MyCalcTest, CalculateGraphEmptyString) {
  s21::MyCalc my_calc;
  std::string empty_str = "";
  my_calc.CalculateGraphData(empty_str, 1, 0, 1, 0);

  EXPECT_EQ(my_calc.get_XData().size(), 0);
  EXPECT_EQ(my_calc.get_YData().size(), 0);
}

TEST(MyCalcTest, CalculateGraphValidString) {
  s21::MyCalc my_calc;
  std::string test_string = "x^2=";
  my_calc.CalculateGraphData(test_string, 1, 0, 1, 0);
}

TEST(MyCalcTest, AnnuityTest) {
  s21::MyCalc my_calc;
  my_calc.CalculateLoanParameters("100000", "10", "12", true);
  std::vector<std::string> test_monthly_payments =
      my_calc.get_monthly_payments();
  std::string test_overpayment = my_calc.get_overpayment_str();
  std::string test_total_payment = my_calc.get_total_payment();

  ASSERT_EQ(test_monthly_payments[0], "Ежемесячный платёж: 8791.59");
  ASSERT_EQ(test_overpayment, "5499.08");
  ASSERT_EQ(test_total_payment, "105499.08");
}

TEST(MyCalcTest, DifferentiatedTest) {
  s21::MyCalc calc;
  calc.CalculateLoanParameters("100000", "10", "12", false);
  std::vector<std::string> test_monthly_payments = calc.get_monthly_payments();
  std::string test_overpayment = calc.get_overpayment_str();
  std::string test_total_payment = calc.get_total_payment();

  ASSERT_EQ(test_monthly_payments[0], "1: 9166.66");
  ASSERT_EQ(test_overpayment, "5416.62");
  ASSERT_EQ(test_total_payment, "105416.62");
}

TEST(MyCalcTest, CreditValidInput) {
  s21::MyCalc calc;
  std::string amount = "123.456";
  std::string rate = "12.45";
  std::string term = "123";
  bool result = calc.ValidateUserInput(amount, rate, term);
  EXPECT_TRUE(result);
}

TEST(MyCalcTest, CreditInvalidInput) {
  s21::MyCalc calc;
  std::string amount1 = "abc";
  std::string amount2 = "123";
  std::string rate1 = "12.45";
  std::string rate2 = "1.4.5";
  std::string term1 = "123";
  std::string term2 = "12.3";
  std::string term3 = "12f3";

  bool result1 = calc.ValidateUserInput(amount1, rate1, term1);
  bool result2 = calc.ValidateUserInput(amount2, rate2, term1);
  bool result3 = calc.ValidateUserInput(amount2, rate1, term2);
  bool result4 = calc.ValidateUserInput(amount2, rate1, term3);
  bool result5 = calc.ValidateUserInput(amount1, rate2, term2);

  EXPECT_FALSE(result1);
  EXPECT_FALSE(result2);
  EXPECT_FALSE(result3);
  EXPECT_FALSE(result4);
  EXPECT_FALSE(result5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
