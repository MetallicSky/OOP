#include "squarecreation.h"
#include "ui_squarecreation.h"

SquareCreation::SquareCreation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SquareCreation)
{
    ui->setupUi(this);
}

SquareCreation::~SquareCreation()
{
    delete ui;
}

void SquareCreation::on_pushButton_randomise_clicked()
{
    int minR = ui->spinBox_randomMin->value();
    int maxR = ui->spinBox_randomMax->value();
    int cornerX;
    int cornerY;
    cornerX = rand() % (maxR - minR + 1) + minR;
    cornerY = rand() % (maxR - minR + 1) + minR;
    int side = 0;
    while (side == 0)
    {
        side = rand() % (maxR - minR + 1) + minR;
    }
    ui->spinBox_cornerX->setValue(cornerX);
    ui->spinBox_cornerY->setValue(cornerY);
    ui->spinBox_side->setValue(side);
}

void SquareCreation::on_spinBox_randomMin_valueChanged(int arg1)
{
    ui->spinBox_randomMax->setMinimum(ui->spinBox_randomMin->value() + 1);
}

void SquareCreation::on_spinBox_randomMax_valueChanged(int arg1)
{
    ui->spinBox_randomMin->setMaximum(ui->spinBox_randomMax->value() - 1);
}

void SquareCreation::on_pushButton_add_clicked()
{
    ui->pushButton_add->setChecked(true);
    emit finish();
    close();
}

int SquareCreation::getCornerX()
{
    return ui->spinBox_cornerX->value();
}

int SquareCreation::getCornerY()
{
    return ui->spinBox_cornerY->value();
}

int SquareCreation::getSide()
{
    return ui->spinBox_side->value();
}

bool SquareCreation::valid()
{
    return ui->pushButton_add->isChecked();
}
