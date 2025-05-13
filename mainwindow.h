#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets>
#include <QTimer>
#include <qdebug.h>
#include "symulacja.h"
#include "generatorsygnalu.h"
#include "regulatorpid.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_dodajWspolczynnik_clicked();

    void on_usunWspolczynnik_clicked();
    void addValueWZadanaIRegulowana(double zadana, double regulowana);
    void addValueWUchybu(double uchyb);
    void addValueWsterowania(double sterowanie, double P, double I, double D);

    void updateSimulation();
    void on_StartSymulacji_clicked();

    void on_PauzaWznowienie_clicked();

    void on_WprowadzenieZmian_clicked();

    void on_resetPamieci_clicked();

    void setupChartZR();
    void setupChartU();
    void setupChartS();

    void on_zaklocenie_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QLineSeries *S_Z;
    QLineSeries *S_R;

    QLineSeries *S_U;

    QLineSeries *S_S;
    QLineSeries *S_P;
    QLineSeries *S_I;
    QLineSeries *S_D;


    QChart *C_ZR;
    QChart *C_U;
    QChart *C_S;

    QChartView *chartViewZR;
    QChartView *chartViewU;
    QChartView *chartViewS;

    Symulacja symulacja;
    QTimer simulationTimer;
    double czas = 0;
};
#endif
