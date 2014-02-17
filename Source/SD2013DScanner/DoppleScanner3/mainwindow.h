#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    /// Scans directory for duplicates when 'Scan!' button clicked.
    void on_scanButton_clicked();
    /// Deletes files that have their checkboxes checked when 'Delete Chosen Files' button clicked.
    void on_deleteButton_clicked();
    /// Sets the state of all checkboxes to the state of the current masterCheck if its state's been changed.
    void on_masterCheck_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
