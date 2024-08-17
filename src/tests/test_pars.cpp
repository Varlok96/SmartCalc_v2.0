#include <gtest/gtest.h>

#include <string>

#include "../exampleModel.h"

TEST(pars, mathematical_expression) {
  s21::ExampleModel m1, m2, m3, m4;
  m1.setData("2+5/2");
  m2.setData("2/5+2");
  m3.setData("4/(45-6)*12-4");
  m4.setData("4^(45-6)^12-4");
  std::string postfix_1 = "2 5 2 / + ";
  std::string postfix_2 = "2 5 / 2 + ";
  std::string postfix_3 = "4 45 6 - / 12 * 4 - ";
  std::string postfix_4 = "4 45 6 - ^ 12 ^ 4 - ";
  EXPECT_EQ(m1.pars(), postfix_1);
  EXPECT_EQ(m2.pars(), postfix_2);
  EXPECT_EQ(m3.pars(), postfix_3);
  EXPECT_EQ(m4.pars(), postfix_4);
}

TEST(pars, unary_minus) {
  s21::ExampleModel m1, m2, m3, m4, m5, m6, m7, m8;
  m1.setData("-2+5/2");
  m2.setData("-2/5+2");
  m3.setData("-2+5/2*(-4*3/2)-1");
  m4.setData("-2+5/((2*(-4*3/2))-1)");
  m5.setData("-2*(((5*3)/4)/1)");
  m6.setData("-2*((5*3)/4)");
  m7.setData("2-4/(45-6)*12-(42+53)");
  m8.setData("2-4/(45-6)*12-(42+53)");
  std::string postfix_1 = "0 2 - 5 2 / + ";
  std::string postfix_2 = "0 2 5 / - 2 + ";
  std::string postfix_3 = "0 2 - 5 2 / 0 4 3 * 2 / - * + 1 - ";
  std::string postfix_4 = "0 2 - 5 2 0 4 3 * 2 / - * 1 - / + ";
  std::string postfix_5 = "0 2 5 3 * 4 / 1 / * - ";
  std::string postfix_6 = "0 2 5 3 * 4 / * - ";
  std::string postfix_7 = "2 4 45 6 - / 12 * - 42 53 + - ";
  std::string postfix_8 = "2 4 45 6 - / 12 * - 42 53 + - ";

  EXPECT_EQ(m1.pars(), postfix_1);
  EXPECT_EQ(m2.pars(), postfix_2);
  EXPECT_EQ(m3.pars(), postfix_3);
  EXPECT_EQ(m4.pars(), postfix_4);
  EXPECT_EQ(m5.pars(), postfix_5);
  EXPECT_EQ(m6.pars(), postfix_6);
  EXPECT_EQ(m7.pars(), postfix_7);
  EXPECT_EQ(m8.pars(), postfix_8);
}

TEST(pars, double_numbers) {
  s21::ExampleModel m1, m2;
  m1.setData("2.2+5/2");
  m2.setData("2.34-43.123/(456.312-654)*123.543-(42.123+534.432");
  std::string postfix_1 = "2.2 5 2 / + ";
  std::string postfix_2 =
      "2.34 43.123 456.312 654 - / 123.543 * - 42.123 534.432 + - ";
  EXPECT_EQ(m1.pars(), postfix_1);
  EXPECT_EQ(m2.pars(), postfix_2);
}

TEST(pars, parenthesis) {
  s21::ExampleModel m1, m2;
  m1.setData("(2+(3+4)*(5-2)");
  m2.setData("2+((3+4)*(5-2))");
  std::string postfix_1 = "2 3 4 + 5 2 - * + ";
  std::string postfix_2 = "2 3 4 + 5 2 - * + ";
  EXPECT_EQ(m1.pars(), postfix_1);
  EXPECT_EQ(m2.pars(), postfix_2);
}

