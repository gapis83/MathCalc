#ifndef SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_MAINWINDOW_H
#define SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "creditcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void UpdateResultShow();
  void OnPushButtonEqualsClicked();
  void OnPushButtonClickedAC();
  void OnPushButtonBackspaceClicked();
  void OnPushButtonGraphClicked();
  void UpdateGraph(double x_min, double x_max, double y_min, double y_max);

  void on_pushButton_credit_clicked();

 private:
  Ui::MainWindow *ui;
  Controller *controller;
  std::map<QPushButton *, std::string> ButtonToSymbol;
  QCustomPlot *CustomPlot;
  CreditCalc *creditcalc;
  void InitializeButtonToSymbol();
};
}  // namespace s21

#endif  // SRC_SMARTCALC_V2_SRC_SMARTCALC_V2_MAINWINDOW_H
