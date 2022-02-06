#pragma once
#include <stdlib.h>
#include <stdio.h>

class Object
{
    public:
        virtual void serialise(FILE * fp){};
        virtual void deserialise(FILE * fp){};
    private:
};