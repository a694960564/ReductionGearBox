#ifndef CONTROLER_H
#define CONTROLER_H

#include <QDockWidget>

namespace Ui {
class Controler;
}

class Controler : public QDockWidget
{
    Q_OBJECT

public:
    explicit Controler(QWidget *parent = nullptr);
    ~Controler();

private:
    Ui::Controler *ui;
signals:
    void SetValue(int);
};

#endif // CONTROLER_H
