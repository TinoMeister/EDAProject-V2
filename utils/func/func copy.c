#include <stdio.h>
#include "stdlib.h"

#include "../utils.h"

int getTotalJob(Job* jb)
{
    int total = 0;

    while (jb != NULL)
    {
        if (total < jb->id)
            total = jb->id;
        
        jb = jb->next;
    }

    return total;   
}

int getMaxOp(Job* jb)
{
    Operation *temp;
    int total = 0;


    while (jb != NULL)
    {
        temp = jb->op;
        while (temp != NULL)
        {
            if (total < temp->id)
                total = temp->id;
            
            temp = temp->next;
        }
        
        jb = jb->next;
    }

    return total;   
}

Operation* getLower(Operation* op, int idOp) 
{
    Operation *lowest = NULL, *temp = op;
    int lower = 999;

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (temp->id == idOp && lower >= temp->time)
                lower = temp->time;
            
            temp = temp->next;
        }

        temp = op;
        while (temp != NULL)
        {
            if (temp->id == idOp && lower == temp->time)
                lowest = addOperation(lowest, temp->id, temp->idMachine, temp->time);
            
            temp = temp->next;
        }
    }

    return lowest;
}

Operation* getOp(Operation* op, int idOp) 
{
    Operation *opId = NULL, *temp = op;

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (temp->id == idOp)
                opId = addOperation(opId, temp->id, temp->idMachine, temp->time);
            
            temp = temp->next;
        }
    }

    return opId;
}

bool hasLower(Job* job, int time)
{
    bool val = false;
    Operation *temp;

    if (job != NULL)
    {
        temp = job->op;

        if (temp != NULL)
            while (temp != NULL)
            {
                if (temp->time < time)
                    val = true;
                
                temp = temp->next;
            }
    }

    return val;
}

void showEscalation4(Job* jb)
{
    Job *temp, *temp2;
    Operation *op1, *op2, *bestOp = NULL;
    int totalOp = getMaxOp(jb), totalJob = getTotalJob(jb), totalT = 0, bestTotalT = 0, count;
    printf("TJB: %d - TOP:%d\n\n", totalJob, totalOp);    

    if (jb != NULL)
    {
        // goes from 1 to total of Operations id
        for (int i = 0; i < totalOp; i++)
        {
            temp = jb;
            count = 0;
            
            // goes from job to job
            while (temp != NULL)
            {
                //printf("Job:%d | Op:%d\n", temp->id, i);
                // gets all the operations relative about the id Operations and Job
                op1 = getOp(temp->op, (i+1));

                // goes operation to operation from previoes fetch
                while (op1 != NULL)
                {
                    temp2 = jb;
                    // goes from job to job
                    while (temp2 != NULL)
                    {
                        // gets all the operations relative about the id Operations an Job
                        op2 = getOp(temp2->op, (i+1));  

                        // goes operation to operation from previoes fetch
                        while (op2 != NULL)
                        {
                            if (temp->id != temp2->id && op1->idMachine == op2->idMachine && op1->time >= op2->time && !hasLower(temp2, op2->time))
                            {
                                //printf("Job:%d | Op:%d | M:%d | T:%d --- ", temp->id, (i+1), op1->idMachine, op1->time);
                                //printf("Job:%d | Op:%d | M:%d | T:%d\n", temp2->id, (i+1), op2->idMachine, op2->time);
                                totalT += op2->time;
                            }

                            op2 = op2->next;
                        }

                        temp2 = temp2->next;
                    }
                    //printf("\n");

                    // Get the best Operation with lower time
                    if (bestOp == NULL)
                    {
                        bestOp = op1;
                        bestTotalT = totalT;
                    }
                    else
                    {
                        if (totalT + op1->time < bestTotalT + bestOp->time)
                        {
                            bestOp = op1;
                            bestTotalT = totalT;
                        }                             
                    }

                    totalT = 0;
                    op1 = op1->next;
                }

                if (bestOp != NULL)
                {
                    //// FALTA BUSCAR O TEMPO EM QUE COMECA O SEU TEMPO DA MAQUINA E NAO DO SEU TEMPO ANTERIOR!!!
                    //// FALTA CRIAR UMA FORMA MELHOR DE GUARDAR!!!!
                    printf("Job:%d | Op:%d | M:%d | ST:%d | ET:%d\n\n", temp->id, bestOp->id, bestOp->idMachine, bestTotalT, (bestTotalT + bestOp->time));
                }
            
                //printf("B| Job:%d | Op:%d | M:%d | ST:%d | ET:%d\n", temp->id, bestOp->id, bestOp->idMachine, bestCount, bestCount + bestOp->time);

                bestTotalT = 0;
                bestOp = NULL;
                count++;
                temp = temp->next;
            }

            printf("\n");
        }
    }    
}

