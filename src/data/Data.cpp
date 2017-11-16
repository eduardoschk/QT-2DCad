#include "Data.h"

Data::Data() {}
Data::~Data() 
{
    if ( currentArchive )
        delete currentArchive;
}

Archive * Data::getCurrentArchive()
{
    return currentArchive;
}

void Data::setCurrentArchive( Archive * archive )
{
    currentArchive= archive;
}