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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNueva;
    QAction *actionAbrir;
    QAction *actionGuardar;
    QAction *actionSalir;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QDoubleSpinBox *dsbInferior;
    QLabel *label_3;
    QDoubleSpinBox *dsbSuperior;
    QLabel *label_4;
    QDoubleSpinBox *dsbPaso;
    QLabel *label;
    QLineEdit *etFuncion;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnGraf;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblTextoFuncion;
    QLabel *lblGraf;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QStatusBar *barraEstado;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1016, 619);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"   /* Estilo general de la ventana y paneles */\n"
"    QMainWindow, QWidget#centralwidget {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
"    }\n"
"\n"
"QDialog {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
"    }\n"
"\n"
"    /* Barra de men\303\272s */\n"
"    QMenuBar {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
"    }\n"
"    QMenuBar::item:selected {\n"
"        background-color: #673AB7;\n"
"        color: #FFFFFF;\n"
"    }\n"
"\n"
"	/* QLAbels*/\n"
"	QLabel{\n"
"		 background-color: #FCECC0;\n"
"        color: #000000;\n"
"	}\n"
"\n"
"    /* Barra de estado con fondo crema unificado */\n"
"    QStatusBar {\n"
"        background-color: #FCECC0;\n"
"        color: #673AB7;\n"
"    }\n"
"	\n"
"	/* QToolBar*/\n"
"	QToolBar{\n"
"		background-color:#FCECC0;\n"
"		color:#673AB7;\n"
"	}\n"
"\n"
"	QToolBar:separator{\n"
"		background-color:#FCECC0;\n"
"	}\n"
"\n"
"/* Estado Hover: Efecto simulado de hundido (Sunken) al pasar el"
                        " rat\303\263n */\n"
"QToolBar QToolButton:hover {\n"
"    background-color: #FCECC0; /* Un gris m\303\241s oscuro que el fondo para dar profundidad */\n"
"    border-top: 1px solid #999999;     /* Sombra interna superior */\n"
"    border-left: 1px solid #999999;    /* Sombra interna izquierda */\n"
"    border-bottom: 1px solid #ffffff;  /* Brillo inferior */\n"
"    border-right: 1px solid #ffffff;   /* Brillo derecho */\n"
"}\n"
"\n"
"/* Estado Pressed: Hundido real y m\303\241s profundo al hacer clic */\n"
"QToolBar QToolButton:pressed, QToolBar QToolButton:checked {\n"
"    background-color: #b0b0b0; /* A\303\272n m\303\241s oscuro */\n"
"    border-top: 2px solid #666666;\n"
"    border-left: 2px solid #666666;\n"
"    border-bottom: 1px solid #e0e0e0;\n"
"    border-right: 1px solid #e0e0e0;\n"
"    padding-top: 5px;  /* Desplaza ligeramente el texto/icono hacia abajo */\n"
"    padding-left: 5px; /* Desplaza ligeramente hacia la derecha para simular presi\303\263n */\n"
"}\n"
"\n"
"    /* Estilo gen\303"
                        "\251rico para botones que a\303\261adas en el futuro */\n"
