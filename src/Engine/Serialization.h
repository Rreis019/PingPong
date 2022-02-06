#include <string>

enum ESaveFormat
{
    ESF_BINARY,
    ESF_TEXT
};

inline int saveFormat = ESF_TEXT;

class bin
{
public:
    static void  save(FILE* fp,std::string str)
    {
        int lenght = str.length() + 1; // +1 for null terminator
        fwrite(&lenght, sizeof(int), 1, fp);
        fwrite(str.c_str(), sizeof(char), lenght, fp);
    }

    static void save(FILE* fp,int value){fwrite(&value, sizeof(int), 1, fp);}
    static void save(FILE* fp,float value){fwrite(&value, sizeof(float), 1, fp);}
    static void save(FILE* fp,unsigned char value){fwrite(&value, sizeof(unsigned char), 1, fp);}

    static void read(FILE* fp,std::string& str)
    {
        int lenght = 0;
        char buffer[32];
        fread(&lenght, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), lenght, fp);
        str = buffer;
    }

    static void read(FILE* fp,int& value){fread(&value, sizeof(int), 1, fp);}
    static void read(FILE* fp,float& value){fread(&value, sizeof(float), 1, fp);}
    static void read(FILE* fp,unsigned char& value){fread(&value, sizeof(unsigned char), 1, fp);}
};


class txt
{
public:
    static void save(FILE* fp,std::string variableName,std::string value)
    {
        fprintf(fp,"%s : %s\n",variableName.c_str(),value.c_str());
    }

    static void save(FILE* fp,std::string variableName,int value)
    {
        fprintf(fp,"%s : %d\n",variableName.c_str(),value);
    }

    static void save(FILE* fp,std::string variableName,float value)
    {
        fprintf(fp,"%s : %f\n",variableName.c_str(),value);
    }

    static void save(FILE* fp,std::string variableName,unsigned char value)
    {
        fprintf(fp,"%s : %d\n",variableName.c_str(),value);
    }

    static void read(FILE* fp,std::string& value)
    {
        char buffer[256];
        char buffer2[256];
        fscanf(fp,"%s : %s\n",buffer,buffer2);
        value = buffer2;
    }

    static void read(FILE* fp,int& value)
    {
        char buffer[256];
        fscanf(fp,"%s : %d\n",buffer,&value);
    }

    static void read(FILE* fp,float& value)
    {
        char buffer[256];
        fscanf(fp,"%s : %f\n",buffer,&value);
        value = value;
    }

    static void read(FILE* fp,unsigned char& value)
    {
        char buffer[256];
        fscanf(fp,"%s : %d\n",buffer,value);
        value = value;
    }


};

#define SAVE(fp,variable) saveFormat == ESF_BINARY ? bin::save(fp,variable) : txt::save(fp,#variable,variable);
#define READ(fp,variable) saveFormat == ESF_BINARY ? bin::read(fp,variable) : txt::read(fp,variable);