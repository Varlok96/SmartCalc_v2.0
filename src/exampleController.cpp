#include "exampleController.h"

int s21::ExampleController::result() {
  return model.math_operations(x, model.pars(), res, rad);
}

double s21::CreditController::annuit() { return model.annuit(); }

double s21::CreditController::diff() { return model.diff(); }

void s21::DebitController::result_debit(double period, double st_plus,
                                        double st_minus) {
  model.result_debit(period, st_plus, st_minus);
}