#include "circlecreation.h"
#include "ui_circlecreation.h"
#include <QDialog>


CircleCreation::CircleCreation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CircleCreation)
{
    ui->setupUi(this);

}

CircleCreation::~CircleCreation()
{
    delete ui;
}

void CircleCreation::on_spinBox_randomMin_valueChanged(int arg1)
{
    ui->spinBox_randomMax->setMinimum(ui->spinBox_randomMin->value() + 1);
}

void CircleCreation::on_spinBox_randomMax_valueChanged(int arg1)
{
    ui->spinBox_randomMin->setMaximum(ui->spinBox_randomMax->value() - 1);
}

void CircleCreation::on_pushButton_randomise_clicked()
{

    int minR = ui->spinBox_randomMin->value();
    int maxR = ui->spinBox_randomMax->value();
    int centerX;
    int centerY;
    centerX = rand() % (maxR - minR + 1) + minR;
    centerY = rand() % (maxR - minR + 1) + minR;
    int ringX = centerX;
    int ringY = centerY;
    while (ringX == centerX && ringY == centerY)
    {
        ringX = rand() % (maxR - minR + 1) + minR;
        ringY = rand() % (maxR - minR + 1) + minR;
    }
    ui->spinBox_centerX->setValue(centerX);
    ui->spinBox_centerY->setValue(centerY);
    ui->spinBox_ringX->setValue(ringX);
    ui->spinBox_ringY->setValue(ringY);
}

void CircleCreation::on_pushButton_add_clicked()
{
    ui->pushButton_add->setChecked(true);
    emit finish();
    //close();
}

int CircleCreation::getCenterX()
{
    return ui->spinBox_centerX->value();
}

int CircleCreation::getCenterY()
{
    return ui->spinBox_centerY->value();
}

int CircleCreation::getRingX()
{
    return ui->spinBox_ringX->value();
}

int CircleCreation::getRingY()
{
    return ui->spinBox_ringY->value();
}

bool CircleCreation::valid()
{
    return ui->pushButton_add->isChecked();
}
