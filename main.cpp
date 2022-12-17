#include "import.h"
#include "DataIO.h"
#include "DataBase.h"

int main() {
    static unsigned char data[12][14];
    static char filename[240];
    static VirusData VirData[12];
    while(true) {
        std::cout<<"请输入入库文件:"<<std::endl;
        std::cin>>filename;
        ReadFile(filename, &data[0][0]);
        make_VirData_By_Zmpi_Data(&data[0][0], &VirData[0]);
        for (int i = 0; i < 12; i++) {
            if(VirData[i].DT!=0)
                Insert(VirData[i]);
        }
//        std::cout<<"请输入检测文件:"<<std::endl;
//        std::cin>>filename;
//        ReadFile(filename,&data[0][0]);
//        make_VirData_By_Zmpi_Data(&data[0][0], &VirData[0]);
//        for(int i=0;i<12;i++)
//        {
//            std::cout<<"第"<<i<<"个病毒点情况为"<<Find(VirData[i])<<std::endl;
//        }
        leadout("bd.zmpi");
//        leadin("bd.zmpi");
    }
    return 0;
}
