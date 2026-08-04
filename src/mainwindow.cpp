#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Config.h"

#include <QTimer>
#include <QDateTime>
#include <QLayout>

#include <QFormLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QMessageBox>

// Ciclo de vida de la app, constructor y destructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    setWindowTitle(Config::APP_NAME);
    setWindowIcon(QIcon(":/recursos/icono.jpeg"));
    setWindowFilePath(Config::APP_NAME);

    qApp->installEventFilter(this);
    ui->etFuncion->installEventFilter(this);
    ui->dsbInferior->installEventFilter(this);
    ui->dsbSuperior->installEventFilter(this);
    ui->dsbPaso->installEventFilter(this);

    initUi();

}

MainWindow::~MainWindow(){
    delete ui;
}

//
// Configuracion App
//
void MainWindow::initUi(){
    initBarraEstado();
    initReloj();
    initDsb();
    lblTexto->setText("Representación Gráficas de Funciones V 1.0");
    desactivaControles();
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
    QString estiloEtiquetas = "QLabel { "
                              "color: #F63D03; "
                              "font-weight: bold; "
                              "padding: 2px 5px; "
                              "}";

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

void MainWindow::initDsb(){
    ui->dsbInferior->setRange(-100, 100);
    ui->dsbSuperior->setRange(-100, 100);
    ui->dsbPaso->setRange(-1, 1);

    ui->dsbInferior->setDecimals(2);
    ui->dsbSuperior->setDecimals(2);
    ui->dsbPaso->setDecimals(2);

    ui->dsbInferior->setValue(0.00);
    ui->dsbSuperior->setValue(0.00);
    ui->dsbPaso->setValue(0.00);

}

void MainWindow::activaControles(){
    ui->etFuncion->setEnabled(true);
    ui->dsbInferior->setEnabled(true);
    ui->dsbSuperior->setEnabled(true);
    ui->dsbPaso->setEnabled(true);
    ui->btnGraf->setEnabled(true);
}

void MainWindow::desactivaControles(){
    ui->etFuncion->setEnabled(false);
    ui->dsbInferior->setEnabled(false);
    ui->dsbSuperior->setEnabled(false);
    ui->dsbPaso->setEnabled(false);
    ui->btnGraf->setEnabled(false);
}

void MainWindow::limpiaControles(){
    ui->etFuncion->setText("");
    ui->dsbInferior->setValue(0.0);
    ui->dsbSuperior->setValue(0.0);
    ui->dsbPaso->setValue(0.0);

}

//
// SLOTS
//
void MainWindow::on_actionSalir_triggered(){
    salir();
}

void MainWindow::on_actionNueva_triggered(){
    nuevaFuncion();
}


//
// Funciones Protegidas
//
bool MainWindow::eventFilter(QObject *obj, QEvent *ev){

    // 1. PROTECCIÓN PRINCIPAL CONTRA PUNTEROS NULOS (Satisface a Clang al 100%)
    if(!ui ||
        !ui->dsbInferior ||
        ! ui->dsbSuperior ||
        !ui->dsbPaso ||
        !ui->etFuncion
        ){
        return QMainWindow::eventFilter(obj, ev);
    }

    QWidget *w = qobject_cast<QWidget*>(obj);

    //
    // KeyPress
    //
    if(ev->type() == QEvent::KeyPress){
        QKeyEvent *teclaEv = static_cast<QKeyEvent*>(ev);

        //ventanaOrigen == MainWIndow Tecla == ESC
        if(w && w->window() == this){
            if(teclaEv->key() == Qt::Key_Escape){
                salir();
                return true;
            }
        }

        // obj == etFuncion Tecla == Return
        if(obj == ui->etFuncion){
            if(teclaEv->key() == Qt::Key_Return || teclaEv->key() == Qt::Key_Enter){
                procesaFuncion();
            }
        }

        // obj == dsbInferior Tecla == Return
        if(obj == ui->dsbInferior){
            if(teclaEv->key() == Qt::Key_Return || teclaEv->key() == Qt::Key_Enter){
                ui->dsbSuperior->setFocus();
            }
        }

        // obj == dsbSuperior Tecla == Return
        if(obj == ui->dsbSuperior){
            if(teclaEv->key() == Qt::Key_Return || teclaEv->key() == Qt::Key_Enter){
                ui->dsbPaso->setFocus();
            }
        }

        // obj == dsbPaso Tecla == Return
        if(obj == ui->dsbPaso){
            if(teclaEv->key() == Qt::Key_Return || teclaEv->key() == Qt::Key_Enter){
               ui->etFuncion->setFocus();
            }
        }
    }

    //
    //  Recibe el foco
    //
    if(ev->type() == QEvent::FocusIn){
        if(obj == ui->dsbInferior){
            QTimer::singleShot(0, ui->dsbInferior, &QDoubleSpinBox::selectAll);
        }
        if(obj == ui->dsbSuperior){
            QTimer::singleShot(0, ui->dsbSuperior, &QDoubleSpinBox::selectAll);
        }
        if(obj == ui->dsbPaso){
            QTimer::singleShot(0, ui->dsbPaso, &QDoubleSpinBox::selectAll);
        }
    }

    //
    // Pierde el Foco
    //
    if(ev->type() == QEvent::FocusOut){
        if(obj == ui->dsbInferior){
            QLineEdit *le = ui->dsbInferior->findChild<QLineEdit*>();
            QTimer::singleShot(0, le, &QLineEdit::deselect);
            }
        if(obj == ui->dsbSuperior){
            QLineEdit *le = ui->dsbSuperior->findChild<QLineEdit*>();
            QTimer::singleShot(0, le, &QLineEdit::deselect);
        }
        if(obj == ui->dsbPaso){
            QLineEdit *le = ui->dsbPaso->findChild<QLineEdit*>();
            QTimer::singleShot(0, le, &QLineEdit::deselect);
        }
    }

    return QMainWindow::eventFilter(obj, ev);
}

//
// Funciones privadas
//
void MainWindow::salir(){
    close();
}

void MainWindow::nuevaFuncion(){
    activaControles();
    ui->dsbInferior->setFocus();
}

void MainWindow::abrirFuncion(){

}

void MainWindow::guardarFuncion(){

}

void MainWindow::procesaFuncion(){

}

