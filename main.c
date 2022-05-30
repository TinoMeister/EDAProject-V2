#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "utils/utils.h"

void showJb(Job * jb)
{
    int count = 0;

    if (jb != NULL)
    {
        printf("Index | Id \n");
        while (jb != NULL)
        {
            printf("%d | %d\n", (count+1), jb->id);
            jb = jb->next;
            count++;
        }
    }    
    else 
    {
        printf("Lista vazia");
    }

    printf("\n\n");
}

void showOp(Job * jb)
{
   Operation *temp;
    int count = 0;

    if (jb)
    {
        printf("IdJob | IndexOp | IdOp | IdM | Time \n");
        while (jb != NULL)
        {
            if (jb->op != NULL)
            {
                temp = jb->op;
                count = 0;

                while (temp != NULL)
                {
                    printf("%d | %d | %d | %d | %d\n", jb->id, (count+1), temp->id, temp->idMachine, temp->time);
                    
                    count++;
                    temp = temp->next;
                }

                printf("\n");
            }
            
            jb = jb->next;
        }
    }    
    else 
    {
        printf("Lista vazia");
    }

    printf("\n\n"); 
}

void showAll(Job * jb)
{
    Operation *temp;

    if (jb)
    {
        printf("IdJob | IdOp | IdM | Time \n");
        while (jb != NULL)
        {
            if (jb->op != NULL)
            {
                temp = jb->op;
                while (temp != NULL)
                {
                    printf("%d | %d | %d | %d\n", jb->id, temp->id, temp->idMachine, temp->time);
                    temp = temp->next;
                }

                printf("\n");
            }
            
            jb = jb->next;
        }
    }    
    else 
    {
        printf("Lista vazia");
    }

    printf("\n\n");
}

