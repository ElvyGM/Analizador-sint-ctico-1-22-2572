#include "mainwindow.h"
#include "lexerbridge.h"
#include "parser.h"
#include "ui_mainwindow.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Analizador Sintactico");
    ui->tablaTokens->horizontalHeader()->setStretchLastSection(true);
    ui->tablaTokens->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tablaTokens->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    connect(ui->botonAnalizar, &QPushButton::clicked, this, &MainWindow::analizarCodigo);
    connect(ui->botonLimpiar, &QPushButton::clicked, this, &MainWindow::limpiarCodigo);
    connect(ui->botonEjemplo, &QPushButton::clicked, this, &MainWindow::cargarEjemplo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::analizarCodigo()
{
    const QString codigo = ui->editorCodigo->toPlainText();
    if (codigo.trimmed().isEmpty()) {
        QMessageBox::information(this, "Analizador Sintactico", "Escribe o carga codigo antes de analizar.");
        return;
    }

    const QList<Token> tokens = analizarConFlex(codigo);
    ui->tablaTokens->setRowCount(tokens.size());
    for (int fila = 0; fila < tokens.size(); ++fila) {
        ui->tablaTokens->setItem(fila, 0, new QTableWidgetItem(tokens.at(fila).lexema));
        ui->tablaTokens->setItem(fila, 1, new QTableWidgetItem(tokens.at(fila).tipo));
        ui->tablaTokens->setItem(fila, 2, new QTableWidgetItem(QString::number(tokens.at(fila).linea)));
    }
    const ResultadoSintactico resultado = analizarSintaxis(tokens);
    if (resultado.valido) {
        ui->labelEstado->setText("Sintaxis valida");
        ui->labelEstado->setStyleSheet("color: #147a32; font-weight: bold;");
        ui->resultadoSintactico->setPlainText("ANALISIS COMPLETADO SIN ERRORES\n\nArbol sintactico simplificado\n" + resultado.arbol);
    } else {
        ui->labelEstado->setText(QString("Sintaxis invalida: %1 error(es)").arg(resultado.errores.size()));
        ui->labelEstado->setStyleSheet("color: #b42318; font-weight: bold;");
        ui->resultadoSintactico->setPlainText("ERRORES SINTACTICOS\n\n" + resultado.errores.join('\n') +
                                              "\n\nArbol parcial\n" + resultado.arbol);
    }
    ui->labelResumen->setText(QString("Tokens analizados: %1").arg(tokens.size()));
}

void MainWindow::limpiarCodigo()
{
    ui->editorCodigo->clear();
    ui->tablaTokens->setRowCount(0);
    ui->resultadoSintactico->clear();
    ui->labelEstado->setText("Sin analizar");
    ui->labelEstado->setStyleSheet(QString());
    ui->labelResumen->setText("Tokens analizados: 0");
}

void MainWindow::cargarEjemplo()
{
    ui->editorCodigo->setPlainText(
        "int main() {\n"
        "    int numero = 10;\n"
        "    if (numero >= 5) {\n"
        "        return numero + 1;\n"
        "    }\n"
        "}\n");
}

