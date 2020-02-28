#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>

/* No of threads */
#define Kitne_Threads 4

/*  Gobal Variables  */
char *string, *subString;
int stringSize,subStirngSize; // size of both string
int count =0; //  to count how many substirngs
int start =0; //  to cater the index of the string


void *number_substring(void *); //  thread function
void reader(); // reader  from file
void print(char *,int ); // print string


int main(int argc, char**argv)
{
    reader(); //  reading both strings
    print(string,stringSize); // print the string

    print(subString,subStirngSize); // print the string

    if(stringSize % Kitne_Threads != 0) //  check if even no of threads
    {
        perror("not valid .!!!\n existing the program.!");
        exit(1);
    }
    if(subStirngSize <= (stringSize /Kitne_Threads)) //  checking the substring size
    {
         pthread_t *t; // making  a thread pointer 
        long thread_id =0;
        t  =(pthread_t*) malloc(sizeof(pthread_t)*Kitne_Threads); // allocating
        for(int i=0; i<=stringSize; i++)
        {
            start = i;
             pthread_create(&t[thread_id], NULL, number_substring,NULL); //  checking the substring
             sleep(0.5);
             thread_id++;

        }
           
        for(int i=0;i<Kitne_Threads;i++)
            pthread_join(t[i], NULL); //  waiting for all threads to  finished

        printf("( %s ,  %s) = %d \n",string, subString,count);
    }
  
   
}

void reader()
{
    FILE * file = fopen("strings.txt","r"); //  text file of stirng
    if(file == NULL) //  check if the file is empty
    {
        perror("File not Found..!!!\n");
        exit(1);
    }
    fscanf(file,"%d",&stringSize);
    string = (char*)malloc(sizeof(char)*stringSize); //  alloacting the stirng
    fscanf(file,"%s", string);
    fscanf(file,"%d",&subStirngSize);
    subString = (char*)malloc(sizeof(char)*subStirngSize); // allocating the substring
    fscanf(file,"%s",subString);
}

void print(char *str,int size)
{
    for(int i=0;i <size; i++)
        printf("%c",str[i]);
    
    printf("\n");
}
void *number_substring(void *ptr)
{
     if(string[start] ==  subString[0]) //  check if the first index match if matcehd then countinue 
     {                                  // otherwise leave it 
         int loopcount =0;
         for(int i =0; i<subStirngSize; i++)
         {
             if(string[(start+i)] == subString[i])
             {
                loopcount ++;
            }
        }
        if(loopcount == subStirngSize) //  check if the loopcounter is equal to the substring size
            count++; 
    }
       
    pthread_exit(NULL);
}