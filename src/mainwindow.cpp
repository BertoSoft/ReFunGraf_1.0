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
#include <QFileDialog>

// Ciclo de vida de la app, constructor y destructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    setWindowTitle(Config::APP_NAME);
    setWindowIcon(QIcon(":/recursos/icono.jpeg"));

    initUi();

    // Permite capturar el movimiento del ratón aunque no se haga clic
    ui->lblGraf->setMouseTracking(true);

    // Instalar filtros de eventos de forma segura (QUITANDO qApp para evitar duplicados)
    this->installEventFilter(this);
    ui->lblGraf->installEventFilter(this);
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
    initSp();
    lblTexto->setText("Representación Gráficas de Funciones V 1.0");
    desactivaControles();
    ui->actionGuardar->setEnabled(false);
}

void MainWindow::initSp(){
    QStringList lista;

    ui->spIntegral->addItem("Elige un Método Integral");
    ui->spIntegral->addItem("Método Trapecio");
    ui->spIntegral->addItem("Método Simpson");
    ui->spIntegral->addItem("Método Simpson 3/8");
    ui->spIntegral->addItem("Método Boole");

    connect(ui->spIntegral, &QComboBox::currentIndexChanged, this, [this](int indice){
        this->dibujaIntegral(indice);
    });
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
                              "color: #673AB7; "
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
    ui->dsbInferior->setLocale(QLocale::C);
    ui->dsbSuperior->setLocale(QLocale::C);
    ui->dsbPaso->setLocale(QLocale::C);

    ui->dsbInferior->setRange(-100, 100);
    ui->dsbSuperior->setRange(-100, 100);
    ui->dsbPaso->setRange(0, 1);

    ui->dsbInferior->setDecimals(2);
    ui->dsbSuperior->setDecimals(2);
    ui->dsbPaso->setDecimals(5);

    ui->dsbInferior->setSingleStep(10);
    ui->dsbSuperior->setSingleStep(10);
    ui->dsbPaso->setSingleStep(0.001);


    ui->dsbInferior->setValue(0.00);
    ui->dsbSuperior->setValue(0.01);
    ui->dsbPaso->setValue(0.00);

    // Hacemos que el paso sea como minimo 0.0001 y que limite supeior siempre sea mayor
    ui->dsbPaso->setMinimum(0.00001);
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
    ui->chkEjes->setEnabled(true);
    ui->chkEscala->setEnabled(true);
    ui->chkRejilla->setEnabled(true);
    ui->lblGraf->setEnabled(true);
    ui->spIntegral->setEnabled(true);
}

void MainWindow::desactivaControles(){
    ui->etFuncion->setEnabled(false);
    ui->dsbInferior->setEnabled(false);
    ui->dsbSuperior->setEnabled(false);
    ui->dsbPaso->setEnabled(false);
    ui->btnGraf->setEnabled(false);
    ui->chkEjes->setEnabled(false);
    ui->chkEscala->setEnabled(false);
    ui->chkRejilla->setEnabled(false);
    ui->lblGraf->setEnabled(false);
    ui->spIntegral->setEnabled(false);
}

void MainWindow::limpiaControles(){
    ui->etFuncion->setText("");
    ui->dsbInferior->setValue(0.0);
    ui->dsbSuperior->setValue(0.0);
    ui->dsbPaso->setValue(0.0);
    ui->spIntegral->setCurrentIndex(0);
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
    QString str = "";
    //Borramos la lblGraf
    ui->lblGraf->clear();

    m_datos = procesaFuncion();
    if(!m_datos.isEmpty()){
        QPixmap miPixMap = dibujaEjes(m_datos);
        dibujaFuncion(m_datos, miPixMap);

        //AL FINAL: Si hay un método integral seleccionado, se calcula e itera.
        // Como dibujaFuncion ya guardó m_pixmap de forma segura, calculaTrapecios()
        // encontrará la gráfica lista y pintará el verde encima a la primera.
        int indiceMetodo = ui->spIntegral->currentIndex();
        if (indiceMetodo > 0) {
            dibujaIntegral(indiceMetodo);
        }

        ui->lblGraf->setFocus();
        str = "Representando la función: ";
        str.append(ui->etFuncion->text());
        lblTexto->setText(str);
        ui->actionGuardar->setEnabled(true);
    }
}

