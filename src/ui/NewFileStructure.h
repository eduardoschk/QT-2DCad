#pragma once
#ifndef INCLUDED_NEW_FILE_STRUCTURE_H
#define INCLUDED_NEW_FILE_STRUCTURE_H

#include <string>
#include "Size.h"

struct NEW_FILE_STRUCTURE
{
   std::string name;
   Size size;

   bool isValid() { return name.size() > 0 && !size.isNull(); }
};

#endif // INCLUDED_NEW_FILE_STRUCTURE_H