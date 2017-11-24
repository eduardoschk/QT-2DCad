#pragma once
#ifndef INCLUDED_NEW_DRAW_POPUP_H
#define INCLUDED_NEW_DRAW_POPUP_H

#include <QDialog>
#include "NewFileStructure.h"

class QSpinBox;
class QLineEdit;

class NewDrawPopup : public QDialog
{
    Q_OBJECT
private:
   QLineEdit* nameText;
   QSpinBox* widthText;
   QSpinBox* heightText;

   NEW_FILE_STRUCTURE* nfs;

   void configurePopupLayout();

public:
   ~NewDrawPopup();
   NewDrawPopup(NEW_FILE_STRUCTURE* _nfs);

private slots:
   void accept();
};

#endif // INCLUDED_NEW_DRAW_POPUP_H