"    QPushButton {\n"
"        background-color: #F63D03;\n"
"        color: #FFFFFF;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #673AB7;\n"
"    }\n"
"    QPushButton:pressed {\n"
"    	background-color: #000000;\n"
"    }\n"
"\n"
"	QProgressBar {\n"
"       background-color: #FCECC0;      /* Color de Fondo Crema */\n"
"   		border: 1px solid #673AB7;       /* Color Secundario */\n"
"       text-align: center;  							 /* Centra el porcentaje */    \n"
"       font-weight: bold;\n"
"       color: #000000;              					/* Texto del % en negro */\n"
"   }\n"
"   QProgressBar::chunk {\n"
"       background-color: #F63D03;      /* Color Primario Naranja */\n"
"   }"));
        MainWindow->setIconSize(QSize(24, 24));
        actionNueva = new QAction(MainWindow);
        actionNueva->setObjectName("actionNueva");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/recursos/nuevo1.jpeg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionNueva->setIcon(icon);
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName("actionAbrir");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/recursos/abrir.jpeg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAbrir->setIcon(icon1);
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName("actionGuardar");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/recursos/guardar1.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionGuardar->setIcon(icon2);
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName("actionSalir");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/recursos/salir.jpeg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSalir->setIcon(icon3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        dsbInferior = new QDoubleSpinBox(centralwidget);
        dsbInferior->setObjectName("dsbInferior");
        dsbInferior->setStyleSheet(QString::fromUtf8(" background-color: #FCECC0;\n"
"        color: #F63D03;"));

        verticalLayout->addWidget(dsbInferior);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        dsbSuperior = new QDoubleSpinBox(centralwidget);
        dsbSuperior->setObjectName("dsbSuperior");
        dsbSuperior->setStyleSheet(QString::fromUtf8(" background-color: #FCECC0;\n"
"        color: #F63D03;"));

        verticalLayout->addWidget(dsbSuperior);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        dsbPaso = new QDoubleSpinBox(centralwidget);
        dsbPaso->setObjectName("dsbPaso");
        dsbPaso->setStyleSheet(QString::fromUtf8(" 	background-color: #FCECC0;\n"
"    color: #F63D03;"));

        verticalLayout->addWidget(dsbPaso);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        etFuncion = new QLineEdit(centralwidget);
        etFuncion->setObjectName("etFuncion");
        QFont font;
        font.setPointSize(16);
        etFuncion->setFont(font);
        etFuncion->setStyleSheet(QString::fromUtf8(" 	background-color: #FCECC0;\n"
"   	color: #F63D03;"));

        verticalLayout->addWidget(etFuncion);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btnGraf = new QPushButton(centralwidget);
        btnGraf->setObjectName("btnGraf");
        btnGraf->setMinimumSize(QSize(0, 35));

        verticalLayout->addWidget(btnGraf);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(10, 20);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lblTextoFuncion = new QLabel(centralwidget);
        lblTextoFuncion->setObjectName("lblTextoFuncion");
        QFont font1;
        font1.setPointSize(14);
        lblTextoFuncion->setFont(font1);

        verticalLayout_2->addWidget(lblTextoFuncion);

        lblGraf = new QLabel(centralwidget);
        lblGraf->setObjectName("lblGraf");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblGraf->sizePolicy().hasHeightForWidth());
        lblGraf->setSizePolicy(sizePolicy);
        lblGraf->setStyleSheet(QString::fromUtf8("background-color: #000000;\n"
"color:#FFFFFF;"));
        lblGraf->setFrameShape(QFrame::Shape::WinPanel);
        lblGraf->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(lblGraf);

        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 10);

        verticalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1016, 23));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName("menuArchivo");
        MainWindow->setMenuBar(menubar);
        barraEstado = new QStatusBar(MainWindow);
        barraEstado->setObjectName("barraEstado");
        MainWindow->setStatusBar(barraEstado);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuArchivo->menuAction());
        menuArchivo->addAction(actionNueva);
        menuArchivo->addAction(actionAbrir);
        menuArchivo->addAction(actionGuardar);
        menuArchivo->addAction(actionSalir);
        toolBar->addAction(actionSalir);
        toolBar->addSeparator();
        toolBar->addSeparator();
        toolBar->addAction(actionNueva);
        toolBar->addAction(actionAbrir);
        toolBar->addAction(actionGuardar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNueva->setText(QCoreApplication::translate("MainWindow", "Nueva Funci\303\263n", nullptr));
        actionAbrir->setText(QCoreApplication::translate("MainWindow", "Abrir funci\303\263n", nullptr));
        actionGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar funci\303\263n", nullptr));
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "L\303\255mite Inferior:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "L\303\255mite Superior", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Tama\303\261o de pase:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Funcion:", nullptr));
        btnGraf->setText(QCoreApplication::translate("MainWindow", "Dibujar Gr\303\241fica", nullptr));
        lblTextoFuncion->setText(QCoreApplication::translate("MainWindow", "Representaci\303\263n gr\303\241fica de la funci\303\263n ", nullptr));
        lblGraf->setText(QString());
        menuArchivo->setTitle(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
