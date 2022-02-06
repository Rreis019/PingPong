#include "CSingleton.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring> //include C strings
#include <cstdarg> //include va_start amd /'va_end'
        
class CScene : public CSingleton<CScene>
{
    public:
           
        static void saveScene(char* fileName);
        static void loadScene(char* fileName);
};
