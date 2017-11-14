#pragma once
#ifndef INCLUDED_COMMAND_NEW_H
#define INCLUDED_COMMAND_NEW_H

#include <string>

#include "Command.h"

class CommandNew :
    public Command
{
private:
    std::string pathAndFileName;
    int width;
    int height;

public:
    CommandNew( std::string _pathAndFileName , int _width , int _height ) :
        pathAndFileName ( _pathAndFileName ), width(_width), height(_height) {}
    ~CommandNew() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_NEW_H