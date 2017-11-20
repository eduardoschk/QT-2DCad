#include "NewDrawPopup.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QMessageBox>

NewDrawPopup::~NewDrawPopup()
{
   delete nameLabel;
   delete nameText;
   delete widthLabel;
   delete widthText;
   delete heigthLabel;
   delete heigthText;
}

NewDrawPopup::NewDrawPopup()
{
   configurePopupLayout();
}

void NewDrawPopup::configurePopupLayout()
{
   nameLabel = new QLabel( "Nome do Arquivo" , this );
   nameText = new QLineEdit( this );

   widthLabel = new QLabel( "Largura do Desenho" , this );
   widthText = new QSpinBox( this );
   widthText->setSuffix( " Px" );
   widthText->setRange( 10 , 10000 );
   widthText->setValue( 800 );

   heigthLabel = new QLabel( "Altura do Desenho" , this );
   heigthText = new QSpinBox( this );
   heigthText->setSuffix( " Px" );
   heigthText->setRange( 10 , 10000 );
   heigthText->setValue( 600 );

   QPushButton * cancelButton = new QPushButton( "Cancelar" , this );
   QPushButton * createButton = new QPushButton( "Criar" , this );

   QVBoxLayout * layout = new QVBoxLayout( this );
   layout->addWidget( nameLabel );
   layout->addWidget( nameText );
   layout->addWidget( widthLabel );
   layout->addWidget( widthText );
   layout->addWidget( heigthLabel );
   layout->addWidget( heigthText );

   QHBoxLayout * hLayout = new QHBoxLayout( this );
   hLayout->addWidget( cancelButton );
   hLayout->addWidget( createButton );

   layout->addLayout( hLayout );

   connect( cancelButton , SIGNAL( released() ) , this , SLOT( cancel() ) );
   connect( createButton , SIGNAL( released() ) , this , SLOT( create() ) );

   setLayout( layout );
}

void NewDrawPopup::show()
{
    setVisible( true );
}

void NewDrawPopup::cancel()
{
   emit( sigCancel() );
}

void NewDrawPopup::create()
{
   if ( nameText->text().length() > 0 ) {
      emit( createNewArchive( nameText->text() , widthText->value() , heigthText->value()));
   }
   else {
      QMessageBox::warning( this , tr( "Falha" ) ,
         tr( "O arquivo necessita ter um nome.\n") ,
         QMessageBox::Ok );
   }
}