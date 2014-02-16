#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TreeScanner.h"
#include "UserInterface.h"
#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scanButton_clicked()
{
    TreeScanner scanner;
    UserInterface ui1;
    map < string, vector <string> > classes;
    QString directoryInput = ui->pathInput->text();
    scanner.GroupIntoClasses (directoryInput.toLocal8Bit().constData(),classes);
    QString output;
    ui1.qtOutput(classes,&output,ui->tableWidget);
  //  ui->textEdit->setPlainText(output);


}

void MainWindow::on_pushButton_clicked()
{   int rCount = ui->tableWidget->rowCount();
    UserInterface ui1;
    for (int i =1;i<rCount-1;i++)
    {
        QCheckBox* cBox = qobject_cast<QCheckBox*> (ui->tableWidget->cellWidget(i,1));
        if(cBox->isChecked()&& !(ui->tableWidget->item(i,1)->text()->isEmpty()))
            ui1.deleteFile(cBox->text().toStdString());
    }
    on_scanButton_clicked();
}
