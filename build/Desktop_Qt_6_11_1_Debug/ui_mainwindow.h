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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
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
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *dsbInferior;
    QLabel *label_3;
    QDoubleSpinBox *dsbSuperior;
    QLabel *label;
    QLineEdit *etFuncion;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_4;
    QComboBox *spIntegral;
    QLabel *label_4;
    QDoubleSpinBox *dsbIntervalos;
    QSpacerItem *verticalSpacer_4;
    QPushButton *btnGraf;
    QSpacerItem *verticalSpacer_3;
    QLabel *lblIntegral;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *chkEjes;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *chkEscala;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *chkRejilla;
    QSpacerItem *horizontalSpacer_3;
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
"        color: #673AB7;\n"
"	}\n"
"\n"
"	QComboBox {\n"
"    	background-color: #FCECC0; /* Tu color de fondo (ejemplo: morado de tu app) */\n"
"    	color: #F63D03;              /* Color del texto */\n"
"   		border: 1px solid #F63D03; /* Obligatorio: define un borde para activar el fondo */\n"
"    	border-radius: 4px;\n"
"    	padding: 4px 10px;\n"
"	}\n"
"\n"
"	QComboBox:hover{\n"
"		background-color:#673AB7;\n"
"		color:#FF"
                        "FFFF;\n"
"	}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"       background-color: #FCECC0;  /* Mismo color de fondo para la lista */\n"
"       color: #F63D03;              /* Texto de la lista en color primario */\n"
"       selection-background-color: #673AB7;  /* Fondo morado al seleccionar un elemento */\n"
"       selection-color: white;    /* Texto blanco para el elemento seleccionado */\n"
"       border: 1px solid #673AB7;\n"
"    }\n"
"\n"
"    /* Barra de estado con fondo crema unificado */\n"
"    QStatusBar {\n"
"        background-color: #FCECC0;\n"
"        color: #000000;\n"
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
"/* Estado Hover: Efecto simulado de hundido (Sunken) al pasar el rat\303\263n */\n"
"QToolBar QToolButton:hover {\n"
"    background-color: #FCECC0; /* Un gris m\303\241s oscuro que el fondo para dar profundidad */\n"
"    border-top: 1px solid"
                        " #999999;     /* Sombra interna superior */\n"
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
"\n"
"	QRadioButton{\n"
"		background-color:#FCECC0;\n"
"		color:#673AB7;\n"
"	}\n"
"\n"
"    /* Estilo gen\303\251rico para botones que a\303\261adas en el futuro */\n"
"    QPushButton {\n"
"        "
                        "background-color: #F63D03;\n"
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
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        dsbInferior = new QDoubleSpinBox(centralwidget);
        dsbInferior->setObjectName("dsbInferior");
        dsbInferior->setStyleSheet(QString::fromUtf8(" background-color: #FCECC0;\n"
"        color: #F63D03;"));

        verticalLayout_3->addWidget(dsbInferior);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        dsbSuperior = new QDoubleSpinBox(centralwidget);
        dsbSuperior->setObjectName("dsbSuperior");
        dsbSuperior->setStyleSheet(QString::fromUtf8(" background-color: #FCECC0;\n"
"        color: #F63D03;"));

        verticalLayout_3->addWidget(dsbSuperior);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        etFuncion = new QLineEdit(centralwidget);
        etFuncion->setObjectName("etFuncion");
        QFont font;
        font.setPointSize(16);
        etFuncion->setFont(font);
        etFuncion->setStyleSheet(QString::fromUtf8(" 	background-color: #FCECC0;\n"
"   	color: #F63D03;"));

        verticalLayout_3->addWidget(etFuncion);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalSpacer_2 = new QSpacerItem(192, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        spIntegral = new QComboBox(centralwidget);
        spIntegral->setObjectName("spIntegral");
        spIntegral->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(spIntegral);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout_4->addWidget(label_4);

        dsbIntervalos = new QDoubleSpinBox(centralwidget);
        dsbIntervalos->setObjectName("dsbIntervalos");
        dsbIntervalos->setStyleSheet(QString::fromUtf8(" 	background-color: #FCECC0;\n"
"    color: #F63D03;"));

        verticalLayout_4->addWidget(dsbIntervalos);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        btnGraf = new QPushButton(centralwidget);
        btnGraf->setObjectName("btnGraf");
        btnGraf->setMinimumSize(QSize(0, 35));

        verticalLayout_5->addWidget(btnGraf);

        verticalSpacer_3 = new QSpacerItem(192, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        lblIntegral = new QLabel(centralwidget);
        lblIntegral->setObjectName("lblIntegral");
        QFont font1;
        font1.setPointSize(14);
        lblIntegral->setFont(font1);
        lblIntegral->setStyleSheet(QString::fromUtf8("background-color: #FCECC0;\n"
"   	color: #F63D03;"));
        lblIntegral->setFrameShape(QFrame::Shape::WinPanel);
        lblIntegral->setFrameShadow(QFrame::Shadow::Plain);

        verticalLayout_5->addWidget(lblIntegral);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        chkEjes = new QRadioButton(centralwidget);
        chkEjes->setObjectName("chkEjes");
        chkEjes->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        chkEjes->setStyleSheet(QString::fromUtf8(""));
        chkEjes->setChecked(true);
        chkEjes->setAutoExclusive(false);

        horizontalLayout->addWidget(chkEjes);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        chkEscala = new QRadioButton(centralwidget);
        chkEscala->setObjectName("chkEscala");
        chkEscala->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        chkEscala->setStyleSheet(QString::fromUtf8(""));
        chkEscala->setChecked(true);
        chkEscala->setAutoExclusive(false);

        horizontalLayout_2->addWidget(chkEscala);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        chkRejilla = new QRadioButton(centralwidget);
        chkRejilla->setObjectName("chkRejilla");
        chkRejilla->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        chkRejilla->setStyleSheet(QString::fromUtf8(""));
        chkRejilla->setChecked(true);
        chkRejilla->setAutoExclusive(false);

        horizontalLayout_3->addWidget(chkRejilla);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 1);
        verticalLayout_5->setStretch(2, 1);
        verticalLayout_5->setStretch(3, 1);
        verticalLayout_5->setStretch(6, 1);
        verticalLayout_5->setStretch(7, 10);
        verticalLayout_5->setStretch(8, 1);

        horizontalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lblTextoFuncion = new QLabel(centralwidget);
        lblTextoFuncion->setObjectName("lblTextoFuncion");
        lblTextoFuncion->setFont(font1);
        lblTextoFuncion->setStyleSheet(QString::fromUtf8("color:#673AB7"));
        lblTextoFuncion->setAlignment(Qt::AlignmentFlag::AlignCenter);

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

        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 10);

        horizontalLayout_5->addLayout(horizontalLayout_4);

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
        label->setText(QCoreApplication::translate("MainWindow", "Funcion:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Numero Intervalos.", nullptr));
        btnGraf->setText(QCoreApplication::translate("MainWindow", "Dibujar Gr\303\241fica", nullptr));
        lblIntegral->setText(QString());
        chkEjes->setText(QCoreApplication::translate("MainWindow", "Pintar Ejes    ", nullptr));
        chkEscala->setText(QCoreApplication::translate("MainWindow", "Pintar Escala", nullptr));
        chkRejilla->setText(QCoreApplication::translate("MainWindow", "Pintar Rejilla", nullptr));
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
