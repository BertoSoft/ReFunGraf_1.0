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
    QList<QPointF> procesaFuncion();
    QPixmap dibujaEjes(QList<QPointF> datos);
    void dibujaFuncion(QList<QPointF> datos, QPixmap lienzo);



    double maxFuncion(QList<QPointF> datos);
    double minFuncion(QList<QPointF> datos);

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
