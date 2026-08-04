#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tinyexpr.h"

#include <QTimer>
#include <QDateTime>
#include <QLayout>

#include <QFormLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>

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
    ui->dsbPaso->setDecimals(4);

    ui->dsbInferior->setSingleStep(10);
    ui->dsbSuperior->setSingleStep(10);
    ui->dsbPaso->setSingleStep(0.001);


    ui->dsbInferior->setValue(0.00);
    ui->dsbSuperior->setValue(0.01);
    ui->dsbPaso->setValue(0.00);

    // Hacemos que el paso sea como minimo 0.0001 y que limite supeior siempre sea mayor
    ui->dsbPaso->setMinimum(0.0001);
    connect(ui->dsbInferior, &QDoubleSpinBox::valueChanged, this, [this](double val){
        ui->dsbSuperior->setMinimum(val + 0.01);
    });

    //Ahora procesamos la funcion y la dibujamos

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

void MainWindow::on_btnGraf_clicked(){
    QVector<Config::datosGraf> datos = procesaFuncion();
    dibujaFuncion(datos);
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
                ui->btnGraf->click();
                return true;
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
            lblTexto->setText("Introduce el límite inferior de la función...");
        }
        if(obj == ui->dsbSuperior){
            QTimer::singleShot(0, ui->dsbSuperior, &QDoubleSpinBox::selectAll);
            lblTexto->setText("Introduce el límite superior de la función...");
        }
        if(obj == ui->dsbPaso){
            QTimer::singleShot(0, ui->dsbPaso, &QDoubleSpinBox::selectAll);
            lblTexto->setText("Introduce el intervalo de paso de la función...");
        }
        if(obj == ui->etFuncion){
            QTimer::singleShot(0, ui->etFuncion, &QLineEdit::selectAll);
            lblTexto->setText("Define la función matemática...");
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

QVector<Config::datosGraf> MainWindow::procesaFuncion(){
    QVector<Config::datosGraf> vectorDatosGraf;

    // Si etFuncion esta en blanco
    if(ui->etFuncion->text().trimmed().isEmpty()){
        QMessageBox::critical(
            this,
            Config::APP_NAME,
            "Debes especificar una funcion matemática..."
            );
        ui->etFuncion->setFocus();
        return vectorDatosGraf;
    }

    QString strFuncion = ui->etFuncion->text().trimmed();
    double xMin = ui->dsbInferior->value();
    double xMax = ui->dsbSuperior->value();
    double paso = ui->dsbPaso->value();

    //
    // Libreria externa tinyExpr
    //
    // Configurar la variable que el parser va a buscar en el string (en este caso 'x')
    double x_actual;
    te_variable vars[] = {{"x", &x_actual}};

    // Compilar la expresión matemática introducida por el usuario
    int error;
    te_expr* expr = te_compile(strFuncion.toStdString().c_str(), vars, 1, &error);

    if (!expr) {
        QMessageBox::critical(this, Config::APP_NAME, "Error de sintaxis en la función matemática.");
        return vectorDatosGraf;
    }

    double x = xMin;
    while (x < xMax + (paso / 2.0)) {
        x_actual = x;       // Actualiza el valor de la variable vinculada al parser
        double y = te_eval(expr); // Evalúa la ecuación automáticamente (ej: "sin(x) + 2")

        Config::datosGraf punto;
        punto.x = x;
        punto.y = y;
        vectorDatosGraf.append(punto);

        x += paso;
    }

    te_free(expr); // Liberar la memoria del parser

    // ... enviar vectorDatosGraf a tu lienzo de dibujo ...
    return vectorDatosGraf;
}

void MainWindow::dibujaFuncion(QVector<Config::datosGraf> datos){
    if(datos.isEmpty()) return;

    // 1. Obtener las dimensiones actuales del QLabel en píxeles de pantalla
    int ancho   = ui->lblGraf->width();
    int alto    = ui->lblGraf->height();

    // Control de seguridad por si el widget aún no está renderizado
    if (ancho <= 0 || alto <= 0) {
        ancho = 600;
        alto = 400;
    }

    // 2. Crear el lienzo en memoria (Pixmap) del tamaño exacto del QLabel
    QPixmap lienzo(ancho, alto);
    lienzo.fill(Qt::black); // Fondo negro para la línea de la función

    QPainter painter(&lienzo);
    painter.setRenderHint(QPainter::Antialiasing); // Activa suavizado de bordes

    // 3. Encontrar mínimos y máximos matemáticos para escalar el dibujo
    double minX = datos.first().x, maxX = datos.first().x;
    double minY = datos.first().y, maxY = datos.first().y;

    for (const auto &p : datos) {
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    double rangoX = (maxX - minX == 0) ? 1.0 : (maxX - minX);
    double rangoY = (maxY - minY == 0) ? 1.0 : (maxY - minY);

    // 4. Configurar las propiedades de tu lápiz de dibujo
    QPen lapiz(QColor("#F63D03"), 2); // Naranja corporativo de tu app
    painter.setPen(lapiz);

    // 5. Recorrer el vector y enlazar los puntos calculados
    bool esPrimerPunto = true;
    QPointF puntoAnterior;

    for (const auto &p : datos) {
        // Conversión matemática a las coordenadas del plano de píxeles del QLabel
        // En pantallas el (0,0) está arriba a la izquierda. Invertimos Y restando del 'alto' total
        double pixelX = ((p.x - minX) / rangoX) * ancho;
        double pixelY = alto - (((p.y - minY) / rangoY) * alto);

        QPointF puntoActual(pixelX, pixelY);

        if (esPrimerPunto) {
            esPrimerPunto = false;
        } else {
            // Une el punto anterior con el actual mediante un tramo de recta
            painter.drawLine(puntoAnterior, puntoActual);
        }
        puntoAnterior = puntoActual;
    }

    painter.end(); // Finalizar las operaciones sobre el lienzo de memoria

    // 6. Asignar el Pixmap pintado al QLabel de la interfaz de usuario
    ui->lblGraf->setPixmap(lienzo);

}


