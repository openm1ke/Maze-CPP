#include "s21_model.h"

namespace s21 {

Model::Model() {}

void Model::SetMazeSize(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("Неверные размеры лабиринта.");
  }
  rows_ = rows;
  cols_ = cols;
}

int Model::GetMazeRows() { return rows_; }

int Model::GetMazeCols() { return cols_; }

std::vector<std::vector<int>>& Model::GetRightBorders() {
  return right_borders_;
}

std::vector<std::vector<int>>& Model::GetBottomBorders() {
  return bottom_borders_;
}

int Model::GetRandomInt() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 1);
  return distribution(gen);
}

//  заполняем линию уникальными значениями множеств
void Model::FillLineSet() {
  for (int i = 0; i < cols_; i++) {
    if (line_[i] == 0) {
      line_[i] = count_;
      count_++;
    }
  }
}

//  объединение множеств с одинаковыми значениями
void Model::MergeLineSet(int i, int element) {
  int set = line_[i + 1];
  for (int j = 0; j < cols_; j++) {
    if (line_[j] == set) {
      line_[j] = element;
    }
  }
}

//  подсчет количества уникальных значений
int Model::CountUniqueSet(int element) {
  int count = 0;
  for (int i = 0; i < cols_; i++) {
    if (line_[i] == element) {
      count++;
    }
  }
  return count;
}

//  подсчет горизонтальных линий
int Model::CountHorizontalLines(int row, int element) {
  int count = 0;
  for (int i = 0; i < cols_; i++) {
    if (line_[i] == element && bottom_borders_[row][i] == 0) {
      count++;
    }
  }
  return count;
}

//  проверка горизонтальных линий
void Model::CheckHorizontalLines(int row) {
  for (int i = 0; i < cols_; i++) {
    if (CountHorizontalLines(row, line_[i]) == 0) {
      bottom_borders_[row][i] = 0;
    }
  }
}

//  добавление горизонтальных линий
void Model::AddHorizontalLine(int row) {
  for (int i = 0; i < cols_; i++) {
    int rand = GetRandomInt();
    if (CountUniqueSet(line_[i]) != 1 || rand == 1) {
      bottom_borders_[row][i] = 1;
    }
  }
}

//  добавление вертикальных линий
void Model::AddVerticalLine(int row) {
  for (int i = 0; i < cols_ - 1; i++) {
    int rand = GetRandomInt();
    if (rand == 1 || line_[i] == line_[i + 1]) {
      right_borders_[row][i] = 1;
    } else {
      MergeLineSet(i, line_[i]);
    }
  }
  right_borders_[row][cols_ - 1] = 1;
}

//  добавление новой линии
void Model::AddNewLine(int row) {
  for (int i = 0; i < cols_; i++) {
    if (bottom_borders_[row][i] == 1) {
      line_[i] = 0;
    }
  }
}

//  проверка последней линии
void Model::CheckLastLine() {
  for (int i = 0; i < cols_ - 1; i++) {
    if (line_[i] != line_[i + 1]) {
      right_borders_[rows_ - 1][i] = 0;
      MergeLineSet(i, line_[i]);
    }
  }
}

//  добавление конечной линии
void Model::AddLastLine() {
  FillLineSet();
  AddVerticalLine(rows_ - 1);
  CheckLastLine();
}

//  генерация лабиринта
void Model::GenerateMaze(int rows, int cols) {
  SetMazeSize(rows, cols);

  right_borders_.resize(rows_, std::vector<int>(cols_));
  bottom_borders_.resize(rows_, std::vector<int>(cols_));
  line_.resize(cols_, 0);

  for (int i = 0; i < rows_ - 1; i++) {
    FillLineSet();
    AddVerticalLine(i);
    AddHorizontalLine(i);
    CheckHorizontalLines(i);
    AddNewLine(i);
  }
  AddLastLine();
  line_.clear();
  count_ = 1;
}

void Model::ReadFromFile(std::string filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Не удалось открыть файл: " << filename << std::endl;
    exit(1);
  }

  if (!(file >> rows_ >> cols_)) {
    std::cerr << "Ошибка при считывании размеров массивов." << std::endl;
    exit(1);
  }

  if (rows_ <= 0 || cols_ <= 0) {
    std::cerr << "Размеры должны быть больше нуля." << std::endl;
    exit(1);
  }

  right_borders_ =
      std::vector<std::vector<int>>(rows_, std::vector<int>(cols_));

  for (auto& row : right_borders_)
    for (int& element : row) file >> element;

  std::string emptyLine;
  std::getline(file, emptyLine);

  bottom_borders_ =
      std::vector<std::vector<int>>(rows_, std::vector<int>(cols_));
  for (auto& row : bottom_borders_)
    for (int& element : row) file >> element;

  file.close();
}

void Model::ClearData() {
  right_borders_.clear();
  bottom_borders_.clear();
  wave_matrix_.clear();
  line_.clear();
  rows_ = 0;
  cols_ = 0;
  count_ = 1;
}

std::vector<Point> Model::GetPath(const Point& start, const Point& end) {
  if (start.row < 0 || start.col < 0 || end.row < 0 || end.col < 0) {
    std::cerr << "Неверные координаты точек." << std::endl;
    exit(1);
  }
  count_ = 1;
  wave_matrix_.clear();
  wave_matrix_.resize(rows_, std::vector<int>(cols_, 0));
  wave_matrix_[start.row][start.col] = count_;
  bool hasPath = true;
  while (wave_matrix_[end.row][end.col] == 0 && (hasPath = GetWave())) {
    count_++;
  }
  return FindPath(end, hasPath);
}

bool Model::GetWave() {
  bool flag = false;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (wave_matrix_[i][j] == count_) {
        flag = true;
        if (j < cols_ - 1 && !right_borders_[i][j] && !wave_matrix_[i][j + 1]) {
          wave_matrix_[i][j + 1] = count_ + 1;
        }
        if (j > 0 && !right_borders_[i][j - 1] && !wave_matrix_[i][j - 1]) {
          wave_matrix_[i][j - 1] = count_ + 1;
        }
        if (i > 0 && !bottom_borders_[i - 1][j] && !wave_matrix_[i - 1][j]) {
          wave_matrix_[i - 1][j] = count_ + 1;
        }
        if (i < rows_ - 1 && !bottom_borders_[i][j] &&
            !wave_matrix_[i + 1][j]) {
          wave_matrix_[i + 1][j] = count_ + 1;
        }
      }
    }
  }

  return flag;
}

std::vector<Point> Model::FindPath(Point pos, bool hasPath) const {
  std::vector<Point> path;
  int count = count_;

  if (hasPath) {
    path.push_back({pos.row, pos.col});
  }

  while (count != 1 && hasPath) {
    count--;
    if (pos.col < cols_ - 1 && wave_matrix_[pos.row][pos.col + 1] == count &&
        !right_borders_[pos.row][pos.col]) {
      ++pos.col;
    } else if (pos.col > 0 && wave_matrix_[pos.row][pos.col - 1] == count &&
               !right_borders_[pos.row][pos.col - 1]) {
      --pos.col;
    } else if (pos.row > 0 && wave_matrix_[pos.row - 1][pos.col] == count &&
               !bottom_borders_[pos.row - 1][pos.col]) {
      --pos.row;
    } else if (pos.row < rows_ - 1 &&
               wave_matrix_[pos.row + 1][pos.col] == count &&
               !bottom_borders_[pos.row][pos.col]) {
      ++pos.row;
    }
    path.push_back({pos.row, pos.col});
  }

  return path;
}

}  // namespace s21
