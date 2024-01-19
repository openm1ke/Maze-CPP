/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSpinBox *cols_spinbox;
    QLabel *cols_label;
    QLabel *rows_label;
    QSpinBox *rows_spinbox;
    QPushButton *open_button;
    QPushButton *generate_button;
    QPushButton *clear_button;
    QLabel *filename_label;
    QPushButton *savetofile_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(665, 520);
        MainWindow->setMinimumSize(QSize(665, 520));
        MainWindow->setMaximumSize(QSize(696, 520));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        cols_spinbox = new QSpinBox(centralwidget);
        cols_spinbox->setObjectName("cols_spinbox");
        cols_spinbox->setGeometry(QRect(610, 70, 45, 24));
        QFont font;
        font.setFamilies({QString::fromUtf8("Gotham Pro")});
        cols_spinbox->setFont(font);
        cols_spinbox->setMinimum(1);
        cols_spinbox->setMaximum(50);
        cols_spinbox->setValue(10);
        cols_label = new QLabel(centralwidget);
        cols_label->setObjectName("cols_label");
        cols_label->setGeometry(QRect(530, 70, 81, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gotham Pro")});
        font1.setPointSize(12);
        font1.setBold(false);
        cols_label->setFont(font1);
        rows_label = new QLabel(centralwidget);
        rows_label->setObjectName("rows_label");
        rows_label->setGeometry(QRect(557, 100, 51, 21));
        rows_label->setFont(font1);
        rows_spinbox = new QSpinBox(centralwidget);
        rows_spinbox->setObjectName("rows_spinbox");
        rows_spinbox->setGeometry(QRect(610, 100, 45, 24));
        rows_spinbox->setFont(font);
        rows_spinbox->setMinimum(1);
        rows_spinbox->setMaximum(50);
        rows_spinbox->setValue(10);
        open_button = new QPushButton(centralwidget);
        open_button->setObjectName("open_button");
        open_button->setGeometry(QRect(530, 10, 125, 24));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gotham Pro")});
        font2.setPointSize(12);
        open_button->setFont(font2);
        generate_button = new QPushButton(centralwidget);
        generate_button->setObjectName("generate_button");
        generate_button->setGeometry(QRect(530, 130, 125, 24));
        generate_button->setFont(font2);
        clear_button = new QPushButton(centralwidget);
        clear_button->setObjectName("clear_button");
        clear_button->setGeometry(QRect(530, 160, 125, 24));
        clear_button->setFont(font2);
        filename_label = new QLabel(centralwidget);
        filename_label->setObjectName("filename_label");
        filename_label->setGeometry(QRect(530, 40, 121, 21));
        savetofile_button = new QPushButton(centralwidget);
        savetofile_button->setObjectName("savetofile_button");
        savetofile_button->setGeometry(QRect(530, 190, 125, 24));
        QFont font3;
        font3.setPointSize(12);
        savetofile_button->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "view", nullptr));
        cols_label->setText(QCoreApplication::translate("MainWindow", "Columns", nullptr));
        rows_label->setText(QCoreApplication::translate("MainWindow", "Rows", nullptr));
        open_button->setText(QCoreApplication::translate("MainWindow", "Open file", nullptr));
        generate_button->setText(QCoreApplication::translate("MainWindow", "Create Maze", nullptr));
        clear_button->setText(QCoreApplication::translate("MainWindow", "Clear Area", nullptr));
        filename_label->setText(QString());
        savetofile_button->setText(QCoreApplication::translate("MainWindow", "Save to file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