void MainWindow::on_chkEjes_clicked(){
    QList<QPointF> datos =procesaFuncion();
    QPixmap miPixmap = dibujaEjes(datos);
    dibujaFuncion(datos, miPixmap);
}

void MainWindow::on_chkEscala_clicked(){
    QList<QPointF> datos =procesaFuncion();
    QPixmap miPixmap = dibujaEjes(datos);
    dibujaFuncion(datos, miPixmap);
}

void MainWindow::on_chkRejilla_clicked(){
    QList<QPointF> datos =procesaFuncion();
    QPixmap miPixmap = dibujaEjes(datos);
    dibujaFuncion(datos, miPixmap);
}

void MainWindow::on_actionGuardar_triggered(){
    guardarFuncion();
}

void MainWindow::on_actionAbrir_triggered(){
    abrirFuncion();
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
                double paso = (ui->dsbSuperior->value() - ui->dsbInferior->value()) / 10000;
                ui->dsbPaso->setValue( paso);
                ui->dsbPaso->setMinimum(paso);
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

    // ==========================================
    // SECCIÓN: Resize (Cambio de Tamaño)
    // ==========================================
    if(ev->type() == QEvent::Resize){

        if(obj == ui->lblGraf){
            if(!m_datos.isEmpty()){
                QPixmap tmp = dibujaEjes(m_datos);
                dibujaFuncion(m_datos, tmp);
                if(ui->spIntegral->currentIndex()>0){
                    dibujaIntegral(ui->spIntegral->currentIndex());
                }
            }
        }
    }

    // ==========================================
    // SECCIÓN: MouseMove, movimiento del raton
    // ==========================================
    if(ev->type() == QEvent::MouseMove){

        // ui.lblGraf
        if(obj == ui->lblGraf && ui->lblGraf->isEnabled()){
            QMouseEvent *mouseEv = static_cast<QMouseEvent*>(ev);

            double pixelX = mouseEv->position().x();
            double pixelY = mouseEv->position().y();

            dibujaCoordenadas(pixelX, pixelY);
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
    QString strRutaArchivo = QFileDialog::getOpenFileName(
        this,
        Config::APP_NAME,
        QDir::homePath(),
        "Archivos de Texto (*.txt);;Archivos de Datos (*.dat);;Todos los archivos (*.*)"
        );

    if(strRutaArchivo.isEmpty()){
        return; // El usuario cancelo
    }

    QFile archivo(strRutaArchivo);
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(
            this,
            Config::APP_NAME,
            "Error: No se pudo abrir el archivo."
            );
        return;
    }

    QTextStream entrada(&archivo);
    entrada.setEncoding(QStringConverter::Utf8);

    QList<QPointF> datos;
    QString linea;

    QString strFuncion;
    double limiteInferior = 0.0;
    double limiteSuperior = 0.0;
    double paso = 0.0;
    int lineaMetadatos = 0;

    while(entrada.readLineInto(&linea)){
        linea = linea.trimmed();
        if(linea.isEmpty()){
            continue;
        }

        if(linea.startsWith("#")){
            QString contenido = linea.mid(1).trimmed();

            if(!contenido.startsWith("[PUNTOS:")){ // Ignorar la linea que empieza por [PUNTOS:
                lineaMetadatos ++;
                if(lineaMetadatos == 1) strFuncion = contenido;
                else if(lineaMetadatos == 2) limiteInferior = contenido.toDouble();
                else if(lineaMetadatos == 3) limiteSuperior = contenido.toDouble();
                else if(lineaMetadatos == 4) paso = contenido.toDouble();
            }
            continue;
        }

        // Leemos la matriz de QPOnitF
        QStringList partes = linea.split(',');
        if(partes.size() == 2){
            bool xOk, yOk;
            double x = partes[0].toDouble(&xOk);
            double y = partes[1].toDouble(&yOk);

            if(xOk && yOk){
                datos.append(QPointF(x, y));
            }
        }
    }
    archivo.close();

    // 5. Validar si se cargaron datos válidos
    if (datos.isEmpty()) {
        QMessageBox::warning(
            this,
            Config::APP_NAME,
            "El archivo no contiene puntos válidos o el formato es incorrecto."
            );
        return;
    }

    if(lineaMetadatos == 4){
        ui->etFuncion->setText(strFuncion);
        ui->dsbInferior->setValue(limiteInferior);
        ui->dsbSuperior->setValue(limiteSuperior);
        ui->dsbPaso->setValue(paso);

        QString str = "Representando la función: ";
        str.append(ui->etFuncion->text());
        lblTexto->setText(str);
        activaControles();
        ui->btnGraf->setEnabled(true);
        ui->btnGraf->click();
    }
}

void MainWindow::guardarFuncion(){
    QList<QPointF> datos = procesaFuncion();
    if(datos.isEmpty()){
        return;
    }

    QString nombreSugerido = ui->etFuncion->text().trimmed();
    nombreSugerido.replace(QRegularExpression("[\\\\/:*?\"<>|()]"), "_");
    if (nombreSugerido.isEmpty()) {
        nombreSugerido = "datos_funcion";
    }

    QString strRutaArchivo = QFileDialog::getSaveFileName(
        this,
        "Guardar datos de la funcion",
        QDir::homePath() + "/" + nombreSugerido + ".txt",
        "Archivos de Texto (*.txt);;Archivos de Datos (*.dat);; Todos los archivos (*.*)"
        );

    if(strRutaArchivo.isEmpty()){
        return; // El usuario cancelo la operacion
    }

    QFile archivo(strRutaArchivo);

    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(
            this,
            Config::APP_NAME,
            "Error: No se pudo abrir el archivo para escribir en modo texto."
            );
        return;
    }

    QTextStream salida(&archivo);
    salida.setEncoding(QStringConverter::Utf8);

    // Escribios los metadatos precedidos de #
    salida << "#" + ui->etFuncion->text().trimmed() + "\n";
    salida << "# " << ui->dsbInferior->value() << "\n";
    salida << "# " << ui->dsbSuperior->value() << "\n";
    salida << "# " << ui->dsbPaso->value() << "\n";

    // 7. Escribir la línea de cabecera informativa
    salida << "# [PUNTOS:" << datos.size() << "]\n";

    // 8. Escribir el vector de puntos (X,Y) con alta precisión decimal
    salida << qSetRealNumberPrecision(10);
    for (const QPointF &punto : datos) {
        salida << punto.x() << "," << punto.y() << "\n";
    }

    // 9. Cerrar el flujo de datos del archivo
    archivo.close();

    QMessageBox::information(
        this,
        Config::APP_NAME,
        "El archivo se ha guardado correctamente."
        );
}

