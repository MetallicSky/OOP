#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDialog>
#include "Shapes.h"



vector<Shape*> shapes;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_coords->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Circle_clicked()
{
    ui->pushButton_Rectangle->setChecked(false);
    ui->pushButton_Square->setChecked(false);
    ui->pushButton_Triangle->setChecked(false);

    ui->pushButton_Circle->setChecked(true);

    ui->groupBox_coords->show();

    ui->label1->show();
    ui->label1->setText("Центр окружности");
    ui->label1_Brackets->show();
    ui->spinBox_1X->show();
    ui->spinBox_1X->setValue(0);
    ui->spinBox_1Y->show();
    ui->spinBox_1Y->setValue(0);

    ui->label2->show();
    ui->label2->setText("Координаты точки на окружности");
    ui->label2_Brackets->show();
    ui->spinBox_2X->show();
    ui->spinBox_2X->setValue(0);
    ui->spinBox_2Y->show();
    ui->spinBox_2Y->setValue(0);


    ui->spinBox_randomMin->show();
    ui->spinBox_randomMin->setValue(0);
    ui->label_randomMin->show();
    ui->spinBox_randomMax->show();
    ui->spinBox_randomMax->setValue(10);
    ui->label_randomMax->show();
    ui->pushButton_randomise->show();

    ui->pushButton_add->show();

    ui->label3_Brackets->hide();
    ui->spinBox_3X->hide();
    ui->spinBox_3X->setValue(0);
    ui->spinBox_3Y->hide();
    ui->spinBox_3Y->setValue(0);
    ui->label3->hide();
    ui->label3->setText("");
}

void MainWindow::on_pushButton_Square_clicked()
{
    ui->pushButton_Rectangle->setChecked(false);
    ui->pushButton_Circle->setChecked(false);
    ui->pushButton_Triangle->setChecked(false);

    ui->pushButton_Square->setChecked(true);

    ui->groupBox_coords->show();

    ui->label1->show();
    ui->label1->setText("Левый нижний угол");
    ui->label1_Brackets->show();
    ui->spinBox_1X->show();
    ui->spinBox_1X->setValue(0);
    ui->spinBox_1Y->show();
    ui->spinBox_1Y->setValue(0);

    ui->label2->show();
    ui->label2->setText("Сторона квадрата");
    ui->label2_Brackets->hide();
    ui->spinBox_2X->show();
    ui->spinBox_2X->setValue(0);
    ui->spinBox_2Y->hide();
    ui->spinBox_2Y->setValue(0);


    ui->spinBox_randomMin->show();
    ui->spinBox_randomMin->setValue(0);
    ui->label_randomMin->show();
    ui->spinBox_randomMax->show();
    ui->spinBox_randomMax->setValue(10);
    ui->label_randomMax->show();
    ui->pushButton_randomise->show();

    ui->pushButton_add->show();

    ui->label3_Brackets->hide();
    ui->spinBox_3X->hide();
    ui->spinBox_3X->setValue(0);
    ui->spinBox_3Y->hide();
    ui->spinBox_3Y->setValue(0);
    ui->label3->hide();
    ui->label3->setText("");
}

void MainWindow::on_spinBox_randomMin_valueChanged(int arg1)
{
    ui->spinBox_randomMax->setMinimum(ui->spinBox_randomMin->value() + 1);
}

void MainWindow::on_spinBox_randomMax_valueChanged(int arg1)
{
    ui->spinBox_randomMin->setMaximum(ui->spinBox_randomMax->value() - 1);
}

