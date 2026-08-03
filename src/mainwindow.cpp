#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Config.h"

#include <QTimer>
#include <QDateTime>
#include <QLayout>

#include <QFormLayout>
#include <QSplitter>
#include <QLineEdit>

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



    // --- DISEÑO DE LA INTERFAZ (20% Izquierda / 80% Derecha) ---

    // 1. Crear el divisor principal (Splitter) en horizontal
    QSplitter *splitterPrincipal = new QSplitter(Qt::Horizontal, this);

    // 2. PANEL IZQUIERDO: Controles de usuario (20%)
    QWidget *contenedorControles = new QWidget(splitterPrincipal);
    QVBoxLayout *layoutControles = new QVBoxLayout(contenedorControles);
    QFormLayout *formulario      = new QFormLayout();

    // Instanciar los controles de entrada de datos
    txtFuncion = new QLineEdit(contenedorControles);
    txtFuncion->setPlaceholderText("Ej: x*x - 4");

    spinXMin = new QDoubleSpinBox(contenedorControles);
    spinXMin->setRange(-1000.0, 1000.0);
    spinXMin->setValue(-10.0);

    spinXMax = new QDoubleSpinBox(contenedorControles);
    spinXMax->setRange(-1000.0, 1000.0);
    spinXMax->setValue(10.0);

    spinPaso = new QDoubleSpinBox(contenedorControles);
    spinPaso->setRange(0.001, 10.0);
    spinPaso->setSingleStep(0.1);
    spinPaso->setValue(0.1);

    btnGraficar = new QPushButton("Representar", contenedorControles);

    // Añadir los controles al formulario
    formulario->addRow("Función f(x):", txtFuncion);
    formulario->addRow("X Mínima:", spinXMin);
    formulario->addRow("X Máxima:", spinXMax);
    formulario->addRow("Paso (Δx):", spinPaso);

    // Organizar el panel izquierdo
    layoutControles->addLayout(formulario);
    layoutControles->addWidget(btnGraficar);
    layoutControles->addStretch(); // Empuja los controles hacia arriba para que se vea ordenado

    // 3. PANEL DERECHO: Cuadro de la Gráfica (80%)
    // Nota: Usamos un QWidget temporal de fondo gris. Aquí irá tu librería gráfica.
    widgetGrafica = new QWidget(splitterPrincipal);
    widgetGrafica->setStyleSheet("background-color: #FAFAFA; border: 1px solid #CCCCCC;");

    // 4. Añadir ambos paneles al splitter
    splitterPrincipal->addWidget(contenedorControles);
    splitterPrincipal->addWidget(widgetGrafica);

    // 5. Configurar los tamaños proporcionales exactos (20% y 80%)
    // Le asignamos un peso relativo a cada elemento. 20 y 80 aseguran la proporción perfecta.
    QList<int> tamanos;
    tamanos << 80 << 20;
    splitterPrincipal->setSizes(tamanos);

    // Evita que el panel de control colapse por completo a 0 píxeles si el usuario arrastra el divisor
    splitterPrincipal->setCollapsible(0, false);
    splitterPrincipal->setCollapsible(1, false);

    // 6. Establecer el splitter como el componente central de la ventana principal
    setCentralWidget(splitterPrincipal);

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
                              "color: #000000; "
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

//
// SLOTS
//
void MainWindow::on_actionSalir_triggered(){
    salir();
}

//
// Funciones
//
void MainWindow::salir(){
    close();
}

void MainWindow::nuevaFuncion(){

}

void MainWindow::abrirFuncion(){

}

void MainWindow::guardarFuncion(){

}