double MainWindow::maxFuncion(QList<QPointF> datos){
    double dMax = -std::numeric_limits<double>::infinity();
    const double TOLERANCIA = 100;

    if(datos.isEmpty()){
        return dMax;
    }

    if(!std::isnan(datos.first().y()) && !std::isinf(datos.first().y())){
        if(datos.first().y() > TOLERANCIA) {
            dMax = TOLERANCIA;
        }
        else{
            dMax = datos.first().y();
        }
    }

    for(const auto &p:datos){
        if( p.y() > dMax && !std::isnan(p.y()) && !std::isinf(datos.first().y())){
            if(p.y() > TOLERANCIA) continue;
            dMax = p.y();
        }
    }

    if(dMax == -std::numeric_limits<double>::infinity()){
        return TOLERANCIA;
    }
    return dMax;
}

double MainWindow::minFuncion(QList<QPointF> datos){
    double dMin = std::numeric_limits<double>::infinity();
    const double TOLERANCIA = -100;


    if(datos.isEmpty()){
        return dMin;
    }

    if(!std::isnan(datos.first().y()) && !std::isinf(datos.first().y())){
        if(datos.first().y() < TOLERANCIA){
            dMin = TOLERANCIA;
        }
        else{
            dMin = datos.first().y();
        }
    }

    for(const auto &p:datos){
        if(p.y() < dMin && !std::isnan(p.y()) && !std::isinf(datos.first().y())){
            if(p.y() < TOLERANCIA) continue;
            dMin = p.y();
        }
    }

    if(dMin == std::numeric_limits<double>::infinity()){
        return TOLERANCIA;
    }

    return dMin;
}