TEST(pars, trigonometric) {
  s21::ExampleModel m1, m2, m3, m4, m5, m6, m7, m8, m9;
  m1.setData("sin(45)");
  m2.setData("cos(45)");
  m3.setData("tg(45)");
  m4.setData("atg(45)");
  m5.setData("asin(0.5)");
  m6.setData("acos(0.5)");
  m7.setData("ln(15)");
  m8.setData("log(15)");
  m9.setData("sqrt(9)");
  std::string postfix_1 = "45 s ";
  std::string postfix_2 = "45 c ";
  std::string postfix_3 = "45 t ";
  std::string postfix_4 = "45 T ";
  std::string postfix_5 = "0.5 S ";
  std::string postfix_6 = "0.5 C ";
  std::string postfix_7 = "15 l ";
  std::string postfix_8 = "15 L ";
  std::string postfix_9 = "9 k ";
  EXPECT_EQ(m1.pars(), postfix_1);
  EXPECT_EQ(m2.pars(), postfix_2);
  EXPECT_EQ(m3.pars(), postfix_3);
  EXPECT_EQ(m4.pars(), postfix_4);
  EXPECT_EQ(m5.pars(), postfix_5);
  EXPECT_EQ(m6.pars(), postfix_6);
  EXPECT_EQ(m7.pars(), postfix_7);
  EXPECT_EQ(m8.pars(), postfix_8);
  EXPECT_EQ(m9.pars(), postfix_9);
}

TEST(pars, x) {
  s21::ExampleModel m1, m2, m3, m4, m5;
  m1.setData("x");
  m2.setData("x+5");
  m3.setData("5+x");
  m4.setData("sin(x)");
  m5.setData("x+x");
  std::string postfix_1 = "x ";
  std::string postfix_2 = "x 5 + ";
  std::string postfix_3 = "5 x + ";
  std::string postfix_4 = "x s ";
  std::string postfix_5 = "x x + ";
  EXPECT_EQ(m1.pars(), postfix_1);
  EXPECT_EQ(m2.pars(), postfix_2);
  EXPECT_EQ(m3.pars(), postfix_3);
  EXPECT_EQ(m4.pars(), postfix_4);
  EXPECT_EQ(m5.pars(), postfix_5);
}

TEST(math_operations, result) {
  s21::ExampleModel m1;
  double result1 = 0, result2 = 0, result3 = 0, result4 = 0;
  double x = 0;
  m1.math_operations(x, "1 2 3 * +", &result1, 0);
  m1.math_operations(x, "1 2 3 * 4 / + 5 -", &result2, 0);
  m1.math_operations(x, "1 2 3 4 / 5 - * +", &result3, 0);
  m1.math_operations(x, "4 8 6 - ^", &result4, 0);
  EXPECT_EQ(result1, 7);
  EXPECT_EQ(result2, -2.5);
  EXPECT_EQ(result3, -7.5);
  EXPECT_EQ(result4, 16);
}

TEST(math_operations, double_numbers) {
  s21::ExampleModel m1;
  double result1 = 0;
  double x1 = 0;
  m1.math_operations(
      x1, "2.34 43.123 456.312 654 - / 123.543 * - 42.123 534.432 + - ",
      &result1, 0);
  EXPECT_NEAR(result1, -547.26574264, 0.0000001);
}

TEST(math_operations, trigonometric_rad) {
  s21::ExampleModel m1;
  double result1 = 0, result2 = 0, result3 = 0, result4 = 0, result5 = 0,
         result6 = 0, result7 = 0, result8 = 0, result9 = 0;
  double x1 = 0;
  m1.math_operations(x1, "45 s", &result1, 1);
  m1.math_operations(x1, "45 c", &result2, 1);
  m1.math_operations(x1, "45 t", &result3, 1);
  m1.math_operations(x1, "1 S", &result4, 1);
  m1.math_operations(x1, "1 C", &result5, 1);
  m1.math_operations(x1, "30 T", &result6, 1);
  m1.math_operations(x1, "45 l", &result7, 1);
  m1.math_operations(x1, "45 L", &result8, 1);
  m1.math_operations(x1, "9 k", &result9, 1);
  EXPECT_EQ(result1, sin(45));
  EXPECT_EQ(result2, cos(45));
  EXPECT_EQ(result3, tan(45));
  EXPECT_EQ(result4, asin(1));
  EXPECT_EQ(result5, acos(1));
  EXPECT_EQ(result6, atan(30));
  EXPECT_EQ(result7, log(45));
  EXPECT_EQ(result8, log10(45));
  EXPECT_EQ(result9, sqrt(9));
}

