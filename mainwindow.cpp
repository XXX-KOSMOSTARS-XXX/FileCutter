#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QTextStream>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->SelectFileA, SIGNAL(clicked(bool)), this, SLOT(on_SelectFileA_clicked(bool)));
    connect(ui->SelectFileA, SIGNAL(clicked(bool)), this, SLOT(on_CreationFileB_clicked(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SelectFileA_clicked(bool checked)
{
    Q_UNUSED(checked);
    filePathA = QFileDialog::getOpenFileName(0, QStringLiteral("Выберите файл А"), "");
}

void MainWindow::on_CreationFileB_clicked(bool checked)
{
    Q_UNUSED(checked);
    try{
        recall.openFileA(filePathA);
        recall.creationFileB();
    }
    catch(QString &exception)
    {
        QMessageBox::warning(0, QStringLiteral("Ошибка"), exception);
    }
}
