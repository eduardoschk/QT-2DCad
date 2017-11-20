#pragma once 
#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

class File;

class Data {
private:
    File * currentFile;
public:
    Data();
    ~Data();

    File & getCurrentFile();
    void setCurrentFile(File * file);
};

#endif // INCLUDED_DATA_H