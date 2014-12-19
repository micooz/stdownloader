#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <boost/regex.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->linePattern->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_linePattern_textChanged(const QString &arg1)
{
    std::string src = ui->plainSrc->document()->toPlainText().toStdString();

    if(arg1.isEmpty()){
        return;
    }

    _result.clear();
    try{
        boost::smatch matches;
        boost::regex pattern(arg1.toStdString());

        std::string::const_iterator s = src.begin();
        std::string::const_iterator e = src.end();

        while ( boost::regex_search(s, e, matches, pattern) ) {

            for (size_t i = 0; i < matches.size(); ++i) {
                if (matches[i].matched){
                    _result.push_back(matches.str(i));
                    _result.push_back("\n");
                }
            }

            s = matches[0].second;
        }
        if(_result.empty()){
            _result.push_back("Nothing found!");
        }
    }catch(const boost::exception &err){
        _result.push_back("Pattern error!");
    }

    std::string rst;
    for(std::vector<std::string>::iterator line = _result.begin() ; line != _result.end(); line++){
        rst.append(*line);
    }

    ui->plainResult->setDocument(new QTextDocument(QString(rst.c_str())));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()){
        if(_result.size() >= 2){

            std::vector<std::string> copy_rst( _result );

            copy_rst.erase(_result.begin());
            copy_rst.erase(_result.begin());

            std::string rst;
            for(std::vector<std::string>::iterator line = copy_rst.begin() ; line != copy_rst.end(); line++){
                rst.append(*line);
            }

            ui->plainResult->setDocument(new QTextDocument(QString(rst.c_str())));
        }
    }else{
        std::string rst;
        for(std::vector<std::string>::iterator line = _result.begin() ; line != _result.end(); line++){
            rst.append(*line);
        }

        ui->plainResult->setDocument(new QTextDocument(QString(rst.c_str())));
    }
}

void MainWindow::on_linePattern_editingFinished()
{
    QString pattern = ui->linePattern->text();
    pattern.replace("\\","\\\\");
    pattern.replace("\"","\\\"");

    ui->lineCstyle->setText(pattern);
}