QList<QPointF> MainWindow::procesaFuncion(){
    QList<QPointF> datos;

    if(ui->etFuncion->text().trimmed().isEmpty()){
        QMessageBox::critical(
            this,
            Config::APP_NAME,
            "Debes especificar una funcion matemática..."
            );
        ui->etFuncion->setFocus();
        return datos;
    }

    QString strFuncion = ui->etFuncion->text().trimmed();
    strFuncion.replace('.', ',');
    double xMax = ui->dsbSuperior->value();
    double xMin = ui->dsbInferior->value();
    double paso = ui->dsbPaso->value();

    strFuncion.replace('.', ',');

    //
    // Libreria externa tinyExpr, Configurar la variable que el parser va a buscar en el string (en este caso 'x')
    //
    double x_actual;
    te_variable vars[] = {{"x", &x_actual, TE_VARIABLE}};

    // Compilar la expresión matemática introducida por el usuario
    int error;
    te_expr* expr = te_compile(strFuncion.toStdString().c_str(), vars, 1, &error);

    if (!expr) {
        QMessageBox::critical(this, Config::APP_NAME, "Error de sintaxis en la función matemática.");
        return datos;
    }

    double x = xMin;
    while (x <= xMax + (paso / 2.0)) {
        x_actual = x;       // Actualiza el valor de la variable vinculada al parser
        double y = te_eval(expr); // Evalúa la ecuación automáticamente

        datos.append(QPointF(x, y));


        x +=paso;
    }
    te_free(expr); // Liberar la memoria del parser

    return datos;
}

