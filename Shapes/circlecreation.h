#ifndef CIRCLECREATION_H
#define CIRCLECREATION_H

#include <QMainWindow>

namespace Ui {
class CircleCreation;
}

class CircleCreation : public QMainWindow
{
    Q_OBJECT

public:
    explicit CircleCreation(QWidget *parent = nullptr);
    ~CircleCreation();

    int getCenterX();

    int getCenterY();

    int getRingX();

    int getRingY();

    bool valid();

signals:
    void finish();

private slots:
    void on_spinBox_randomMin_valueChanged(int arg1);

    void on_spinBox_randomMax_valueChanged(int arg1);

    void on_pushButton_randomise_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::CircleCreation *ui;
};

#endif // CIRCLECREATION_H
