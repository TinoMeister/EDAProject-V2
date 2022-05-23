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

void showOp(Operation * obj)
{
    int count = 0;

    if (obj != NULL)
    {
        printf("Index | Id | Machine | Time\n");
        while (obj != NULL)
        {
            printf("%d | %d | %d | %d\n", (count+1), obj->id, obj->idMachine, obj->time);
            obj = obj->next;
            count++;
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
    int count = 0;

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
            }
            
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

int getTotalTime(Operation* op)
{
    int total = 0;

    if (!op) return total;

    while (op)
    {
        total += op->time;
        op = op->next;
    }
    
    return total;
}
// Show the process plan by printing to the console
void showPPlan(ProcessPlan* pplan)
{
    Job *jb = NULL;
    Operation *op = NULL;
    int count = 1, time = 0;

    if (!pplan)
    {
        printf("lista Vazia!!!");
        return;
    }
    

    while (pplan)
    {
        jb = pplan->jb;

        if (jb->id != 0)
        {
            time = 0;
            printf("C: %d - ", count);
            count++;
            while (jb)
            {
                //showAll(jb);

                //printf("J: %d - ", jb->id);
                //op = jb->op;
                time = getTotalTime(jb->op);

                /*printf("Op: ");

                while (op)
                {
                    printf("%d,%d,%d - ", op->id, op->idMachine, op->time);

                    op = op->next;
                }*/

                printf("%d | ", time);

                jb = jb->next;
            }

            printf("\n\n"); 
        }

        pplan = pplan->next;
    }
}

int main(int argc, char const *argv[])
{
    clock_t start, end;
    double time_taken;

    Job *jb = NULL;
    ProcessPlan *finalPPlan = NULL;
    Job *finalJb = NULL, *combJb = NULL;

    jb = loadData(jb);
    //showAll(jb);

    //start = clock();

    //finalJb = getCombinations(jb);
    
    //combJb = getLowerCombinations(finalJb);
    
    //finalPPlan = getCombinationsJb(combJb);

    // Best - 20 | 20 | 28 | 15 | 18 | 22 | 19 | 21 | 

    //showAll(combJb);

    //showPPlan(finalPPlan);

    //getPossibilities(finalPPlan);

    
    /*
    end = clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("fun() took %f seconds to execute \n\n", time_taken);
    */

    //showPPlan(finalPPlan);

    //jb = addOpJob(jb, 1, 6, 1, 12);

    //saveData(jb);


    
    // jb = loadData(jb); // Load Data

    printf("Add Job! \n");
    jb = addJob(jb, 1);
    jb = addJob(jb, 8);
    jb = addJob(jb, 4);
    jb = addJob(jb, 9);
    jb = addJob(jb, 2);
    showJb(jb);

    printf("Delete Job! \n");
    jb = deleteJob(jb, 3);
    showJb(jb);
    
    printf("Add Op! \n");
    jb = addOpJob(jb, 1, 1, 1, 2);
    jb = addOpJob(jb, 1, 2, 1, 1);
    jb = addOpJob(jb, 1, 1, 4, 8);
    jb = addOpJob(jb, 1, 3, 7, 4);
    jb = addOpJob(jb, 1, 3, 2, 9);
    jb = addOpJob(jb, 8, 1, 2, 9);
    
    //jb = addOpJob(jb, 8, 3, 1, 12);
    //jb = addOpJob(jb, 8, 4, 1, 12);
    showAll(jb);

    printf("Edit Op! \n");
    jb = editOpJob(jb, 1, 1, 2, 3, 20);
    showAll(jb);
    jb = editOpJob(jb, 1, 4, 1, 1, 10);
    showAll(jb);
    jb = editOpJob(jb, 1, 4, 2, 3, 15);    
    showAll(jb);
    //jb = editOpJob(jb, 1, 4, 1, 1, 15); // It's supposed to be blank because its insurting the same id of operation
    showAll(jb);


    printf("Delete Op! \n");
    jb = deleteOpJob(jb, 8, 1);
    showAll(jb);
    jb = deleteOpJob(jb, 1, 3);
    showAll(jb);
    //jb = deleteOpJob(jb, 1, 15); // It's supposed to be blank because its delting a index higher then the total of Jobs
    showAll(jb);

    //saveData(jb); // Save Data
    

    return 0;
}
