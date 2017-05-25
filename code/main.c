/**
 
 CS265 Project 1
 main.c
 Purpose: encrypt and decrypt LETTER TO THE TEMPLARS - PART 3.
 
 @author  Manzoor AHMED
 @author  Gaurav  GUPTA
 @version 1.1.0
 @date    10/04/2016
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//checks key for validateion
int checkKey(int key);

//manipulates file data by shifting elements with given key
int fileManipulation(int arr[][7], int rows, int Key, int choice);

// encrypt or decrypt based on given choice
int implementation(int choice);


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

int fileManipulation(int arr[][7], int rows, int Key, int choice){
	
    //name of the file
	char fileName[100];
    
    FILE *fp1;
	
    int tempKey = Key, indexVal=0, indexRev = 6;
	//block for storing swapped characters
    char c[7];

    //user wants to encrypt a file
	if(choice ==1){
        
		printf("\n File name to save cipher text (without .txt extension) >> ");
		scanf("%s", fileName);
		strcat(fileName,".txt");
		fp1 = fopen(fileName,"w");
        
        //make sure file exists
		if(fp1){
            
            //each row
            for( int indexRow=0; indexRow <= rows; indexRow++ ){
                
                //each block
                for( int indexCol=0; indexCol < 7; indexCol++ ){
                    
                    //get each digit
                    indexVal = tempKey%10;
                    
                    indexVal = indexVal-1;
                    
                    //next key digits..
                    tempKey = tempKey/10;
                    
                    //store at indexVal position
                    c[indexVal] = arr[indexRow][indexRev];
                    
                    indexRev--;
                }
                
                //reset
                indexRev = 6;
                tempKey =Key;
                
                //save and print each block of data
                for(int tempIndex = 0; tempIndex < 7; tempIndex++){
                    
                    fputc(c[tempIndex], fp1);
                    
                    putchar(c[tempIndex]);
                }
            }
            fclose(fp1);
            return 1; // success
		}
        else{
			return 0; // failure
        }
	}
    //user wants to decrypt 
	else if(choice ==2){
		
        printf("\n File name to save plain text (without .txt extension) >> ");
		
        scanf("%s", fileName);
		
        strcat(fileName,".txt");
		
        fp1 = fopen(fileName,"w");
		
        if(fp1){
            
            //each rows
			for(int indexRow=0; indexRow<=rows; indexRow++){
				
                //each column
                for(int indexCol=0;indexCol<7;indexCol++){
					
                    //each digit of the key
                    indexVal = tempKey % 10;
					
                    indexVal = indexVal - 1;
					
                    //next key digits...
                    tempKey = tempKey / 10;
					
                    //store
                    c[indexRev] = arr[indexRow][indexVal];
					
                    indexRev--;
                    
				}//for
                
				indexRev = 6;
				tempKey =Key;
				
                //each block of data
                for(int tempIndex = 0; tempIndex < 7; tempIndex++) {
					
                    //save in file
                    fputc(c[tempIndex], fp1);
					
                    //print
                    putchar(c[tempIndex]);
                    
				}//for
                
			}//for
            
			fclose(fp1);
            
			return 1; // success
		}//if
        else{
			return 0; // failure
        }
	}
    else{
        return 0;
    }
}
/*
 * Function: implementation
 * ----------------------------
 *   cleans the content of a file
 
 *   choice : 1 for encrypting, 2 for decrypting
 *
 *   returns: 1, 0 success or failier
 */

int implementation(int choice){
	
    char fileName[100];
	int buff, count =0, index=0, total, key, flag = 1, success = 0;
	FILE *fp;    
   
    //user wants to encrypt
    if(choice ==1){
        printf("\n File name to Encrypt ( without the .txt extension ) >> ");
    }
    
    //user wants to decrypt
    else if(choice ==2){
        printf("\n File name to Decrypt ( without the .txt extension ) >> ");
    }
    
    scanf("%s", fileName);
    strcat(fileName,".txt");
	
    fp = fopen(fileName, "r");
    
    if(fp){
		
        printf("\n Enter the Key \t >> ");
		
        scanf("%d",&key);
		
        //validate key first
        flag = checkKey(key);
		
        if(flag!=0){
			
            fseek(fp, 0, SEEK_END);
            
            //file size
			total = ftell(fp);
			
            printf("%d", total);
			
            fseek(fp, 0, SEEK_SET);
			
            //rows of the file
            int rows = (total / 7) + 1;
			
            int arr[rows][7];
		
            printf("\n");
			
            while((buff = getc(fp)) != EOF){
				
                if(isspace(buff))
					//skipp...
                    continue;
				
                if( count % 7 == 0 && count != 0)
					index = index+1;
				
                arr[index][count%7] = buff;
				
                putchar(buff);
				
                count++;
			}//while
            
            printf("\n\n");
		
            //encrypt or decrypt based on choice
            success = fileManipulation(arr, index, key, choice);
		
        }//if
		
        fclose(fp);
        
        if(success ==1){
            return 1;
        }
        else{
            return 0;
        }
	}
    
	else{
            //can't find valid file
			printf("No such file exist");
			return 0;
	}		
}

/*
 * Function: checkKey
 * ----------------------------
 *   checks users given key for validattion
 
 *   choice : 1 for encrypting, 2 for decrypting
 *
 *   returns: 1 for correct key, 0  invalid key
 */

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
                
                printf("invalid value");
                
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
        printf("\n Invalid Key\n");
        return 0; //invalid key
    }
}


int main() {
	
    int choice, success =0;
    int valid = 0; //not valid
    
    printf("\n ***********************************************************************\n");
    printf("\n OPERATIONS \n");
    printf("\n 1 : Encrypt file ");
    printf("\n 2 : Decrypt file ");
    printf("\n 3 : Quit ");
    printf("\n ***********************************************************************");
    printf("\n >> ");
    
    scanf("%d",&choice);
    
    while (valid != 1 ) {
        
        if ( ( choice == 1 ) || ( choice == 2 ) || ( choice == 3) ) {
            
            valid = 1;
            break;
        }
        else{
            
            printf("\n Invalid input, try again\n");
            printf(">>");
            scanf("%d", &choice);
        }
    }
    
    if( ( choice  == 1 ) || ( choice == 2 )){
        
        //do the operation
        success = implementation(choice);
    }
    
    else{
        printf("\n Program exited by user\n");
        return 0;
    }
	
    if(success ==1){
        printf("\n Operation successfully completed\n");
    }
    else{
        printf("\n Operation Failed\n ");
    }
	
    return 0;
}
