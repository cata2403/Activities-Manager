#include <QtWidgets/QApplication>
#include <QWidget>
#include "service_activitati.h"
#include "gui.h"
#include "gui_VM.h"
#include "tester.h"
#include "repo_fisiere.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Tester::run_all_tests();
    Repo_Fisiere r1{"MulteDate.txt"}; 
    Repo_Memorie r2{}; 
    Validator v; 
    ServActivitati serv{r1,r2,v};  

    QApplication a(argc, argv);  
    GUI_VM window{ serv }; 
    //GUI window{ serv };
    window.show();
    return a.exec();
}
