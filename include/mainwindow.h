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
    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void on_actionSalir_triggered();

    void on_actionNueva_triggered();

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
    void procesaFuncion();

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
