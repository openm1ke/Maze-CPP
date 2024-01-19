#include <QApplication>

#include "view/s21_view.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);
  view.show();
  return app.exec();
}
