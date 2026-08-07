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

    // 2. Inicializar componentes de la UI (Crea lblTexto, lblFecha, etc.)
    initUi();


    // Permite capturar el movimiento del ratón aunque no se haga clic
    ui->lblGraf->setMouseTracking(true);


    // Le dice a Qt que esta ventana principal interceptará los eventos del label
    ui->lblGraf->installEventFilter(this);

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
    ui->actionGuardar->setEnabled(false);
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
    ui->dsbInferior->setLocale(QLocale::C);
    ui->dsbSuperior->setLocale(QLocale::C);
    ui->dsbPaso->setLocale(QLocale::C);

    ui->dsbInferior->setRange(-100, 100);
    ui->dsbSuperior->setRange(-100, 100);
    ui->dsbPaso->setRange(-1, 1);

    ui->dsbInferior->setDecimals(2);
    ui->dsbSuperior->setDecimals(2);
    ui->dsbPaso->setDecimals(3);

    ui->dsbInferior->setSingleStep(10);
    ui->dsbSuperior->setSingleStep(10);
    ui->dsbPaso->setSingleStep(0.001);


    ui->dsbInferior->setValue(0.00);
    ui->dsbSuperior->setValue(0.01);
    ui->dsbPaso->setValue(0.00);

    // Hacemos que el paso sea como minimo 0.0001 y que limite supeior siempre sea mayor
    ui->dsbPaso->setMinimum(0.001);
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
    QString str = "";
    //Borramos la lblGraf
    ui->lblGraf->clear();

    m_datos = procesaFuncion();
    if(!m_datos.isEmpty()){
        QPixmap miPixMap = dibujaEjes(m_datos);
        dibujaFuncion(m_datos, miPixMap);
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
    double dMax;

    if(datos.isEmpty()){
        return dMax;
    }

    if(!std::isnan(datos.first().y()) && !std::isinf(datos.first().y())){
        dMax = datos.first().y();
    }
    else{
        dMax = 0;
    }

    for(const auto &p:datos){
        if( p.y() > dMax && !std::isnan(p.y()) && !std::isinf(datos.first().y())){
            dMax = p.y();
        }
    }

    return dMax;
}

double MainWindow::minFuncion(QList<QPointF> datos){
    double dMin;

    if(datos.isEmpty()){
        return dMin;
    }

    if(!std::isnan(datos.first().y()) && !std::isinf(datos.first().y())){
        dMin = datos.first().y();
    }
    else{
        dMin = 0;
    }

    for(const auto &p:datos){
        if(p.y() < dMin && !std::isnan(p.y()) && !std::isinf(datos.first().y())){
            dMin = p.y();
        }
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
    te_variable vars[] = {{"x", &x_actual}};

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

    miPixmap = QPixmap(ancho, alto);
    miPixmap.fill(Qt::black);

    QPainter painter(&miPixmap);

    double xMax = ui->dsbSuperior->value();
    double xMin = ui->dsbInferior->value();
    double yMax = maxFuncion(datos);
    double yMin = minFuncion(datos);

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
        if(origenY >0 && origenY <= alto){
            painter.drawLine(0, origenY, ancho, origenY);
        }
        else{
            origenY = alto - 20;
        }

        //Eje y
        if(origenX > 0 && origenX <= ancho){
            painter.drawLine(origenX , 0, origenX, alto);
        }
        else{
            origenX = ancho - 20;
        }

    }

    //
    // Dibujar las marcas de la escala y los textos
    //
    if(ui->chkEscala->isChecked()){
        QPen penMarcas(Qt::yellow, 1, Qt::SolidLine);
        painter.setPen(penMarcas);
        painter.setFont(QFont("Arial", 8));

        //Eje x
        for(double x = xMin; x <= xMax; x += pasoRejillaX){
            if(qFuzzyIsNull(x))continue;
            int px = mapearX(x);
            painter.drawLine(px , origenY - 10, px, origenY + 10);
            painter.drawText(px - 25, origenY - 10,  QString::number(x, 'g', 3));
        }

        //Eje y
        for(double y = yMin; y <= yMax; y += pasoRejillaY){
            if(qFuzzyIsNull(y))continue;
            int py = mapearY(y);
            painter.drawLine(origenX - 10, py, origenX + 10, py);
            painter.drawText(origenX - 16, py + 16, QString::number(y, 'g', 3));
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

    for(const auto &p: m_datos){
        double pixelX = ((p.x() - m_xMin) / rangoX) * ancho;
        double pixelY = alto - (((p.y() - m_yMin) / rangoY) * alto);

        painter.drawPoint(pixelX, pixelY);
    }

    painter.end(); // Finalizar las operaciones sobre el lienzo de memoria

    // 6. Asignar el Pixmap pintado al QLabel de la interfaz de usuario
    ui->lblGraf->setPixmap(miPixmap);
}

void MainWindow::dibujaCoordenadas(double pixelX, double pixelY){

    int ancho = ui->lblGraf->width();
    int alto = ui->lblGraf->height();

    double rangoX = (qFuzzyCompare(m_xMax, m_xMin)) ? 1.0 : (m_xMax - m_xMin);
    double rangoY = (qFuzzyCompare(m_yMax, m_yMin)) ? 1.0 : (m_yMax - m_yMin);


    //Asegurarse de que los pixeles esten entre los limites
    if(pixelX >= 0 && pixelX <= ancho && pixelY >= 0 && pixelY <= alto){

        // 2. CONVERSIÓN INVERSA: De píxeles de pantalla a coordenadas matemáticas (X, Y)
        double valorX = m_xMin + (pixelX / ancho) * rangoX;
        double valorY = m_yMin + ((alto - pixelY) / alto) * rangoY;
        // Define un margen de error (tolerancia) según la escala de tus datos
        const double tolerancia = ui->dsbPaso->value() * 10;
        bool encontrado = false;

        // Si el raton esta encima de la funcion :
        for(const auto &p: m_datos){
            if(std::abs(p.x() - valorX) < tolerancia && std::abs(p.y() - valorY) < tolerancia){
                QString str = "x = ";
                str.append(QString::number(valorX));
                str.append("    y = ");
                str.append(QString::number(valorY));
                lblTexto->setText(str);
                encontrado = true;
                break;
            }
            if(!encontrado){ // Se recorrio el bucle y no se paso por encima de la funcion
                QString str = "Representando la función: ";
                str.append(ui->etFuncion->text());
                lblTexto->setText(str);
            }
        }
    }
}

