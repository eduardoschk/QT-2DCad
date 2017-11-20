#pragma once
#ifndef INCLUDED_DRAW_AREA_H
#define INCLUDED_DRAW_AREA_H

#include <QGraphicsView>
#include <deque>

enum SHAPE_TYPE {
    LINE,
    BEZIER,
    ARC
};

class DrawArea 
    : public QGraphicsView
{
    Q_OBJECT
private:
    int widthDraw;
    int heightDraw;
    int limitWidth;
    int limitHeight;
    float scale;

    QGraphicsScene * scene;
    std::deque<QGraphicsItem*> itens;

    QScrollBar * hScrollBar;
    int widthHorizontalScrollBar;
    QScrollBar * vScrollBar;
    int heigthVerticalScrollBar;

    SHAPE_TYPE currentShape;

    QPoint points[2];
    QGraphicsItem * currentItem;

    void clearPoints();
    QPoint correctPointInRelationToScrollbar(QPoint point);

    void changedSize();

    void configureScrollBar();
    void configureDefaultValues();
    
    int calcNewDrawingWidth();
    int calcNewDrawingHeight();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;

public:
   ~DrawArea();
    DrawArea(int _widthArea, int _heightArea, int _limitWidth, int _limitHeight);

    void setScale( float scale );
    void setShapeToDraw(SHAPE_TYPE shape);
    void setLimitArea( const QSize & size );

    void drawLine( QPoint initial, QPoint final );
    void drawArc( QPoint center , QPoint initial , QPoint final );
    void drawBezier( QPoint initial , QPoint control , QPoint final );

signals:
    void drawLineFinish( QPoint , QPoint );
    void drawArcFinish( QPoint , QPoint , QPoint );
    void drawBezierFinish( QPoint , QPoint , QPoint );

public slots:
    void heightScrollChanged( int value );
    void widthScrollChanged(int value );
};
  
#endif // INCLUDED_DRAW_AREA_H