#include "mainwindow.h"
#include "findpath.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QTextEdit>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include <QSplitter>
#include <string>

using namespace std;
mainwindow::mainwindow(QWidget *parent)
    : QWidget(parent){

    string theSource = "";
    string theDestination = "";
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);
    this->resize(1280, 720);
    this->setWindowTitle("Test GPS");
    QTextEdit *top = new QTextEdit();
    top->setText("Please choose a starting point and destination point: ");
    top->setAlignment(Qt::AlignCenter);
    top->setReadOnly(true);
    top->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    top->setStyleSheet("font: 40px;");
    top->setMaximumHeight(60);

    QSplitter *splitter = new QSplitter(this);
    splitter->setMaximumHeight(30);

    QTextEdit *source = new QTextEdit();
    string sourceText = "Source: " + theSource;
    source->setText("Source: ");
    source->setAlignment(Qt::AlignLeft);
    //source->setReadOnly(true);
    source->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    source->setStyleSheet("font: 25px;");
    source->setMaximumHeight(35);



    QTextEdit *destination = new QTextEdit();
    string destinationText = "Destination: " + theDestination;
    destination->setText("Destination: ");
    destination->setAlignment(Qt::AlignLeft);
    //destination->setReadOnly(true);
    destination->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    destination->setStyleSheet("font: 25px;");
    destination->setMaximumHeight(35);

    splitter->addWidget(source);
    splitter->addWidget(destination);

    QPixmap image(":/map.JPG");
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(image);
     //imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vbox->addWidget(top);
    vbox->addWidget(splitter);
    vbox->addWidget(imageLabel);

    QString sourceInput = source->toPlainText();

    QString destinationInput = destination->toPlainText();

    if(QString::compare(sourceInput, "school", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "gym", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "restaurant", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "work", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "hotel", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "pharmacy", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "hospital", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "store", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "airport", Qt::CaseInsensitive)) {

        }

    }

    if(QString::compare(sourceInput, "airport", Qt::CaseInsensitive)) {

        if(QString::compare(destinationInput, "park", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "gym", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "restaurant", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "work", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hotel", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "pharmacy", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "hospital", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "store", Qt::CaseInsensitive)) {

        }

        if(QString::compare(destinationInput, "school", Qt::CaseInsensitive)) {

        }

    }

    QMouseEvent *e;
    if(e->buttons() == Qt::LeftButton) {
        //if(selectionRect.contains(e->pos())) {
       //std::cout << "Left Button was Click" << std::endl;

        //} else {
            //selectionRect.setTopLeft(e->pos());
            //selectionRect.setBottomRight(e->pos());
        //}
    }

}

/*
void mainwindow::paintEvent(QPaintEvent *e) {
    mainwindow::paintEvent(e);
    QPainter painter(this);
    painter.setPen(QPen(QBrush(QColor(0,0,0,180)),1,Qt::DashLine));
    painter.setBrush(QBrush(QColor(255,255,255,120)));

    painter.drawRect(selectionRect);

} */
