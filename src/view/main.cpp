#include <QApplication>

#include "../controller/controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");
  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString& locale : uiLanguages) {
    const QString baseName = "smartcalc_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  Ui_MainWindow* uiInstance = new Ui_MainWindow();
  s21::MyCalc* modelInstance =
      new s21::MyCalc();  // Инициализация modelInstance

  // создание объекта контроллера с передачей параметров
  s21::Controller controller(uiInstance, modelInstance);

  // Передаем контроллер при создании объекта MainWindow
  s21::MainWindow w(&controller);
  w.setWindowTitle("SmartCalc_v2.0");
  w.show();

  return a.exec();
}
