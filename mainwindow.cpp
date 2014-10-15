#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(640, 640);
    maskstriple = new MaskStriple(this);
    setCentralWidget(maskstriple);

    QMenu *file = new QMenu("&Файл", this);
    QAction *saveImage = file->addAction("Сохранить картинку");
    QAction *clearImage = file->addAction("Очистить картинку");
    QAction *dataToClipboard = file->addAction("Поместить битовую маску трафарета в буфер обмена");
    QAction *exit = file->addAction("Выход");

    saveImage->setShortcut(QKeySequence("CTRL+S"));
    clearImage->setShortcut(QKeySequence("CTRL+L"));
    dataToClipboard->setShortcut(QKeySequence("CTRL+C"));

    QMenu *view = new QMenu("&Вид", this);
    QAction *paintGrid = view->addAction("Рисовать сетку");
    paintGrid->setCheckable(true);
    paintGrid->setChecked(true);

    menuBar()->addMenu(file);
    menuBar()->addMenu(view);
    QAction* help = menuBar()->addAction("&Помощь");
    help->setShortcut(QKeySequence("F1"));

    QToolBar *tool = new QToolBar(this);
    tool->addAction(saveImage);
    tool->addAction(clearImage);
    tool->addAction(dataToClipboard);

    addToolBar(tool);

    saveImage->setIcon(QIcon(":/pict/save"));
    clearImage->setIcon(QIcon(":/pict/clear"));
    dataToClipboard->setIcon(QIcon(":/pict/clipboard"));

    connect(saveImage, SIGNAL(triggered()), maskstriple, SLOT(saveImage()));
    connect(clearImage, SIGNAL(triggered()), maskstriple, SLOT(clearMask()));
    connect(dataToClipboard, SIGNAL(triggered()), SLOT(addDataToClipboard()));
    connect(paintGrid, SIGNAL(triggered(bool)), maskstriple, SLOT(setPaintGrid(bool)));
    connect(help, SIGNAL(triggered()), SLOT(aboutProgram()));
    connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::addDataToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(maskstriple->dataMask());
}

void MainWindow::aboutProgram()
{
    QMessageBox::about(this, "Подсказка", "Эта программа предназначена помочь в создании второй лабораторной работы по графике. В этой программе вы сможете создать картинку трафарета и затем получить его битовую маску.\nНажимая левой кнопкой мыши по рабочей области вы будете закрашивать пикселы в черный цвет, правой кнопкой мыши – в белый. (Внимание – при наложении трафарета на полигон черный пикселы будут соответствовать пустому месту на полигоне)\nЗакончив работу над созданием картинки ее можно сохранить (Ctrl + S) вызвав меню Файл – Сохранить изображение.\nЧтобы получить битовую маску полученного трафарета выберите пункт меню Файл - Поместить битовую маску трафарета в буфер обмена, после чего битовая маска будет скопирована в буфер обмена, и вы сможете вставать ее в файл вашей программы.\nПрограмму создал Разоренов Даниил. Powered by Qt Framework.");
}
