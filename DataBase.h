//
// Created by 吴叶轩 on 2021/7/22.
//

#include "import.h"
#include "DataType.h"


#ifndef ZMPI_DATABASE_H
#define ZMPI_DATABASE_H

#endif //ZMPI_DATABASE_H


tlx::btree_map<VirusData,VirusType> DataBase;


inline void Insert(const VirusData &s)
{
    DataBase[s]=NONE;
}

inline void Remove(const VirusData &s)
{
    auto it=DataBase.find(s);
    if(it!=DataBase.end())
        DataBase.erase(it);
}

inline VirusType Find(const VirusData &s)
{
    auto it=DataBase.find(s);
    if(it!=DataBase.end())
        return it->second;
    else    return (VirusType)0;
}

inline void leadout(const char * filename)
{
    FILE * ptrfile = fopen(filename,"wb");
    if(ptrfile== nullptr)
    {
        assert(false);
    }
    for(auto it=DataBase.begin();it!=DataBase.end();it++)
    {
        fwrite(&(it->first),sizeof(VirusData),1,ptrfile);
        fwrite(&(it->second),sizeof(VirusType),1,ptrfile);
    }
    fclose(ptrfile);
}

inline void leadin(const char * filename)
{
    FILE * ptrfile= fopen(filename,"rb");
    if(ptrfile== nullptr)
    {
        assert(false);
    }
    static unsigned char buf[sizeof(VirusData)+sizeof(VirusType)];
    static VirusData VD;
    static VirusType VT;
    while(fread(buf,sizeof(buf),1,ptrfile)==1)
    {
        memcpy(&VD,buf,sizeof(VirusData));
        memcpy(&VT,buf,sizeof(VirusType));
    }
    fclose(ptrfile);
}