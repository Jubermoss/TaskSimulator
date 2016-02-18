//
//  Simulator.cpp
//  ProcessSimulator
//
//  Created by J. Manuel Mosso on 2/12/15.
//  Copyright © 2015 J. Manuel Mosso. All rights reserved.
//

//v0.01ALPHA

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#define DIF !=

struct nodo *listaG;
int cuantum=5, memoria=1024;
typedef struct nodo *APNODO;
struct nodo {
    int id;
    int size;
    int time;
    APNODO sigte;
};

#define ID(l) ((l)->id)
#define SIZE(l) ((l)->size)
#define TIME(l) ((l)->time)
#define SIGTE(l) ((l)->sigte)

void implista(APNODO lista){
    printf("    ");
    for (;lista DIF NULL;lista=SIGTE(lista))
        printf("[P%d|%ds|%d]->",ID(lista),TIME(lista),SIZE(lista));
    printf("\n");
}

APNODO nuevo (int id,int size,int time){
    APNODO aprnvo;
    aprnvo=(APNODO)malloc(sizeof (struct nodo));
    ID(aprnvo)=id;
    SIZE(aprnvo)=size;
    TIME(aprnvo)=time;
    SIGTE(aprnvo)= NULL;
    return aprnvo;
}



int Alta(void){
    struct nodo *p,*t,*s;
    int i=0,n,size,time,id;
    
    printf("          How many processes are going to enter?  ");
    scanf("%d",&n);
    printf("\n           > PROCESS %d",i);
    printf("\n\n             Size: ");
    scanf("%d",&size);
    memoria=memoria-size;
    if(memoria<0){
        memoria=memoria+size;
        printf("\n   Available memory exceeded: %d",memoria);
        getchar();
        return -1;
    }
    printf("             Execution time: ");
    scanf("%d",&time);
    id=i;
    
    p=nuevo(id,size,time);
    i++;
    t=p;
    while(i<n){
        id=i;
        printf("\n           > PROCESS %d",i);
        printf("\n\n             Size: ");
        scanf("%d",&size);
        memoria=memoria-size;
        if(memoria<0){
            memoria=memoria+size;
            printf("\n    Available memory exceeded: %d",memoria);
            implista(p);
            listaG=p;
            return i;
        }
        printf("             Execution time: ");
        scanf("%d",&time);
        s=nuevo(id,size,time);
        SIGTE(t)=s;
        t=s;
        i++;
    }
    implista(p);
    listaG=p;
    return n-1;
}

int insertar(APNODO lista,int id, int size,int time){
    struct nodo *t,*q;
    
    t=lista;
    while(SIGTE(t) DIF NULL){
        t=SIGTE(t);
    }
    q=nuevo(id+1,size,time);
    SIGTE(t)=q;
    return id+1;
}

bool liberar(APNODO lista,APNODO t){
    struct nodo *q,*l;
    
    if(SIGTE(lista) == NULL){
        free(lista);
        lista=NULL;
        return true;
    }
    if(lista==t){
        q=lista;
        lista=SIGTE(q);
        listaG=SIGTE(q);
        t=SIGTE(q);
        free(q);
        return false;
    }
    if(SIGTE(t)==NULL){
        q=lista;
        while(SIGTE(q) DIF NULL){
            l=q;
            q=SIGTE(q);
        }
        SIGTE(l)=NULL;
        t=l;
        free(q);
        return false;
    }
    

    q=lista;
    l=t;
    while(SIGTE(q) DIF t){
        q=SIGTE(q);
    }
    SIGTE(q)=SIGTE(t);
    t=SIGTE(t);
    free(l);
    return false;
}

APNODO liberart(APNODO lista,APNODO t){
    struct nodo *q,*l;
    
    if(SIGTE(lista) == NULL){
        free(lista);
        lista=NULL;
        listaG=NULL;
        return NULL;
    }
    if(lista==t){
        q=lista;
        lista=SIGTE(q);
        listaG=SIGTE(q);
        t=SIGTE(q);
        free(q);
        return t;
    }
    if(SIGTE(t)==NULL){
        q=lista;
        while(SIGTE(q) DIF NULL){
            l=q;
            q=SIGTE(q);
        }
        SIGTE(l)=NULL;
        t=lista;
        free(q);
        return t;
    }
    q=lista;
    l=t;
    while(SIGTE(q) DIF t){
        q=SIGTE(q);
    }
    SIGTE(q)=SIGTE(t);
    t=SIGTE(t);
    free(l);
    return t;
}


int eliminar(APNODO lista, int id, int n){
    struct nodo *q;
    bool band=true;
    
    q=lista;
    while(ID(q)DIF id && band==true){
        if(SIGTE(q) DIF NULL){
            
            q=SIGTE(q);
        }
        else{
            band=false;
        }
    }
    if(band==false){
        printf("\n\n      The process was not found");
        getchar();
        return n;
    }
    else{
        memoria=memoria+SIZE(q);
        liberar(lista,q);
    }
    return n-1;
}

