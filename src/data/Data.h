#pragma once 
#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

class Archive;

class Data {
private:
    Archive * currentArchive;
public:
    Data();
    ~Data();

    Archive * getCurrentArchive();
    void setCurrentArchive(Archive * archive);
};

#endif // INCLUDED_DATA_H