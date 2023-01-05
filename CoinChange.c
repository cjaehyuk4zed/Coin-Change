#include <stdio.h>
#include <stdlib.h>

// Coin Change algorithm by Jaehyuk Chang
// The goal of this algorithm is to give 'change' to a person
// Using the least number of coins in total

// The main algorithm for calculating the change to be given
void calc(int val, int* cnum, int* coin, int** clist, int num){
    int idx, tmp;
    int prev_total = INT_MAX;
    int new_total = 0;
    int* cnum_tmp = (int*)malloc(sizeof(int)*num);

    for(int i=num-1;i>=0;i--){
        new_total = 0;
        tmp = val; // tmp variable to keep original value of 'val' for loop
        for(int i=0;i<num;i++){ // reset values of tmp=val, and cnum_tmp to 0
            *(cnum_tmp+i) = 0;
        }
        if(*(coin+i) <= tmp){
            tmp = tmp - *(coin+i);
            *(cnum_tmp+i) = *(cnum_tmp+i) + 1;
            //printf("cnum_tmp[%d] : %d\n", i, *(cnum_tmp+i));
        }

        if(tmp > 0 && tmp != val){ // add pre-calculated values in previous index - dynamic programming
            idx = tmp / *coin; // index of pre-calculated values to be added
            //printf("change : %d\n", val);
            for(int i=0;i<num;i++){
                *(cnum_tmp+i) = *(cnum_tmp+i)+*(*(clist+idx)+i);
                //printf("after loop : cnum_tmp[%d] : %d\n", i, *(cnum_tmp+i));
                new_total = new_total + *(cnum_tmp+i);
                //printf("new_total : %d\n", new_total); 
            }
            // if the new calculation has less coins than the previous calculation
            if(new_total < prev_total){ 
                prev_total = new_total;
                for(int i=0;i<num;i++){
                    *(cnum+i) = *(cnum_tmp+i);
                    //printf("cnum_tmp : %d ", *(cnum_tmp + i)); 
                }
            }
        }
        else { // if it's the first in the index, and there are no 'pre-calculated values' to add
            if(tmp != val){ 
                for(int i=0;i<num;i++){
                    *(cnum+i) = *(cnum_tmp+i);
                    //printf("cnum_tmp[%d] : %d ", i, *(cnum_tmp + i)); 
                    //printf("cnum[%d] : %d ", i, *(cnum+i)); 
                }
            break;
            }
        }
    }
    return;
}


int main() {
    int num, change;
    printf("Enter number of coins : ");
    scanf("%d", &num);

    printf("\nEnter the values of each coin : ");
    int *coin; // array for the currency value of the coins 
    coin = (int*)malloc(sizeof(int)*num);
    for(int i=0;i<num;i++){scanf("%d", coin+i);}

    int **clist; // matrix (double pointesr array) for the calculation index
    clist = (int**)malloc(sizeof(int*)*__INT32_MAX__); // INT32_MAX to make an array large enough

    // For easy calculation of min max * idx, start from idx 1
    int max = 1;
    int min = 1;
    int *cnum;
    cnum = (int*)malloc(sizeof(int)*num); // potentially try adding cnum in while loop

    printf("\nEnter the numbers to be calculated : ");
    while(scanf("%d", &change) && change != 0){
        int idx = change / *coin; // make smallest coin be the set unit for counting
        if (max < idx) {max = idx;} // check if the value is already calculated and stored in array
        //printf("idx : %d, min : %d, max : %d\n", idx, min, max); 
        while (min <= max) {
            //printf("current min : %d\n", min);
            for(int i=0;i<num;i++){
                *(cnum+i) = 0;
                clist[min] = 0;
                *(clist+min) = (int*)malloc(sizeof(int));
                clist[min][i] = 0;
            }

            int val = min*(*coin);
            calc(val, cnum, coin, clist, num);
            for(int i=0;i<num;i++){ // until '=num', with final value being total num of coins
                //printf("after calc : i : %d ", i); 
                //printf("cnum[%d] : %d ", i, *(cnum+i));
                *(*(clist+min)+i) = *(cnum+i); 
            }
            min++;
        }

        printf("%d:", change); // print final results
        for(int i=0; i<num;i++){
            printf(" %d(%d)", *(coin+i), *(*(clist+idx)+i));
        }
        printf("\n"); 
    }   
    return 0;
}