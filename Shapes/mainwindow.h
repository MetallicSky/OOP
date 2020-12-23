#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_spinBox_randomMin_valueChanged(int arg1);

    void on_spinBox_randomMax_valueChanged(int arg1);

    void on_pushButton_randomise_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_Circle_clicked();

    void on_pushButton_Square_clicked();

    void on_pushButton_Rectangle_clicked();

    void on_pushButton_Triangle_clicked();

    void on_pushButton_delete_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
