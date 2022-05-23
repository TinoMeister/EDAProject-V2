#include <stdio.h>
#include <stdlib.h>

#include "../class.h"

ProcessPlan* createPPlanOp(ProcessPlan* pplan, Job* jb)
{
    ProcessPlan *temp = pplan, *newpPlan = malloc(sizeof(ProcessPlan));
    Job *newJob = NULL;
    Operation *tempOp = jb->op;

    if (!newpPlan) return NULL;

    newJob = addJob(newJob, jb->id);
    if (newJob)
    {
        while (tempOp)
        {
            newJob = addOpJobNOrder(newJob, jb->id, tempOp->id, tempOp->idMachine, tempOp->time);

            tempOp = tempOp->next;
        }
    }

    if (!newJob) return pplan;

    newpPlan->jb = newJob;
    newpPlan->next = NULL;

    if (!pplan) 
        pplan = newpPlan;
    else
    {
        while (temp->next) temp = temp->next;

        temp->next = newpPlan;
    }

    return pplan;
}

ProcessPlan* createPPlanJb(ProcessPlan* pplan, Job* jb)
{
    ProcessPlan *temp = pplan, *newpPlan = malloc(sizeof(ProcessPlan));
    Job *newJb = NULL, *tempJb = NULL, *finalJb = NULL;
    Operation *tempOp;

    if (!newpPlan) return NULL;

    while (jb)
    {
        newJb = addJob(newJb, jb->id);

        if (newJb)
        {
            tempOp = jb->op;
            
            while (tempOp)
            {
                newJb = addOpJobNOrder(newJb, jb->id, tempOp->id, tempOp->idMachine, tempOp->time);

                tempOp = tempOp->next;
            }
        }

        jb = jb->next;
    }    

    if (!newJb) return pplan;

    newpPlan->jb = newJb;
    newpPlan->next = NULL;

    if (!pplan) 
        pplan = newpPlan;
    else
    {
        while (temp->next) temp = temp->next;

        temp->next = newpPlan;
    }

    return pplan;
}

ProcessPlan* addPPlanJb(ProcessPlan* pplan, Job* jb)
{
    ProcessPlan *temp = pplan;
    Job *newJob = NULL, *tempJb;
    Operation *tempOp;

    if (!pplan) return NULL;

    newJob = addJob(newJob, jb->id);

    if (newJob)
    {
        tempOp = jb->op;

        while (tempOp)
        {
            newJob = addOpJobNOrder(newJob, jb->id, tempOp->id, tempOp->idMachine, tempOp->time);

            tempOp = tempOp->next;
        } 
    } 

    while (temp->next)
        temp = temp->next;

    tempJb = temp->jb;
    while (tempJb->next) 
        tempJb = tempJb->next;

    newJob->next = NULL;
    tempJb->next = newJob;

    return pplan;
}