QPixmap MainWindow::dibujaEjes(QList<QPointF> datos){
    QPixmap miPixmap;

    if(!ui->lblGraf) return miPixmap;

    int ancho = ui->lblGraf->width();
    int alto = ui->lblGraf->height();
    double xMax = ui->dsbSuperior->value();
    double xMin = ui->dsbInferior->value();
    double yMax = maxFuncion(datos);
    double yMin = minFuncion(datos);

    miPixmap = QPixmap(ancho, alto);
    miPixmap.fill(Qt::black);
    QPainter painter(&miPixmap);

    // si ymin == yMax, tenemos que colocar un rango
    if(yMin == yMax){
        yMax ++;
        yMin --;
    }

    auto mapearX = [=] (double x){
        return static_cast<int>((x - xMin) / (xMax - xMin) * ancho);
    };

    auto mapearY = [=] (double y){
        return static_cast<int>((yMax - y) / (yMax - yMin) * alto);
    };

    double pasoRejillaX = (xMax -xMin)/10;
    double pasoRejillaY = (yMax - yMin) / 10;
    int origenX = mapearX(0);
    int origenY = mapearY(0);

    //
    //Dibujar la rejilla de fondo
    //
    if(ui->chkRejilla->isChecked()){
        QPen penRejilla(Config::colorSecundario, 1, Qt::DotLine);
        painter.setPen(penRejilla);

        //Lineas verticales
        for(double x = xMin; x <= xMax; x+= pasoRejillaX){
            int px = mapearX(x);
            painter.drawLine(px, 0, px, alto);
        }
        // Lineas horizontales
        for(double y = yMin; y <= yMax; y += pasoRejillaY){
            int py = mapearY(y);
            painter.drawLine(0, py, ancho, py);
        }
    }

    //
    // Dibujar los ejes
    //
    if(ui->chkEjes->isChecked()){
        QPen penEjes(Qt::white, 2, Qt::SolidLine);
        painter.setPen(penEjes);

        // Eje x
        if(origenY < 0 || origenY >= alto){
            origenY = alto - 20;
        }
        painter.drawLine(0, origenY, ancho, origenY);

        //Eje y
        if(origenX < 0 || origenX >= ancho){
            origenX = ancho - 20;
        }
        painter.drawLine(origenX , 0, origenX, alto);

    }

    //
    // Dibujar las marcas de la escala y los textos
    //
    if(ui->chkEscala->isChecked()){
        QPen penMarcas(Qt::yellow, 1, Qt::SolidLine);
        painter.setPen(penMarcas);
        painter.setFont(QFont("Arial", 8));

        //Eje x, si origenY > Alto / 2 --> lettra arriba, sno letra abajo
        int textoX, textoY;
        if(origenY > (alto /2)){
            textoY = origenY - 25;
        }
        else{
            textoY = origenY + 25;
        }
        for(double x = xMin; x <= xMax; x += pasoRejillaX){
            if(std::abs(x) < (pasoRejillaX / 2)) continue;
            int px = mapearX(x);
            painter.drawLine(px , origenY - 10, px, origenY + 10);
            painter.drawText(px - 10, textoY,  QString::number(x, 'g', 3));
        }

        //Eje y
        if(origenX > (ancho / 2)){
            textoX = origenX - 40;
        }
        else{
            textoX = origenX + 20;
        }
        for(double y = yMin; y <= yMax; y += pasoRejillaY){
            if(std::abs(y) < (pasoRejillaY / 2)) continue;
            int py = mapearY(y);
            painter.drawLine(origenX - 10, py, origenX + 10, py);
            painter.drawText(textoX, py + 6, QString::number(y, 'g', 3));
        }
    }

    // Finalizar el dibujo y cargarlo en el QLabel de la UI
    painter.end();
    ui->lblGraf->setPixmap(miPixmap);

    return miPixmap;
}

void MainWindow::dibujaFuncion(QList<QPointF> datos, QPixmap miPixmap){
    if(datos.isEmpty())return;

    int ancho = ui->lblGraf->width();
    int alto = ui->lblGraf->height();

    if(ancho <= 0 || alto <= 0){
        ancho = 800;
        alto = 600;
    }

    QPainter painter(&miPixmap);
    painter.setRenderHint(QPainter::Antialiasing); // Activa suavizado de bordes

    // Maximos y minimos
    m_xMin = datos.first().x();
    m_xMax = datos.last().x();
    m_yMin = minFuncion(datos);
    m_yMax = maxFuncion(datos);

    if(qFuzzyCompare(m_yMin, m_yMax)){
        m_yMin --;
        m_yMax ++;
    }

    double rangoX = (qFuzzyCompare(m_xMax, m_xMin)) ? 1.0 : (m_xMax - m_xMin);
    double rangoY = (qFuzzyCompare(m_yMax, m_yMin)) ? 1.0 : (m_yMax - m_yMin);

    QPen penPuntos(Config::colorPrimario, 1);
    painter.setPen(penPuntos);

    double pixelXOld = ((datos[0].x() - m_xMin) / rangoX) * ancho;
    double pixelYOld = alto - (((datos[0].y() - m_yMin) / rangoY) * alto);
    for(const auto &p: datos){
        double pixelX = ((p.x() - m_xMin) / rangoX) * ancho;
        double pixelY = alto - (((p.y() - m_yMin) / rangoY) * alto);

        painter.drawLine(pixelXOld, pixelYOld, pixelX, pixelY);
        pixelXOld = pixelX;
        pixelYOld = pixelY;
    }

    painter.end(); // Finalizar las operaciones sobre el lienzo de memoria

    // 6. Asignar el Pixmap pintado al QLabel de la interfaz de usuario y al pixmap miembro
    m_pixmap = miPixmap;
    m_pixmapIntegral = miPixmap;
    ui->lblGraf->setPixmap(miPixmap);
}

