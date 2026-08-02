#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
