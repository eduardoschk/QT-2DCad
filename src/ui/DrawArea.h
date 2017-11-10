#ifndef INCLUDED_DRAW_AREA_H
#define INCLUDED_DRAW_AREA_H

#include <QGraphicsView>
#include <deque>

enum SHAPE {
    LINE,
    BEZIER,
    ARC
};

class DrawArea 
    : public QGraphicsView
{
    Q_OBJECT
private:
    int widthArea;
    int heightArea;
    float scale;

    QGraphicsScene * scene;
    std::deque<QGraphicsItem*> itens;

    QScrollBar * hScrollBar;
    int widthHorizontalScrollBar;
    QScrollBar * vScrollBar;
    int heigthVerticalScrollBar;

    SHAPE currentShape;

    QPoint points[2];
    QGraphicsItem * currentItem;

    void clearPoints();
    QPoint corrigeScrollPoint(QPoint point);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;

    bool eventFilter( QObject * , QEvent * ) override;

public:
    ~DrawArea() {}
    DrawArea(int _widthArea, int _heightArea);

    void setScale( float scale );
    void setShapeToDraw(SHAPE shape);

public slots:
    void scrollPress( int i );
    void scrollRelease(int i);
};
  
#endif // INCLUDED_DRAW_AREA_H