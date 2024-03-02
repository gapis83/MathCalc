#include "creditcalc.h"

#include "ui_creditcalc.h"

s21::CreditCalc::CreditCalc(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditCalc), controller(controller) {
  ui->setupUi(this);
  InitializeUIValues();
  //    connect(ui->pushButton_start, &QPushButton::clicked, this,
  //    &CreditCalc::on_pushButton_start_clicked);
}

s21::CreditCalc::~CreditCalc() { delete ui; }

void s21::CreditCalc::InitializeUIValues() {
  ui->lineEdit_amount->setText("1000000");
  ui->lineEdit_term->setText("12");
  ui->lineEdit_rate->setText("5.0");
  ui->radioButton_annuity->setChecked(true);
}

void s21::CreditCalc::ClearUIFields() {
  ui->lineEdit_overpayment->clear();
  ui->lineEdit_total_payment->clear();
}

void s21::CreditCalc::on_calculate_clicked() {
  ClearUIFields();
  std::string amount_std = ui->lineEdit_amount->text().toStdString();
  std::string term_std = ui->lineEdit_term->text().toStdString();
  std::string rate_std = ui->lineEdit_rate->text().toStdString();
  if (controller->ValidateInputFields(amount_std, rate_std, term_std)) {
    ui->list_values->clear();
    bool annuity = true;
    if (ui->radioButton_annuity->isChecked()) {
      annuity = true;
    } else if (ui->radioButton_differentiated->isChecked()) {
      annuity = false;
    }
    controller->CalculateCredit(amount_std, rate_std, term_std, annuity);
    QString overpayment_result =
        QString::fromStdString(controller->get_overpayment_str());
    ui->lineEdit_overpayment->setText(overpayment_result);
    QString total_payment_result =
        QString::fromStdString(controller->get_total_payment_str());
    ui->lineEdit_total_payment->setText(total_payment_result);
    UpdateListWidget();
  }
}

void s21::CreditCalc::UpdateListWidget() {
  // Добавляем данные из monthly_payments_ в QListWidget
  ui->list_values->clear();
  for (const std::string &payment : controller->get_monthly_payments()) {
    ui->list_values->addItem(QString::fromStdString(payment));
  }
}
