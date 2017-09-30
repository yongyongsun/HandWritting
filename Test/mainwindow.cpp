#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qDebug>
#include "PaintArea.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onBtnClicked()));

    area = new PaintArea();
    area->show();
    //ui->verticalLayout->addWidget(area);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnClicked()
{
    QString str = QCoreApplication::applicationDirPath() + "/NoName.jpg";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),
                                str,
                                tr("Images (*.png *.xpm *.jpg)"));
    area->saveImage(fileName,"png");
}
