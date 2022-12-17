//
// Created by 吴叶轩 on 2021/7/22.
//
#include "import.h"

#ifndef ZMPI_DATATYPE_H
#define ZMPI_DATATYPE_H

#endif //ZMPI_DATATYPE_H


struct ZmpiData
{
    unsigned char type;//1-12
    unsigned char val[14];

    ZmpiData()
    {
        type=0;
        memset(val,0,sizeof(val));
    }

    inline ZmpiData operator=(const ZmpiData &a)
    {
        type=a.type;
        for(int i=0;i<14;i++)
            val[i]=a.val[i];
        return *this;
    }
};

inline bool operator<(const ZmpiData &a,const ZmpiData &b)
{
    if(a.type!=b.type)
        return a.type<b.type;
    for(int i=0;i<14;i++)
        if(a.val[i]!=b.val[i])
            return a.val[i]<b.val[i];

    return false;
}



enum DataType
{
    ZMPI=1
};

enum VirusType
{
    NONE=1
};

struct VirusData
{
    ZmpiData ZD;
    DataType DT;

    VirusData()
    {
        DT=(DataType)0;
    }

    inline void operator= (const VirusData &a)
    {
        if(DT!=a.DT && DT!=(DataType)0)
        {
            assert(false);
            //return VirusData();
        }
        if(DT==(DataType)0)
        {
            DT=a.DT;
        }
        if(DT==ZMPI) {
            ZD = a.ZD;
        }
        //return *this;
    }
};

inline bool operator< (const VirusData &a,const VirusData &b)
{
    if(a.DT!=b.DT)
    {
        return a.DT<b.DT;
    }
    if(a.DT==ZMPI)
    {
        return a.ZD<b.ZD;
    }
    return false;
}

inline void make_VirData_By_Zmpi_Data(unsigned char * VirData,VirusData * VD)//VD 至少要有12个成员,依次按原版Zmpi顺序排列,如果全空,则Zmpi数据指针为nullptr
{
    for(int i=0;i<12;i++)
    {
        VD[i].DT=ZMPI;
        VD[i].ZD.type=i+1;
        memcpy(VD[i].ZD.val,VirData+i*14,14);
        for(int j=0;j<14;j++) {
            if (VD[i].ZD.val[j] != 0)
                goto End;
        }
        VD[i].DT=(DataType)0;
        End:;
    }
}