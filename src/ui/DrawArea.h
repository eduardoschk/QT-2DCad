#pragma once
#ifndef INCLUDED_DRAW_AREA_H
#define INCLUDED_DRAW_AREA_H

#include <map>
#include <deque>
#include <QWidget>

#include "Point.h"

class DrawArea : public QWidget
{
Q_OBJECT
private:
   std::map<int,std::deque<Point>> points;
   void configureDefaultValues();

protected:
   void paintEvent(QPaintEvent* event) override;
   void mousePressEvent(QMouseEvent* event) override;
   void mouseMoveEvent(QMouseEvent* event) override;
   void mouseReleaseEvent(QMouseEvent* event) override;

public:
   ~DrawArea();
   DrawArea(QWidget* parent);

   void clearArea();
   void eraseShape(int idShape);
   void drawPoint(int idShape,Point point);
   void drawPoints(int idShape,std::deque<Point>& points);

signals:
   void mousePress(Point);
   void mouseMove(Point);
   void mouseRelease(Point);

};

#endif // INCLUDED_DRAW_AREA_H