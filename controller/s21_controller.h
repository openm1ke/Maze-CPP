#ifndef SRC_CONTROLLER_S21_CONTROLLER_H_
#define SRC_CONTROLLER_S21_CONTROLLER_H_

#include "../model/s21_model.h"

namespace s21 {
class Controller {
 public:
  /**
   * Конструктор контроллера
   */
  explicit Controller(Model* model);
  /**
   * Метод создания лабиринта с параметрами ширины и высоты
   * @param rows - ширина лабиринта
   * @param cols - высота лабиринта
   */
  void SetMazeSize(int rows, int cols);
  /**
   * Метод получения ширины лабиринта
   * @return - ширина лабиринта
   */
  int GetMazeRows();
  /**
   * Метод получения высоты лабиринта
   * @return - высота лабиринта
   */
  int GetMazeCols();
  /**
   * Метод генерации случайного лабиринта с параметрами ширины и высоты
   * @param rows - ширина лабиринта
   * @param cols - высота лабиринта
   */
  void GenerateMaze(int rows, int cols);
  /**
   * Метод считывания лабиринта из файла
   * @param filename - имя файла
   */
  void ReadFromFile(std::string filename);
  /**
   * Метод получения матрицы заполнения лабиринта стенами справа
   */
  const std::vector<std::vector<int>>& GetRightBorders();
  /**
   * Метод получения матрицы заполнения лабиринта снизу
   */
  const std::vector<std::vector<int>>& GetBottomBorders();
  /**
   * Метод очистки данных
   */
  void ClearData();
  /**
   * Метод получения пути из модели
   * @param start - координаты начальной точки
   * @param end - координаты конечной точки
   * @return - путь
   */
  const std::vector<Point> GetPath(const Point& start, const Point& end);
  /**
   * Метод установки координат начальной точки для поиска пути
   * @param start - координаты начальной точки
   */
  void SetStartPoint(const Point& start) { model_->SetStartPoint(start); }
  /**
   * Метод установки координат конечной точки для поиска пути
   * @param end - координаты конечной точки
   */
  void SetEndPoint(const Point& end) { model_->SetEndPoint(end); }
  /**
   * Метод получения координат начальной точки для поиска пути
   * @return - координаты начальной точки
   */
  const Point& GetStartPoint() const { return model_->GetStartPoint(); }
  /**
   * Метод получения координат конечной точки для поиска пути
   * @return - координаты конечной точки
   */
  const Point& GetEndPoint() const { return model_->GetEndPoint(); }

 private:
  Model* model_ = nullptr;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_S21_CONTROLLER_H_