void MainWindow::dibujaCoordenadas(double pixelX, double pixelY){

    int ancho = ui->lblGraf->width();
    int alto = ui->lblGraf->height();

    // NOTA DE PROTECCIÓN: recalculamos dinámicamente yMin e yMax de forma exacta a dibujaEjes()
    double yMax = maxFuncion(m_datos);
    double yMin = minFuncion(m_datos);

    if (qFuzzyCompare(yMin, yMax)) {
        yMax++;
        yMin--;
    }

    double rangoX = (qFuzzyCompare(m_xMax, m_xMin)) ? 1.0 : (m_xMax - m_xMin);
    double rangoY = (qFuzzyCompare(m_yMax, m_yMin)) ? 1.0 : (m_yMax - m_yMin);

    //Asegurarse de que los pixeles esten entre los limites
    if(pixelX >= 0 && pixelX <= ancho && pixelY >= 0 && pixelY <= alto){

        // CONVERSIÓN INVERSA EXACTA: Mapeo milimétrico de píxeles a unidades matemáticas
        double valorX = m_xMin + (pixelX / ancho) * rangoX;
        double valorY = yMax - (pixelY / alto) * rangoY; // CORREGIDO: Origen superior izquierdo de Qt calibrado

        // Tolerancia de captura en píxeles (puedes aumentarla a 5 o 6 si usas pantallas High-DPI)
        const double tolerancia = 5.0;

        // Si el raton esta encima de la funcion :
        for(const auto &p: m_datos){

            //CONVERTIR EL PUNTO DE LA FUNCIÓN A PÍXELES DE PANTALLA
            double pX = ((p.x() - m_xMin) / rangoX) * ancho;
            double pY = alto - (((p.y() - m_yMin) / rangoY) * alto);

            // 3. CALCULAR DISTANCIA REAL EN PÍXELES (Pitágoras: Verificamos un radio circular)
            double distancia = std::hypot(pixelX - pX, pixelY - pY);

            if(distancia <= tolerancia){

                // Formateamos los números flotantes con un límite legible de 3 decimales
                QString str = QString("x = %1   y = %2")
                                  .arg(QString::number(p.x(), 'f', 3),
                                       QString::number(p.y(), 'f', 3)); // CORREGIDO: Muestra el punto exacto del vector

                QPixmap pixmapTexto = m_pixmapIntegral;
                QPainter painter(&pixmapTexto);

                // Configurar fuente y color
                QFont fuente("Arial", 14, QFont::Bold);
                painter.setFont(fuente);
                painter.setPen(QPen(Config::backColor));

                // si estamos en la primera mitad de la grafica o en la segunda
                double ptoX = 0.0;
                if((ancho - pixelX) < 250){
                    ptoX = pixelX - 250;
                }
                else{
                    ptoX = pixelX;
                }
                painter.drawText(ptoX, pixelY, str);

                painter.end();
                ui->lblGraf->setPixmap(pixmapTexto);
                break;
            }
            ui->lblGraf->setPixmap(m_pixmapIntegral);
        }
    }
}

void MainWindow::dibujaIntegral(int indice){

    switch (indice) {
        case 0:
            ui->spIntegral->setCurrentIndex(0);
            break;
        case 1:
            calculaTrapecios();
            break;
        case 2:
            calculaSimpson();
            break;
        case 3:
            calculaSimpson38();
            break;
        case 4:
            calculaBoole();
            break;
        default:
            break;
    }
}

