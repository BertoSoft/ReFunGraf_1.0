#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLabel>

#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "Config.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void on_actionSalir_triggered();
    void on_actionNueva_triggered();
    void on_btnGraf_clicked();

    void on_chkEjes_clicked();

    void on_chkEscala_clicked();

    void on_chkRejilla_clicked();

    void on_actionGuardar_triggered();

    void on_actionAbrir_triggered();

    void on_spIntegral_activated(int index);

private:
    void initUi();
    void initBarraEstado();
    void refrescaReloj();
    void initReloj();
    void initDsb();
    void initSp();
    void activaControles();
    void desactivaControles();
    void limpiaControles();

    void salir();
    void nuevaFuncion();
    void abrirFuncion();
    void guardarFuncion();
    QList<QPointF> procesaFuncion(double intervalos);
    QPixmap dibujaEjes(QList<QPointF> datos);
    void dibujaFuncion(QList<QPointF> datos, QPixmap lienzo);
    void dibujaCoordenadas(double x, double y);
    double maxFuncion(QList<QPointF> datos);
    double minFuncion(QList<QPointF> datos);
    void dibujaIntegral(int indice);
    void calculaTrapecios();
    void calculaSimpson();
    void calculaSimpson38();
    void calculaBoole();

    //
    // Punteros encapsulados protegidos de manipulaciones externas
    //
    QLabel *lblTexto{nullptr};
    QLabel *lblFecha{nullptr};
    QLabel *lblReloj{nullptr};

    QTimer *timerReloj{nullptr};

    // =========================================================================
    // VARIABLES MIEMBRO DE CLASE (Persistencia para el rastreo del ratón)
    // =========================================================================
    QList<QPointF>  m_datos;                 // Guarda el último vector de puntos graficado
    int             m_intervalos =  10000;   // Numero de divisiones del intervalo
    double          m_xMin =        0.0;     // Límite mínimo real en X
    double          m_xMax =        0.0;     // Límite máximo real en X
    double          m_yMin =        0.0;     // Valor mínimo real en Y (calculado)
    double          m_yMax =        0.0;     // Valor máximo real en Y (calculado
    QPixmap         m_pixmap;                // PIxmap sin integral
    QPixmap         m_pixmapIntegral;        // Pixmap con integral

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
