#include "mainwindow.h"
#include "Config.h"

#include <QApplication>
#include <QTimer>
#include <QSplashScreen>
#include <QProgressBar>
#include <QThread>

int main(int argc, char *argv[]){

    #if defined(Q_OS_LINUX)
        qputenv("QT_QPA_PLATFORM", "xcb");
    #endif

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/recursos/icono.jpeg"));
    QApplication::setApplicationName(Config::APP_NAME);

    // 1. INICIALIZACIÓN DEL SPLASH Y BARRA DE PROGRESO
    QPixmap pixmap(":/recursos/logo.png");
    QSplashScreen splash(pixmap); // Cambiado a objeto local (gestión de memoria automática)
    QProgressBar progressBar(&splash);

    // configuracion de splash
    progressBar.setGeometry(10, pixmap.height() - 35, pixmap.width() - 20, 18);
    progressBar.setRange(0, 100);
    progressBar.setTextVisible(true);

    progressBar.show();
    splash.show();

    // 2. BUCLE ÚNICO DE CARGA (Sustituye a todos los QTimer)
    for (int i = 0; i <= 100; ++i) {
        progressBar.setValue(i);

        // Uso de switch: es más rápido para el compilador y ejecuta código solo en el paso exacto
        switch (i) {
        case 0:
            splash.showMessage("Cargando módulos matemáticos ...\n\n", Qt::AlignBottom | Qt::AlignLeft, Config::colorPrimario);
            break;
        case 33:
            splash.showMessage("Cargando datos de configuración...\n\n", Qt::AlignBottom | Qt::AlignLeft, Config::colorPrimario);
            break;
        case 66:
            splash.showMessage("Cargando módulos gráficos...\n\n", Qt::AlignBottom | Qt::AlignLeft, Config::colorPrimario);
            break;
        default:
            break;
        }

        a.processEvents();      // Fuerza a Qt a pintar los cambios en la pantalla
        QThread::msleep(25);    // 25ms * 100 pasos = 2.5 segundos exactos de carga
    }

    // 3. CREACIÓN Y MUESTRA DE LA VENTANA
    MainWindow w;
    w.show();

    // Retraso para que se ejecute la orde de maximizado
    QTimer::singleShot(10, &w, [&w](){
        w.setWindowState(Qt::WindowMaximized);
    });

    splash.finish(&w);
    return a.exec();
}