void MainWindow::calculaTrapecios(){
    double area = 0.0;
    double ancho = ui->lblGraf->width();
    double alto = ui->lblGraf->height();

    auto mapearX = [=] (double x){
        return ((x - m_xMin) / (m_xMax - m_xMin)) * ancho;
    };

    auto mapearY = [=] (double y){
        return ((m_yMax - y) / (m_yMax - m_yMin)) * alto;
    };

    bool tmp = m_pixmap.isNull();


    QPixmap miPixmap = m_pixmapIntegral;
    QPainter pintor(&miPixmap);
    pintor.setRenderHint(QPainter::Antialiasing);

    // Configurar colores del sombreado (Verde semi-transparente)
    pintor.setBrush(QColor(46, 125, 50, 60));
    pintor.setPen(QPen(QColor(46, 125, 50, 150), 1, Qt::SolidLine));

    // CORRECCIÓN 3: Limitar de forma segura la base del trapecio (el eje Y = 0) dentro del recuadro visual
    int pixelOrigenY = mapearY(0.0);
    if (pixelOrigenY < 0) pixelOrigenY = 0.0;
    if (pixelOrigenY > alto) pixelOrigenY = alto;

    for(int i =0; i < m_datos.size() -1; i++){
        double x0 = m_datos[i].x();
        double x1 = m_datos[i+1].x();
        double y0 = m_datos[i].y();
        double y1 = m_datos[i+1].y();

        // CORRECCIÓN DEFINITIVA: Filtro de seguridad + Umbral Anti-Asíntotas
        // Si el valor absoluto de Y supera las 100,000 unidades, asumimos que es un pico de infinito inestable.
        const double UMBRAL_ASINTOTA = 100000.0;

        if (std::isnan(y0) || std::isinf(y0) || std::abs(y0) > UMBRAL_ASINTOTA ||
            std::isnan(y1) || std::isinf(y1) || std::abs(y1) > UMBRAL_ASINTOTA)
        {
            continue; // Saltamos el trapecio que roza el abismo/infinito de la asíntota
        }

        // Calculamos el h de este intervalo para admitir máxima precisión ante cualquier desborde o redondeo
        double h_local = x1 - x0;

        // Sumatoria del trapecio actual
        area += (h_local / 2.0) * (y0 + y1);

        // Obtenemos los pixeles del trapecio
        double pixelX0 = mapearX(x0);
        double pixelX1 = mapearX(x1);
        double pixelY0 = mapearY(y0);
        double pixelY1 = mapearY(y1);

        // CORRECCIÓN CRÍTICA 2: Validar que los píxeles calculados no se desborden de la pantalla por culpa del pico de 1/x
        if(pixelY0 < 0.0) pixelY0 = 0.0; if(pixelY0 > alto) pixelY0 = alto;
        if(pixelY1 < 0.0) pixelY1 = 0.0; if(pixelY1 > alto) pixelY1 = alto;

        QPolygonF trapecioVisual;
        trapecioVisual << QPointF(pixelX0, pixelOrigenY)   // Esquina inferior izquierda (en el eje)
                       << QPointF(pixelX0, pixelY0)   // Esquina superior izquierda (en la curva)
                       << QPointF(pixelX1, pixelY1) // Esquina superior derecha (en la curva)
                       << QPointF(pixelX1, pixelOrigenY); // Esquina inferior derecha (en el eje)

        pintor.setPen(Qt::NoPen); // Quitar borde al trapecio para que el relleno sea homogéneo
        pintor.drawPolygon(trapecioVisual); 
    }
    pintor.end();

    // CORRECCIÓN CRÍTICA 3: Sincronizar simultáneamente el buffer integral y la visualización de la UI
    m_pixmapIntegral = miPixmap;
    ui->lblGraf->setPixmap(m_pixmapIntegral);

    // Formateo de cadena más eficiente con sintaxis moderna de Qt
    ui->lblIntegral->setText(QString("Área = %1 Unidades.").arg(QString::number(area, 'f', 6)));
}

void MainWindow::calculaSimpson(){

}

void MainWindow::calculaSimpson38(){

}

void MainWindow::calculaBoole(){

}


