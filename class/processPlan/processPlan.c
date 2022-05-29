#include <stdio.h>
#include <stdlib.h>

#include "../class.h"

// Create a Process Plan with all the Operations
ProcessPlan* createPPlanOp(ProcessPlan* pplan, Job* jb)
{
    ProcessPlan *temp = pplan, *newpPlan = malloc(sizeof(ProcessPlan));
    Job *newJob = NULL;
    Operation *tempOp;

    // If the process plan is NULL then return NULL
    if (!newpPlan) return NULL;

    // Add a new Job
    newJob = addJob(newJob, jb->id);
    if (newJob)
    {
        // Save all of the Operations into that job
        tempOp = jb->op;
        
        while (tempOp)
        {
            newJob = addOpJobNOrder(newJob, jb->id, tempOp->id, tempOp->idMachine, tempOp->time);

            tempOp = tempOp->next;
        }
    }

    // if the newJob is Null the return the list Process Plan
    if (!newJob) return pplan;

    // Save the job into the list
    newpPlan->jb = newJob;
    newpPlan->next = NULL;

    if (!pplan) 
        pplan = newpPlan;
    else
    {
        while (temp->next) temp = temp->next;

        temp->next = newpPlan;
    }

    // Return Process Plan
    return pplan;
}

// Create a Process Plan with all the jobs and Operations
ProcessPlan* createPPlanJb(ProcessPlan* pplan, Job* jb)
{
    ProcessPlan *temp = pplan, *newpPlan = malloc(sizeof(ProcessPlan));
    Job *newJb = NULL, *tempJb = NULL, *finalJb = NULL;
    Operation *tempOp;

    // If cant create a new process plan then return NULL
    if (!newpPlan) return NULL;

    // Goes by all the jobs
    while (jb)
    {
        // Create a new job
        newJb = addJob(newJb, jb->id);

        if (newJb)
        {
            // Save all the Operations into the Job
            tempOp = jb->op;
            
            while (tempOp)
            {
                newJb = addOpJobNOrder(newJb, jb->id, tempOp->id, tempOp->idMachine, tempOp->time);

                tempOp = tempOp->next;
            }
        }

        jb = jb->next;
    }    

    // If somethin whent wrong then return the list
    if (!newJb) return pplan;

    // Save the new list of Jobs and Operations into the list of Process Plan
    newpPlan->jb = newJb;
    newpPlan->next = NULL;

    if (!pplan) 
        pplan = newpPlan;
    else
    {
        while (temp->next) temp = temp->next;

        temp->next = newpPlan;
    }

    // Return Process Plan
    return pplan;
}

// Add a new Job to the last element on the list Process Plan
ProcessPlan* addPPlanJb(ProcessPlan* pplan, Job* jb)
{
    ProcessPlan *temp = pplan;
    Job *newJob = NULL, *tempJb;
    Operation *tempOp;

    // If the list Process Plan is Null then return NULL
    if (!pplan) return NULL;

    // Create a new Job
    newJob = addJob(newJob, jb->id);

    if (newJob)
    {
        // Save all the Operations to the Job
        tempOp = jb->op;

        while (tempOp)
        {
            newJob = addOpJobNOrder(newJob, jb->id, tempOp->id, tempOp->idMachine, tempOp->time);

            tempOp = tempOp->next;
        } 
    } 

    // Goes to the last element on the list Precess Plan
    while (temp->next) temp = temp->next;

    // Goes to the last element on the list Job
    tempJb = temp->jb;
    while (tempJb->next)  tempJb = tempJb->next;

    // Save the new Job
    newJob->next = NULL;
    tempJb->next = newJob;

    // Return Process Plan
    return pplan;
}