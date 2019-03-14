#ifndef HUNGRYAPP_H_INCLUDED
#define HUNGRYAPP_H_INCLUDED



#endif // HUNGRYAPP_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int order=0;
struct Rest{            //Data which describes restaurant
    char nameR[20], addR[20], category[20];
    char menu[5][20];
    int seats,MaxSeats;         //seats available and maximum seats in a given restaurant
    struct rest* nextR;
};
struct User{                //Data which describes user
    char nameU[20], addU[20], phoneU[10];
    int IDU;                 //user will be assigned a user ID for convenience
    struct user* nextU;
};
struct Agent{           //Data which describes agent
    char nameA[20], phoneA[10], Add[20];
    int IDA;             //agent will be assigned a agent ID for convenience
    int ava;
    float sal;                //when  ava = 1 agent is available otherwise busy
    struct agent* nextA;
};
struct Order{
    char name[20], rest[20], item[20];
    int orderno,agentAssg;
    struct Order* next;
};
