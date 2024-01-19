#ifndef SRC_MODEL_S21_MODEL_H_
#define SRC_MODEL_S21_MODEL_H_

#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

namespace s21 {

/**
 * Структура для хранения координат
 */
struct Point {
  /**
   * Координата по оси Х
   */
  int row;
  /**
   * Координата по оси Y
   */
  int col;
  /**
   * Конструктор
   */
  Point() : row(0), col(0) {}
  /**
   * Конструктор
   * @param row - координата по оси Х
   * @param col - координата по оси Y
   */
  Point(int row, int col) : row(row), col(col) {}
};

class Model {
 public:
  /**
   *  Конструктор модели
   */
  Model();
  /**
   * Создание лабиринта с параметрами ширины и высоты
   * @param rows - ширина лабиринта
   * @param cols - высота лабиринта
   */
  void SetMazeSize(int rows, int cols);
  /**
   * Метод получения ширины лабиринта
   */
  int GetMazeRows();
  /**
   * Метод получения высоты лабиринта
   */
  int GetMazeCols();
  /**
   * Метод получения случайного числа 0 или 1
   */
  int GetRandomInt();
  /**
   * Метод получения матрицы заполнения лабиринта стенами справа
   * @return - матрица заполнения лабиринта стенами справа
   */
  std::vector<std::vector<int>>& GetRightBorders();
  /**
   * Метод получения матрицы заполнения лабиринта снизу
   * @return - матрица заполнения лабиринта стенами снизу
   */
  std::vector<std::vector<int>>& GetBottomBorders();
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
   * Метод установки координат начальной точки для поиска пути
   * @param start - координаты начальной точки
   */
  void SetStartPoint(const Point& start) { start_ = start; }
  /**
   * Метод установки координат конечной точки для поиска пути
   * @param end - координаты конечной точки
   */
  void SetEndPoint(const Point& end) { end_ = end; }
  /**
   * Метод получения координат начальной точки для поиска пути
   * @return - координаты начальной точки
   */
  const Point& GetStartPoint() const { return start_; }
  /**
   * Метод получения координат конечной точки для поиска пути
   * @return - координаты конечной точки
   */
  const Point& GetEndPoint() const { return end_; }
  /**
   * Метод получения пути из начальной точки в конечную
   * @param start - координаты начальной точки
   * @param end - координаты конечной точки
   * @return - путь из начальной точки в конечную
   */
  std::vector<Point> GetPath(const Point& start, const Point& end);
  /**
   * Метод очистки лабиринта
   */
  void ClearData();

 protected:
  /**
   * Метод заполнения лабиринта стенами
   */
  void FillLineSet();
  /**
   * Метод объединения множеств с одинаковыми значениями
   * @param i - индекс линии
   * @param element - значение
   */
  void MergeLineSet(int i, int element);
  /**
   * Метод подсчет количества уникальных значений в множестве
   * @param element - значение множества
   */
  int CountUniqueSet(int element);
  /**
   * Метод подсчета количества множеств с определенным значением в линии
   * @param row - индекс линии
   * @param element - значение
   */
  int CountHorizontalLines(int row, int element);
  /**
   * Метод проверки горизонтальных линий
   * @param row - индекс линии
   */
  void CheckHorizontalLines(int row);
  /**
   * Метод добавления стен снизу в линию
   * @param row - индекс линии
   */
  void AddHorizontalLine(int row);
  /**
   * Метод добавления стен справа в линию
   * @param row - индекс линии
   */
  void AddVerticalLine(int row);
  /**
   * Метод добавления новой линии на основе предыдущей
   * @param row - индекс линии
   */
  void AddNewLine(int row);
  /**
   * Метод проверки последей линии
   */
  void CheckLastLine();
  /**
   * Метод добавления конечной линии
   */
  void AddLastLine();
  /**
   * Метод поиска пути
   * @param pos - координаты начальной точки
   * @param hasPath - флаг наличия пути
   * @return - путь состоящий из координат
   */
  std::vector<Point> FindPath(Point pos, bool hasPath) const;
  /**
   * Метод проверки пути
   */
  bool GetWave();

 private:
  int rows_ = 0;
  int cols_ = 0;
  int count_ = 1;
  std::vector<int> line_;
  Point start_;
  Point end_;
  std::vector<std::vector<int>> right_borders_, bottom_borders_, wave_matrix_;
};

}  // namespace s21
#endif  // SRC_MODEL_S21_MODEL_H_
