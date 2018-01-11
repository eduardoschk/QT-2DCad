#pragma once
#ifndef INCLUDED_COMMAND_H
#define INCLUDED_COMMAND_H

class Data;
class UserInterface;

class Command {
public:
   virtual ~Command() {}
   Command() {}

   virtual void exec(Data& data, UserInterface& ui) = 0;
};

#endif // INCLUDED_COMMAND_H