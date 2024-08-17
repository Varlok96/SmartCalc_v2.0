#include "exampleModel.h"

std::string s21::ExampleModel::pars() {
  std::stack<char> stack_elem;
  std::string postfix = "";
  int i = 0;
  while (data[i]) {
    if (data[i] == '(') {
      stack_elem.push(data[i++]);
      continue;
    }
    if (is_digit(data[i])) {
      while (is_digit(data[i])) {
        postfix += data[i++];
      }
      postfix += ' ';
      continue;
    }
    if (data[i] == ')') {
      delete_elem(&stack_elem, &postfix, true);
    }
    if (is_operand(data[i])) {
      if ((i == 0 || data[i - 1] == '(') && data[i] == '-') {
        postfix += "0 ";
      }
      if (!stack_elem.empty()) {
        if (priority(data[i]) < priority(stack_elem.top())) {
          delete_elem(&stack_elem, &postfix, true);
        } else if (priority(data[i]) == priority(stack_elem.top()) &&
                   stack_elem.top() != '(') {
          postfix += write_elem(&stack_elem);
        }
      }
      stack_elem.push(trigonometric(data, &i));
    }
    i++;
  }
  delete_elem(&stack_elem, &postfix, false);
  return postfix;
}

std::string s21::ExampleModel::write_elem(std::stack<char>* stack_elem) {
  std::string postfix = "";
  postfix += stack_elem->top(), postfix += ' ';
  stack_elem->pop();
  return postfix;
}

void s21::ExampleModel::delete_elem(std::stack<char>* stack_elem,
                                    std::string* postfix, bool flag) {
  while (!stack_elem->empty()) {
    if (stack_elem->top() == '(') {
      stack_elem->pop();
      if (flag) {
        break;
      } else {
        continue;
      }
    }
    *postfix += write_elem(stack_elem);
  }
}

bool s21::ExampleModel::is_digit(char elem) {
  return ((elem >= 48 && elem <= 57) || elem == 46 || elem == 120 ||
          elem == 44);
}

bool s21::ExampleModel::is_operand(char elem) {
  std::string str = "+-*/%^ksctal";
  return (str.find(elem) != std::string::npos);
}

char s21::ExampleModel::trigonometric(std::string infix, int* i) {
  char result = infix[*i];
  if (infix[*i] == 's' && infix[*i + 1] == 'i') {
    result = 's', *i += 2;
  } else if (infix[*i] == 's' && infix[*i + 1] == 'q') {
    result = 'k', *i += 3;
  } else if (infix[*i] == 'c') {
    result = 'c', *i += 2;
  } else if (infix[*i] == 't') {
    result = 't', *i += 1;
  } else if (infix[*i] == 'l' && infix[*i + 1] == 'n') {
    result = 'l', *i += 1;
  } else if (infix[*i] == 'l' && infix[*i + 1] == 'o') {
    result = 'L', *i += 2;
  } else if (infix[*i] == 'a' && infix[*i + 1] == 's') {
    result = 'S', *i += 3;
  } else if (infix[*i] == 'a' && infix[*i + 1] == 'c') {
    result = 'C', *i += 3;
  } else if (infix[*i] == 'a' && infix[*i + 1] == 't') {
    result = 'T', *i += 2;
  }
  return result;
}

int s21::ExampleModel::math_operations(double x, std::string postfix,
                                       double* res, bool rad) {
  std::stack<double> stack_math;
  int error = 0, i = 0, j = 0;
  double r1 = 0.0, r2 = 0.0;
  std::string operand = "+-*/%^";
  std::string trigonometric = "sctSCTlLk";
  while (postfix[i] != '\0') {
    char c1[255] = {0};
    r1 = 0.0;
    r2 = 0.0;
    if (postfix[i] == 'x') {
      stack_math.push(x);
      i++;
    }
    if (is_digit(postfix[i])) {
      j = 0;
      while (postfix[i] != ' ') {
        c1[j++] = postfix[i++];
      }
      stack_math.push(digit_reform(c1));
    }
    if (operand.find(postfix[i]) != std::string::npos) {
      r2 = top_pop(&stack_math);
      if (!stack_math.empty()) {
        r1 = top_pop(&stack_math);
      } else {
        r1 = r2, r2 = 0.0;
      }
      stack_math.push(result_operand(postfix[i], r1, r2, &error));
    }
    if (trigonometric.find(postfix[i]) != std::string::npos) {
      r1 = top_pop(&stack_math);
      if (rad) {
        stack_math.push(result_trigonometric_rad(postfix[i], r1));
      } else {
        stack_math.push(result_trigonometric_grad(postfix[i], r1));
      }
    }
    i++;
  }
  *res = stack_math.top();
  return error;
}

double s21::ExampleModel::top_pop(std::stack<double>* stack_math) {
  double result = 0.0;
  if (!stack_math->empty()) {
    result = stack_math->top();
    stack_math->pop();
  }
  return result;
}

int s21::ExampleModel::priority(char elem) {
  int priority = 0;
  switch (elem) {
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case 's':
    case 'c':
    case 't':
    case 'a':
    case 'l':
      priority = 4;
      break;
  }
  return priority;
}

