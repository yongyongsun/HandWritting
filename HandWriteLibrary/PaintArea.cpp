#include "paintarea.h"
#include<QPainter>
#include "dataprovide.h"
#include<qDebug>
#include<QApplication>
#include<QDesktopWidget>
#define HANDWRITE_WIDTH 600
#define NIB_PRESSURE 2047

PaintArea::PaintArea(QWidget *parent):QWidget(parent)
  , m_pDataprovi(NULL)
{
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    m_pDataprovi = new DataProvide(this);
    m_pDataprovi->setDataCallback((DataCallback*)this); //设置数据送达

    Start = QPoint(0,0);
    End = QPoint(0,0);
    bInit = false;
    scale = 1;
    angle = 0;
    shear = 0;
    penColor = Qt::black;
    brushColor = Qt::black;
    penWidth = 1;
    penStyle = Qt::SolidLine;

    QSize size = m_pDataprovi->getCanvasSize();
    qreal scales = (qreal)size.height()/(qreal)size.width();
    image = QImage(HANDWRITE_WIDTH,HANDWRITE_WIDTH * scales,QImage::Format_RGB32);

    qDebug()<<"PaintArea image width = "<<image.width()<<",height = "<<image.height();
    nWZoom = size.width()/HANDWRITE_WIDTH;
    nHZoom = size.height()/(HANDWRITE_WIDTH*scales);

    backcolor = qRgb(255,255,255);
    image.fill(backcolor);

    this->setFixedSize(HANDWRITE_WIDTH,HANDWRITE_WIDTH * scales);
}

void PaintArea::dataActivated(int x, int y, int preasure)
{
    qDebug()<<"PaintArea::dataActivated"<<"x = "<<x<<",y = "<<y<<",preasure = "<<preasure;

    if (preasure <= 0 || preasure > NIB_PRESSURE)//笔尖压力0~2047
    {
        bInit = false;
        return;
    }

    //根据笔尖压力设置画笔宽度
    int npen = preasure / (NIB_PRESSURE/3);
    setPenWidth(npen);


    //转换坐标映射：手写板与画布比例映射
    QPoint pNew(x/nWZoom,y/nHZoom);

    if (!bInit)
    {
        Start = pNew;
        bInit = true;
    }
    QPoint p = pNew - Start;
    if (p.manhattanLength() > 1)
    {
        End = pNew;
        paint(image);
    }

}


void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.scale(scale,scale);

    if(angle)
    {
        QPointF center(image.width()/2.0,image.height()/2.0);
        painter.translate(center);
        painter.rotate(angle);
        painter.translate(-center);
    }
    if(shear)
    {
        painter.shear(shear,shear);
    }
    painter.drawImage(0,0,image);

}
//void PaintArea::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton)
//    {
//        Start = event ->pos();
//    }

//}
//void PaintArea::mouseMoveEvent(QMouseEvent *event)
//{
//    if(event->buttons()&Qt::LeftButton)
//    {
//        End = event ->pos();
//        paint(image);
//    }

//}
//void PaintArea::mouseReleaseEvent(QMouseEvent *event)
//{

//    if(event->button() == Qt::LeftButton)
//    {
//        End = event ->pos();
//        paint(image);
//    }

//}
void PaintArea::paint(QImage &Cimage)
{
    QPainter p(&Cimage);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen = QPen();
    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    p.setPen(pen);

//    int x,y,w,h;
//    x = Start.x();
//    y = Start.y();
//    w = End.x() - x;
//    h = End.y() - y;

    p.drawLine(Start,End);
    Start = End;

    update();
}
void PaintArea::setImageSize(int width,int height)
{

    QImage newImage(width,height,QImage::Format_RGB32);
    image = newImage;
    update();

}
void PaintArea::setImageColor(QColor color)
{

    backcolor=color.rgb();
    image.fill(backcolor);
    update();

}
bool PaintArea::saveImage(const QString &filename, const char *fileFormat)
{

    QImage visibleImage = image;
    if(visibleImage.save(filename,fileFormat))
    {
        return true;

    }
    else
        return false;

}
bool PaintArea::openImage(const QString &filename)
{

    QImage loadedImage;
    if(!loadedImage.load(filename))
        return false;
    QSize newsize = loadedImage.size();
    setImageSize(newsize.width(),newsize.height());
    image = loadedImage;
    update();
    return true;

}
QSize PaintArea::getImageSize()
{

    return image.size();

}
void PaintArea::zoomIn()
{

    scale *= 1.2;
    update();

}
void PaintArea::zoomOut()
{

    scale /=1.2;
    update();

}
void PaintArea::zoom_1()
{

    scale = 1;
    angle = 0;
    shear = 0;
    update();

}
void PaintArea::Rotate()
{

    angle += 45;
    update();

}
void PaintArea::Shear()
{

    shear += 0.2;
    update();

}
void PaintArea::Clear()
{

    image.fill(backcolor);
    update();

}
void PaintArea::setPenStyle(Qt::PenStyle style)
{

    penStyle = style;

}
void PaintArea::setBrushColor(QColor color)
{

    brushColor = color;

}
void PaintArea::setPenWidth(int w)
{

    penWidth = w;

}
void PaintArea::setPenColor(QColor color)
{

    penColor = color;

}

 void PaintArea::resizeEvent ( QResizeEvent * event )
 {

     QWidget::resizeEvent(event);
 }
