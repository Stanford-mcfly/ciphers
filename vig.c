
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

 void upper(char* s){
  for (int i = 0; s[i]!='\0'; i++) {
      if(s[i] >= 'a' && s[i] <= 'z') {
         s[i] = s[i] -32;
      }
   }
 }

 char* encryption(char* msg , char* key){
    int msgLen = strlen(msg), keylen = strlen(key), i, j;
    char* encryptedMsg = (char*)malloc(sizeof(char)*msgLen+1);
    for(i = 0, j=0; i < msgLen; ++i,++j){

        if(!isalpha(msg[i])){
        encryptedMsg[i] = msg[i];
        continue;
        }

        if(isupper(msg[i]))
        encryptedMsg[i] = ((msg[i] + key[i%keylen]) % 26) + 'A';

        else if(islower(msg[i]))
        encryptedMsg[i] = tolower(((toupper(msg[i]) + key[i%keylen]) % 26) + 'A');

    }

    encryptedMsg[i] = '\0';
    return encryptedMsg;

 }

char* decryption(char * encryptedMsg, char* key){
      int msgLen = strlen(encryptedMsg), keylen = strlen(key), i, j;
      char* decryptedMsg = (char*)malloc(sizeof(char)*msgLen+1);

      for(i = 0; i < msgLen; ++i){

        if(!isalpha(encryptedMsg[i])){
        decryptedMsg[i] = encryptedMsg[i];
        continue;
        }

        if(isupper(encryptedMsg[i]))
        decryptedMsg[i] = (((encryptedMsg[i] - key[i%keylen]) + 26) % 26) + 'A';
        
        else if(islower(encryptedMsg[i]))
        decryptedMsg[i] = tolower((((toupper(encryptedMsg[i]) - key[i%keylen]) + 26) % 26) + 'A');
      }

    decryptedMsg[i] = '\0';
    return decryptedMsg;
}
int main(){
  FILE * f , * fp;
  char dir[] = "files";
  char back[] = "\\";
  char* enc , * dec ,* buff = NULL;
  char de[] = "decrypt.txt";
  char en[] = "encrypt.txt";
  char temp[100] , key[100];
  int c = mkdir(dir);
  int choice , k;
  char filename[100];
  printf("WHAT DO YOU WANT TO DO ?  \n 1.ENCRYPTION \n 2.DECRYPTION \n 3.EXIT \n ENTER THE CHOICE :");
  scanf("%d",&choice);
  while(choice!=3){
    switch(choice){
      case 1 :
      printf("Enter the file name : ");
      scanf("%s",filename);
      printf("\nEnter the key : ");
      scanf("%s",key);
      upper(key);
      f = fopen(filename,"r");
      if(f==NULL) printf("file is not opened.");
      fseek(f,0,SEEK_END);
      k = ftell(f);
      rewind(f);
      strcpy(temp,dir);
      strcat(temp,back);
      strcat(temp,en);
      fp = fopen(temp,"w");
      getdelim( &buff, &k, '\0', f); 
      enc = encryption(buff,key);
      fputs(enc,fp);
      fclose(f);
      fclose(fp);
      break;

      case 2 :
      printf("Enter the file name : ");
      scanf("%s",filename);
      printf("\nEnter the key : ");
      scanf("%s",key);
      upper(key);
      f = fopen(filename,"r");
      if(f==NULL) printf("file is not opened.");
      fseek(f,0,SEEK_END);
      k = ftell(f);
      rewind(f);
      strcpy(temp,dir);
      strcat(temp,back);
      strcat(temp,de);
      fp = fopen(temp,"w");
      getdelim( &buff, &k, '\0', f); 
      dec = decryption(buff,key);
      fputs(dec,fp);
      fclose(f);
      fclose(fp);
      break;

      default:
      printf("\n Enter a valid choice :");
      break;

    }
    strcpy(temp,"");
    printf("\nENTER THE CHOICE :");
    scanf("%d",&choice);
  }

  return 0;
}
