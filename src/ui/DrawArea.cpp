#include "DrawArea.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

DrawArea::~DrawArea() 
{
   coordinatesOfTheShapesDrawn.clear();
}

DrawArea::DrawArea(QWidget* parent) : QWidget(parent)
{
   configureDefaultValues();
   setCursor(Qt::CrossCursor);
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::configureDefaultValues()
{
   setAutoFillBackground(true);
   setBackgroundRole(QPalette::Base);
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::paintEvent(QPaintEvent* event)
{
   QPainter painter(this);
   if (coordinatesOfTheShapesDrawn.size() > 0) {
      for (std::pair<int,std::deque<Coordinate>> coordinatesOfShape : coordinatesOfTheShapesDrawn) {
         if (coordinatesOfShape.second.size() > 0) {
            QPainterPath path;
            path.moveTo(coordinatesOfShape.second.front().x,coordinatesOfShape.second.front().y);
            for (Coordinate coordinate : coordinatesOfShape.second)
               path.lineTo(coordinate.x,coordinate.y);
            painter.drawPath(path);
         }
      }
   }
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
   Coordinate pos= Coordinate(event->pos().x(),event->pos().y());
   emit(mousePress(pos));
   event->accept();
}

void DrawArea::mouseMoveEvent(QMouseEvent* event)
{
   Coordinate pos= Coordinate(event->pos().x(),event->pos().y());
   emit(mouseMove(pos));
   event->accept();
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
   Coordinate pos= Coordinate(event->pos().x(),event->pos().y());
   emit(mouseRelease(pos));
   event->accept();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::clearArea()
{
   coordinatesOfTheShapesDrawn.clear();
   repaint();
}

void DrawArea::eraseShape(int idShape)
{
   coordinatesOfTheShapesDrawn.erase(idShape);
   update();
}

void DrawArea::drawCoordinate(int idShape,Coordinate& coordinate)
{
   auto shape= coordinatesOfTheShapesDrawn.find(idShape);
   if (shape != coordinatesOfTheShapesDrawn.end()) {
      shape->second.push_back(coordinate);
   }
   else {
      std::deque<Coordinate> newShapeCoordinates;
      newShapeCoordinates.push_back(coordinate);
      coordinatesOfTheShapesDrawn.insert(std::pair<int,std::deque<Coordinate>>(idShape,newShapeCoordinates));
   }
   update();
}

void DrawArea::drawCoordinates(int idShape,std::deque<Coordinate>& newCoordinates)
{
   auto shape= coordinatesOfTheShapesDrawn.find(idShape);
   if (shape != coordinatesOfTheShapesDrawn.end()) {
      shape->second.swap(newCoordinates);
   }
   else
      coordinatesOfTheShapesDrawn.insert(std::pair<int,std::deque<Coordinate>>(idShape,newCoordinates));
   update();
}
