/**
 
 CS265 Project 1
 main.c
 Purpose: Perform a brute force attack agianst cipher text.
 
 @author  Manzoor AHMED
 @author  Gaurav  GUPTA
 @version 1.1.0
 @date    10/06/2016
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//checks key for validation
int checkKey(int key);

/*
 * Function: fileManipulation
 * ----------------------------
 *   swaps the the content of a file
 *
 *   arr    : data from file
 *   rows   : number of blocks
 *   key    : the key to encrypt or decrypt
 *   choice : 1 for encrypting, 2 for decrypting
 *
 *   returns: 1, 0 success or failier
 */

int fileManipulation(int arr[][7], int rows, int totalChar){
	
    //file name
    char fileName[100];
	
    FILE *fp1;
	
    int tempKey, key, indexVal=0, indexRev = 6;
	//block for storing swapped characters
    char c[7];
    
    int tries = 0;
	
    fp1 = fopen("cipherCrack.txt","a+");
	
    if(fp1){
        
        //generate keys...
		for(key =1234567; key<=7654321; key++){
			
            
            tempKey = key;
            if(checkKey(tempKey)){
                
        
                printf("\n TRY: %d KEY:  %d \n", tries , key);
            
                
                //fputs("\n TRY: %d KEY:  %d \n", tries , key);
                
                for(int indexRow=0; indexRow<=rows; indexRow++){
				
                    for(int indexCol=0;indexCol<7;indexCol++){
					
                        indexVal = tempKey%10;
					
                        indexVal = indexVal-1;
					
                        tempKey = tempKey/10;
					
                        //store
                        c[indexRev] = arr[indexRow][indexVal];
					
                        indexRev--;
                    }
                
                    indexRev = 6;
				
                    tempKey =key;
				
                    for(int tempIndex = 0; tempIndex < 7; tempIndex++) {
                    
                        fputc(c[tempIndex], fp1);
                        putchar(c[tempIndex]);
                    }
                }
        
                printf("\n");
            
               fputs("\n",fp1);
               fputs("\n",fp1);
                
                tries++;
            }//if
        }//for
        
        printf("TRYIES : %d ", tries);
        fclose(fp1);
        
		return 1; // success
	}
	else
		return 0; // failure
	
}
/*
 * Function: implementation
 * ----------------------------
 *   cleans the content of a file
 
 *   choice : 1 for encrypting, 2 for decrypting
 *
 *   returns: 1, 0 success or failier
 */

int implementation(){
	char fileName[100];
	int buff, count =0, index=0, total, key , flag = 1, success = 0;
	FILE *fp;    
	printf("\n Enter the file name that you want to Decrypt(without the .txt extension)\t");
	scanf("%s", fileName);
	strcat(fileName,".txt");
	fp = fopen(fileName, "r");
	if(fp){
		fseek(fp, 0, SEEK_END);
			total = ftell(fp);
			printf("%d", total);
			fseek(fp, 0, SEEK_SET);
			int rows = (total/7)+1;
			int arr[rows][7];
			printf("\n");
			while((buff = getc(fp)) != EOF){
				if(isspace(buff))
					continue;
				if(count%7==0 && count != 0)
					index = index+1;
				arr[index][count%7] = buff;
				//putchar(buff);
				count++;
			}
			printf("\n\n");
		
		success = fileManipulation(arr, index, count);
		fclose(fp);
		if(success == 0)
			return 0;
		else
			return 1;
	}
	else{
			printf("No such file exist");
			return 0;
	}		
}

int checkKey(int key){
    
    int checker = 0, value = 0, x = 0, flag = 1;
    
    if( key > 7654321 || key < 1234567 ){
        
        printf("flag set to 0 in key boundry");
        
        return 0;
    }
    else {
        
        //check all degits
        for(int index=0; index<7;index++) {
            
            // if degit is 8, 9 or 0
            if((key %10 ) > 7 || (key %10) ==0) {
                
                //invalid
                flag =0;
                break;
            }
            
            value = key % 10;
            
            key = key / 10;
            
            x = 1<<value ;
            
            if((checker & x)>0) {
                
                //printf("invalid value");
                
                flag =0;
                
                break;
            }
            
            checker = checker | x;
        }
    }
    
    if(flag ==1){
        return 1; //a valid key
    }
    else {
        //printf("\n Invalid Key\n");
        return 0; //invalid key
    }
}


int main() {
	
    int success =0;
   
    //timer
    clock_t start_time;
    clock_t end_time;
    clock_t total_time;
    
    //start
    start_time = clock();
    
    //start the attack
    success = implementation();
    
    //done
    end_time = clock();
    
    //calculte elapsed time
    total_time = (double)(end_time - start_time);
    
    if( success == 1 ){
        
		printf("\n Operation Successfully completed.");
        printf("\n Operation Time:  %lu \n\n", total_time);
    }
    
    else{
        printf("\n Operation Failed");
        return 0;
    }
}
