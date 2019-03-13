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
    char nameA[20], phoneA[10], add[20];
    int IDA;             //agent will be assigned a agent ID for convenience
    int ava;                //when  ava = 1 agent is available otherwise busy
    struct agent* nextA;
};
struct Order{
    char name[20], rest[20], item[20];
    int orderno,agentAssg;
    struct Order* next;
};
struct Rest* initRest(struct Rest* head){
    struct Rest* temp=NULL;
    int i,j,n;
    printf("Enter the number of restaurants\n");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        head=(struct Rest*)malloc(sizeof(struct Rest));
        printf("Enter the name of Restaurant\n");
        scanf("%s",head->nameR);
        printf("Enter the address\n");
        scanf("%s",head->addR);
        printf("Enter the category of Restaurant\n");
        scanf("%s",head->category);
        printf("Enter the 5 menu items\n");
        for(j=0;j<5;j++){
            scanf("%s",head->menu[j]);
        }
        printf("Enter the maximum seats in the restaurant\n");
        scanf("%d",&(head->MaxSeats));
        head->nextR=temp;
        temp=head;
    }
    return head;
}
struct User* initUser(struct User* head){
    struct User* temp=NULL;
    int i,n;
    printf("Enter the number of users\n");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        head=(struct User*)malloc(sizeof(struct User));
        printf("Enter the name of the User\n");
        scanf("%s",head->nameU);
        printf("Enter the address of the User\n");
        scanf("%s",head->addU);
        printf("Enter the user phone number\n");
        scanf("%s",head->phoneU);
        head->IDU=i+1;
        head->nextU=temp;
        temp=head;
    }
    return head;
}
struct Agent* initAgent(struct Agent* head){
    struct Agent* temp=NULL;
    int i,n;
    printf("Enter the number of agents\n");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        head=(struct Agent*)malloc(sizeof(struct Agent));
        printf("Enter the name of the Agent\n");
        scanf("%s",head->nameA);
        printf("Enter the address of the Agent\n");
        scanf("%s",head->add);
        printf("Enter the agent phone number\n");
        scanf("%s",head->phoneA);
        head->IDA=i+1;
        head->ava=1;
        head->nextA=temp;
        temp=head;
    }
    return head;
}
void SearchBasedOnCategory(struct Rest* head, char ptr[]){
    int i;
    printf("The results of given category are\n");
    for(i=0;i<5;i++){
        if(strcmp(ptr,head->category)==0){
            printf("%s\n",head->nameR);
        }
        head=head->nextR;
    }
}
void SearchBasedOnCuisine(struct Rest* head, char ptr[]){
    int i,j;
    printf("The given cuisine can be found here\n");
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(strcmp(ptr,head->menu[j])==0){
                printf("%s\n",head->nameR);
            }
        }
        head=head->nextR;
    }
}
void SearchBasedOnArea(struct Rest* head, char ptr[]){
    int i;
    printf("The Restaurants in given area are\n");
    for(i=0;i<5;i++){
        if(strcmp(ptr,head->addR)==0){
            printf("%s\n",head->nameR);
        }
        head=head->nextR;
    }
}

void PrintAgent(struct Agent* head){
    printf("All agent's details are as follows...\n");
    while(head!=NULL){
        printf("Agent ID: %d\n",head->IDA);
        printf("Agent name: %s\n",head->nameA);
        printf("Working area: %s\n",head->add);
        printf("Agent's contact details: %s\n",head->phoneA);
        if(head->ava==1){
            printf("Agent available for service\n");
        }
        else{
            printf("Agent currently not available\n");
        }
        printf("\n");
        head=head->nextA;
    }
}
void PrintLiveOrders(struct Order* head){
    if(head==NULL){
        printf("No live order present\n");
    }
    else{
        while(head!=NULL){
            printf("Live orders are...\n");
            printf("Order number: %d\n",head->orderno);
            printf("Order of %s for %s to be delivered from restaurant %s\n",head->item,head->name,head->rest);
            printf("\n");
            head=head->next;
        }
    }
}
void PrintAreawiseAgent(struct Agent* head, char area[]){
    printf("Agents currently  in the area are:\n");
    while((head!=NULL)&&(strcmp(head->add,area)!=0)){
        head=head->nextA;
    }
    printf("%s\n",head->nameA);
}
void PrintRestaurant(struct Rest* head){
    int i;
    printf("Following are  the restaurant associated with us\n");
    while(head!=NULL){
        printf("Restaurant name: %s\n",head->nameR);
        printf("Category of restaurant: %s\n",head->category);
        printf("Total seats: %d\n",head->MaxSeats);
        printf("Restaurant address: %s\n",head->addR);
        printf("The menu: ");
        for(i=0;i<5;i++){
            printf("%s ",head->menu[i]);
        }
        printf("\n\n");
        head=head->nextR;
    }
}
void main(){
    int x,i,f=1;
    char a[30],b[30],c[30],d[30];
    printf("Initialize the database\n");
    struct Rest* rest=NULL;
    struct User* user=NULL;
    struct Agent* agent=NULL;
    struct Order* o=NULL;
    printf("Initialize restaurants\n");
    rest=initRest(rest);
    user=initUser(user);
    agent=initAgent(agent);
    printf("Following are the services we provide:\n");
    printf("Search:\n1. Based on category\n2. Based on cuisine\n3. Based on area\n");
    printf("Order:\n4. Place order\n5. Delivery\n6. Cancel order\n");
    printf("Show details:\n7. Print agent list with details\n8. Print live orders\n9. Print area wise agents\n10. Print all restaurant details\n11. Exit\n");
    printf("Enter index number of the service you want...\n");
    while(f==1){
        scanf("%d",&x);
        switch(x){
            case 1: printf("Enter the category\n");
                    scanf("%s",a);
                    SearchBasedOnCategory(rest,a);
                    break;
            case 2: printf("Enter cuisine\n");
                    scanf("%s",b);
                    SearchBasedOnCuisine(rest,b);
                    break;
            case 3: printf("Enter area\n");
                    scanf("%s",c);
                    SearchBasedOnArea(rest,c);
                    break;
            case 4: printf("Enter number of orders\n");
                    scanf("%d",&i);
                    //o=placeOrder(o,i,rest,user,agent);
                    break;
            case 5: //Delivery(o,agent);
                    break;
            case 6: printf("Enter the order number to cancel\n");
                    scanf("%d",&i);
                   // Cancel(o,agent,i);
                    break;
            case 7: PrintAgent(agent);
                    break;
            case 8: PrintLiveOrders(o);
                    break;
            case 9: printf("Enter the area\n");
                    scanf("%s",d);
                    PrintAreawiseAgent(agent,d);
                    break;
            case 10:PrintRestaurant(rest);
                    break;
            case 11:f=0;
                    break;
        }
    }
}