double s21::ExampleModel::result_operand(char postfix, double r1, double r2,
                                         int* error) {
  double result = 0;
  switch (postfix) {
    case '+':
      result = r1 + r2;
      break;
    case '-':
      result = r1 - r2;
      break;
    case '*':
      result = r1 * r2;
      break;
    case '/':
      if (r2 == 0) {
        *error = 1;
        result = 0;
      } else {
        result = r1 / r2;
      }
      break;
    case '%':
      result = fmod(r1, r2);
      break;
    case '^':
      result = pow(r1, r2);
      break;
  }
  return result;
}

double s21::ExampleModel::result_trigonometric_rad(char postfix, double r1) {
  switch (postfix) {
    case 's':
      return sin(r1);
    case 'c':
      return cos(r1);
    case 't':
      return tan(r1);
    case 'S':
      return asin(r1);
    case 'C':
      return acos(r1);
    case 'T':
      return atan(r1);
    case 'l':
      return log(r1);
    case 'L':
      return log10(r1);
    case 'k':
      return sqrt(r1);
    default:
      return 0.0;
  }
}

double s21::ExampleModel::result_trigonometric_grad(char postfix, double r1) {
  switch (postfix) {
    case 's':
      return sin(r1 * M_PI / 180.0);
    case 'c':
      return cos(r1 * M_PI / 180.0);
    case 't':
      return tan(r1 * M_PI / 180.0);
    case 'S':
      return asin(r1 * M_PI / 180.0);
    case 'C':
      return acos(r1 * M_PI / 180.0);
    case 'T':
      return atan(r1 * M_PI / 180.0);
    case 'l':
      return log(r1);
    case 'L':
      return log10(r1);
    case 'k':
      return sqrt(r1);
    default:
      return 0.0;
  }
}

double s21::ExampleModel::digit_reform(char* c1) {
  double digit = 0.0;
  digit = std::stod(c1);
  return digit;
}

double s21::CreditModel::annuit() {
  percent = percent / 1200;
  monthly = summ * (percent * pow((1 + percent), term) /
                    (pow((1 + percent), term) - 1));
  overpay = monthly * term - summ;
  return overpay + summ;
}

double s21::CreditModel::diff() {
  int debt_sum = summ / term;
  double buf_sum = summ;
  double itog = 0.0;

  monthly = (summ * percent / 100 * 30.4166666666667 / 365) + debt_sum;
  monthly_2 = monthly;

  for (int i = 0; i < term; i++) {
    monthly_2 = (buf_sum * percent / 100 * 30.4166666666667 / 365) + debt_sum;
    buf_sum = buf_sum - debt_sum;
    itog = itog + monthly_2;
  }

  overpay = itog - debt_sum * term;

  return itog;
}

void s21::DebitModel::result_debit(double period, double st_plus,
                                   double st_minus) {
  double result_plus = 0.0;
  double result_minus = 0.0;
  int count_plus = 0, count_p, count_minus = 0, count_m;
  count_plus = data / st_plus;
  count_minus = data / st_minus;

  if (kapital && period != 0) {
    result = summ * pow_debit(stavka, data, period);
    count_p = count_plus;
    while (count_p > 0) {
      result_plus =
          plus + result_plus * pow_debit(stavka, 30.4166666666667, st_plus);
      count_p--;
    }
    result_plus = result_plus *
                  pow_debit(stavka, (data - (st_plus * count_plus)), st_plus);
    count_m = count_minus;
    while (count_m > 0) {
      result_minus =
          minus + result_minus * pow_debit(stavka, 30.4166666666667, st_minus);
      count_m--;
    }
    result_minus =
        result_minus *
        pow_debit(stavka, (data - (st_minus * count_minus)), st_minus);
    result = result + result_plus - result_minus;
    result_procent =
        result - summ - (count_plus * plus) + (count_minus * minus);

  } else {
    double result_pp = plus;
    double result_mm = minus;
    count_p = count_plus;
    while (count_p - 1 > 0) {
      result_plus += result_pp * stavka / 100 * 30.4166666666667 / 365;
      count_p--;
      result_pp += plus;
    }
    if (data / st_plus > 1) {
      result_plus +=
          result_pp * stavka / 100 * (data - (st_plus * count_plus)) / 365;
    }

    count_m = count_minus;
    while (count_m - 1 > 0) {
      result_minus += result_mm * stavka / 100 * 30.4166666666667 / 365;
      count_m--;
      result_mm += minus;
    }
    if (data / st_minus > 1) {
      result_minus +=
          minus * stavka / 100 * (data - (st_minus * count_minus)) / 365;
    }
    result_procent =
        (summ * stavka * data / 365) / 100 + result_plus - result_minus;
    result = summ + (plus * count_plus) - (minus * count_minus);
  }
  double fix_summ = 1000000 * nalog / 100;
  double year = data / (365);
  result_nalog = (result_procent - (fix_summ * year)) * 0.13;
}

double s21::DebitModel::pow_debit(double stavka, double data, double period) {
  return pow((1 + stavka / 100 / (365 / period)), data / period);
}
