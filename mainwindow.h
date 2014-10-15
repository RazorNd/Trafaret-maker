#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maskstriple.h"
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    MaskStriple* maskstriple;
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

private slots:
    void addDataToClipboard();
    void aboutProgram();
};

#endif // MAINWINDOW_H
