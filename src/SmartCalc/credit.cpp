#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  double summ, itog = 0, percent;
  int term;
  summ = ui->sumcredit->text().toDouble();
  term = ui->loan_term->text().toInt();
  percent = ui->percent->text().toDouble();
  s21::CreditController model_credit(summ, term, percent);
  if (ui->annuit->isChecked()) {
    itog = model_credit.annuit();
    QString qsum = QString::number(itog, 'f', 2);
    QString qmonth = QString::number(model_credit.SetMonthly(), 'f', 2);
    QString qover = QString::number(model_credit.SetOverpay(), 'f', 2);
    ui->all_sum->setText(qsum);
    ui->percent_pay->setText(qover);
    ui->month_pay->setText(qmonth);
  } else if (ui->diff->isChecked()) {
    itog = model_credit.diff();
    QString qmonth = QString::number(model_credit.SetMonthly(), 'f', 2);
    ui->month_pay->setText(qmonth + " ... ");
    qmonth = QString::number(model_credit.SetMonthly_2(), 'f', 2);
    ui->month_pay->setText(ui->month_pay->text() + qmonth);
    QString qsum = QString::number(itog, 'f', 2);
    QString qover = QString::number(model_credit.SetOverpay(), 'f', 2);
    ui->all_sum->setText(qsum);
    ui->percent_pay->setText(qover);
  }
}
