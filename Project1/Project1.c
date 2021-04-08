//CS 3377 project 1
//Nick Garrett


# include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 64

//variable definitions
int i;
char input[LEN];
char *path = "~";

struct node {
    int data;
    struct node *leftChild, *rightChild;
};



//node *root, *cwd;               //root and cwd pointers

char line[128];                 //user inputStruct
char command[16];               //command and pathname strings
char dname[64], bname[64];      //dirname  and basename string holders
char pathname[64];



//mkdir
int mkdir(char *string, char **terms)
{
    printf("mkdir");
    return -1;
}

//rmdir
int rmdir(char *string, char **terms)
{
    printf("rmdir");
    return -1;
}

//cd
int cd(char *string, char **terms)
{
    printf("cd");
    return -1;
}

//ls
int ls(char *string, char **terms)
{
    printf("ls");
    return -1;
}

//pwd
int pwd(char *string, char **terms)
{
    printf("pwd");
    return -1;
}

//creat
int creat(char *string, char **terms)
{
    printf("creat");
    return -1;
}

//rm
int rm(char *string, char **terms)
{
    printf("rm");
    return -1;
}

//save
int save(char *string, char **terms)
{
    printf("save");
    return -1;
}

//reload
int reload(char *string, char **terms)
{
    printf("reload");
    return -1;
}

//menu
int menu(char *string, char **terms)
{
    printf("menu");
    return -1;
}

//quit
int quit(char *string, char **terms)
{
    exit(1);
    printf("Error: this code should not be capable of running.  It is immidiately after an exit() statement.");
    return -1;
}


char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm", "reload", "save", "menu", "quit", NULL};
//runCommand
int runCommand(char *string, char **terms)
{
    //printf("findCMD\tterms[0] = %s\n",terms[0]);
    for(int i = 0; cmd[i]!=NULL; i++){

        //when the user-inputted term matches the term from the list
        if(!strcmp(terms[0], cmd[i])){

            //match the function call with whichever iteration the terms match
            switch(i)
            {
                case 0: mkdir(string, terms);   break;
                case 1: rmdir(string, terms);   break;
                case 2: ls(string,terms);       break;
                case 3: cd(string, terms);      break;
                case 4: pwd(string, terms);     break;
                case 5: creat(string, terms);   break;
                case 6: rm(string, terms);      break;
                case 7: reload(string, terms);  break;
                case 8: save(string, terms);    break;
                case 9: menu(string, terms);    break;
                case 10: quit(string, terms);   break;
                default: printf("Error: this should not occur.\n Somehow, you were able to access this error call which is only possible if your command is in the list of available strings, yet doesn't match any of the strings.");
            }
            return i;       //found command: return index i
        }


    }
    printf("%s: Command not found\n", terms[0]);

    //command not found: return -1
    return -1;
}

//tokenize
char **tokenize(char *String, const char *KEY)
{
    //initial variables
    int i;
    char s [256];

    //close function if the input string is empty
    if(!strcmp(String, ""))return NULL;

    //allocate space for the array of strings for the path
    char **TokenizedPATH = malloc(sizeof(char) * 255);

    //tokenize the string PATHNAME based on the key KEY
    strcpy(s, String);
    char* token = strtok(s, KEY);
    i = 0;

    //while there are still characters left
    while (token != NULL)
    {

        TokenizedPATH[i++] = token;
        //printf("token: %s\n", token);
        token = strtok(NULL, KEY);
    }

    //ensure that the TokenizedPATH is null-terminated
    TokenizedPATH[sizeof(TokenizedPATH)] = NULL;



    //getCommand(cmd, tokenizedStringArray, HOME);
    runCommand(String, TokenizedPATH);

    return TokenizedPATH;
}

//getCommand
//getInput
char * getInput()
{
    //user input prompt
    printf("user:%s$ ",path);
    char command[64];
    fgets(command,64,stdin);
}

int main()
{

    while(1){

        char * command = getInput();

        //remove the \n tag at the end of the input string
        command[strlen(command) -1] = 0;

        //tokenize the input string
        tokenize(command, "/");


    }


}
