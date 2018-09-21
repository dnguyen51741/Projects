#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QPainter>

class mainwindow : public QWidget
{
private:
    QRect selectionRect;
public:
    mainwindow(QWidget *parent = 0);
    //void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
