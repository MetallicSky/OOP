#ifndef SQUARECREATION_H
#define SQUARECREATION_H

#include <QMainWindow>

namespace Ui {
class SquareCreation;
}

class SquareCreation : public QMainWindow
{
    Q_OBJECT

public:
    explicit SquareCreation(QWidget *parent = nullptr);
    ~SquareCreation();

    int getCornerX();

    int getCornerY();

    int getSide();

    bool valid();

signals:
    void finish();

private slots:
    void on_pushButton_randomise_clicked();

    void on_spinBox_randomMin_valueChanged(int arg1);

    void on_spinBox_randomMax_valueChanged(int arg1);

    void on_pushButton_add_clicked();

private:
    Ui::SquareCreation *ui;
};

#endif // SQUARECREATION_H
