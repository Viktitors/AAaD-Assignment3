#include <stdio.h>

void main(){
    int i,lorry=4000;
    int numgoods;
    printf("Enter the number of goods:\n");
    scanf("%d", &numgoods);
    int goods[numgoods];
    int solution[numgoods];//EXHAUSTIVITY FROM 0->1-2-3->4 BT.COND
    int LorryFreeSpace[3]={lorry,lorry,lorry};
    for(i=0;i<numgoods;i++){
        printf("Introduce the packet[%d]:\n",i+1);
        scanf("%d",&goods[i]);
        solution[i]=0;       
    }
    switch(backtracking(numgoods,lorry, solution,LorryFreeSpace,goods)){
        case 1:{ 
            printf("Oracle was wrong, the weight of all the goods is greater than the lorries total capacity\n");
            break;
        }
        case 2:{ 
            printf("Oracle was wrong, there is at least 1 packet that weights more than 4000\n");
            break;
        }
        case 3:{
            printf("Oracle was right\n");
            printf("Packet ordering list: ");
            for(i=0;i<numgoods;i++){        
                printf("%d, ",solution[i]);  
            }
            printf("\n");
            break;
        }
        case -1:{ 
            printf("Oracle was wrong, there is no possible combinations to transport all goods\n");
            break;
        }
    }
    system("pause");
}    
int backtracking(int numgoods,int lorry,int solution[], int LorryFreeSpace[], int goods[]){
    int i,sum=0;
    for(i=0;i<numgoods;i++){
        if(lorry<goods[i]){
            return 2;
            break;
        }
        sum+=goods[i];      
    }
    if(sum>(LorryFreeSpace[0]+LorryFreeSpace[1]+LorryFreeSpace[2])){
        return 1;
    }     
    i=0;    
           while(i<numgoods && i>-1){  
            solution[i]++;            
            if(solution[i]==4){         //DEAD NODE-BT FIRING CONDITION
                solution[i]=0; 
                if(i!=0)LorryFreeSpace[solution[i-1]-1]+=goods[i-1];    //undo the recalculation of weights, unless we're in an impossible case, to avoid out of bound errors
                i--;               
            }
            else if( (LorryFreeSpace[ solution[i]-1 ]-goods[i]) >=0 ){       //LIVE NODE                
                LorryFreeSpace[ solution[i]-1 ]-=goods[i];
                i++;
            }                                                          
        }
    if(i==-1)return -1; 
return 3;
}