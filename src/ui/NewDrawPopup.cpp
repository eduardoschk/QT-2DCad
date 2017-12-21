#include "NewDrawPopup.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include "NewFileStructure.h"

int MIN_RANGE= 10;
int MAX_RANGE= 10000;
int DEFAULT_WIDTH= 800;
int DEFAULT_HEIGHT= 600;

NewDrawPopup::~NewDrawPopup() {}        

NewDrawPopup::NewDrawPopup(NEW_FILE_STRUCTURE* _nfs)
{
   nfs= _nfs;
   configurePopupLayout();
}

///////////////////////////////////////////////////////////////////////////////

void NewDrawPopup::configurePopupLayout()
{
   QLabel* nameLabel= new QLabel("Nome do Arquivo",this);
   nameText= new QLineEdit(this);

   QLabel* widthLabel= new QLabel("Largura do Desenho",this);
   widthText= new QSpinBox(this);
   widthText->setSuffix(" Px");
   widthText->setRange(MIN_RANGE,MAX_RANGE);
   widthText->setValue(DEFAULT_WIDTH);

   QLabel* heightLabel= new QLabel("Altura do Desenho",this);
   heightText= new QSpinBox(this);
   heightText->setSuffix(" Px");
   heightText->setRange(MIN_RANGE,MAX_RANGE);
   heightText->setValue(DEFAULT_HEIGHT);

   QPushButton* cancelButton= new QPushButton("Cancelar",this);
   QPushButton* createButton= new QPushButton("Criar",this);
   createButton->setDefault(true);

   QVBoxLayout* layout= new QVBoxLayout(this);
   layout->addWidget(nameLabel);
   layout->addWidget(nameText);
   layout->addWidget(widthLabel);
   layout->addWidget(widthText);
   layout->addWidget(heightLabel);
   layout->addWidget(heightText);

   QHBoxLayout* hLayout= new QHBoxLayout(this);
   hLayout->addWidget(cancelButton);
   hLayout->addWidget(createButton);

   layout->addLayout(hLayout);

   connect(cancelButton,SIGNAL(released()),this,SLOT(reject()));
   connect(createButton,SIGNAL(released()),this,SLOT(accept()));

   setLayout(layout);
}

///////////////////////////////////////////////////////////////////////////////

void NewDrawPopup::accept()
{
   nfs->width= widthText->value();
   nfs->height= heightText->value();
   nfs->name= nameText->text().toStdString();

   QDialog::accept();
}