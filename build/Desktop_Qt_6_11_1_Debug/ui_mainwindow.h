/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *barraEstado;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"   /* Estilo general de la ventana y paneles */\n"
"    QMainWindow, QWidget#centralwidget {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
"    }\n"
"\n"
"    /* Barra de men\303\272s */\n"
"    QMenuBar {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
"        border-bottom: 1px solid #673AB7;\n"
"    }\n"
"    QMenuBar::item:selected {\n"
"        background-color: #673AB7;\n"
"        color: #FFFFFF;\n"
"    }\n"
"\n"
"	QLabel{\n"
"		 background-color: #FCECC0;\n"
"        color: #000000;\n"
"	}\n"
"\n"
"    /* Barra de estado con fondo crema unificado */\n"
"    QStatusBar {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
"        spacing: 0px; /* <--- A\303\221ADE ESTA L\303\215NEA */\n"
"    }\n"
"\n"
"    /* Estilo gen\303\251rico para botones que a\303\261adas en el futuro */\n"
"    QPushButton {\n"
"        background-color: #F63D03;\n"
"        color: #FFFFFF;\n"
"        border: none;\n"
"        padding: 6px 12px;\n"
"      "
                        "  border-radius: 4px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #673AB7;\n"
"    }\n"
"    QPushButton:pressed {\n"
"    	background-color: #000000;\n"
"    }\n"
"\n"
"	QProgressBar {\n"
"   		border: 1px solid #673AB7;       /* Color Secundario */\n"
"       background-color: #FCECC0;      /* Color de Fondo Crema */\n"
"       text-align: center;  							 /* Centra el porcentaje */    \n"
"       border-radius: 3px;\n"
"       font-weight: bold;\n"
"       color: #000000;              					/* Texto del % en negro */\n"
"   }\n"
"   QProgressBar::chunk {\n"
"       background-color: #F63D03;      /* Color Primario Naranja */\n"
"   }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        barraEstado = new QStatusBar(MainWindow);
        barraEstado->setObjectName("barraEstado");
        MainWindow->setStatusBar(barraEstado);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
