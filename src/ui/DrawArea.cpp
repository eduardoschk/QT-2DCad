#include "DrawArea.h"

#include <QtMath>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

DrawArea::~DrawArea() 
{
   points.clear();
}

DrawArea::DrawArea(QSize size,QWidget* parent) : QWidget(parent)
{
   //resize(size);
   setFixedSize(size);
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
      for (std::pair<int,std::deque<QPoint>> pointsOfShape : points) {
         if (pointsOfShape.second.size() > 0) {
            QPainterPath path;
            path.moveTo(pointsOfShape.second.front());
            for (QPoint point : pointsOfShape.second)
               path.lineTo(point);
            painter.drawPath(path);
         }
      }
   }
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
   emit(mousePress(event->pos()));
   event->accept();
}

void DrawArea::mouseMoveEvent(QMouseEvent* event)
{
   emit(mouseMove(event->pos()));
   event->accept();
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
   emit(mouseRelease(event->pos()));
   event->accept();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::setArea(const QSize size)
{
   //resize(size);
   setFixedSize(size);
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

void DrawArea::drawPoint(int idShape,QPoint point)
{
   auto shape= points.find(idShape);
   if (shape != points.end()) {
      shape->second.push_back(point);
   }
   else {
      std::deque<QPoint> newShapePoints;
      newShapePoints.push_back(point);
      points.insert(std::pair<int,std::deque<QPoint>>(idShape,newShapePoints));
   }
   update();
}

void DrawArea::drawPoints(int idShape,std::vector<QPoint> newPoints)
{
   auto shape= points.find(idShape);
   if (shape != points.end()) {
      shape->second.insert(shape->second.end(),newPoints.begin(),newPoints.end());
   }
   else {
      std::deque<QPoint> newShapePoints;
      newShapePoints.insert(newShapePoints.begin(),newPoints.begin(),newPoints.end());
      points.insert(std::pair<int,std::deque<QPoint>>(idShape,newShapePoints));
   }
   update();
}