void MainWindow::on_pushButton_randomise_clicked()
{

    int minR = ui->spinBox_randomMin->value();
    int maxR = ui->spinBox_randomMax->value();
    int X1;
    int Y1;
    X1 = rand() % (maxR - minR + 1) + minR;
    Y1 = rand() % (maxR - minR + 1) + minR;

    int X2 = X1;
    int Y2 = Y1;

    int X3 = X1;
    int Y3 = Y1;

    while (X2 == X1 && Y2 == Y1)
    {
        X2 = rand() % (maxR - minR + 1) + minR;
        Y2 = rand() % (maxR - minR + 1) + minR;
    }

    while ((X3 == X1 && Y3 == Y1) || (X3 == X2 && Y3 == Y2))
    {
        X3 = rand() % (maxR - minR + 1) + minR;
        Y3 = rand() % (maxR - minR + 1) + minR;
    }

    ui->spinBox_1X->setValue(X1);
    ui->spinBox_1Y->setValue(Y1);

    ui->spinBox_2X->setValue(X2);
    ui->spinBox_2Y->setValue(Y2);

    ui->spinBox_3X->setValue(X3);
    ui->spinBox_3Y->setValue(Y3);
}

void MainWindow::on_pushButton_add_clicked()
{
    if (ui->pushButton_Circle->isChecked())
    {
        customCOORD center;
        center.X = ui->spinBox_1X->value();
        center.Y = ui->spinBox_1Y->value();

        customCOORD radius;
        radius.X = ui->spinBox_2X->value();
        radius.Y = ui->spinBox_2Y->value();
        shapes.push_back(new Circle(center, radius));

        string desc = "Circle ";
        desc += shapes[shapes.size() - 1]->toString();
        QString qdesc = QString::fromStdString(desc);
        ui->listWidget->addItem(qdesc);
    }
    else if (ui->pushButton_Square->isChecked())
    {
        customCOORD bottomLeftCorner;
        bottomLeftCorner.X = ui->spinBox_1X->value();
        bottomLeftCorner.Y = ui->spinBox_1Y->value();

        customCOORD topRightCorner;
        topRightCorner.X = bottomLeftCorner.X + ui->spinBox_2X->value();
        topRightCorner.Y = bottomLeftCorner.Y + ui->spinBox_2X->value();
        shapes.push_back(new Square(bottomLeftCorner, topRightCorner));

        string desc = "Square ";
        desc += shapes[shapes.size() - 1]->toString();
        QString qdesc = QString::fromStdString(desc);
        ui->listWidget->addItem(qdesc);
    }
    else if (ui->pushButton_Rectangle->isChecked())
    {
        customCOORD corner1;
        corner1.X = ui->spinBox_1X->value();
        corner1.Y = ui->spinBox_1Y->value();

        customCOORD corner2;
        corner2.X = ui->spinBox_2X->value();
        corner2.Y = ui->spinBox_2Y->value();
        shapes.push_back(new Rect(corner1, corner2));

        string desc = "Rectangle ";
        desc += shapes[shapes.size() - 1]->toString();
        QString qdesc = QString::fromStdString(desc);
        ui->listWidget->addItem(qdesc);
    }
    else
    {
        customCOORD corner1;
        corner1.X = ui->spinBox_1X->value();
        corner1.Y = ui->spinBox_1Y->value();

        customCOORD corner2;
        corner2.X = ui->spinBox_2X->value();
        corner2.Y = ui->spinBox_2Y->value();

        customCOORD corner3;
        corner3.X = ui->spinBox_3X->value();
        corner3.Y = ui->spinBox_3Y->value();
        shapes.push_back(new Triangle(corner1, corner2, corner3));

        string desc = "Triangle ";
        desc += shapes[shapes.size() - 1]->toString();
        QString qdesc = QString::fromStdString(desc);
        ui->listWidget->addItem(qdesc);
    }

    repaint();
}

void MainWindow::on_pushButton_Rectangle_clicked()
{
    ui->pushButton_Square->setChecked(false);
    ui->pushButton_Circle->setChecked(false);
    ui->pushButton_Triangle->setChecked(false);

    ui->pushButton_Rectangle->setChecked(true);

    ui->groupBox_coords->show();

    ui->label1->show();
    ui->label1->setText("Один из углов");
    ui->label1_Brackets->show();
    ui->spinBox_1X->show();
    ui->spinBox_1X->setValue(0);
    ui->spinBox_1Y->show();
    ui->spinBox_1Y->setValue(0);

    ui->label2->show();
    ui->label2->setText("Противоположный угол");
    ui->label2_Brackets->show();
    ui->spinBox_2X->show();
    ui->spinBox_2X->setValue(0);
    ui->spinBox_2Y->show();
    ui->spinBox_2Y->setValue(0);


    ui->spinBox_randomMin->show();
    ui->spinBox_randomMin->setValue(0);
    ui->label_randomMin->show();
    ui->spinBox_randomMax->show();
    ui->spinBox_randomMax->setValue(10);
    ui->label_randomMax->show();
    ui->pushButton_randomise->show();

    ui->pushButton_add->show();

    ui->label3_Brackets->hide();
    ui->spinBox_3X->hide();
    ui->spinBox_3X->setValue(0);
    ui->spinBox_3Y->hide();
    ui->spinBox_3Y->setValue(0);
    ui->label3->hide();
    ui->label3->setText("");
}

