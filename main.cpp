#include "import.h"
#include "DataIO.h"
#include "DataBase.h"

int main() {
    static unsigned char data[12][14];
    static char filename[240];
    static VirusData VirData[12];
    while(true) {
        std::cout<<"����������ļ�:"<<std::endl;
        std::cin>>filename;
        ReadFile(filename, &data[0][0]);
        make_VirData_By_Zmpi_Data(&data[0][0], &VirData[0]);
        for (int i = 0; i < 12; i++) {
            if(VirData[i].DT!=0)
                Insert(VirData[i]);
        }
//        std::cout<<"���������ļ�:"<<std::endl;
//        std::cin>>filename;
//        ReadFile(filename,&data[0][0]);
//        make_VirData_By_Zmpi_Data(&data[0][0], &VirData[0]);
//        for(int i=0;i<12;i++)
//        {
//            std::cout<<"��"<<i<<"�����������Ϊ"<<Find(VirData[i])<<std::endl;
//        }
        leadout("bd.zmpi");
//        leadin("bd.zmpi");
    }
    return 0;
}
