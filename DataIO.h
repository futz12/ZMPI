//
// Created by 吴叶轩 on 2021/7/22.
//

#include "import.h"

#ifndef ZMPI_DATAIO_H
#define ZMPI_DATAIO_H

#endif //ZMPI_DATAIO_H

const int addr_int[]={150,300,600,0,1200,1800,1500,2300,2700,200,3000,3500};
const std::string addr_chars[]={"C","S","M","嬱","Z","B","P","D","H","E","F","G"};

inline bool ReadFile(char * filename,unsigned char * VirBYTE) //VirBYTE大小应保证有 12*14=168 BYTE
{
    unsigned long long single_size=0;
    static unsigned char buf[16];

    memset(VirBYTE,0,168);
    FILE *ptrFile= nullptr;
    ptrFile = fopen(filename, "rb");
    if(ptrFile==nullptr)
    {
        assert(false);
        return false;
    }
    fseek(ptrFile,0,SEEK_END);
    unsigned long long size=ftell(ptrFile);
    if(size>2097152LL)
    {
        single_size=size/12;
    }
    for(int i=0;i<12;i++)
    {
        if(i==3)
            fseek(ptrFile,0,SEEK_SET);
        else    if(single_size!=0)
        {
            fseek(ptrFile,single_size*((i<3)?(i+1):i)-1,SEEK_SET);
        }   else    {
            fseek(ptrFile,addr_int[i]-1,SEEK_SET);
        }
        if(i!=3)
        {
            while(fread(buf,1,1,ptrFile)==1)
            {
                if(buf[0]==addr_chars[i][0])
                {
                    fseek(ptrFile,-14,SEEK_CUR);
                    fread(buf,1,14,ptrFile);
                    memcpy(VirBYTE+i*14,buf,14);
                    break;
                }
            }
        }  else if(i==3){
            while(fread(buf,2,1,ptrFile)==1)
            {
                if(buf[0]==(unsigned char)addr_chars[i][0] && buf[1]==(unsigned char)addr_chars[i][1])
                {
                    fseek(ptrFile,-15,SEEK_CUR);
                    fread(buf,1,14,ptrFile);
                    memcpy(VirBYTE+i*14,buf,14);
                    break;
                }
                if(buf[1]==(unsigned char)addr_chars[i][0])
                    fseek(ptrFile,-1,SEEK_CUR);
            }
        }
    }
    fclose(ptrFile);
    return true;
}