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

private:
    void initUi();
    void initBarraEstado();
    void refrescaReloj();
    void initReloj();
    void initDsb();
    void activaControles();
    void desactivaControles();
    void limpiaControles();

    void salir();
    void nuevaFuncion();
    void abrirFuncion();
    void guardarFuncion();
    QVector<Config::datosGraf> procesaFuncion();
    void dibujaFuncion(QVector<Config::datosGraf> vectorDatosGraf, QPixmap lienzo);
    QPixmap dibujaEjes(QVector<Config::datosGraf> vectorDatosGraf);

    QList<QPointF> procesaFuncion_bis();
    QPixmap dibujaEjes_bis(QList<QPointF> datos);
    void dibujaFuncion_bis(QList<QPointF> datos, QPixmap lienzo);



    double maxFuncion(QVector<Config::datosGraf> vectorDatosGraf);
    double minFuncion(QVector<Config::datosGraf> vectorDatosGraf);

    //
    // Punteros encapsulados protegidos de manipulaciones externas
    //
    QLabel *lblTexto{nullptr};
    QLabel *lblFecha{nullptr};
    QLabel *lblReloj{nullptr};

    QTimer *timerReloj{nullptr};

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