void showEscalation3(Job* jb)
{
    Job *temp, *temp2;
    Operation *op1, *op2, *bestOp = NULL;
    int totalOp = getMaxOp(jb), totalJob = getTotalJob(jb), totalT = 0, bestTotalT = 0, count;
    int start[totalOp][totalJob], end[totalOp][totalJob];
    printf("TJB: %d - TOP:%d\n\n", totalJob, totalOp);

    // Clean double array
    for (int i = 0; i < totalOp; i++)
    {
        for (int j = 0; j < totalJob; j++)
        {
            start[i][j] = 0;
            end[i][j] = 0;
        }  
    }
    

    if (jb != NULL)
    {
        // goes from 1 to total of Operations id
        for (int i = 0; i < totalOp; i++)
        {
            temp = jb;
            count = 0;
            
            // goes from job to job
            while (temp != NULL)
            {
                //printf("Job:%d | Op:%d\n", temp->id, i);
                // gets all the operations relative about the id Operations and Job
                op1 = getOp(temp->op, (i+1));

                // goes operation to operation from previoes fetch
                while (op1 != NULL)
                {
                    temp2 = jb;
                    // goes from job to job
                    while (temp2 != NULL)
                    {
                        // gets all the operations relative about the id Operations an Job
                        op2 = getOp(temp2->op, (i+1));  

                        // goes operation to operation from previoes fetch
                        while (op2 != NULL)
                        {
                            /*if (op1->idMachine == op2->idMachine && op1->time != op2->time)
                            {
                                printf("Job:%d | Op:%d | M:%d | T:%d --- ", temp->id, i, op1->idMachine, op1->time);
                                printf("Job:%d | Op:%d | M:%d | T:%d\n", temp2->id, i, op2->idMachine, op2->time);
                            }*/

                            if (temp->id != temp2->id && op1->idMachine == op2->idMachine && op1->time > op2->time)
                            {
                                //printf("Job:%d | Op:%d | M:%d | T:%d --- ", temp->id, (i+1), op1->idMachine, op1->time);
                                //printf("Job:%d | Op:%d | M:%d | T:%d\n", temp2->id, (i+1), op2->idMachine, op2->time);
                                totalT += op2->time;
                            }

                            op2 = op2->next;
                        }

                        temp2 = temp2->next;
                    }

                    // Get the best Operation with lower time
                    if (bestOp == NULL)
                    {
                        bestOp = op1;
                        bestTotalT = totalT;
                    }
                    else
                    {
                        if (totalT + op1->time < bestTotalT + bestOp->time)
                        {
                            bestOp = op1;
                            bestTotalT = totalT;
                        }                             
                    }

                    totalT = 0;
                    op1 = op1->next;
                }

                if (bestOp != NULL)
                {
                    //// FALTA BUSCAR O TEMPO EM QUE COMECA O SEU TEMPO DA MAQUINA E NAO DO SEU TEMPO ANTERIOR!!!
                    //// FALTA CRIAR UMA FORMA MELHOR DE GUARDAR!!!!
                    //printf("Job:%d | Op:%d | M:%d | ST:%d | ET:%d\n", temp->id, bestOp->id, bestOp->idMachine, bestTotalT, (bestTotalT + bestOp->time));
                    
                    
                    start[i][count] = (i == 0) ? bestTotalT : end[i-1][count] + bestTotalT;
                    end[i][count] = start[i][count] + bestOp->time;
                }
            
                //printf("B| Job:%d | Op:%d | M:%d | ST:%d | ET:%d\n", temp->id, bestOp->id, bestOp->idMachine, bestCount, bestCount + bestOp->time);

                bestTotalT = 0;
                bestOp = NULL;
                count++;
                temp = temp->next;
            }

            //printf("\n");
        }

        for (int i = 0; i < totalOp; i++)
        {
            for (int j = 0; j < totalJob; j++)
            {
                if (end[i][j] != 0)
                    printf("Job:%d | Op:%d | JS:%d | JE:%d\n", (j+1), (i+1), start[i][j], end[i][j]);
            }  

            printf("\n");
        }
    }    
}