void MainWindow::on_pushButton_Triangle_clicked()
{
    ui->pushButton_Square->setChecked(false);
    ui->pushButton_Circle->setChecked(false);
    ui->pushButton_Rectangle->setChecked(false);

    ui->pushButton_Triangle->setChecked(true);

    ui->groupBox_coords->show();

    ui->label1->show();
    ui->label1->setText("Угол 1");
    ui->label1_Brackets->show();
    ui->spinBox_1X->show();
    ui->spinBox_1X->setValue(0);
    ui->spinBox_1Y->show();
    ui->spinBox_1Y->setValue(0);

    ui->label2->show();
    ui->label2->setText("Угол 2");
    ui->label2_Brackets->show();
    ui->spinBox_2X->show();
    ui->spinBox_2X->setValue(0);
    ui->spinBox_2Y->show();
    ui->spinBox_2Y->setValue(0);


    ui->spinBox_randomMin->show();
    ui->spinBox_randomMin->setValue(0);
    ui->label_randomMin->show();
    ui->spinBox_randomMax->show();
    ui->spinBox_randomMax->setValue(10);
    ui->label_randomMax->show();
    ui->pushButton_randomise->show();

    ui->pushButton_add->show();

    ui->label3_Brackets->show();
    ui->spinBox_3X->show();
    ui->spinBox_3X->setValue(0);
    ui->spinBox_3Y->show();
    ui->spinBox_3Y->setValue(0);
    ui->label3->show();
    ui->label3->setText("Угол 3");
}

void MainWindow::on_pushButton_delete_clicked()
{
    shapes.erase(shapes.begin() + ui->listWidget->currentRow());
    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    on_listWidget_currentRowChanged(ui->listWidget->currentRow());
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    switch (currentRow)
    {
    case -1:
        ui->pushButton_up->setEnabled(false);
        ui->pushButton_down->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
        break;
    case 0:
        ui->pushButton_up->setEnabled(false);
        ui->pushButton_delete->setEnabled(true);
        if (ui->listWidget->count() == 1)
            ui->pushButton_down->setEnabled(false);
        else
            ui->pushButton_down->setEnabled(true);
        break;
    default:
        ui->pushButton_up->setEnabled(true);
        ui->pushButton_delete->setEnabled(true);
        if (currentRow < ui->listWidget->count() - 1)
            ui->pushButton_down->setEnabled(true);
        else
            ui->pushButton_down->setEnabled(false);
        break;
    }
}

void MainWindow::on_pushButton_up_clicked()
{
    int currentRow = ui->listWidget->currentRow();
    swap(shapes[currentRow], shapes[currentRow - 1]);
    QListWidgetItem* currentItem = ui->listWidget->takeItem(currentRow);
    ui->listWidget->insertItem(currentRow - 1, currentItem);

    ui->listWidget->setCurrentRow(currentRow - 1);
    on_listWidget_currentRowChanged(ui->listWidget->currentRow());
}

void MainWindow::on_pushButton_down_clicked()
{
    int currentRow = ui->listWidget->currentRow();
    swap(shapes[currentRow], shapes[currentRow + 1]);
    QListWidgetItem* currentItem = ui->listWidget->takeItem(currentRow);
    ui->listWidget->insertItem(currentRow + 1, currentItem);

    ui->listWidget->setCurrentRow(currentRow + 1);
    on_listWidget_currentRowChanged(ui->listWidget->currentRow());
}

