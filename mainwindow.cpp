#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::displayMatrixResult(const Matrix &matrix, const QString& operation) {
    QDialog resultDialog(this);
    resultDialog.setWindowTitle(operation + " Result");
    //window constraints
    resultDialog.setMinimumSize(300, 200);

    int rows = matrix.getRows();
    int cols = matrix.getCols();

    QTableWidget *tableWidget = new QTableWidget(rows, cols, &resultDialog);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(matrix(i,j), 'f', 5));
            tableWidget->setItem(i, j, item);
        }
    }

    QVBoxLayout *layout = new QVBoxLayout(&resultDialog);
    layout->addWidget(tableWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, &resultDialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &resultDialog, &QDialog::accept);

    resultDialog.resize(400, 400);
    resultDialog.exec();
}
bool MainWindow::setmatrix(Matrix &matrix, const QString &matrixName) {
    bool ok;
    int rows = QInputDialog::getInt(this, matrixName + " Rows", "Enter the number of rows:", 3, 1, 100, 1, &ok);
    if (!ok) return false;

    int cols = QInputDialog::getInt(this, matrixName + " Columns", "Enter the number of columns:", 3, 1, 100, 1, &ok);
    if (!ok) return false;

    QDialog dialog(this);
    dialog.setWindowTitle(matrixName + " Input");
    dialog.setMinimumSize(300, 200);

    QTableWidget *tableWidget = new QTableWidget(rows, cols, &dialog);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem("0"));
        }
    }
    int cellWidth = 60;
    int cellHeight = 30;
    tableWidget->horizontalHeader()->setDefaultSectionSize(cellWidth);
    tableWidget->verticalHeader()->setDefaultSectionSize(cellHeight);


    int tableWidth = tableWidget->columnWidth(0) * cols + tableWidget->verticalHeader()->width() + 20;
    int tableHeight = tableWidget->rowHeight(0) * rows + tableWidget->horizontalHeader()->height() + 20;

    QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
    dialog.resize(qMin(screenSize.width() - 100, tableWidth + 50),
                  qMin(screenSize.height() - 100, tableHeight + 100));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(tableWidget);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // Construct the result matrix directly into the reference
        Matrix temp(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QTableWidgetItem *item = tableWidget->item(i, j);
                if (!item || item->text().isEmpty()) {
                    QMessageBox::warning(this, "Error", "Empty cell detected.");
                    return false;
                }

                double value = item->text().toDouble(&ok);
                if (!ok) {
                    QMessageBox::warning(this, "Error", "Invalid number at " + QString::number(i+1) + "," + QString::number(j+1));
                    return false;
                }
                temp(i, j) = value;
            }
        }
        matrix = temp; // Uses your Matrix assignment operator
        return true;
    }
    return false;
}

void MainWindow::on_btn_sum_clicked() {
    Matrix A(1,1), B(1,1);
    if (setmatrix(A, "Matrix A") && setmatrix(B, "Matrix B")) {
        // Logic: Check if dimensions match for addition
        if (A.getRows() == B.getRows() && A.getCols() == B.getCols()) {
            Matrix result = A + B;
            displayMatrixResult(result, "Matrix Addition");
            QMessageBox::information(this, "Success", "Addition Complete.");
        } else {
            QMessageBox::critical(this, "Math Error", "Matrices must be the same size!");
        }
    }
}

void MainWindow::on_btn_sub_clicked()
{
    Matrix A(1,1), B(1,1);
    if (setmatrix(A, "Matrix A") && setmatrix(B, "Matrix B")) {
        // Logic: Check if dimensions match for subtraction
        if (A.getRows() == B.getRows() && A.getCols() == B.getCols()) {
            Matrix result = A - B;
            displayMatrixResult(result, "Matrix Subtraction");
            QMessageBox::information(this, "Success", "Subtraction Complete.");
        } else {
            QMessageBox::critical(this, "Math Error", "Matrices must be the same size!");
        }
    }
}

void MainWindow::on_btn_mult_clicked()
{
    Matrix A(1,1), B(1,1);
    if (setmatrix(A, "Matrix A") && setmatrix(B, "Matrix B")) {
        // Logic: Check if dimensions match multiplication
        if (A.getCols() == B.getRows()) {
            Matrix result = A * B;
            displayMatrixResult(result, "Matrix Multiplication");
            QMessageBox::information(this, "Success", "Multiplication Complete.");
        } else {
            QMessageBox::critical(this, "Math Error", "Matrices sizes not correct");
        }
    }
}


void MainWindow::on_btn_pow_clicked()
{
    Matrix A(1,1);
    if (setmatrix(A, "Matrix A") ){
        Matrix result = A;
        bool ok;
        if(A.getRows() == A.getCols()){
            int k =QInputDialog::getInt(this," Factor", "Enter the power factor:", 3, 1, 100, 1, &ok);
            if (k >=1){
                for (int i =0; i < k-1; i++){
                    result *= A;
                }
                displayMatrixResult(result, "Resulting Matrix");
                    QMessageBox::information(this, "Status", "Success.");
            }
        }else{
            QMessageBox::critical(this, "Status", "Sizing error.");
        }
    }
}


void MainWindow::on_btn_det_clicked()
{
    Matrix A(1,1);
    if (setmatrix(A, "Matrix A")) {
        // Logic: Check if matrix is square
        if (A.getCols() == A.getRows()) {
            SquareMatrix result = A;
            double detValue = result.det();
            QMessageBox::information(this, "Determinant Result", "The determinant of Matrix A is: " + QString::number(detValue));
            QMessageBox::information(this, "Success", "Determinant found successfully.");
        } else {
            QMessageBox::critical(this, "Math Error", "Matrices sizes not correct");
        }
    }
}


void MainWindow::on_btn_inv_clicked()
{
    Matrix A(1,1);
    if (setmatrix(A, "Matrix A")) {
        // Logic: Check if matrix is square
        if (A.getCols() == A.getRows()) {
            SquareMatrix sA = A;
            SquareMatrix result = sA.inverse();
            displayMatrixResult(result, "Inverted Matrix");
            QMessageBox::information(this, "Success", "Inverse matrix found successfully.");
        } else {
            QMessageBox::critical(this, "Math Error", "Matrices sizes not correct");
        }
    }
}


void MainWindow::on_btn_rank_clicked()
{
    Matrix A(1,1);
    if (setmatrix(A, "Matrix A") ){
        double rank = A.rank(A);
        QMessageBox::information(this, "Success", "The rank of Matrix A is: "+QString::number(rank));
    }
}
void MainWindow::on_btn_systems_clicked(){
    //no code yet
}
