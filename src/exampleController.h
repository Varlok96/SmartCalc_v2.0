#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "exampleModel.h"

namespace s21 {
class ExampleController {
 public:
  ExampleController(){};
  ExampleController(std::string infix, double x_, double* res_, bool rad_)
      : model(infix, rad_), x(x_), res(res_), rad(rad_){};
  int result();
  void set_x(double x_) { x = x_; }

 private:
  ExampleModel model;
  std::string postfix;
  double x;
  double* res;
  double rad;
};

class CreditController {
 public:
  CreditController(){};
  CreditController(double summ_, int term_, double percent_)
      : model(summ_, term_, percent_){};

  double annuit();
  double diff();

  double SetMonthly() { return model.SetMonthly(); }
  double SetOverpay() { return model.SetOverpay(); }
  double SetMonthly_2() { return model.SetMonthly_2(); }

 private:
  CreditModel model;
};

class DebitController {
 public:
  DebitController(){};
  DebitController(double summ_, int stavka_, double nalog_, double plus_,
                  double minus_, int data_, int kapital_)
      : model(summ_, stavka_, nalog_, plus_, minus_, data_, kapital_){};

  void result_debit(double period, double st_plus, double st_minus);
  double SetRezult() { return model.SetRezult(); }
  double SetRezultProcent() { return model.SetRezultProcent(); }
  double SetRezultNalog() { return model.SetRezultNalog(); }

 private:
  DebitModel model;
};

}  // namespace s21

#endif
