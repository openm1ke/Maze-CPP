#include "s21_controller.h"

namespace s21 {

Controller::Controller(Model* model) : model_(model) {}

void Controller::SetMazeSize(int rows, int cols) {
  model_->SetMazeSize(rows, cols);
}

void Controller::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

int Controller::GetMazeRows() { return model_->GetMazeRows(); }

int Controller::GetMazeCols() { return model_->GetMazeCols(); }

void Controller::ReadFromFile(std::string filename) {
  model_->ReadFromFile(filename);
}

const std::vector<std::vector<int>>& Controller::GetRightBorders() {
  return model_->GetRightBorders();
}

const std::vector<std::vector<int>>& Controller::GetBottomBorders() {
  return model_->GetBottomBorders();
}

void Controller::ClearData() { model_->ClearData(); }

const std::vector<Point> Controller::GetPath(const Point& start,
                                             const Point& end) {
  return model_->GetPath(start, end);  // Метод для получения пути из модели
}

}  // namespace s21
