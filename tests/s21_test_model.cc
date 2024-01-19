#include <gtest/gtest.h>

#include <iostream>

#include "../model/s21_model.h"

TEST(Test, GetSetMazeSize) {
  s21::Model* model = new s21::Model();
  EXPECT_EQ(model->GetMazeRows(), 0);
  EXPECT_EQ(model->GetMazeCols(), 0);
  model->SetMazeSize(5, 6);
  EXPECT_EQ(model->GetMazeRows(), 5);
  EXPECT_EQ(model->GetMazeCols(), 6);
  EXPECT_THROW(model->SetMazeSize(-1, 0), std::invalid_argument);
  delete model;
}

TEST(Test, GetRightBorders) {
  s21::Model* model = new s21::Model();
  EXPECT_TRUE(model->GetRightBorders().empty());
  delete model;
}

TEST(Test, GetBottomBorders) {
  s21::Model* model = new s21::Model();
  EXPECT_TRUE(model->GetBottomBorders().empty());
  delete model;
}

TEST(Test, GetRandomInt) {
  s21::Model* model = new s21::Model();
  int rand = model->GetRandomInt();
  EXPECT_TRUE(rand == 0 || rand == 1);
  delete model;
}

TEST(Test, GenerateMaze) {
  s21::Model* model = new s21::Model();
  int rows = 5;
  int cols = 10;
  model->GenerateMaze(rows, cols);
  EXPECT_EQ(model->GetMazeRows(), rows);
  EXPECT_EQ(model->GetMazeCols(), cols);
  EXPECT_EQ(model->GetRightBorders().size(), rows);
  EXPECT_EQ(model->GetBottomBorders().size(), rows);
  auto r_borders = model->GetRightBorders();
  auto b_borders = model->GetBottomBorders();
  for (auto i = 0; i < rows; i++) {
    for (auto j = 0; j < cols; j++) {
      EXPECT_TRUE(r_borders[i][j] == 0 || r_borders[i][j] == 1);
      EXPECT_TRUE(b_borders[i][j] == 0 || b_borders[i][j] == 1);
    }
  }
  delete model;
}

TEST(Test, GenerateMazeOne) {
  s21::Model* model = new s21::Model();
  int rows = 1;
  int cols = 1;
  model->GenerateMaze(rows, cols);
  EXPECT_EQ(model->GetMazeRows(), rows);
  EXPECT_EQ(model->GetMazeCols(), cols);
  EXPECT_EQ(model->GetRightBorders().size(), rows);
  EXPECT_EQ(model->GetBottomBorders().size(), rows);
  auto r_borders = model->GetRightBorders();
  auto b_borders = model->GetBottomBorders();
  for (auto i = 0; i < rows; i++) {
    for (auto j = 0; j < cols; j++) {
      EXPECT_EQ(r_borders[i][j], 1);
      EXPECT_EQ(b_borders[i][j], 0);
    }
  }
  delete model;
}

TEST(Test, ReadFromFile) {
  s21::Model* model = new s21::Model();
  std::string filename = "mazes/maze4.txt";
  model->ReadFromFile(filename);
  EXPECT_EQ(model->GetMazeRows(), 4);
  EXPECT_EQ(model->GetMazeCols(), 4);
  std::vector<std::vector<int>> r_borders = {
      {0, 0, 0, 1},
      {1, 0, 1, 1},
      {0, 1, 0, 1},
      {0, 0, 0, 1},
  };
  std::vector<std::vector<int>> b_borders = {
      {1, 0, 1, 0},
      {0, 0, 1, 0},
      {1, 1, 0, 1},
      {1, 1, 1, 1},
  };
  EXPECT_EQ(model->GetRightBorders().size(), 4);
  EXPECT_EQ(model->GetBottomBorders().size(), 4);
  EXPECT_EQ(model->GetRightBorders(), r_borders);
  EXPECT_EQ(model->GetBottomBorders(), b_borders);
  delete model;
}

TEST(Test, ReadFromFileThrowOpen) {
  s21::Model* model = new s21::Model();
  std::string filename = "mazes/aboba.txt";
  ASSERT_EXIT(model->ReadFromFile(filename), ::testing::ExitedWithCode(1), "");
  delete model;
}

TEST(Test, ReadFromFileThrowNegative) {
  s21::Model* model = new s21::Model();
  std::string filename = "mazes/negative.txt";
  ASSERT_EXIT(model->ReadFromFile(filename), ::testing::ExitedWithCode(1), "");
  delete model;
}

TEST(Test, ReadFromFileThrowEmpty) {
  s21::Model* model = new s21::Model();
  std::string filename = "mazes/empty_row_col.txt";
  ASSERT_EXIT(model->ReadFromFile(filename), ::testing::ExitedWithCode(1), "");
  delete model;
}

TEST(Test, ClearData) {
  s21::Model* model = new s21::Model();
  model->ClearData();
  EXPECT_EQ(model->GetMazeRows(), 0);
  EXPECT_EQ(model->GetMazeCols(), 0);
  EXPECT_TRUE(model->GetRightBorders().empty());
  EXPECT_TRUE(model->GetBottomBorders().empty());
  delete model;
}

TEST(Test, GetPath) {
  s21::Model* model = new s21::Model();
  model->ReadFromFile("mazes/maze4.txt");
  s21::Point start = {2, 0};
  s21::Point end = {3, 3};
  std::vector<s21::Point> path = model->GetPath(start, end);
  std::vector<s21::Point> original_path = {{3, 3}, {3, 2}, {2, 2}, {2, 3},
                                           {1, 3}, {0, 3}, {0, 2}, {0, 1},
                                           {1, 1}, {2, 1}, {2, 0}};
  for (auto i = 0; i < static_cast<int>(original_path.size()) &&
                   i < static_cast<int>(path.size());
       i++) {
    EXPECT_EQ(path[i].row, original_path[i].row);
    EXPECT_EQ(path[i].col, original_path[i].col);
  }
  delete model;
}

TEST(Test, GetPathInvalid) {
  s21::Model* model = new s21::Model();
  model->ReadFromFile("mazes/maze4.txt");
  s21::Point start = {-2, 0};
  s21::Point end = {3, 3};
  ASSERT_EXIT(model->GetPath(start, end), ::testing::ExitedWithCode(1), "");
  delete model;
}