int main(int argc, char const *argv[])
{
    // Variables
    Job *jb = NULL, *result;
    char option;
    int index, idJb, idOp, idMachine, time;
    char locationFile[256];

    // Variables for Escalation
    Job *jbTemp = NULL, *finalJb = NULL, *combJb = NULL;
    ProcessPlan *finalPPlan = NULL;
    clock_t start, end;
    double time_taken;

    // Load jobs from DB
    jb = loadData(jb);

    while (option != 'x')
    {
        system("clear");

        printf("------------------------------------------------------------------\n");
        printf("|                        WELCOME TO FJSSP                        |\n");
        printf("------------------------------------------------------------------\n\n");

        printf("Operations:\n");
        printf("a) Insert new Job        b) Delete Job          c) Add Operation\n");
        printf("d) Edit Operation        e) Delete Operation    f) See All\n");
        printf("g) Escalation            h) Diff Escalation     x) Exit\n\n");

        // Ask for option to execute
        printf("Option: ");
        scanf(" %c", &option);
        option = tolower(option); // Put the result of the user to lower

        switch (option)
        {
            case 'a':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                             ADD JOB                            |\n");
                printf("------------------------------------------------------------------\n\n");

                // Ask for id of Job
                printf("Insert id of new Job: ");
                scanf("%d", &idJb);

                // Add a new operation and return True or False
                result = addJob(jb, idJb);

                // Print if is Successfull or if there is a problem
                if (result)
                {
                    jb = result;
                    printf("\nSuccessfully Inserted!!\n\n");
                }
                else
                    printf("\nSomething went wrong!!\n\n");

                break;

            case 'b':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                          DELETE JOB                            |\n");
                printf("------------------------------------------------------------------\n\n");

                // Show all jobs
                showJb(jb);

                // Ask for index
                printf("\nInsert index to delete: ");
                scanf("%d", &index);

                // Delete the Job
                result = deleteJob(jb, index);

                // Print if is Successfull or if there is a problem
                if (result)
                {
                    jb = result;
                    printf("Successfully Deleted!!\n\n");
                }
                else
                    printf("Something went wrong!!\n\n");
                break;
            
            case 'c':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                        ADD OPERATION                           |\n");
                printf("------------------------------------------------------------------\n\n");

                // Show all jobs
                showJb(jb);

                // Ask for id of Job, id Operation, id of Machine and time
                printf("Insert id of Job: ");
                scanf("%d", &idJb);

                printf("Insert id of operation: ");
                scanf("%d", &idOp);

                printf("Insert Machine number: ");
                scanf("%d", &idMachine);

                printf("Insert time of Machine: ");
                scanf("%d", &time);

                // Add a new operation and return True or False
                result = addOpJob(jb, idJb, idOp, idMachine, time);

                // Print if is Successfull or if there is a problem
                if (result)
                {
                    jb = result;
                    printf("\nSuccessfully Inserted!!\n\n");
                }
                else
                    printf("\nSomething went wrong!!\n\n");

                break;

            case 'd':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                        EDIT OPERATION                          |\n");
                printf("------------------------------------------------------------------\n\n");

                // Show all operations
                showOp(jb);

                // Ask for id of Job, id Operation, id of Machine and time
                printf("Insert id of Job: ");
                scanf("%d", &idJb);

                printf("Insert index to edit: ");
                scanf("%d", &index);

                printf("Insert id of operation: ");
                scanf("%d", &idOp);

                printf("Insert Machine number: ");
                scanf("%d", &idMachine);

                printf("Insert time of Machine: ");
                scanf("%d", &time);

                // Edit operation and return True or False
                result = editOpJob(jb, idJb, index, idOp, idMachine, time);

                // Print if is Successfull or if there is a problem
                if (result)
                {
                    jb = result;
                    printf("\nSuccessfully Inserted!!\n\n");
                }
                else
                    printf("\nSomething went wrong!!\n\n");
                break;

            case 'e':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                       DELETE OPERATION                         |\n");
                printf("------------------------------------------------------------------\n\n");

                // Show all operations
                showOp(jb);

                // Ask for id of Job, id Operation, id of Machine and time
                printf("Insert id of Job: ");
                scanf("%d", &idJb);

                printf("Insert index to delete: ");
                scanf("%d", &index);

                // Delete operation and return True or False
                result = deleteOpJob(jb, idJb, index);

                // Print if is Successfull or if there is a problem
                if (result)
                {
                    jb = result;
                    printf("\nSuccessfully Inserted!!\n\n");
                }
                else
                    printf("\nSomething went wrong!!\n\n");
                break;

            case 'f':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                          SEE ALL JOB                           |\n");
                printf("------------------------------------------------------------------\n\n");

                // Show all jobs
                showAll(jb);
                break;

            case 'g':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                           ESCALATION                           |\n");
                printf("------------------------------------------------------------------\n\n");

                start = clock();

                finalJb = getCombinations(jb);
                combJb = getBestCombinations(finalJb);
                finalPPlan = getCombinationsJb(combJb);
                getPossibilities(finalPPlan);

                end = clock();
                time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("fun() took %f seconds to execute \n", time_taken);
                printf("File saved at db/bestEscalation.txt\n\n");
                break;

            case 'h':
                system("clear");

                printf("------------------------------------------------------------------\n");
                printf("|                      DIFFERENT ESCALATION                      |\n");
                printf("------------------------------------------------------------------\n\n");

                printf("Insert location of file: ");
                scanf("%s", locationFile);

                jbTemp = loadDataByLoc(jbTemp, locationFile);

                start = clock();

                finalJb = getCombinations(jbTemp);
                combJb = getBestCombinations(finalJb);
                finalPPlan = getCombinationsJb(combJb);
                getPossibilities(finalPPlan);

                end = clock();
                time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("fun() took %f seconds to execute \n", time_taken);
                printf("File saved at db/bestEscalation.txt\n\n");

                break;

            case 'x':
                // Save Jobs to DB
                saveData(jb);
                // Clean List Jobs
                clean(jb);

                printf("See you next time!\n\n");
                break;

            default:
                printf("You enter a wrong option, please select another!\n\n");
                break;
        }

        if (option != 'x') {
            printf("Press [Enter] key to continue.\n");
            while(getchar()!='\n'); // option TWO to clean stdin
            getchar(); // wait for ENTER 
        }
    }
    
    return 0;
}
