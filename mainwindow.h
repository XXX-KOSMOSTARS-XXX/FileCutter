#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "for_logic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SelectFileA_clicked(bool checked);
    void on_CreationFileB_clicked(bool checked);

private:
    for_logic recall;
    Ui::MainWindow *ui;
    QString filePathA;
};

#endif // MAINWINDOW_H
