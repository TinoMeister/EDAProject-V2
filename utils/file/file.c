#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils.h"

// Load data of Operation
Job* loadData(Job* jb) 
{
    // Open file
    FILE *f = fopen("db/db.txt", "r");
    char line[256];
    int idJob, idOp, idMachine, time, count = 0;

    // Verify if isnt null
    if (f == NULL) 
    {
        printf("Error opening file!\n");
        return NULL;
    }

    // Get the text line by line
    while (fgets(line, sizeof(line), f)) 
    {
        // Remove the ";" and get the values and insert into the list
        char *ptr = strtok(line, ";");
        idJob = (int)strtol(ptr, (char **)NULL, 10);

        ptr = strtok(NULL, ";");
        idOp = (int)strtol(ptr, (char **)NULL, 10);

        ptr = strtok(NULL, ";");
        idMachine = (int)strtol(ptr, (char **)NULL, 10);

        ptr = strtok(NULL, ";");
        time = (int)strtol(ptr, (char **)NULL, 10);

        //printf("%d %d %d %d\n", idJob, idOp, idMachine, time);

        if (idJob != count)
        {
            jb = addJob(jb, idJob);
            count = idJob;
        }
        
        jb = addOpJob(jb, idJob, idOp, idMachine, time);
    }

    // Close File
    fclose(f);

    // Return the list
    return jb;
}

// Save data of Object
void saveData(Job* jb)
{
    Operation *temp;

    // Open file
    FILE *f = fopen("db/db.txt", "w");

    // Verify if isnt null
    if (f == NULL) printf("Error opening file!\n");

    // Goes operation a operation and saves it into a line in the file
    if (jb != NULL)
    {
        while (jb != NULL)
        {
            if (jb->op != NULL)
            {
                temp = jb->op;
                while (temp != NULL)
                {
                    fprintf(f, "%d;%d;%d;%d\n", jb->id, temp->id, temp->idMachine, temp->time);
                    temp = temp->next;
                }
            }
            
            jb = jb->next;
        }
    }    
    
    // Close File
    fclose(f);
}