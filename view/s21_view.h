#ifndef SRC_VIEW_S21_VIEW_H_
#define SRC_VIEW_S21_VIEW_H_

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

#include "../controller/s21_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class Model;

class View : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * Конструктор окна
   */
  explicit View(s21::Controller *controller = nullptr);
  /**
   * Деструктор окна
   */
  ~View();

 protected:
  /**
   * Метод отрисовки линий в окне
   * @param event - событие отрисовки
   */
  void paintEvent(QPaintEvent *event) override;
  /**
   * Метод обработки нажатия мыши
   * @param event - событие нажатия мыши
   */
  void mousePressEvent(QMouseEvent *event) override;
  /**
   * Метод инициализации переменных для отрисовки лабиринта
   */
  void Initialize();
  /**
   * Метод отрисовки лабиринта
   * @param painter - холст для отрисовки
   */
  void DrawMaze(QPainter *painter);
  /**
   * Метод отрисовки начальной и конечной точек
   * @param painter - холст для отрисовки
   */
  void DrawStartEndPoints(QPainter *painter);
  /**
   * Метод отрисовки пути
   * @param painter - холст для отрисовки
   */
  void DrawPath(QPainter *painter);

 private slots:
  void on_clear_button_clicked();
  void on_generate_button_clicked();
  void on_open_button_clicked();

  void on_savetofile_button_clicked();

 private:
  Ui::MainWindow *ui_;
  s21::Controller *controller_;
  int offset_ = 10;
  double maze_size_ = 500.0;
  double cell_width_, cell_height_;
  int maze_rows_, maze_cols_;
  bool is_start_set_ = false;
  bool is_end_set_ = false;
};
}  // namespace s21
#endif  // SRC_VIEW_S21_VIEW_H_
