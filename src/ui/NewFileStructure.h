#pragma once
#ifndef INCLUDED_NEW_FILE_STRUCTURE_H
#define INCLUDED_NEW_FILE_STRUCTURE_H

#include <string>

struct NEW_FILE_STRUCTURE
{
   std::string name;
   int width;
   int height;

   bool isValid()
   {
      return name.size() > 0 && width > 0 && height > 0;
   }
};

#endif // INCLUDED_NEW_FILE_STRUCTURE_H