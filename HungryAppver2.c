#include "HungryApp.h"
struct Rest* initRest(struct Rest* head){
    struct Rest* temp=NULL;
    int i,j;
    for(i=0;i<5;i++){
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
    int i;
    for(i=0;i<5;i++){
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
    int i;
    for(i=0;i<5;i++){
        head=(struct Agent*)malloc(sizeof(struct Agent));
        printf("Enter the name of the Agent\n");
        scanf("%s",head->nameA);
        printf("Enter the address of the Agent\n");
        scanf("%s",head->Add);
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
struct Order* placeOrder(struct Order* head1, int n, struct Rest* head2, struct User* head3, struct Agent* head4){
    struct Order* temp1, *temp2,*temp=NULL;
    int i;
    temp1=head3;
    temp2=head4;
    for(i=0;i<n;i++){
        head1=(struct Order*)malloc(sizeof(struct Order));
        printf("Enter name of user\n");
        scanf("%s",head1->name);
        printf("Enter name of restaurant\n");
        scanf("%s",head1->rest);
        printf("Enter name of item to order\n");
        scanf("%s",head1->item);
        (head1->orderno)=order+1;
        order++;
        head1->next=temp;
        temp=head1;
        head3=temp1;
        while((head3!=NULL)&&(strcmp(head3->nameU,head1->name)!=0)){
            head3=head3->nextU;
        }
        if(head3==NULL){
            printf("User does not exist\n");
        }
        else{
            head4=temp2;
            while((head4!=NULL)&&((head4->ava!=1)&&strcmp(head4->Add,head3->addU)!=0)){
                head4=head4->nextA;
            }    //User details are known now assign details to agent
            if(head4==NULL){
                printf("No Agent free at this moment\n");
            }
            else{
                head1->agentAssg=head4->IDA;
                head4->ava=0;
                printf("Details of Order:\n");                      //prints details  of order one at time
                printf("Order number: %d\n",head1->orderno);
                printf("Ordered from restaurant %s\n",head1->rest);
                printf("Delivery to %s\n",head1->name);
                printf("Delivery Agent assigned %s\n",head4->nameA);
                printf("Order placed and will reach you shortly\n");
            }
        }
    }
    return head1;
}
 struct Order* DeleteNode(struct Order **head, int x, struct Agent* a){
    struct Order* prev, *temp= *head;
    prev=head;
    if(temp!=NULL && temp->orderno==x){
        *head=temp->next;
        while(a!=NULL){
            if(a->IDA==temp->agentAssg){
                a->ava=1;
            }
            a=a->nextA;
        }
        free(temp);
        temp=NULL;
        return *head;
    }
    while(temp!=NULL && temp->orderno!=x){
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        return *head;
    }
    while(a!=NULL){
        if(a->IDA==temp->agentAssg){
            a->ava=1;
        }
        a=a->nextA;
    }
    prev->next=temp->next;
    free(temp);
    temp=NULL;
    return *head;
}
struct Order* Delivery(struct Order* head, struct Agent* head1){
    int x;
    printf("Enter the order number which is completed\n");
    scanf("%d",&x);
    head=DeleteNode(&head, x, head1);
    return head;
}
struct Order* Cancel(struct Order* head, struct Agent* head1){
    int x;
    printf("Enter the order number to cancel\n");
    scanf("%d",&x);
    head=DeleteNode(&head,x,head1);
    printf("Order is canceled\n");
    return head;
}
void PrintAgent(struct Agent* head){
    printf("All agent's details are as follows...\n");
    while(head!=NULL){
        printf("Agent name: %s\n",head->nameA);
        printf("Agent ID: %d\n",head->IDA);
        printf("Agent's current working area: %s\n",head->Add);
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
        order=0;
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
    while(head!=NULL){
        if(strcmp(head->Add,area)==0){
            printf("%s\n",head->nameA);
        }
        head=head->nextA;
    }
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
    while(f==1){
        printf("\n");
        printf("Following are the services we provide:\n");
        printf("Search:\n1. Based on category\n2. Based on cuisine\n3. Based on area\n");
        printf("Order:\n4. Place order\n5. Delivery\n6. Cancel order\n");
        printf("Show details:\n7. Print agent list with details\n8. Print live orders\n9. Print area wise agents\n10. Print restaurant details\n11. Exit\n");
        printf("Enter index number of the service you want...\n\n");
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
                    o=placeOrder(o,i,rest,user,agent);
                    break;
            case 5: o=Delivery(o,agent);
                    break;
            case 6: o=Cancel(o,agent);
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
