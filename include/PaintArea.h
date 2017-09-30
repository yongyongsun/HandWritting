#ifndef PAINTAREA_H
#define PAINTAREA_H
#include "HandWriteLibrary_global.h"
#include <QWidget>
#include<QMouseEvent>
#include<QPoint>
#include<stdio.h>
#include <QTextStream>
#include "DataCallback.h"

class DataProvide;
class HANDWRITELIBRARYSHARED_EXPORT PaintArea : public QWidget, public DataCallback
{
    Q_OBJECT
public:
    PaintArea(QWidget *parent = 0);

    bool saveImage(const QString &filename ,const char *fileFormat);

protected:
    void dataActivated(int x, int y, int preasure);
    void paintEvent(QPaintEvent *);
//    void mousePressEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent ( QResizeEvent * event );
private:
    void paint(QImage&);
    void setImageSize(int width,int height);
    void setImageColor(QColor color);
    bool openImage(const QString &filename);
    QSize getImageSize();
    void zoomIn();
    void zoomOut();
    void zoom_1();
    void Rotate();
    void Shear();
    void Clear();
    void setPenStyle(Qt::PenStyle);
    void setPenWidth(int w);
    void setPenColor(QColor color);
    void setBrushColor(QColor color);
private:
    DataProvide *m_pDataprovi;
    QImage image;
    QRgb backcolor;
    QPoint Start,End;
    qreal scale;
    int angle;
    qreal shear;
    QColor penColor;
    QColor brushColor;
    int penWidth;
    Qt::PenStyle penStyle;
    bool bInit;
    int nWZoom; //画布和手写板的宽度缩放比例
    int nHZoom; //画布和手写板的高度缩放比例

};
 
#endif // PAINTAREA_H
