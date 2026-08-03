#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

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
    void salir();
    void nuevaFuncion();
    void abrirFuncion();
    void guardarFuncion();

private slots:
    void on_actionSalir_triggered();

private:
    void initUi();
    void initBarraEstado();
    void refrescaReloj();
    void initReloj();

    //
    // Punteros encapsulados protegidos de manipulaciones externas
    //
    QLabel *lblTexto{nullptr};
    QLabel *lblFecha{nullptr};
    QLabel *lblReloj{nullptr};

    QTimer *timerReloj{nullptr};






    // NUEVOS COMPONENTES DEL FORMULARIO DE DATOS
    QLineEdit       *txtFuncion;
    QDoubleSpinBox  *spinXMin;
    QDoubleSpinBox  *spinXMax;
    QDoubleSpinBox  *spinPaso;
    QPushButton     *btnGraficar;
    QWidget         *widgetGrafica; // Contenedor del 80% derecho

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
