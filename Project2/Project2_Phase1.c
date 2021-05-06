//Project2.c
//by Nick Garrett
/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <pwd.h>


//set a variable to the cwd to print to the user
char *path = "~";
char **envArray;

//initialize


//cd
int cd (char** terms)
{
    //get HOME directory location
    struct passwd *pw = getpwuid(getuid());
    const char *HOME = pw->pw_dir;
    //printf("(cd) home: %s\n", HOME);

    //initialize variables
    int r;
    char *s;
    char buf[256];

    //printf("CHECKING STATUS GETCOMMAND: cd was entered; changing directory logic... \n");

    //if the user typed in a path
    if(terms[1]!=NULL && strcmp(terms[1]," ") && strstr(terms[1], "/") != NULL)
    {
        //printf("CHECKING STATUS GETCOMMAND: changing directory to \"%s\"\n",terms[1]);
        r = chdir(terms[1]);
        s = getcwd(buf, 256);
        //printf("CHECKING STATUS GETCOMMAND: new directory is: %s\n", s);
    }
        //if the user didn't type in a path
    else
    {
        //printf("CHECKING STATUS GETCOMMAND: going to the home directory: %s\n", HOME);
        r = chdir(HOME);
        s = getcwd(buf, 256);
        //printf("CHECKING STATUS GETCOMMAND: new directory is: %s\n", s);
    }

    //change the path of the user (which is printed on the psudo cmd-line)
    path = s;
    //printf("CHECKING STATUS GETCOMMAND: new directory is: %s\n", s);
}



int runCommand(char **command)
{
    //create strings
    char src[255];
    char executablePath[255];

    //copy strings to the src and executablePath
    strcpy(executablePath,"/bin/");
    strcpy(src,  command[0]);
    strcat(executablePath,src);

    // child process identification number
    pid_t  pid;
    int status;

	printf("executable path: %s", executablePath);
    //fork the process
    pid = fork();

    //parent
    if ( pid )
    {
        pid = wait( &status );
        //printf("child killed\n");

    }

    //child
    else
    {
        char* envp[] = { NULL };
        //printf("running command %s", executablePath);
        if (execve(executablePath, command, envp) == -1)
            printf("%s: command not found\n", command[0]);

        exit(1);
    }

    //printf("end of runCommand\n");
    return 1;
}

//get the command from the input string
    int getCommand(char* string, char** terms)
{
    int commandRun;
    //variable definitions
    //printf("CHECKING STATUS GETCOMMAND: home:%s\n", HOME);
    int i, termsNumber, commandOptionsLength, r;
    char buf[256];
    char *s;
    //char* commandsList[] = {"ls","mkdir", "rmdir", "cd", "pwd", "creat", "rm", "reload", "save", "menu", "quit", "exit", NULL};
    char* commandsList[] = {"cd", "exit", NULL};

    //printf("CHECKING STATUS GETCOMMAND: command string: %s\n", string);


    //find and run the command
    int commandFound = 0;
    for(i = 0; commandsList[i] != NULL; i++)
    {
        if(!strcmp(terms[0], commandsList[i]))
        {
            //update variable to represent that command has been found
            commandFound = 1;

            //printf("CHECKING STATUS GETCOMMAND: strings are equal: %s, %s\n", string, command[i]);
            switch(i)
            {
                //cd
                case 0:
                    //printf("CKECKING STATUS GETCOMMAND: cd starting\n");
                    cd(terms);
                    return 1;
                    break;

                //exit
                case 1:
                    //printf("CHECKING STATUS GETCOMMAND: command exit will run in 3... 2... 1...\n");
                    exit(1);
                    printf("Error: the system should have exited by now\n");
                    return 1;
                    break;

                default:
                    printf("%s: command not found\t(this error return shouldn't even be possible.  If you have managed it... I tip my [very small] hat to you)\n",string);
            }
        }

        //run if the command is not cd or exit
        else if(commandsList[i+1] == NULL && !commandFound)
        {
            //printf("%s: command not found\n", string);
            commandRun = runCommand(terms);
            if(commandRun==1)return 1;
            break;

        //printf("CHECKING STATUS GETCOMMAND: command: %d : %s\n",i, command[i]);


    }

    printf("Error: command not found");
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

    //printf all the tokenized strings of the path
/*
    for(int i = 0; TokenizedPATH[i] != NULL; i++)
    {
        printf("(TokenizePATHNAME) Term %d of TokenizedPATH (which has size %ld): %s \n",i,sizeof(TokenizedPATH[i]),TokenizedPATH[i]);
    }
*/

    //getCommand(cmd, tokenizedStringArray, HOME);
    getCommand(String, TokenizedPATH);

    return TokenizedPATH;
}

//getInput
char * getInput()
{
    //user input prompt
    printf("user:%s$ ",path);
    char command[64];
    fgets(command,64,stdin);
}

//main
int main(int argc, char *argv[], char *env[ ])
{
    envArray = env;
    //start while infinite loop
    while(1)
    {
        char* cmd;
        char* terms = NULL;
        char sum[64];
        int iteration, i;

        char * command = getInput();

        //remove the \n tag at the end of the input string
        command[strlen(command) -1] = 0;

        //printf("CHECKING STATUS MAIN: command =  %s, len(command) = %d.\n",command, (int) strlen(command));

        //tokenize the command
        char **tokenizedStringArray = tokenize(command, " ");


    }

    return -1;
}
