#pragma once
#ifndef INCLUDED_NEW_DRAW_POPUP_H
#define INCLUDED_NEW_DRAW_POPUP_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QSpinBox;

class NewDrawPopup 
    : public QDialog
{
    Q_OBJECT
private:
    QLabel * nameLabel;
    QLineEdit * nameText;
    QLabel * widthLabel;
    QSpinBox * widthText;
    QLabel * heigthLabel;
    QSpinBox * heigthText;

    void configurePopupLayout();

 private slots:
    void cancel();
    void create();

public:
    NewDrawPopup();
    ~NewDrawPopup();

    void show();

 Q_SIGNALS:
    void sigCancel();
    void createNewArchive( QString , int, int );
};

#endif // INCLUDED_NEW_DRAW_POPUP_H