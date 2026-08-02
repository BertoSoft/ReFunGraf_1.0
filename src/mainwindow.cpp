#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Config.h"

#include <QTimer>
#include <QDateTime>
#include <QLayout>

// Ciclo de vida de la app, constructor y destructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    setWindowTitle(Config::APP_NAME);
    setWindowIcon(QIcon(":/recursos/icono.jpeg"));
    setWindowFilePath(Config::APP_NAME);

    initUi();

}

MainWindow::~MainWindow(){
    delete ui;
}

// Configuracion App
void MainWindow::initUi(){
    initBarraEstado();
    initReloj();
    lblTexto->setText("Representación Gráficas de Funciones V 1.0");
}

void MainWindow::initBarraEstado(){

    // Permite que la barra de estado ocupe toda la ventana
    ui->barraEstado->setSizeGripEnabled(false);

    //instanciamos los controles globales
    lblTexto = new QLabel(ui->barraEstado);
    lblFecha = new QLabel(ui->barraEstado);
    lblReloj = new QLabel(ui->barraEstado);

    // Propiedades de QLabel Uniformes
    const QFrame::Shape     formaPanel      = QFrame::WinPanel;
    const QFrame::Shadow    sombraHundida   = QFrame::Sunken;
    QString estiloEtiquetas = "QLabel { color: #000000; font-weight: bold; padding: 2px 5px; }";

    lblReloj->setAlignment(Qt::AlignCenter);
    lblReloj->setFrameShape(formaPanel);
    lblReloj->setFrameShadow(sombraHundida);
    lblReloj->setStyleSheet(estiloEtiquetas);

    lblFecha->setAlignment(Qt::AlignCenter);
    lblFecha->setFrameShape(formaPanel);
    lblFecha->setFrameShadow(sombraHundida);
    lblFecha->setStyleSheet(estiloEtiquetas);

    lblTexto->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lblTexto->setFrameShape(formaPanel);
    lblTexto->setFrameShadow(sombraHundida);
    lblTexto->setStyleSheet(estiloEtiquetas);

    // Inserción en el Layout de la barra de estado con factores de estiramiento (stretch)
    ui->barraEstado->addPermanentWidget(lblFecha, 3);
    ui->barraEstado->addPermanentWidget(lblReloj, 1);
    ui->barraEstado->addWidget(lblTexto, 15);

}

void MainWindow::initReloj(){
    timerReloj = new QTimer(this);

    connect(timerReloj, &QTimer::timeout, this, &MainWindow::refrescaReloj);
    timerReloj->start(1000);
    refrescaReloj();
}

void MainWindow::refrescaReloj(){
    QDateTime tiempo = QDateTime::currentDateTime();

    lblFecha->setText(tiempo.toString("dddd, d 'de' MMMM 'de' yyyy"));
    lblReloj->setText(tiempo.toString("hh:mm:ss"));
}