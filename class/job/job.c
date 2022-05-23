#include <stdlib.h>

#include "../class.h"

// Get the total of Jobs in the list
int getSizeJb(Job* jb)
{
    int total = 1;

    while (jb)
    {
        total += 1;
        jb = jb->next;
    }

    return total;
}

/*------------------ Operations ------------------------*/

Job* addJob(Job* jb, int id)
{
    Job *aux, *newJob = malloc(sizeof(Job));

    // Verify if can save a new job into memory
    if (!newJob || id <= 0) return NULL;
    
    // Save the information
    newJob->id = id;
    newJob->op = NULL;

    // Save in the first position if list is null
    if (!jb)
    {
        newJob->next = NULL;
        jb = newJob;
    }
    else if (id < jb->id) // Save in the first position if id is lower then the first id of the list
    {
        newJob->next = jb;
        jb = newJob;
    }
    else
    {
        aux = jb;
        
        // While the id is higher then the id of element on the list gets the next element
        while (aux->next && id > aux->next->id) aux = aux->next;

        // Save the new job between the elements
        newJob->next = aux->next;
        aux->next = newJob;
    }

    // Return the job list
    return jb;
}

Job* deleteJob(Job* jb, int index)
{
    Job *temp = jb, *aux;
    int total = getSizeJb(jb);

    // If the list is null or of the index is not bettween 1 and the total of job then return NULL
    if (!jb || index <= 0 || index > total) return NULL;

    // If the index is 1 then gets the next element and put it as first and deletes the first
    if (index == 1) 
    {
        jb = temp->next;
        free(temp);
    }
    else
    {
        // Gets the previous element and the actual element
        for (int i = 1; i < index; i++)
        { 
            aux = temp;
            temp = temp->next;
        }

        // If the actual element is NULL then return NULL
        if (!temp) return NULL;

        // Update the pointer so that the previous element goes to next element of the actual element so it can be free
        aux->next = temp->next;

        free(temp);
    }

    // Return list
    return jb;
}

/*------------------ Jobs Operations ------------------------*/

Job* addOpJob(Job* jb, int idJob, int idOp, int idMachine, int time)
{
    Job *temp = jb;
    Operation *result = NULL;

    // If job is NULL return NULL
    if (!jb || idOp <= 0 || idMachine <= 0 || time <= 0) return NULL;

    // Gets the next element until the id of the list is diferent of the id of the job received
    while (temp && temp->id != idJob) temp = temp->next;
    
    // If the element if not NULL then add a new Operation to that Job
    if (temp) result = addOperation(temp->op, idOp, idMachine, time);

    // If result is NULL then something went wrong and return NULL
    if (result && result->id == -1) return NULL;

    // Update the list of Operations
    temp->op = result;

    // Return job list
    return jb;
}

Job* editOpJob(Job* jb, int idJob, int indexOp, int idOp, int idMachine, int time)
{
    Job *temp = jb;
    Operation *result = NULL;

    // If job is NULL return NULL
    if (!jb || idJob <= 0 || indexOp <= 0 || idOp <= 0 || idMachine <= 0 || time <= 0) return NULL;

    // Gets the next element until the id of the list is diferent of the id of the job received
    while (temp && temp->id != idJob) temp = temp->next;
    
    // If the element if not NULL then edit the Operation to that Job
    if (temp) result = editOperation(temp->op, indexOp, idOp, idMachine, time);

    // If result is NULL then something went wrong and return NULL
    if (result && result->id == -1) return NULL;

    // Update the list of Operations
    temp->op = result;

    // Return job list
    return jb;
}

Job* deleteOpJob(Job* jb, int idJob, int indexOp)
{
    Job *temp = jb;
    Operation *result = NULL;

    // If job is NULL return NULL
    if (!jb || idJob <= 0 || indexOp <= 0) return NULL;

    // Gets the next element until the id of the list is diferent of the id of the job received
    while (temp && temp->id != idJob) temp = temp->next;

    // If the element if not NULL then delete the Operation to that Job
    if (temp) result = deleteOperation(temp->op, indexOp);

    // If result is NULL then something went wrong and return NULL
    if (result && result->id == -1) return NULL;

    // Update the list of Operations
    temp->op = result;

    // Return job list
    return jb;
}

/*------------------ Combinations ------------------------*/
Job* addOpJobNOrder(Job* jb, int idJob, int idOp, int idMachine, int time)
{
    Job *temp = jb;
    Operation *result = NULL;

    // If job is NULL return NULL
    if (!jb || idOp <= 0 || idMachine <= 0 || time <= 0) return NULL;

    // Gets the next element until the id of the list is diferent of the id of the job received
    while (temp && temp->id != idJob) temp = temp->next;
    
    // If the element if not NULL then add a new Operation to that Job
    if (temp) result = addOperationNOrder(temp->op, idOp, idMachine, time);

    // If result is NULL then something went wrong and return NULL
    if (result && result->id == -1) return NULL;

    // Update the list of Operations
    temp->op = result;

    // Return job list
    return jb;
}

Job* createJob(Job* jb, int idJob, Operation* op)
{
    Job *newJob = NULL, *temp = jb;    

    newJob = addJob(newJob, idJob);

    if (newJob) newJob = addOpJobNOrder(newJob, idJob, op->id, op->idMachine, op->time);

    newJob->next = NULL;
    if (!jb)
    {
        jb = newJob;
    }
    else
    {
        while (temp->next) temp = temp->next;
    
        temp->next = newJob;
    }
    

    return jb;
}

Job* createJobOp(Job* jb, int idJob, Operation* op)
{
    Job *newJob = NULL, *temp = jb;
    Operation *tempOp = op;

    newJob = addJob(newJob, idJob);

    if (newJob)
    {
        while (tempOp)
        {
            newJob = addOpJobNOrder(newJob, idJob, tempOp->id, tempOp->idMachine, tempOp->time);

            tempOp = tempOp->next;
        }
    }

    if (!newJob) return jb;

    newJob->next = NULL;

    if (!jb) 
        jb = newJob;
    else
    {
        while (temp->next) temp = temp->next;

        temp->next = newJob;
    }

    return jb;
}

Job* addJobOp(Job* jb, int idJob, Operation* op)
{
    Job *temp = jb;

    if (!jb) return NULL;

    while (temp->next) temp = temp->next;

    temp = addOpJobNOrder(temp, idJob, op->id, op->idMachine, op->time);

    return jb;
}