void showEscalation2(Job* jb)
{
    Job *temp, *temp2;
    Operation *lower, *lower2;
    int totalOp = getMaxOp(jb), totalJob = getTotalJob(jb), count = 0;

    printf("TJB: %d - TOP:%d\n\n", totalJob, totalOp);
    

    if (jb != NULL)
    {
        for (int i = 1; i <= totalOp; i++)
        {
            temp = jb;

            while (temp != NULL)
            {
                printf("Job:%d | Op:%d\n", temp->id, i);
                lower = getLower(temp->op, i);

                if (lower != NULL)
                {
                    temp2 = jb;

                    while (temp2 != NULL)
                    {
                        lower2 = getLower(temp2->op, i);

                        if (lower2 != NULL)
                        {
                            if (lower->idMachine == lower2->idMachine) //&& lower->time > lower2->time)
                            {
                                //count += lower2->time;
                                printf("Job:%d | Op:%d | M:%d | T:%d --- ", temp->id, i, lower->idMachine, lower->time);
                                printf("Job:%d | Op:%d | M:%d | T:%d\n", temp2->id, i, lower2->idMachine, lower2->time);
                            }   
                        }

                        temp2 = temp2->next;
                    }
                }

                //printf("Final: \n");
                //printf("Job:%d | Op:%d | M:%d | TI:%d | TF:%d\n", temp->id, i, lower->idMachine, count, (count + lower->time));

                /*printf("Lower: \n");
                while (lower != NULL)
                {
                    printf("Op:%d | Job:%d | M:%d | T:%d\n", (i+1), temp->id, lower->idMachine, lower->time);
                    lower = lower->next;
                }
                */

                printf("\n\n");

                temp = temp->next;
                count = 0;
            }

            printf("\n");
        }

        
    }    
}

void showEscalation1(Job* jb)
{
    Job *temp, *temp2;
    Operation *lower, *lower2;
    int totalOp = getMaxOp(jb), totalJob = getTotalJob(jb), count;
    int start[totalOp][totalJob], end[totalOp][totalJob];

    for (int i = 0; i < totalOp; i++)
    {
        for (int j = 0; j < totalJob; j++)
        {
            start[i][j] = 0;
            end[i][j] = 0;
        }  
    }
    

    if (jb != NULL)
    {
        for (int i = 0; i <= totalOp; i++)
        {
            temp = jb;
            count = 0;

            while (temp != NULL)
            {
                lower = getLower(temp->op, (i+1));

                /*if (lower != NULL)
                {
                    temp2 = temp->next;

                    while (temp2 != NULL)
                    {
                        lower2 = getLower(temp2->op, (i+1));

                        if (lower2 != NULL)
                        {
                            
                        }

                        temp2 = temp2->next;
                    }
                    
                }

                /*while (lower != NULL)
                {
                    printf("Op:%d | Job:%d | M:%d | T:%d\n", (i+1), temp->id, lower->idMachine, lower->time);
                    lower = lower->next;
                }*/
                
                
                

                if (lower != NULL)
                {
                    temp2 = temp->next;
                    
                    while (temp2 != NULL)
                    {
                        lower2 = getLower(temp2->op, (i+1));

                        if (lower2 != NULL)
                        {
                            if (lower->idMachine == lower2->idMachine && lower->time > lower2->time)
                                start[i][count] = start[i][count] + lower2->time;
                        }

                        temp2 = temp2->next;
                    }
                    
                    start[(i+1)][count] = start[i][count] + lower->time;
                    end[i][count] = start[i][count] + lower->time;
                }


                temp = temp->next;
                count++;
            }
        }

        
    }

    for (int i = 0; i < totalOp; i++)
    {
        for (int j = 0; j < totalJob; j++)
        {
            int en = end[i][j];

            if (en != 0)
                printf("Op:%d | Job:%d | JS:%d | JE:%d\n", (i+1), (j+1), start[i][j], end[i][j]);
        }  

        printf("\n");
    }
    
}