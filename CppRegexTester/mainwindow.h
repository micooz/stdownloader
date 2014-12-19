#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

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
    void on_linePattern_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_linePattern_editingFinished();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> _result;
};

#endif // MAINWINDOW_H
