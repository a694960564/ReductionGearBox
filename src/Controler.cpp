#include "Controler.h"
#include "ui_Controler.h"
#include <QSlider>

Controler::Controler(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Controler)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(-100,100);
    ui->horizontalSlider->setValue(0);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [=](int i){
        SetValue(i);
    });
}

Controler::~Controler()
{
    delete ui;
}
