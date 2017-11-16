#pragma once
#ifndef INCLUDED_COMMAND_OPEN_H
#define INCLUDED_COMMAND_OPEN_H

#include "Command.h"
#include <string>

class CommandOpen :
    public Command
{
private:
    std::string pathAndFileName;
public:
    CommandOpen( std::string _pathAndFileName ) :
        pathAndFileName( _pathAndFileName ) {}
    ~CommandOpen() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_OPEN_H