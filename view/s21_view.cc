#include "s21_view.h"

#include "ui_view.h"

namespace s21 {

View::View(s21::Controller *controller)
    : ui_(new Ui::MainWindow), controller_(controller) {
  ui_->setupUi(this);
  Initialize();
}

View::~View() { delete ui_; }

void View::Initialize() {
  maze_cols_ = controller_->GetMazeCols();
  maze_rows_ = controller_->GetMazeRows();
  cell_width_ = maze_size_ / maze_cols_;
  cell_height_ = maze_size_ / maze_rows_;
  is_end_set_ = false;
  is_start_set_ = false;
  update();
}

void View::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));
  painter.drawRect(offset_, offset_, maze_size_, maze_size_);
  if (maze_cols_ == 0 || maze_rows_ == 0) return;
  DrawMaze(&painter);
  DrawStartEndPoints(&painter);
  DrawPath(&painter);
}

void View::DrawMaze(QPainter *painter) {
  const auto &rightBorders = controller_->GetRightBorders();
  const auto &bottomBorders = controller_->GetBottomBorders();

  if (rightBorders.empty() || bottomBorders.empty()) return;
  for (int i = 0; i < maze_rows_; i++) {
    for (int j = 0; j < maze_cols_; j++) {
      if (bottomBorders[i][j] == 1) {
        painter->drawLine(offset_ + j * cell_width_,
                          offset_ + i * cell_height_ + cell_height_,
                          offset_ + j * cell_width_ + cell_width_,
                          offset_ + i * cell_height_ + cell_height_);
      }
      if (rightBorders[i][j] == 1) {
        painter->drawLine(offset_ + j * cell_width_ + cell_width_,
                          offset_ + i * cell_height_,
                          offset_ + j * cell_width_ + cell_width_,
                          offset_ + i * cell_height_ + cell_height_);
      }
    }
  }
}

void View::mousePressEvent(QMouseEvent *event) {
  int x = event->pos().x();
  int y = event->pos().y();

  int cellX = (x - offset_) / cell_width_ + 1;
  int cellY = (y - offset_) / cell_height_ + 1;

  if (x >= offset_ && x <= offset_ + maze_size_ && y >= offset_ &&
      y <= offset_ + maze_size_) {
    Point clickedPoint(cellY - 1, cellX - 1);
    if (event->button() == Qt::LeftButton) {
      controller_->SetStartPoint(clickedPoint);
      is_start_set_ = true;
    } else if (event->button() == Qt::RightButton) {
      controller_->SetEndPoint(clickedPoint);
      is_end_set_ = true;
    }
    update();  // Обновляем отрисовку
  }
}

void View::on_clear_button_clicked() {
  ui_->filename_label->setText("No file");
  controller_->SetMazeSize(0, 0);
  Initialize();
}

void View::on_generate_button_clicked() {
  ui_->filename_label->setText("No file");
  controller_->ClearData();
  controller_->GenerateMaze(ui_->rows_spinbox->value(),
                            ui_->cols_spinbox->value());
  Initialize();
}

void View::on_open_button_clicked() {
  QString fileName_open;
  fileName_open = QFileDialog::getOpenFileName(
      this, "Открыть файл с лабиринтом", "~/", "*.txt", nullptr,
      QFileDialog::DontUseNativeDialog);
  if (fileName_open.isNull()) {
    return;
  } else {
    QFileInfo fileInfo(fileName_open);
    QString justFileName = fileInfo.fileName();
    controller_->ReadFromFile(fileName_open.toStdString());
    Initialize();
    ui_->filename_label->setText(justFileName);
  }
}

void View::DrawStartEndPoints(QPainter *painter) {
  const Point &startPoint = controller_->GetStartPoint();
  const Point &endPoint = controller_->GetEndPoint();

  if (is_start_set_) {
    double centerX = offset_ + startPoint.col * cell_width_ + cell_width_ / 2;
    double centerY = offset_ + startPoint.row * cell_height_ + cell_height_ / 2;

    painter->setPen(QPen(Qt::blue, 2));
    painter->setBrush(QBrush(Qt::blue));
    painter->drawEllipse(QRectF(centerX - cell_width_ / 4,
                                centerY - cell_height_ / 4, cell_width_ / 2,
                                cell_height_ / 2));
  }

  if (is_end_set_) {
    double centerX = offset_ + endPoint.col * cell_width_ + cell_width_ / 2;
    double centerY = offset_ + endPoint.row * cell_height_ + cell_height_ / 2;

    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(QRectF(centerX - cell_width_ / 4,
                                centerY - cell_height_ / 4, cell_width_ / 2,
                                cell_height_ / 2));
  }
}

void View::DrawPath(QPainter *painter) {
  if (is_start_set_ && is_end_set_) {
    const auto &path = controller_->GetPath(controller_->GetStartPoint(),
                                            controller_->GetEndPoint());
    painter->setPen(QPen(Qt::green, 4));
    if (!path.empty()) {
      for (size_t i = 0; i < path.size() - 1; i++) {
        double centerX = offset_ + path[i].col * cell_width_ + cell_width_ / 2;
        double centerY =
            offset_ + path[i].row * cell_height_ + cell_height_ / 2;
        double nextCenterX =
            offset_ + path[i + 1].col * cell_width_ + cell_width_ / 2;
        double nextCenterY =
            offset_ + path[i + 1].row * cell_height_ + cell_height_ / 2;
        painter->drawLine(centerX, centerY, nextCenterX, nextCenterY);
      }
    }
  }
}

void View::on_savetofile_button_clicked() {
  QString fileName_save;
  fileName_save = QFileDialog::getSaveFileName(
      this, "Выберите файл для сохранения", "~/", "*.txt");
  if (!fileName_save.isEmpty()) {
    QFileInfo fileInfo(fileName_save);
    // Проверяем, указано ли расширение .txt
    if (fileInfo.suffix().isEmpty()) {
      fileName_save += ".txt";
    }
    QFile file(fileName_save);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      //  сохраняем размеры лабиринта
      out << maze_rows_ << " " << maze_cols_ << "\n";

      const auto &rightBorders = controller_->GetRightBorders();
      const auto &bottomBorders = controller_->GetBottomBorders();

      for (int i = 0; i < maze_rows_; i++) {
        for (int j = 0; j < maze_cols_; j++) {
          out << rightBorders[i][j] << " ";
        }
        out << "\n";
      }

      for (int i = 0; i < maze_rows_; i++) {
        for (int j = 0; j < maze_cols_; j++) {
          out << bottomBorders[i][j] << " ";
        }
        out << "\n";
      }
      // Закрываем файл
      file.close();
      QMessageBox::information(this, "Успех",
                               "Данные успешно сохранены в файл.");
    } else {
      QMessageBox::warning(this, "Ошибка",
                           "Не удалось открыть файл для записи.");
    }
  }
}

}  // namespace s21
