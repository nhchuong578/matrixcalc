#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QPushButton>
#include <QHeaderView>
#include <QGuiApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVector>
#include <QMainWindow>
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool setmatrix(Matrix &matrix, const QString &matrixName);
    void on_btn_sum_clicked();
    void displayMatrixResult(const Matrix &matrix, const QString &operation);
    void on_btn_sub_clicked();

    void on_btn_mult_clicked();

    void on_btn_pow_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
