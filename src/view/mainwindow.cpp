#include "mainwindow.h"

#include "ui_mainwindow.h"

s21::MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(controller) {
  ui->setupUi(this);
  this->setFixedSize(1170, 480);
  ui->result_show->setText("");
  InitializeButtonToSymbol();

  ui->graph_widget->setInteraction(QCP::iRangeZoom, true);
  ui->graph_widget->setInteraction(QCP::iRangeDrag, true);
  CustomPlot = ui->graph_widget;

  connect(ui->pushButton_AC, &QPushButton::clicked, this,
          &MainWindow::OnPushButtonClickedAC);
  connect(ui->pushButton_equals, &QPushButton::clicked, this,
          &MainWindow::OnPushButtonEqualsClicked);
  connect(ui->pushButton_Backspace, &QPushButton::clicked, this,
          &MainWindow::OnPushButtonBackspaceClicked);
  connect(ui->pushButton_graph, &QPushButton::clicked, this,
          &MainWindow::OnPushButtonGraphClicked);
}

s21::MainWindow::~MainWindow() { delete ui; }

void s21::MainWindow::InitializeButtonToSymbol() {
  ButtonToSymbol[this->ui->pushButton_0] = "0";
  ButtonToSymbol[this->ui->pushButton_1] = "1";
  ButtonToSymbol[this->ui->pushButton_2] = "2";
  ButtonToSymbol[this->ui->pushButton_3] = "3";
  ButtonToSymbol[this->ui->pushButton_4] = "4";
  ButtonToSymbol[this->ui->pushButton_5] = "5";
  ButtonToSymbol[this->ui->pushButton_6] = "6";
  ButtonToSymbol[this->ui->pushButton_7] = "7";
  ButtonToSymbol[this->ui->pushButton_8] = "8";
  ButtonToSymbol[this->ui->pushButton_9] = "9";
  ButtonToSymbol[this->ui->pushButton_X] = "x";
  ButtonToSymbol[this->ui->pushButton_plus] = "+";
  ButtonToSymbol[this->ui->pushButton_minus] = "-";
  ButtonToSymbol[this->ui->pushButton_divide] = "/";
  ButtonToSymbol[this->ui->pushButton_multiplication] = "*";
  ButtonToSymbol[this->ui->pushButton_bracket_1] = "(";
  ButtonToSymbol[this->ui->pushButton_bracket_2] = ")";
  ButtonToSymbol[this->ui->pushButton_pow] = "^";
  ButtonToSymbol[this->ui->pushButton_dot] = ".";
  ButtonToSymbol[this->ui->pushButton_mod] = "mod";
  ButtonToSymbol[this->ui->pushButton_sin] = "sin(";
  ButtonToSymbol[this->ui->pushButton_cos] = "cos(";
  ButtonToSymbol[this->ui->pushButton_tan] = "tan(";
  ButtonToSymbol[this->ui->pushButton_Asin] = "asin(";
  ButtonToSymbol[this->ui->pushButton_Acos] = "acos(";
  ButtonToSymbol[this->ui->pushButton_Atan] = "atan(";
  ButtonToSymbol[this->ui->pushButton_ln] = "ln(";
  ButtonToSymbol[this->ui->pushButton_log] = "log(";
  ButtonToSymbol[this->ui->pushButton_sqrt] = "sqrt(";
  ButtonToSymbol[this->ui->pushButton_E] = "e";
  for (const auto &entry : ButtonToSymbol) {
    QPushButton *button = entry.first;
    std::string symbol = entry.second;
    connect(button, &QPushButton::clicked, [this, symbol] {
      controller->InputLine(symbol);
      UpdateResultShow();
    });
  }
}

void s21::MainWindow::OnPushButtonEqualsClicked() {
  ui->expression->setText("");
  controller->InputLine("=");
  ui->expression->setText(QString::fromStdString(controller->GetInputString()));
  ui->result_show->setText("");
  std::string input_string = controller->GetInputString();
  std::string output_string = "";
  std::string line_x = std::to_string(ui->lineEdit_x->text().toDouble());
  controller->ProcessCalculation(input_string, line_x, output_string);
  ui->result_show->setText(QString::fromStdString(output_string));
}

void s21::MainWindow::OnPushButtonClickedAC() {
  controller->ClearStrings();
  UpdateResultShow();
  ui->expression->setText(QString::fromStdString(controller->GetInputString()));
}

void s21::MainWindow::UpdateResultShow() {
  std::string result_string = controller->GetInputString();
  ui->result_show->setText(QString::fromStdString(result_string));
}

void s21::MainWindow::OnPushButtonBackspaceClicked() {
  controller->RemoveLastCharacter();
  UpdateResultShow();
}

void s21::MainWindow::OnPushButtonGraphClicked() {
  double x_max = ui->lineEdit_x_max->text().toDouble();
  double x_min = ui->lineEdit_x_min->text().toDouble();
  double y_max = ui->lineEdit_y_max->text().toDouble();
  double y_min = ui->lineEdit_y_min->text().toDouble();
  std::string input_string = controller->GetInputString();
  if (!input_string.empty()) {
    controller->FillGraphValues(input_string, x_max, x_min, y_max, y_min);
    UpdateGraph(x_min, x_max, y_min, y_max);
  }
}

void s21::MainWindow::UpdateGraph(double x_min, double x_max, double y_min,
                                  double y_max) {
  QVector<double> QVectorXData((controller->get_XData()).begin(),
                               (controller->get_XData()).end());
  QVector<double> QVectorYData((controller->get_YData()).begin(),
                               (controller->get_YData()).end());
  CustomPlot->addGraph();
  CustomPlot->graph(0)->setData(QVectorXData, QVectorYData);
  CustomPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
  CustomPlot->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
  //    CustomPlot->xAxis->setLabel("X Axis Label");
  //    CustomPlot->yAxis->setLabel("Y Axis Label");
  ui->graph_widget->xAxis->setRange(x_min, x_max);
  ui->graph_widget->yAxis->setRange(y_min - 0.5, y_max + 0.5);
  CustomPlot->replot();
  QVectorXData.clear();
  QVectorYData.clear();
  controller->ClearXData();
  controller->ClearYData();
}

void s21::MainWindow::on_pushButton_credit_clicked() {
  CreditCalc *creditcalc = new CreditCalc(controller, this);
  creditcalc->show();
}
