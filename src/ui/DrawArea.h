#pragma once
#ifndef INCLUDED_DRAW_AREA_H
#define INCLUDED_DRAW_AREA_H

#include <map>
#include <QGraphicsView>

class DrawArea : public QGraphicsView
{
   Q_OBJECT
private:
   int widthDraw;
   int heightDraw;
   int limitWidth;
   int limitHeight;
   float scale;

   QGraphicsScene* scene;
   std::map<int,QGraphicsItem*> itens;

   QScrollBar* hScrollBar;
   int widthHorizontalScrollBar;
   QScrollBar* vScrollBar;
   int heigthVerticalScrollBar;

   QPoint correctPointInRelationToScrollbar(QPoint point);

   void changedSize();

   void configureScrollBar();
   void configureDefaultValues();

   int calcNewDrawingWidth();
   int calcNewDrawingHeight();

protected:
   void mousePressEvent(QMouseEvent* event) override;
   void mouseMoveEvent(QMouseEvent* event) override;
   void mouseReleaseEvent(QMouseEvent* event) override;

public:
   ~DrawArea();
   DrawArea(int _widthArea,int _heightArea,int _limitWidth,int _limitHeight);

   void setScale(float scale);
   void setLimitArea(const QSize size);

   void eraseItem(int id);

   void drawLine(int id,QPoint initial,QPoint final);
   void drawArc(int id,QPoint center,QPoint initial,QPoint final);
   void drawBezier(int id,QPoint initial,QPoint control,QPoint final);

signals:
   void mousePress(QPoint);
   void mouseMove(QPoint);
   void mouseRelease(QPoint);

public slots:
   void heightScrollChanged(int value);
   void widthScrollChanged(int value);
};

#endif // INCLUDED_DRAW_AREA_H