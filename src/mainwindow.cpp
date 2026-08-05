#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tinyexpr.h"

#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>

// Ciclo de vida de la app, constructor y destructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    setWindowTitle(Config::APP_NAME);
    setWindowIcon(QIcon(":/recursos/icono.jpeg"));

    // 2. Inicializar componentes de la UI (Crea lblTexto, lblFecha, etc.)
    initUi();

    // 3. Instalar filtros de eventos de forma segura (QUITANDO qApp para evitar duplicados)
    this->installEventFilter(this);
    ui->etFuncion->installEventFilter(this);
    ui->dsbInferior->installEventFilter(this);
    ui->dsbSuperior->installEventFilter(this);
    ui->dsbPaso->installEventFilter(this);

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
    QPixmap miPixMap = dibujaEjes(datos);
    dibujaFuncion(datos, miPixMap);
    ui->lblGraf->setFocus();
}



//
// Funciones Protegidas
//
bool MainWindow::eventFilter(QObject *obj, QEvent *ev){

    // 1. PROTECCIÓN PRINCIPAL CONTRA PUNTEROS NULOS (Clang al 100%)
    if (!ui || !ui->dsbInferior || !ui->dsbSuperior || !ui->dsbPaso || !ui->etFuncion || !lblTexto) {
        return QMainWindow::eventFilter(obj, ev);
    }

    // ==========================================
    // SECCIÓN: KeyPress (Pulsaciones de Teclas)
    // ==========================================
    if (ev->type() == QEvent::KeyPress) {
        QKeyEvent *teclaEv = static_cast<QKeyEvent*>(ev);
        int key = teclaEv->key();
        bool isEnter = (key == Qt::Key_Return || key == Qt::Key_Enter);

        // Tecla ESC: Salir
        if (key == Qt::Key_Escape) {
            QWidget *w = qobject_cast<QWidget*>(obj);
            if (w && w->window() == this) {
                salir();
                return true;
            }
        }

        // Navegación con Enter
        if (isEnter) {
            if (obj == ui->etFuncion) {
                ui->btnGraf->click();
                return true;
            }
            if (obj == ui->dsbInferior) {
                ui->dsbSuperior->setFocus();
                return true; // CORREGIDO: Evita propagación errática
            }
            if (obj == ui->dsbSuperior) {
                ui->dsbPaso->setFocus();
                return true; // CORREGIDO: Evita propagación errática
            }
            if (obj == ui->dsbPaso) {
                ui->etFuncion->setFocus();
                return true; // CORREGIDO: Evita propagación errática
            }
        }
    }

    // ==========================================
    // SECCIÓN: FocusIn (Recibe el Foco)
    // ==========================================
    if (ev->type() == QEvent::FocusIn) {
        if (obj == ui->dsbInferior) {
            QTimer::singleShot(0, ui->dsbInferior, [this]() { ui->dsbInferior->selectAll(); });
            lblTexto->setText("Introduce el límite inferior de la función...");
        }
        else if (obj == ui->dsbSuperior) {
            QTimer::singleShot(0, ui->dsbSuperior, [this]() { ui->dsbSuperior->selectAll(); });
            lblTexto->setText("Introduce el límite superior de la función...");
        }
        else if (obj == ui->dsbPaso) {
            QTimer::singleShot(0, ui->dsbPaso, [this]() { ui->dsbPaso->selectAll(); });
            lblTexto->setText("Introduce el intervalo de paso de la función...");
        }
        else if (obj == ui->etFuncion) {
            QTimer::singleShot(0, ui->etFuncion, [this]() { ui->etFuncion->selectAll(); });
            lblTexto->setText("Define la función matemática...");
        }
    }

    // ==========================================
    // SECCIÓN: FocusOut (Pierde el Foco)
    // ==========================================
    if (ev->type() == QEvent::FocusOut) {
        QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(obj);
        if (spinBox) {
            QLineEdit *le = spinBox->findChild<QLineEdit*>();
            if (le) { // CORREGIDO: Protección crítica contra puntero nulo (Anti-Crash)
                QTimer::singleShot(0, le, [le]() { le->deselect(); });
            }
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

void MainWindow::dibujaFuncion(QVector<Config::datosGraf> datos, QPixmap lienzo){
    if(datos.isEmpty()) return;

    // 1. Obtener las dimensiones actuales del QLabel en píxeles de pantalla
    int ancho   = ui->lblGraf->width();
    int alto    = ui->lblGraf->height();

    // Control de seguridad por si el widget aún no está renderizado
    if (ancho <= 0 || alto <= 0) {
        ancho = 600;
        alto = 400;
    }

    //Borramos la lblGraf
    ui->lblGraf->clear();

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
    QPen lapiz(QColor("#F63D03"), 1); // Naranja corporativo de tu app
    painter.setPen(lapiz);

    // 5. Recorrer el vector y enlazar los puntos calculados
    bool esPrimerPunto = true;
    QPointF puntoAnterior;

    //recorremos elvector datos desde el primero el ultimo
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

QPixmap MainWindow::dibujaEjes(QVector<Config::datosGraf> datos){
    QPixmap miPixMap;

    if (!ui->lblGraf) return miPixMap;

    // 1. Obtener las dimensiones actuales del contenedor del gráfico
    int ancho = ui->lblGraf->width();
    int alto = ui->lblGraf->height();

    // 2. Crear el lienzo (Pixmap) y rellenar el fondo de blanco
    QPixmap pixmap(ancho, alto);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing); // Bordes suaves
    // 3. Definir los límites del mundo matemático (Rango de la vista)
    // Usamos los valores introducidos por el usuario
    double minX = ui->dsbInferior->value();
    double maxX = ui->dsbSuperior->value();

    // Para el eje Y, puedes calcular dinámicamente los min/max de los 'datos'
    // o fijar un rango por defecto (ej. de -10 a 10) para esta vista:
    double minY = -10.0;
    double maxY = 10.0;

    // Lamdas de conversión: Transforma coordenadas matemáticas (x,y) a píxeles de pantalla (px, py)
    auto mapearX = [=](double x) {
        return static_cast<int>((x - minX) / (maxX - minX) * ancho);
    };
    auto mapearY = [=](double y) {
        return static_cast<int>((maxY - y) / (maxY - minY) * alto); // Invertido porque Y crece hacia abajo en pantalla
    };

    // 4. DIBUJAR LA REJILLA DE FONDO (Opcional, ayuda a la escala)
    QPen penRejilla(QColor(230, 230, 230), 1, Qt::DotLine);
    painter.setPen(penRejilla);

    // Líneas verticales de la rejilla
    double pasoEscalaX = (maxX - minX) / 10.0; // 10 divisiones
    for (double x = minX; x <= maxX; x += pasoEscalaX) {
        int px = mapearX(x);
        painter.drawLine(px, 0, px, alto);
    }
    // Líneas horizontales de la rejilla
    double pasoEscalaY = (maxY - minY) / 10.0;
    for (double y = minY; y <= maxY; y += pasoEscalaY) {
        int py = mapearY(y);
        painter.drawLine(0, py, ancho, py);
    }

    // 5. DIBUJAR LOS EJES CARTESIANOS (Negros y más gruesos)
    QPen penEjes(Qt::black, 2, Qt::SolidLine);
    painter.setPen(penEjes);

    int origenX = mapearX(0.0);
    int origenY = mapearY(0.0);

    // Dibujar Eje X (horizontal) si está dentro de la pantalla
    if (origenY >= 0 && origenY <= alto) {
        painter.drawLine(0, origenY, ancho, origenY);
    } else {
        origenY = alto - 20; // Si el 0 matemático está fuera, fijar eje abajo para las etiquetas
    }

    // Dibujar Eje Y (vertical) si está dentro de la pantalla
    if (origenX >= 0 && origenX <= ancho) {
        painter.drawLine(origenX, 0, origenX, alto);
    } else {
        origenX = 20; // Si el 0 matemático está fuera, fijar eje a la izquierda para las etiquetas
    }

    // 6. DIBUJAR LAS MARCAS DE LA ESCALA Y TEXTOS
    QPen penMarcas(Qt::darkGray, 1, Qt::SolidLine);
    painter.setPen(penMarcas);
    painter.setFont(QFont("Arial", 8));

    // Números en el eje X
    for (double x = minX; x <= maxX; x += pasoEscalaX) {
        if (qFuzzyIsNull(x)) continue; // Saltarse el origen (0,0) para que no se solape
        int px = mapearX(x);
        painter.drawLine(px, origenY - 4, px, origenY + 4); // Pequeña marca vertical
        painter.drawText(px - 15, origenY + 18, QString::number(x, 'g', 3));
    }

    // Números en el eje Y
    for (double y = minY; y <= maxY; y += pasoEscalaY) {
        if (qFuzzyIsNull(y)) continue;
        int py = mapearY(y);
        painter.drawLine(origenX - 4, py, origenX + 4, py); // Pequeña marca horizontal
        painter.drawText(origenX + 8, py + 4, QString::number(y, 'g', 3));
    }

    // Finalizar el dibujo y cargarlo en el QLabel de la UI
    painter.end();
    ui->lblGraf->setPixmap(pixmap);
    return pixmap;
}