TEST(math_operations, trigonometric_grad) {
  s21::ExampleModel m1;
  double result1 = 0, result2 = 0, result3 = 0, result4 = 0, result5 = 0,
         result6 = 0, result7 = 0, result8 = 0, result9 = 0;
  double x1 = 0;
  m1.math_operations(x1, "45 s", &result1, 0);
  m1.math_operations(x1, "45 c", &result2, 0);
  m1.math_operations(x1, "45 t", &result3, 0);
  m1.math_operations(x1, "1 S", &result4, 0);
  m1.math_operations(x1, "1 C", &result5, 0);
  m1.math_operations(x1, "30 T", &result6, 0);
  m1.math_operations(x1, "45 l", &result7, 0);
  m1.math_operations(x1, "45 L", &result8, 0);
  m1.math_operations(x1, "9 k", &result9, 0);
  EXPECT_EQ(result1, sin(45 * M_PI / 180.0));
  EXPECT_EQ(result2, cos(45 * M_PI / 180.0));
  EXPECT_EQ(result3, tan(45 * M_PI / 180.0));
  EXPECT_EQ(result4, asin(1 * M_PI / 180.0));
  EXPECT_EQ(result5, acos(1 * M_PI / 180.0));
  EXPECT_EQ(result6, atan(30 * M_PI / 180.0));
  EXPECT_EQ(result7, log(45));
  EXPECT_EQ(result8, log10(45));
  EXPECT_EQ(result9, sqrt(9));
}

TEST(math_operations, mod) {
  s21::ExampleModel m1;
  double result1 = 0;
  double x1 = 0;
  m1.math_operations(x1, "10 3 %", &result1, 0);
  EXPECT_EQ(result1, 1);
}

TEST(math_operations, x) {
  s21::ExampleModel m1;
  double result1 = 0, result2 = 0, result3 = 0, result4 = 0;
  double x = 30;
  m1.math_operations(x, "x 5 +", &result1, 0);
  m1.math_operations(x, "5 x +", &result2, 0);
  m1.math_operations(x, "x s", &result3, 1);
  m1.math_operations(x, "x x +", &result4, 0);
  EXPECT_EQ(result1, 35);
  EXPECT_EQ(result2, 35);
  EXPECT_EQ(result3, sin(30));
  EXPECT_EQ(result4, 60);
}

TEST(math_operations, error) {
  s21::ExampleModel m1;
  double result1 = 0;
  int error = 0;
  double x = 0;
  error = m1.math_operations(x, "0 0 /", &result1, 0);
  EXPECT_EQ(error, 1);
}

TEST(credit, annuit) {
  s21::CreditModel m1(1000000, 12, 15);
  double result = 0, monthly = 0, overpay = 0;
  result = m1.annuit();
  monthly = m1.SetMonthly();
  overpay = m1.SetOverpay();

  EXPECT_NEAR(result, 1083099.75, 0.01);
  EXPECT_NEAR(monthly, 90258.31, 0.01);
  EXPECT_NEAR(overpay, 83099.75, 0.01);
}

TEST(credit, diff) {
  s21::CreditModel m1(1000000, 12, 15);
  double result = 0, monthly = 0, monthly_2 = 0, overpay = 0;
  result = m1.diff();
  monthly = m1.SetMonthly();
  overpay = m1.SetOverpay();
  monthly_2 = m1.SetMonthly_2();

  EXPECT_NEAR(result, 1081246.28, 0.01);
  EXPECT_NEAR(monthly, 95833.00, 0.01);
  EXPECT_NEAR(overpay, 81250.28, 0.01);
  EXPECT_NEAR(monthly_2, 84374.71, 0.01);
}

TEST(debit, no_kapital_procent) {
  s21::DebitModel m1(1000000, 18, 16, 0, 0, 365, 0);
  double rezult = 0, rezult_procent = 0, rezult_nalog = 0;
  m1.result_debit(0, 0, 0);
  rezult = m1.SetRezult();
  rezult_procent = m1.SetRezultProcent();
  rezult_nalog = m1.SetRezultNalog();

  EXPECT_NEAR(rezult, 1000000, 0.01);
  EXPECT_NEAR(rezult_procent, 180000, 0.01);
  EXPECT_NEAR(rezult_nalog, 2600, 0.01);
}

TEST(debit, kapital_procent) {
  s21::DebitModel m1(1000000, 18, 16, 0, 0, 365, 1);
  double rezult = 0, rezult_procent = 0, rezult_nalog = 0;
  m1.result_debit(1, 0, 0);
  rezult = m1.SetRezult();
  rezult_procent = m1.SetRezultProcent();
  rezult_nalog = m1.SetRezultNalog();

  EXPECT_NEAR(rezult, 1197164.24, 0.01);
  EXPECT_NEAR(rezult_procent, 197164.24, 0.01);
  EXPECT_NEAR(rezult_nalog, 4831.35, 0.01);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
