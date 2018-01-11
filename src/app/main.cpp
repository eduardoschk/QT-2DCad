#include <crtdbg.h>
#include "App.h"

#include "Point.h"

#include <iostream>

void main(int argc,char **argv)
{   
   _CrtSetReportMode(_CRT_WARN,_CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_WARN,_CRTDBG_FILE_STDOUT);

   _CrtMemState s1;

   App(argc, argv).run();

   _CrtMemCheckpoint(&s1);
   _CrtMemDumpStatistics(&s1);
}