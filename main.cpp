#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <ApproxResolver.h>
#include <QDebug>
#include <ctime>
#include <QQmlContext>

#include <ApproxFacade.h>
#include <Warehouse.h>
#define POWER 1000000
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ApproxFacade *approxFacade = new ApproxFacade();
    qmlRegisterType<ApproxFacade>();
    qmlRegisterType<Warehouse>();
    engine.rootContext()->setContextProperty("approxFacade", approxFacade);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}



/*

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void fill(int *rep_char,char *temp_buff) {
    int z=1;
    //loop on the chars, and check if should use them
    for (int i=0; i<256; i++)
        if (rep_char[i] != 0) {
            int l=strlen(temp_buff);
            //printf("%d\n", l);
            temp_buff[l]=i; // puts i-character(ascii) to output string
            rep_char[i]--; //decrements i-charcter count
            fill(rep_char,temp_buff);

            //restore the situation
            temp_buff[l]=0;
            rep_char[i]++;
            z=0;
        }
    if (z==1){
        clock_t end = clock();
        float seconds = (float)(end - start) / CLOCKS_PER_SEC;
        printf("Secs: %f\n", seconds);
        start = clock();
        //printf("%s\n", temp_buff);
    }
}

void calc(const char *str) {
    int repetion_of_char[256]={0};
    int l=strlen(str);
    char temp_buff[l+1];
    memset(temp_buff, 0x00, l+1);

    while(*str){
        repetion_of_char[*str++]++; // count how many ripetitions of chars are
    }

    fill(repetion_of_char,temp_buff);
}




int main() {
    char* map = (char*)malloc(3600);
    memset(map, 'E', 3600);
    memset(map, 'C', 2);
    map[3599]=0x00;

    printf("Init ok\n");
    //    char s[]="AAAAAEEEEEEEEEEEEEEE";

    calc(map);

    printf("Total is %d\n", count);

    return 0;
}


*/
