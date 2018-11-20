//
//  main.c
// purpose: to interperte the language BF
// Status: done
// problem with this program: uses int instead of short for array. This is a problem as it uses more data than it needs to
#include <stdio.h>
#include <stdlib.h>

const int debugLV = 1;
short debugCounter = 0; //debug counter for checking :-d-e-b-u-g-:
short importCounter = 0; //import counter
short runCounter = 0; //r counter
short zeroCounter = 0; //z counter
/**
 Purpose: 
    To check the input of the array
 Parameter:
    The input
 Return:
    Return the command code to be used in main
 **/
short checkInput(char input);

/**
 Purpose:
    Adding a space to the right of the array
 Parameter: 
    the address of the pointer to the begining of the array and the size
 Return: 
    void
 **/
void addSpaceToRight(int**array, int*arraySize);

/**
 Purpose:
    Adding a space to the left of the array
 Parameter: 
    the adress of the pointer to the begining of the array and the size
 Return: 
    void
 **/
void addSpaceToLeft(int**array, int*arraySize);

/**
 Purpose:
    to do the command given
 Parameter:
    the index, the arraySize of the array and the array, the list, the index and the size of the command list
 Return: 
    whether of not to stop the program because of an error 0 = success, 1 = failure
 **/
int exeCommand(int*index, int*arraySize, int**array,short**commandList, int*commandSize, int*commandIndex);

/**
 Purpose:
    to store commands in a array and repeat them until the current index is zero
 Parameter:
    index, arraySize, array, command list, command index
 Return: 
    if there is an error with the loop 0 = success, 1 = failure
 **/
int initLoop(int*index,int*arraySize, int**array, short**commandList, int*commandSize, int*commandIndex);

/**
 Purpose:
    to add commmand to the list of command this list of array contains
 Parameter:
    short command and the list to add it to
 Return:
    void
 **/
void addCommand(short cmd, int*commandSize, short**commandList);

/**
 Purpose:
    to check if the user typed in "//import" and store the information inside importCounter
 Parameter:
    the input
 Return:
    void
 **/
void checkForImport(char input);

/**
 Purpose:
    to check if the user typed in "//debug" and store the information inside debugcounter
 Parameter:
    the input
 Return:
    void
 **/
void checkForDebug(char input);

/**
 Purpose:
    to check if the user typed in "//z" and store the information inside zeroCounter
 Parameter:
    the input
 Return:
    void
 **/
void checkForZero(char input);

/**
 Purpose:
    to check for the command to run the entered program
 Parameters:
    the input
 Return:
    void
 **/
void checkForRun(char input);

/**
 Purpose:
    collect all the commands from a file and execute all the commands
 Parameters: 
    the adress of the array
 Return:
    0 = success, 1 = failure
 **/
int import(int*index, int*arraySize, int**array);


int main(int argc, const char * argv[]) {
    int index = 0; // the index of which to apply the command
    short command;
    int arraySize = 1; // to keep the size of the array as c cannot get
    int*array = (int*)calloc(0, sizeof(int));
    
    array[0] = 0;
    
    short*cmdList = malloc(sizeof(short));
    cmdList[0]= 0;
    int sizeOfCMDList = 1;
    
    
    // welcome
    printf("Welcome to the BF interperetor.\nFunctions:\n//import < import from a outside sorce\n//r < run\n//debug < view the array \n//z < reset array \n\ncode starts here:\n");
    
    while (1) {
        while (command != 12) {
            // //r was not writen; continue reading input
            char input;
            scanf(" %c", &input);
            command = checkInput(input);
            
            addCommand(command, &sizeOfCMDList, &cmdList);
            
            if (command == 10) {
                
                //print out the array for debug (cmd 10 means //debug was entered)
                printf("size: %d\nindex: %d",arraySize,index);
                printf("\n|");
                for (int i = 0; i<arraySize; i++) {
                    printf("%d|", (array)[i]);
                }
                printf("\n");
                
            } else if (command == 11) {
                
                //print out the array for import (cmd 11 means //import was entered)
                import(&index, &arraySize, &array);
                
            } else if (command == 13) {
                
                //print out the array for import (cmd 13 means //z was entered)
                //reset the array
                free(array);
                arraySize=1;
                array = (int*)calloc(0, sizeof(int));
                array[0] = 0;
                index = 0;
            }
        }
        
        int*copy = (int*)calloc(arraySize, sizeof(int));
        int copySize = arraySize;
        
        for (int i = 0; i < arraySize; i++) {
            copy[i] = array[i]; // copy of array to the array of copy
        }
        
        for (int i = 0; i < sizeOfCMDList+1; i++) {
            //printf("%d",sizeOfCMDList);
            if(exeCommand(&index, &arraySize, &array, &cmdList, &sizeOfCMDList, &i)){
                // if there is error in exeCommand the array will return to the origional state
                free(array);
                array = malloc(sizeof(int)*copySize);
                
                for (int i = 0; i < copySize; i++) {
                    array[i] = copy[i]; // copy copy[] to the array array[] to return to the origional state
                }
                arraySize = copySize;
            }
        }
        // free and reset everything
        free(cmdList);
        free(copy);
        cmdList = malloc(sizeof(short));
        cmdList[0]=0;
        command = 0;
        sizeOfCMDList = 1;
    }
    return 0;
}


