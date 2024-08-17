#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {
class ExampleModel {
 public:
  ExampleModel() : data(""){};
  ExampleModel(std::string str, bool rad_) : data(str), rad(rad_){};
  std::string pars();
  int math_operations(double x, std::string postfix, double* res, bool rad);
  void setData(std::string infix) { data = infix; }

 private:
  std::string data;
  bool rad;

  bool is_digit(char elem);
  bool is_operand(char elem);
  bool is_trc_func(char elem);
  char trigonometric(std::string infix, int* i);
  int priority(char elem);
  double result_operand(char postfix, double r1, double r2, int* error);
  double result_trigonometric_rad(char postfix, double r1);
  double result_trigonometric_grad(char postfix, double r1);
  double digit_reform(char* c1);
  std::string write_elem(std::stack<char>* stack_elem);
  void delete_elem(std::stack<char>* stack_elem, std::string* postfix,
                   bool flag);
  double top_pop(std::stack<double>* stack_math);
};

class CreditModel {
 public:
  CreditModel(){};
  CreditModel(double summ_, int term_, double percent_)
      : summ(summ_), term(term_), percent(percent_){};
  double annuit();
  double diff();
  double SetMonthly() { return monthly; }
  double SetOverpay() { return overpay; }
  double SetMonthly_2() { return monthly_2; }

 private:
  double summ;
  int term;
  double percent;
  double monthly;
  double overpay;
  double monthly_2;
};

class DebitModel {
 public:
  DebitModel(){};
  DebitModel(double summ_, int stavka_, double nalog_, double plus_,
             double minus_, int data_, int kapital_)
      : summ(summ_),
        stavka(stavka_),
        nalog(nalog_),
        plus(plus_),
        minus(minus_),
        data(data_),
        kapital(kapital_){};

  void result_debit(double period, double st_plus, double st_minus);
  double pow_debit(double stavka, double data, double period);
  double SetRezult() { return result; }
  double SetRezultProcent() { return result_procent; }
  double SetRezultNalog() { return result_nalog; }

 private:
  double summ = 0;
  int stavka = 0;
  double nalog = 0;
  double plus = 0;
  double minus = 0;
  int data = 0;
  int kapital = 0;
  double result = 0;
  double result_procent = 0;
  double result_nalog = 0;
};

}  // namespace s21

#endif  // EXAMPLEMODEL_H
