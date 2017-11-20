#pragma once
#ifndef INCLUDED_COMMAND_CREATE_FILE_H
#define INCLUDED_COMMAND_CREATE_FILE_H

#include <string>
#include "Command.h"

class CommandCreateFile :
   public Command
{
private:
   std::string path;
   int width;
   int height;
public:
   CommandCreateFile( std::string _path , int _width , int _height ) :
      path( _path ) , width( _width ) , height( _height ) {}
   ~CommandCreateFile() {}

   void exec( Data & data , UserInterface & ui );
};

#endif // INCLUDED_COMMAND_CREATE_FILE_H