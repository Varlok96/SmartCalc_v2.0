#include "debit.h"

#include "ui_debit.h"

Debit::Debit(QWidget *parent) : QDialog(parent), ui(new Ui::Debit) {
  ui->setupUi(this);
}

Debit::~Debit() { delete ui; }

void Debit::on_pushButton_result_clicked() {
  double summ, stavka, nalog, plus, minus, data;
  bool kapital;
  summ = ui->doubleSpinBox_sum->value();
  stavka = ui->doubleSpinBox_stavka->value();
  nalog = ui->doubleSpinBox_nalog->value();
  plus = ui->doubleSpinBox_plus->value();
  minus = ui->doubleSpinBox_min->value();
  data = ui->spinBox_data->value();
  kapital = ui->checkBox_kapital->isChecked();
  data *= comboBox_data;
  if (comboBox_period == 0) {
    comboBox_period = comboBox_data * data;
  }
  s21::DebitController model(summ, stavka, nalog, plus, minus, data, kapital);
  model.result_debit(comboBox_period, comboBox_plus, comboBox_minus);

  ui->doubleSpinBox_result_procent->setValue(model.SetRezultProcent());
  ui->doubleSpinBox_result_sum->setValue(model.SetRezult());
  ui->doubleSpinBox_result_nalog->setValue(model.SetRezultNalog());
}

void Debit::on_comboBox_data_activated(int index) {
  if (index == 0) {
    comboBox_data = 1;
  } else if (index == 1) {
    comboBox_data = 30.4166666666667;
  } else if (index == 2) {
    comboBox_data = 30.4166666666667 * 12;
  }
}

void Debit::on_comboBox_period_activated(int index) {
  if (index == 0) {
    comboBox_period = 1;
  } else if (index == 1) {
    comboBox_period = 7;
  } else if (index == 2) {
    comboBox_period = 30.4166666666667;
  } else if (index == 3) {
    comboBox_period = 30.4166666666667 * 3;
  } else if (index == 4) {
    comboBox_period = 30.4166666666667 * 6;
  } else if (index == 5) {
    comboBox_period = 30.4166666666667 * 12;
  } else if (index == 6) {
    comboBox_period = 0;
  }
}

void Debit::on_comboBox_plus_activated(int index) {
  if (index == 0) {
    comboBox_plus = 30.4166666666667;
  } else if (index == 1) {
    comboBox_plus = 30.4166666666667 * 3;
  } else if (index == 2) {
    comboBox_plus = 30.4166666666667 * 6;
  } else if (index == 3) {
    comboBox_plus = 30.4166666666667 * 12;
  }
}

void Debit::on_comboBox_minus_activated(int index) {
  if (index == 0) {
    comboBox_minus = 30.4166666666667;
  } else if (index == 1) {
    comboBox_minus = 30.4166666666667 * 3;
  } else if (index == 2) {
    comboBox_minus = 30.4166666666667 * 6;
  } else if (index == 3) {
    comboBox_minus = 30.4166666666667 * 12;
  }
}