void modificar(APNODO lista, int id, int size, int time){
    struct nodo *q;
    bool band=true;
    
    q=lista;
    while(ID(q)DIF id && band==true){
        if(SIGTE(q) DIF NULL){
            q=SIGTE(q);
        }
        else{
            band=false;
        }
    }
    if(band==false){
        printf("\n\n      The process was not found");
        getchar();
    }
    else{
        
        memoria=memoria-size+SIZE(q);
        if(memoria<0){
            memoria=memoria+size;
            printf("\n**Available memory exceeded: %d",memoria);
            exit(0);
        }
        SIZE(q)=size;
        TIME(q)=time;
        
    }
}

int simular(void){
    struct nodo *t,*l;
    bool band;
    
    
    t=listaG;
    printf("         PROCESS LIST TO SIMULATE: \n\n");
    implista(listaG);
    while(listaG DIF NULL){
        t=listaG;
        for (;t DIF NULL;){
            for(int i=0;i<cuantum && TIME(t)>0;i++){
                TIME(t)=TIME(t)-1;
            }
            if(TIME(t)<=0){
                t=liberart(listaG,t);
            }
            else{
                t=SIGTE(t);
            }
            getchar();
            implista(listaG);
        }
        
        
    }
    return 0;
}




int main(void){
    int OPC,x,n,size,time,id,id2;
    bool verifica=false;
    
    
    while(OPC DIF 7)
    {
        system("clear");
        printf("\n            ==========================================");
        printf("\n                 PROCESS SIMULATOR v0.01ALPHA   \n");
        printf("            ==========================================\n\n");
        printf("\n             CUANTUM: %ds     AVAILABLE MEMORY: %d",cuantum,memoria);
        printf("\n            -------------    -------------------------");
        printf("\n\n          * * * * * * * * * * * * * * * * * * * * * * *");
        printf("\n          *                                           *");
        printf("\n          *                   OPTIONS                 *");
        printf("\n          *                                           *");
        printf("\n          *  1.- ADD TASKS                            *");
        printf("\n          *  2.- INSERT TASK                          *");
        printf("\n          *  3.- DELETE TASK                          *");
        printf("\n          *  4.- UPDATE TASK                          *");
        printf("\n          *  5.- SHOW TASKS LIST                      *");
        printf("\n          *  6.- SIMULATE                             *");
        printf("\n          *  7.- EXIT                                 *");
        printf("\n          *                                           *");
        printf("\n          * * * * * * * * * * * * * * * * * * * * * * *");
        
        printf( "\n\n\n             > CHOOSE THE OPTION: " );
        scanf( "%d", &OPC );
        
        switch ( OPC )
        {
            case 1 : printf( "\n\n                    ADD TASKS   \n" );
                printf("                  --------------------\n\n");
                n=Alta();
                id2=n;
                if(n>=0)
                    verifica=true;
                break;
            case 2 : printf( "\n\n                  INSERTED A NEW TASK\n" );
                printf("                -------------------------------\n\n");
                if(verifica==false){
                    printf("        There are no tasks in the list  ");
                    getchar();
                }
                else{
                    printf("                    Size: ");
                    scanf("%d",&size);
                    memoria=memoria-size;
                    if(memoria<0){
                        memoria=memoria+size;
                        printf("\n**Available memory exceeded: %d",memoria);
                        break;
                    }
                    printf("                    Time: ");
                    scanf("%d",&time);
                    n=insertar(listaG,id2, size, time);
                    id2++;
                }
                
                break;
            case 3 : printf( "\n\n                   DELETE TASK\n" );
                printf("                -------------------------------\n\n");
                if(verifica==false){
                    printf("        There are no tasks in the list  ");
                    getchar();
                }
                else{
                    implista(listaG);
                    printf("\n\n                What task do you want to delete?  ");
                    scanf("%d",&id);
                    n=eliminar(listaG,id,n);
                }
                break;
            case 4 : printf( "\n\n                  UPDATE TASK\n" );
                printf("                ------------------------------\n\n");
                if(verifica==false){
                    printf("        There are no tasks in the list  ");
                    getchar();
                }
                else{
                    implista(listaG);
                    printf("\n\n               What task do you want to update?  ");
                    scanf("%d",&id);
                    printf("\n\n                    Size: ");
                    scanf("%d",&size);
                    memoria=memoria-size;
                    if(memoria<0){
                        memoria=memoria+size;
                        printf("\n**There are no tasks in the list: %d",memoria);
                        break;
                    }
                    memoria=memoria+size;
                    printf("\n                    Time: ");
                    scanf("%d",&time);
                    modificar(listaG,id,size,time);
                }
                break;
            case 5 : printf( "\n\n             THIS IS THE TASKS LIST \n" );
                printf("           --------------------------------------------\n\n");
                if(verifica==false){
                    printf("        There are no tasks in the list  ");
                    getchar();
                }
                else{
                    implista(listaG);
                    getchar();
                }
                break;
            case 6 : printf( "\n\n                   SIMULATING PROCESS\n" );
                printf("                ---------------------------\n\n");
                if(verifica==false){
                    printf("        There are no tasks in the list  ");
                    getchar();
                }
                else{
                    printf("\n");
                    n=simular();
                    printf("\n    END SIMULATION");
                    getchar();
                    verifica=false;
                    
                }
                break;
            case 7 : printf("\n\n    END OF THE PROGRAM\n");
                break;
            default : printf( "\n\n   INVALID OPTION\n\n" );
        }
    }
    getchar();
}


