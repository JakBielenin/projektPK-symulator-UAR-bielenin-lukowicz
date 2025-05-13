#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsLineItem>
#include <QPen>
#include <vector>
#include <QPointF>
#include <QtCharts>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupChartZR();
    setupChartU();
    setupChartS();

    connect(&simulationTimer, &QTimer::timeout, this, &MainWindow::updateSimulation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSimulation()
{
    double wynik = symulacja.KrokSymulacji();
    double wartoscZadana = symulacja.GetWartoscZadana();
    double uchyb = symulacja.GetUchyb();
    double sterowanie = symulacja.GetSterowanie();
    double P = symulacja.getRegulator().GetP();
    double I = symulacja.getRegulator().GetI();
    double D = symulacja.getRegulator().GetD();

    addValueWZadanaIRegulowana(wartoscZadana, wynik);
    addValueWUchybu(uchyb);
    addValueWsterowania(sterowanie, P, I, D);

    czas += 0.1;
}

void MainWindow::setupChartZR(){
    S_Z = new QLineSeries();
    S_R = new QLineSeries();

    S_Z->setName("Wart Zadana");
    S_R->setName("Wart Regulowana");

    C_ZR = new QChart();

    C_ZR->addSeries(S_Z);
    C_ZR->addSeries(S_R);

    C_ZR->createDefaultAxes();
    C_ZR->legend()->setAlignment(Qt::AlignLeft);
    C_ZR->setMargins(QMargins(0, 0, 0, 0));

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX->setTickCount(10);
    axisX->setLabelFormat("%.1f");
    axisX->setMinorTickCount(4);
    axisX->setTitleText("Czas(s)");

    axisY->setTickCount(13);
    axisY->setLabelFormat("%.2f");
    axisY->setMinorTickCount(2);
    axisY->setTitleText("Wartość");

    C_ZR->setAxisX(axisX, S_Z);
    C_ZR->setAxisX(axisX, S_R);
    C_ZR->setAxisY(axisY, S_Z);
    C_ZR->setAxisY(axisY, S_R);

    chartViewZR = new QChartView(C_ZR);
    chartViewZR->setRenderHint(QPainter::Antialiasing);
    chartViewZR->setMaximumSize(ui->WartoscZadanaIRegulowana->width(), ui->WartoscZadanaIRegulowana->height());
    chartViewZR->setStyleSheet("background: transparent; border: none;");

    QLayout *oldLayoutZR = ui->WartoscZadanaIRegulowana->layout();
    if (oldLayoutZR) {
        delete oldLayoutZR;
    }

    QVBoxLayout *layoutZR = new QVBoxLayout(ui->WartoscZadanaIRegulowana);
    layoutZR->addWidget(chartViewZR);
    ui->WartoscZadanaIRegulowana->setLayout(layoutZR);
    C_ZR->layout()->setContentsMargins(0, 0, 0, 0);
}
void MainWindow::setupChartU(){
    S_U = new QLineSeries();

    S_U->setName("Wart Uchybu");

    C_U = new QChart();

    C_U->addSeries(S_U);

    C_U->createDefaultAxes();
    C_U->legend()->setAlignment(Qt::AlignLeft);
    C_U->setMargins(QMargins(0, 0, 0, 0));

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX->setTickCount(10);
    axisX->setLabelFormat("%.1f");
    axisX->setMinorTickCount(4);
    axisX->setTitleText("Czas(s)");

    axisY->setTickCount(5);
    axisY->setLabelFormat("%.1f");
    axisY->setMinorTickCount(2);
    axisY->setTitleText("Wartość");

    C_U->setAxisX(axisX, S_U);
    C_U->setAxisY(axisY, S_U);

    chartViewU = new QChartView(C_U);
    chartViewU->setRenderHint(QPainter::Antialiasing);
    chartViewU->setMaximumSize(ui->WartoscUchybu->width(), ui->WartoscUchybu->height());
    chartViewU->setStyleSheet("background: transparent; border: none;");



    QLayout *oldLayoutU = ui->WartoscUchybu->layout();
    if (oldLayoutU) {
        delete oldLayoutU;
    }

    QVBoxLayout *layoutU = new QVBoxLayout(ui->WartoscUchybu);
    layoutU->addWidget(chartViewU);
    ui->WartoscUchybu->setLayout(layoutU);
    C_U->layout()->setContentsMargins(0, 0, 0, 0);
}
void MainWindow::setupChartS(){

    S_S = new QLineSeries();
    S_P = new QLineSeries();
    S_I = new QLineSeries();
    S_D = new QLineSeries();

    S_S->setName("Sterowanie");
    S_P->setName("P");
    S_I->setName("I");
    S_D->setName("D");

    C_S = new QChart();

    C_S->addSeries(S_S);
    C_S->addSeries(S_P);
    C_S->addSeries(S_I);
    C_S->addSeries(S_D);

    C_S->createDefaultAxes();
    C_S->legend()->setAlignment(Qt::AlignLeft);
    C_S->setMargins(QMargins(0, 0, 0, 0));

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX->setTickCount(10);
    axisX->setLabelFormat("%.1f");
    axisX->setMinorTickCount(4);
    axisX->setTitleText("Czas(s)");

    axisY->setTickCount(5);
    axisY->setLabelFormat("%.1f");
    axisY->setMinorTickCount(1);
    axisY->setTitleText("Wartość");

    C_S->setAxisX(axisX, S_S);
    C_S->setAxisX(axisX, S_P);
    C_S->setAxisX(axisX, S_I);
    C_S->setAxisX(axisX, S_D);

    C_S->setAxisY(axisY, S_S);
    C_S->setAxisY(axisY, S_P);
    C_S->setAxisY(axisY, S_I);
    C_S->setAxisY(axisY, S_D);


    QPen pen1, pen2, pen3;
    pen1.setWidth(1);
    pen2.setWidth(1);
    pen3.setWidth(1);

    pen1.setColor(Qt::green);
    pen2.setColor(Qt::red);
    pen3.setColor(Qt::darkYellow);

    S_P->setPen(pen1);
    S_I->setPen(pen2);
    S_D->setPen(pen3);

    chartViewS = new QChartView(C_S);
    chartViewS->setRenderHint(QPainter::Antialiasing);
    chartViewS->setMaximumSize(ui->WartoscSterowania->width(), ui->WartoscSterowania->height());
    chartViewS->setStyleSheet("background: transparent; border: none;");

    QLayout *oldLayoutS = ui->WartoscSterowania->layout();
    if (oldLayoutS) {
        delete oldLayoutS;
    }

    QVBoxLayout *layoutS = new QVBoxLayout(ui->WartoscSterowania);
    layoutS->addWidget(chartViewS);
    ui->WartoscSterowania->setLayout(layoutS);
    C_S->layout()->setContentsMargins(0, 0, 0, 0);
}


void MainWindow::addValueWZadanaIRegulowana(double zadana, double regulowana){
    S_Z->append(czas, zadana);
    S_R->append(czas, regulowana);

    while (!S_Z->points().isEmpty() && S_Z->points().first().x() < czas - 20) {
        S_Z->remove(0);
    }

    while (!S_R->points().isEmpty() && S_R->points().first().x() < czas - 20) {
        S_R->remove(0);
    }

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const QPointF &point : S_Z->points()) {
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }
    for (const QPointF &point : S_R->points()) {
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }

    maxY += 0.5;
    minY -= 0.5;

    C_ZR->axes(Qt::Horizontal).first()->setRange(qMax(0.0, czas - 20), czas + 1);
    C_ZR->axes(Qt::Vertical).first()->setRange(minY, maxY);

}
void MainWindow::addValueWUchybu(double uchyb){
    S_U->append(czas, uchyb);

    while (!S_U->points().isEmpty() && S_U->points().first().x() < czas - 20) {
        S_U->remove(0);
    }

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const QPointF &point : S_U->points()) {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }

    maxY += 0.5;
    minY -= 0.5;

    C_U->axes(Qt::Horizontal).first()->setRange(qMax(0.0, czas - 20), czas + 1);
    C_U->axes(Qt::Vertical).first()->setRange(minY, maxY);

}
void MainWindow::addValueWsterowania(double sterowanie, double P, double I, double D){
    S_S->append(czas, sterowanie);
    S_P->append(czas, P);
    S_I->append(czas, I);
    S_D->append(czas, D);


    while (!S_S->points().isEmpty() && S_S->points().first().x() < czas - 20) {
        S_S->remove(0);
    }
    while (!S_P->points().isEmpty() && S_P->points().first().x() < czas - 20) {
        S_P->remove(0);
    }
    while (!S_I->points().isEmpty() && S_I->points().first().x() < czas - 20) {
        S_I->remove(0);
    }
    while (!S_D->points().isEmpty() && S_D->points().first().x() < czas - 20) {
        S_D->remove(0);
    }

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const QPointF &point : S_S->points()) {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }   
    for (const QPointF &point : S_P->points()) {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }
    for (const QPointF &point : S_I->points()) {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }
    for (const QPointF &point : S_D->points()) {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }

    maxY += 0.5;
    minY -= 0.5;

    C_S->axes(Qt::Horizontal).first()->setRange(qMax(0.0, czas - 20), czas + 1);
    C_S->axes(Qt::Vertical).first()->setRange(minY, maxY);
}

