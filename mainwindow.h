#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotOpen(bool);
    void slotSave(bool);
    void slotSetFolder(bool);

private:
    void closeCurrentFile();
    Ui::MainWindow *ui;
    QString _currentFileName;
    QString _currentFolder;
    QFile _currentFile;
};
#endif // MAINWINDOW_H
