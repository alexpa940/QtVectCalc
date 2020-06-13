#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set the user interactions for the matrix plot
    ui->mainGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


    vec1 = new QCPItemLine(ui->mainGraph);
    vec1->setPen(QPen(QColor(66, 244, 66)));
    vec1->setHead(QCPLineEnding::esSpikeArrow);
    vec1->start->setCoords(0, 0);
    vec1->end->setCoords(0, 0);

    vec2 = new QCPItemLine(ui->mainGraph);
    vec2->setPen(QPen(QColor(244, 66, 66)));
    vec2->setHead(QCPLineEnding::esSpikeArrow);
    vec2->start->setCoords(0, 0);
    vec2->end->setCoords(0, 0);

    resvec = new QCPItemLine(ui->mainGraph);
    resvec->setPen(QPen(Qt::blue));
    resvec->setHead(QCPLineEnding::esSpikeArrow);
    resvec->start->setCoords(0, 0);
    resvec->end->setCoords(0, 0);

    ui->vX1Edit->setValidator(new QDoubleValidator);
    ui->vX1Edit_2->setValidator(new QDoubleValidator);
    ui->vY1Edit->setValidator(new QDoubleValidator);
    ui->vY1Edit_2->setValidator(new QDoubleValidator);
    ui->vX2Edit->setValidator(new QDoubleValidator);
    ui->vX2Edit_2->setValidator(new QDoubleValidator);
    ui->vY2Edit->setValidator(new QDoubleValidator);
    ui->vY2Edit_2->setValidator(new QDoubleValidator);

    ui->resX->setReadOnly(true);
    ui->resY->setReadOnly(true);

}

MainWindow::~MainWindow()
{
    delete vec1;
    delete vec2;
    delete resvec;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double resxs = 0;
    double resys = 0;

    double resxe = 0;
    double resye = 0;

    //Первый вектор
    QPointF vp1s(ui->vX1Edit->text().toDouble(), ui->vY1Edit->text().toDouble());
    QPointF vp1e(ui->vX1Edit_2->text().toDouble(), ui->vY1Edit_2->text().toDouble());


    //Второй вектор
    QPointF vp2s(ui->vX2Edit->text().toDouble(), ui->vY2Edit->text().toDouble());
    QPointF vp2e(ui->vX2Edit_2->text().toDouble(), ui->vY2Edit_2->text().toDouble());



    if(ui->comboBox->currentText()=="Сложить")
    {
        resxs = ui->vX1Edit->text().toDouble();
        resys = ui->vY1Edit->text().toDouble();

        resxe = ui->vX1Edit_2->text().toDouble() - ui->vX1Edit->text().toDouble()  + ui->vX2Edit_2->text().toDouble() - ui->vX2Edit->text().toDouble();
        resye = ui->vY1Edit_2->text().toDouble() - ui->vY1Edit->text().toDouble()  + ui->vY2Edit_2->text().toDouble() - ui->vY2Edit->text().toDouble();

        QPointF ress(resxs, resys);
        QPointF rese(resxs+resxe, resys+resye);

        vec2->start->setCoords(vp1e);
        vec2->end->setCoords(rese);

        resvec->start->setCoords(ress);
        resvec->end->setCoords(rese);

    }
    else if(ui->comboBox->currentText()=="Вычесть")
    {
        resxs = ui->vX1Edit->text().toDouble();
        resys = ui->vY1Edit->text().toDouble();

        resxe = (ui->vX1Edit_2->text().toDouble() - ui->vX1Edit->text().toDouble())  - (ui->vX2Edit_2->text().toDouble() - ui->vX2Edit->text().toDouble());
        resye = (ui->vY1Edit_2->text().toDouble() - ui->vY1Edit->text().toDouble()) -( ui->vY2Edit_2->text().toDouble() - ui->vY2Edit->text().toDouble());

        QPointF ress(resxs, resys);
        QPointF rese(resxs+resxe, resys+resye);

        vec2->start->setCoords(vp1e);
        vec2->end->setCoords(rese);

        resvec->start->setCoords(ress);
        resvec->end->setCoords(rese);
    }


    vec1->start->setCoords(vp1s);
    vec1->end->setCoords(vp1e);

    ui->resX->setText(QString::number(resxs) + "; " + QString::number(resxe));
    ui->resY->setText(QString::number(resys) + "; " + QString::number(resye));

    ui->mainGraph->replot();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->vX1Edit->clear();
    ui->vX1Edit_2->clear();
    ui->vY1Edit->clear();
    ui->vY1Edit_2->clear();
    ui->vX2Edit->clear();
    ui->vX2Edit_2->clear();
    ui->vY2Edit->clear();
    ui->vY2Edit_2->clear();
    on_pushButton_clicked();
}