void checkForImport(char input){
    // this will check if import is typed will add one until i = amount of letters
    switch (importCounter) {
        case 0:
            if(input == '/'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 1:
            if(input == '/'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 2:
            if(input == 'i'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 3:
            if(input == 'm'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 4:
            if(input == 'p'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 5:
            if(input == 'o'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 6:
            if(input == 'r'){
                importCounter++;
            }else{
                importCounter=0;
            }
            break;
        case 7:
            if (input == 't') {
                importCounter++;
                
            }else{
                importCounter = 0;
            }
            break;
        default:
            importCounter=0;
            
            
            break;
    }
}

void checkForRun(char input){
    // Addone to counter if the "correct" leter is added, until i = amount of letters
    switch (runCounter) {
        case 0:
            if(input == '/'){
                runCounter++;
            }else{
                runCounter=0;
            }
            break;
        case 1:
            if(input == '/'){
                runCounter++;
            }else{
                runCounter=0;
            }
            break;
        case 2:
            if(input == 'r'){
                runCounter++;
            }else{
                runCounter=0;
            }
            break;
        default:
            runCounter=0;
            break;
    }
}
void checkForDebug(char input){
    // Addone to counter if the "correct" leter is added, until i = amount of letters
    switch (debugCounter) {
        case 0:
            if(input == '/'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        case 1:
            if(input == '/'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        case 2:
            if(input == 'd'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        case 3:
            if(input == 'e'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        case 4:
            if(input == 'b'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        case 5:
            if(input == 'u'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        case 6:
            if(input == 'g'){
                debugCounter++;
            }else{
                debugCounter=0;
            }
            break;
        default:
            debugCounter=0;
            break;
    }
}

void checkForZero(char input){
    // Addone to counter if the "correct" leter is added, until i = amount of letters
    switch (zeroCounter) {
        case 0:
            if(input == '/'){
                zeroCounter++;
            }else{
                zeroCounter=0;
            }
            break;
        case 1:
            if(input == '/'){
                zeroCounter++;
            }else{
                zeroCounter=0;
            }
            break;
        case 2:
            if(input == 'z'){
                
                zeroCounter++;
            }else{
                zeroCounter=0;
            }
            break;
        default:
            zeroCounter=0;
            break;
    }
}


short checkInput(char input){
    checkForDebug(input);
    checkForRun(input);
    checkForImport(input);
    checkForZero(input);
    if(input == '>'){
        // Increment the pointer.
        return 1;
        
    }else if(input == '<'){
        // Decrement the pointer.
        return 2;
        
    }else if(input == '+'){
        // Increment the byte at the pointer.
        return 3;
        
    }else if(input == '-'){
        // Decrement the byte at the pointer.
        return 4;
        
    }else if(input == '.'){
        // Output the byte at the pointer.
        
        return 5;
        
    }else if(input == ','){
        // Input a byte and store it in the byte at the pointer.
        return 6;
        
    }else if(input == '['){
        // Jump forward past the matching ] if the byte at the pointer is zero.
        return 7;
        
    }else if(input == ']'){
        
        // Jump backward to the matching [ unless the byte at the pointer is zero.
        return 8;
    }else{
        if(runCounter == 3){
            runCounter = 0;
            return 12;
        }
        
        if(debugCounter == 7){
            debugCounter = 0;
            return 10;
        }
        
        if(importCounter == 8){
            importCounter = 0;
            return 11;
        }
        
        if (zeroCounter == 3) {
            zeroCounter = 0;
            return 13;
        }
        //invalid input
        return 9;
    }
}

void addSpaceToLeft(int**array, int*arraySize){
    
    (*arraySize)++;
    //adding one to the size of the array
    *array = (int*) realloc(*array,(*arraySize)*sizeof(int));
    // reallocating array so that I could have more space
    for (int i = (*arraySize)-1; i>0; i--) {
        // moving everything one to the right so the it would give the illusion of getting a extra space to the left.
        (*array)[i] = (*array)[i-1];
    }
    //all the added arrays start at zero
    (*array)[0] = 0;
    
}

void addSpaceToRight(int**array, int*arraySize){
    (*arraySize)++;
    //adding one to the size of the array
    *array = (int*) realloc(*array,(*arraySize)*sizeof(int));
    (*array)[(*arraySize)-1] = 0; // seting the new array to zero
}

int exeCommand(int*index, int*arraySize, int**array, short**commandList, int*commandSize, int*commandIndex){
    //checking the command and exacuting
    switch ((*commandList)[*commandIndex]) {
        case 1:
            // > is entered
            
            if(*index == *arraySize-1){
                //if there are no spaces right I will add one and move right
                (*index)++;
                addSpaceToRight(array,arraySize);
            }else{
                //there are availble space on right of index
                (*index)++;
            }
            
            break;
        case 2:
            // <
            if(*index == 0){
                //if there are no spaces left I will add one to left
                addSpaceToLeft(array,arraySize);
            }else{
                //there are availble space on left of index
                (*index)--;
            }
            
            break;
        case 3:
            // +
            (*array)[*index]++;
            if((*array)[*index] == 256){
                (*array)[*index] = 0;
            }
            break;
        case 4:
            // -
            (*array)[*index]--;
            if((*array)[*index] == -1){
                (*array)[*index] = 255;
            }
            break;
        case 5:
            // .
            printf("%c",(char)(*array)[*index]);
            break;
        case 6:
            // ,
            {
            char c;
            scanf("%c", &c);
            ((*array)[*index]) = (int)c;
            }
            
            fgetc(stdin);
            break;
        case 7:
            // [
            return initLoop(index, arraySize, array, commandList, commandSize, commandIndex);
            break;
        case 8:
            // ]
            
            break;
        default:
            // invalid
            break;
    }
    return 0; //success
}

int initLoop(int*index,int*arraySize, int**array, short**commandList, int*commandSize, int*commandIndex){
    // index is the current index
    //remember when the loop starts (the index)
    int cmdStartID = *commandIndex + 1;
    
    
    //execution phase
    while ((*array)[*index]){
        // while the current variable is not zero
        
        *commandIndex = cmdStartID; // go to start of loop
        //printf("c: %d\n", (*commandList)[(*commandIndex)]);
        //printf("i: %d\n", (*array)[*index]);
        
        while ((*commandList)[(*commandIndex)] != 8 ) {
            // will command index be on back of loop?
            
            
            if(exeCommand(index, arraySize, array,commandList, commandSize, commandIndex)){
                //return 1 if there is error with the next exeCommand
                return 1;
            }
            
            if(*commandIndex < *commandSize){
                // if there are commands left
                (*commandIndex)++;
            }else{
                // there is no ] so there is an error
                printf("Error: expected ] at the end.\n");
                return 1;
            }
        }
    }
    
    return 0;
}

void addCommand(short cmd, int*sizeOfList, short**commandList){
    
    (*sizeOfList)++;
    *commandList = (short*) realloc(*commandList, (*sizeOfList)*sizeof(short));
    (*commandList)[(*sizeOfList)-1] = cmd;
}


int import(int*index, int*arraySize, int**array){
    //variables
    FILE * file;
    short*cmdList = malloc(sizeof(short));
    cmdList[0]= 0;
    int sizeOfCMDList = 1;
    char*pathin = malloc(sizeof(char));
    int pathSize = 0;
    
    printf("path (end in *): ");
    
    while(pathin[pathSize-1] != '*'){
        //while the user is not done entering a path, keep getting input
        pathSize++;
        pathin = realloc(pathin, pathSize * sizeof(char));
        char input;
        scanf("%c", &input);
        pathin[pathSize-1] = input;
    }
    
    
    // put path into a string
    char pathAsString[pathSize-2];
    for (int i = 1; i < pathSize-1; i++) {
        pathAsString[i-1] = pathin[i];
    }
    
    //printf("path: ");
    //printf("%s",pathAsString);
    
    file = fopen(pathAsString, "r");
    
    if(file != NULL){
        // file is runnable
        printf("\nProgram Start\n");
        while (!feof(file)) {
            short command;
            char character;
            fscanf(file, "%c", &character);
            //scan char by char
            command = checkInput(character);
            addCommand(command, &sizeOfCMDList, &cmdList);
        }
        for (int i = 0; i < sizeOfCMDList+1; i++) {
            //printf("%d",sizeOfCMDList);
            // run command
            if(exeCommand(index, arraySize, array, &cmdList, &sizeOfCMDList, &i)){
                free(cmdList);
                free(pathin);
                fclose(file);
                return 1;
            }
        }
    }else{
        
        // file is NULL meaning that it cannot be found
        printf("\nError: cannot find file\n");
        
        // free it
        free(cmdList);
        free(pathin);
        fclose(file);
        
        return 1;
    }
    
    // free it
    free(cmdList);
    free(pathin);
    
    fclose(file);
    return 0;
}
