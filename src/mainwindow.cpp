#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gl_win* w = new gl_win;
    this->setCentralWidget(w);
    Controler* c = new Controler;
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, c);
    connect(c, &Controler::SetValue, [=](int v){
        w->gearBox->SetValue(v);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
