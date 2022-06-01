#include <stdlib.h>

#include "../class.h"

// Get the total of Jobs in the list
int getSizeJb(Job* jb)
{
    int total = 0;

    while (jb)
    {
        total++;
        jb = jb->next;
    }

    return total;
}

// Verify if the id of job is alredy inserted
bool existsJbId(Job* jb, int id)
{
    bool exists = false;

    if (!jb) return exists;

    while (jb)
    {
        if (jb->id == id) exists = true;

        jb = jb->next;
    }

    return exists;
}

/*------------------ Jobs ------------------------*/

Job* addJob(Job* jb, int id)
{
    Job *aux, *newJob = malloc(sizeof(Job));

    // Verify if can save a new job into memory
    if (!newJob || id <= 0 || existsJbId(jb, id)) return NULL;
    
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

Job* deleteJob(Job* jb, int id)
{
    Job *temp = jb, *aux;
    int total = getSizeJb(jb);

    // If the list is null or of the id is not bettween 1 and the total of job then return NULL
    if (!jb || id <= 0 || id > total) return NULL;

    // If the id is 1 then gets the next element and put it as first and deletes the first
    if (id == 1) 
    {
        jb = temp->next;
        free(temp);
    }
    else
    {
        // Gets the previous element and the actual element
        while (temp && temp->id != id)
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

// Free the list Jobs.
void clean(Job* jb)
{
    Job *auxJb;
    Operation *op, *auxOp;

    while (jb)
    {
        op = jb->op;

        while (op)
        {
            auxOp = op;
            op = op->next;
            free(auxOp);
        }

        auxJb = jb;
        jb = jb->next;
        free(auxJb);
    }
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

    // Add a new Job
    newJob = addJob(newJob, idJob);

    // If its not Null then add the operation to the job
    if (newJob) newJob = addOpJobNOrder(newJob, idJob, op->id, op->idMachine, op->time);

    // Save it in the list
    newJob->next = NULL;
    if (!jb) jb = newJob;
    else
    {
        while (temp->next) temp = temp->next;
    
        temp->next = newJob;
    }

    // return Job
    return jb;
}

Job* createJobOp(Job* jb, int idJob, Operation* op)
{
    Job *newJob = NULL, *temp = jb;
    Operation *tempOp = op;

    // Add a new Job
    newJob = addJob(newJob, idJob);

    // If its not Null then goes by all the operations and add to the job
    if (newJob)
    {
        while (tempOp)
        {
            newJob = addOpJobNOrder(newJob, idJob, tempOp->id, tempOp->idMachine, tempOp->time);

            tempOp = tempOp->next;
        }
    }
    
    // If the newJob is Null then return the list Job
    if (!newJob) return jb;

    newJob->next = NULL;

    // Save it in the list
    if (!jb) jb = newJob;
    else
    {
        while (temp->next) temp = temp->next;

        temp->next = newJob;
    }

    // Return job
    return jb;
}

Job* addJobOp(Job* jb, int idJob, Operation* op)
{
    Job *temp = jb;

    // If job is NUll then return NUll
    if (!jb) return NULL;

    // Goes to the last element on the list
    while (temp->next) temp = temp->next;

    // Add the Operation
    temp = addOpJobNOrder(temp, idJob, op->id, op->idMachine, op->time);

    // return Job
    return jb;
}