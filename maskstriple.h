#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QSize>
#include <QResizeEvent>
#include <QMouseEvent>
#include "mask.h"

class MaskStriple : public QWidget
{
    Q_OBJECT    
    Mask mask;
    QRect workplace;
    QPoint mousePos;
    int sizeCell;
    bool _paintGrid;

public:
    MaskStriple(QWidget *parent = 0);
    ~MaskStriple();

    QString dataMask();
protected:
    void paintEvent(QPaintEvent *pe);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);    
private:
    void paintQuads(int x, int y);
    void paintQuads(int x, int y, QPaintDevice* context);
    void paintMask();
    void paintGrid();
    void checkMouse(QMouseEvent *event);
public slots:
    void saveImage(QString filename);
    void setPaintGrid(bool painting);
    void saveImage();
    void clearMask();
signals:
    void maskUpdated();
};


#endif // WIDGET_H
