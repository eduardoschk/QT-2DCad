#include "DrawArea.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

DrawArea::~DrawArea() 
{
   points.clear();
}

DrawArea::DrawArea(QWidget* parent) : QWidget(parent)
{
   configureDefaultValues();
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
   if (points.size() > 0) {
      for (std::pair<int,std::deque<Point>> pointsOfShape : points) {
         if (pointsOfShape.second.size() > 0) {
            QPainterPath path;
            path.moveTo(pointsOfShape.second.front().x,pointsOfShape.second.front().y);
            for (Point point : pointsOfShape.second)
               path.lineTo(point.x,point.y);
            painter.drawPath(path);
         }
      }
   }
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
   Point pos= Point(event->pos().x(),event->pos().y());
   emit(mousePress(pos));
   event->accept();
}

void DrawArea::mouseMoveEvent(QMouseEvent* event)
{
   Point pos= Point(event->pos().x(),event->pos().y());
   emit(mouseMove(pos));
   event->accept();
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
   Point pos= Point(event->pos().x(),event->pos().y());
   emit(mouseRelease(pos));
   event->accept();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::clearArea()
{
   points.clear();
   repaint();
}

void DrawArea::eraseShape(int idShape)
{
   points.erase(idShape);
   update();
}

void DrawArea::drawPoint(int idShape,Point& point)
{
   auto shape= points.find(idShape);
   if (shape != points.end()) {
      shape->second.push_back(point);
   }
   else {
      std::deque<Point> newShapePoints;
      newShapePoints.push_back(point);
      points.insert(std::pair<int,std::deque<Point>>(idShape,newShapePoints));
   }
   update();
}

void DrawArea::drawPoints(int idShape,std::deque<Point>& newPoints)
{
   auto shape= points.find(idShape);
   if (shape != points.end()) {
      shape->second.swap(newPoints);
   }
   else
      points.insert(std::pair<int,std::deque<Point>>(idShape,newPoints));
   update();
}
