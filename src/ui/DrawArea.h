#pragma once
#ifndef INCLUDED_DRAW_AREA_H
#define INCLUDED_DRAW_AREA_H

#include <map>
#include <deque>
#include <QWidget>

#include "Coordinate.h"

class DrawArea : public QWidget
{
Q_OBJECT
private:
   std::map<int,std::deque<Coordinate>> coordinatesOfTheShapesDrawn;
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
   void drawCoordinate(int idShape,Coordinate& coordinate);
   void drawCoordinates(int idShape,std::deque<Coordinate>& coordinates);

signals:
   void mousePress(Coordinate);
   void mouseMove(Coordinate);
   void mouseRelease(Coordinate);

};

#endif // INCLUDED_DRAW_AREA_H