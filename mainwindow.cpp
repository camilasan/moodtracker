#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->aboutLabel->setText("Made by Camila licensed under GPL-3.0 License @ <a href='https://github.com/camilasan/moodtracker'>github.com/camilasan/moodtracker</a>.");
    QObject::connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::slotOpen);
    QObject::connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::slotSave);
    QObject::connect(ui->setFolderButton, &QPushButton::clicked, this, &MainWindow::slotSetFolder);
}

void MainWindow::slotOpen(bool){
    if (_currentFile.isOpen()){
        _currentFile.close();
    }

    qDebug() << Q_FUNC_INFO << "Looking for files at" <<
                QDir::homePath();
    _currentFileName = QFileDialog::getOpenFileName(this, tr("Open note file"),
                                                    QDir::homePath(),
                                                    "Markdown files (*.md);;Text files (*.txt)");
    _currentFile.setFileName(_currentFileName);
    qDebug() << Q_FUNC_INFO << "Opening note file" <<
                _currentFileName;
    _currentFile.open(QFile::ReadOnly);
    QString content = QString::fromUtf8(_currentFile.readAll());
    ui->textEdit->setPlainText(content);
    _currentFile.close();
}

void MainWindow::slotSave(bool){
    _currentFile.setFileName(_currentFileName);
    _currentFile.open(QFile::WriteOnly);
    QString content = ui->textEdit->toPlainText();
    _currentFile.write(content.toLatin1());
    _currentFile.close();
}

void MainWindow::slotSetFolder(bool){
    _currentFolder = QFileDialog::getExistingDirectory(this,
                                                    tr("Pick folder to save the notes"),
                                                    QDir::homePath());
}

MainWindow::~MainWindow()
{
    if (_currentFile.isOpen()){
        slotSave(true);
        _currentFile.close();
    }
    delete ui;
}

