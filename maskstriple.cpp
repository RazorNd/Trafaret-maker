#include "maskstriple.h"
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QPaintDevice>
#include <QMessageBox>
#include <QFileDialog>


MaskStriple::MaskStriple(QWidget *parent)
    : QWidget(parent)
{
    sizeCell = 1;    
    _paintGrid = true;
    setMinimumSize(320, 320);
}

MaskStriple::~MaskStriple()
{    
}

QString MaskStriple::dataMask()
{
    return mask.data();
}

void MaskStriple::paintEvent(QPaintEvent *pe)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(workplace, Qt::white);
    painter.end();

    if(_paintGrid)
        paintGrid();

    paintMask();
    pe->accept();
}

void MaskStriple::resizeEvent(QResizeEvent *event)
{
    int size = qMin(height(), width());
    size -= size % 32;

    sizeCell = size / 32;

    workplace.setTop((height() / 2) - (size / 2));
    workplace.setLeft((width() / 2) - (size / 2));

    workplace.setSize(QSize(size, size));

    QWidget::resizeEvent(event);    
}

void MaskStriple::mouseMoveEvent(QMouseEvent *event)
{
    checkMouse(event);
    QWidget::mouseMoveEvent(event);
}

void MaskStriple::mousePressEvent(QMouseEvent *event)
{
    checkMouse(event);
    QWidget::mousePressEvent(event);
}

void MaskStriple::paintQuads(int x, int y)
{
    QPoint a = workplace.bottomLeft() + QPoint(x * sizeCell, -(y + 1) * sizeCell);
    QSize size = QSize(sizeCell, sizeCell);    
    QPainter painter;    
    painter.begin(this);
    painter.fillRect(QRect(a, size), Qt::black);
    painter.end();
}

void MaskStriple::paintQuads(int x, int y, QPaintDevice *context)
{
    if(context->height() != context->width() || (context->width() % 32))
    {
        qDebug() << "bad context";
        return;
    }

    int widthQuad = context->width() / 32;
    QSize sizeQuad = QSize(widthQuad, widthQuad);
    QPoint a(x * widthQuad, context->height() - ((y + 1) * widthQuad));

    QPainter painter;
    painter.begin(context);
    painter.fillRect(QRect(a, sizeQuad), Qt::black);
    painter.end();    
}

void MaskStriple::paintMask()
{
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            if(mask.at(i,j))
            {                
                paintQuads(i, j);
            }
        }
    }
}

void MaskStriple::paintGrid()
{
    QPainter painter;
    painter.begin(this);
    for(int i = workplace.top() - 1; i <= workplace.bottom(); i += sizeCell)
    {
        painter.drawLine(workplace.left(), i, workplace.right(), i);
    }
    for(int i = workplace.left() - 1; i <= workplace.right(); i += sizeCell)
    {
        painter.drawLine(i, workplace.top(), i, workplace.bottom());
    }
}

void MaskStriple::checkMouse(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    if(workplace.contains(mousePos) && (event->buttons() & (Qt::LeftButton | Qt::RightButton)))
    {
        this->mousePos = mousePos;
        mousePos -= workplace.topLeft();
        int x = mousePos.x() / sizeCell;
        int y = 31 - (mousePos.y() / sizeCell);
        mask.change(x, y, event->buttons() & Qt::LeftButton);
        emit maskUpdated();
        update();
    }
}

void MaskStriple::saveImage(QString filename)
{
    QImage img(QSize(320, 320), QImage::Format_RGB16);
    img.fill(Qt::white);
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            if(mask.at(i,j))
            {
                paintQuads(i, j, &img);

            }
        }
    }
    img.save(filename, "JPEG");
}

void MaskStriple::setPaintGrid(bool painting)
{
    _paintGrid = painting;
    update();
}

void MaskStriple::saveImage()
{
    QString filename = QFileDialog::getSaveFileName(this, "Имя картинки", "", "Images (*.jpg)");
    if(filename.isEmpty())
        return;
    saveImage(filename);
}

void MaskStriple::clearMask()
{
    mask.clear();
    emit maskUpdated();
    update();
}



