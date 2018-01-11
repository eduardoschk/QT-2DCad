#pragma once
#ifndef INCLUDED_DRAW_AREA_H
#define INCLUDED_DRAW_AREA_H

#include <map>
#include <deque>
#include <vector>
#include <QWidget>

class DrawArea : public QWidget
{
Q_OBJECT
private:
   std::map<int,std::deque<QPoint>> points;
   void configureDefaultValues();

protected:
   void paintEvent(QPaintEvent *event) override;
   void mousePressEvent(QMouseEvent* event) override;
   void mouseMoveEvent(QMouseEvent* event) override;
   void mouseReleaseEvent(QMouseEvent* event) override;

public:
   ~DrawArea();
   DrawArea(QSize size,QWidget* parent);

   void setArea(const QSize size);

   void clearArea();
   void eraseShape(int idShape);
   void drawPoint(int idShape,QPoint point);
   void drawPoints(int idShape,std::vector<QPoint> points);

signals:
   void mousePress(QPoint);
   void mouseMove(QPoint);
   void mouseRelease(QPoint);

};

#endif // INCLUDED_DRAW_AREA_H