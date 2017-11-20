#pragma once
#ifndef INCLUDED_COMMAND_IO_H
#define INCLUDED_COMMAND_IO_H

#include <string>
#include "Command.h"

struct FileParams {
   std::string path;
   std::string name;
};

class CommandIO :
   public Command
{
protected:
   FileParams dividerNameOfPath( std::string completedPath );
public:
   virtual void exec( Data& data , UserInterface& ui ) = 0;
};

#endif // INCLUDED_COMMAND_IO_H