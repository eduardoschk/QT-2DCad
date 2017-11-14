#pragma once 
#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

#include "Archive.h"

class Data {
private:
    Archive * currentArchive;
public:
    Data();
    ~Data();

    Archive * getCurrentArchive();
};

#endif // INCLUDED_DATA_H