void MainWindow::on_dodajWspolczynnik_clicked()
{
    double wspA = ui->WartoscDodawanaA->value();
    double wspB = ui->WartoscDodawanaB->value();
    ui->WspolczynnikiA->addItem(QString::number(wspA, 'f', 2));
    ui->WspolczynnikiB->addItem(QString::number(wspB, 'f', 2));
}

void MainWindow::on_usunWspolczynnik_clicked()
{
    QList<QListWidgetItem*> itemsA = ui->WspolczynnikiA->selectedItems();
    for (QListWidgetItem *item : itemsA) {
        delete ui->WspolczynnikiA->takeItem(ui->WspolczynnikiA->row(item));
    }

    QList<QListWidgetItem*> itemsB = ui->WspolczynnikiB->selectedItems();
    for (QListWidgetItem *item : itemsB) {
        delete ui->WspolczynnikiB->takeItem(ui->WspolczynnikiB->row(item));
    }
}

void MainWindow::on_StartSymulacji_clicked()
{
    on_WprowadzenieZmian_clicked();
    simulationTimer.start();
}

void MainWindow::on_PauzaWznowienie_clicked()
{
    simulationTimer.stop();
}

void MainWindow::on_WprowadzenieZmian_clicked()
{
    simulationTimer.setInterval(ui->interwal->value());
    symulacja.SetRegulatorPID(ui->RegulacjaP->value(), ui->RegulacjaTi->value(), ui->RegulacjaTd->value());

    std::vector<double> wspA, wspB;
    for (int i=0; i<ui->WspolczynnikiA->count(); ++i){
        double wspA_ = ui->WspolczynnikiA->item(i)->text().toDouble();
        wspA.push_back(wspA_);
    }
    for (int i=0; i<ui->WspolczynnikiB->count(); ++i){
        double wspB_ = ui->WspolczynnikiB->item(i)->text().toDouble();
        wspB.push_back(wspB_);
    }

    symulacja.SetModelARX(wspA, wspB, ui->OpoznienieTransportowe->value());

    TypSygnalu sygnal;
    switch (ui->KompozycjaWartosciZadanej->currentIndex()) {
    case 0:
        sygnal = TypSygnalu::jednostkowy;
        break;
    case 1:
        sygnal = TypSygnalu::sinusoidalny;
        break;
    default:
        sygnal = TypSygnalu::prostokatny;
        break;
    }

    double amplituda = ui->spinbox_Amplituda->value();
    double dlugosc = ui->spinbox_Dlugosc->value();
    int wypelnienie = ui->spinBox_Wypelnienie->value();
    symulacja.SetSygnal(sygnal, amplituda, dlugosc, wypelnienie);

}

void MainWindow::on_resetPamieci_clicked()
{
    symulacja.getRegulator().ResetUl();
    symulacja.getRegulator().ResetUd();
}

void MainWindow::on_zaklocenie_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        symulacja.SetWartOdchStd(1);
    }
    else if (arg1 == Qt::Unchecked){
        symulacja.SetWartOdchStd(0);
    }
}

