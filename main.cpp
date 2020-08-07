#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile qssFile(":/qss/default.qss");
    qssFile.open(QFile::ReadOnly);
    const QString styleSheet = QLatin1String(qssFile.readAll());

    app.setApplicationName("Mood tracker");
    app.setWindowIcon(QIcon(":/images/icon.png"));
    app.setStyleSheet(styleSheet);


    MainWindow w;
    w.show();
    return app.exec();
}
