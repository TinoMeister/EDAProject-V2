#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"


/*
Example of getting all combinations!

list of Operations by one job:
1a, 2a, 2b, 3a, 3b

1a : NULL     + [1a] = [1a]
2a : [1a]     + [2a] = [1a, 2a]
2b : [1a]     + [2b] = [1a, 2b]
3a : [1a, 2a] + [3a] = [1a, 2a, 3a], [1a, 2b, 3a]
3b : [1a, 2b] + [3b] = [1a, 2a, 3b], [1a, 2b, 3b]

Final result:
Count: Lista
1: [1a, 2a, 3a]
2: [1a, 2b, 3a]
3: [1a, 2a, 3b]
4: [1a, 2b, 3b]

-------------------------------------- || ------------------------------

Example of getting all combinations!

list of Jobs with there Operations:
Id: Lista
1: [1a, 2a, 3a]
1: [1a, 2b, 3b]
2: [1a, 2a, 3a, 4a]
2: [1a, 2b, 3b, 4b]


1 : NULL         + [1a, 2a, 3a]     = [1a, 2a, 3a]
2 : [1a, 2a, 3a] + [1a, 2a, 3a, 4a] = [1a, 2a, 3a], [1a, 2a, 3a, 4a]
2 : [1a, 2a, 3a] + [1a, 2b, 3b, 4b] = [1a, 2a, 3a], [1a, 2b, 3b, 4b]

1 : NULL         + [1a, 2b, 3b]     = [1a, 2b, 3b]
2 : [1a, 2b, 3b] + [1a, 2a, 3a, 4a] = [1a, 2b, 3b], [1a, 2a, 3a, 4a]
2 : [1a, 2b, 3b] + [1a, 2b, 3b, 4b] = [1a, 2b, 3b], [1a, 2b, 3b, 4b]

Final result:
Count: Lista
1: [1a, 2a, 3a], [1a, 2a, 3a, 4a]
2: [1a, 2a, 3a], [1a, 2b, 3b, 4b]
3: [1a, 2b, 3b], [1a, 2a, 3a, 4a]
4: [1a, 2b, 3b], [1a, 2b, 3b, 4b]
*/

/*--------------------- Functions -----------------------*/
// Get the total number of process plan 
int getTotalPPlan(ProcessPlan* pplan)
{
    int count = 0;

    if (!pplan) return count;

    while (pplan)
    {
        count++;
        pplan = pplan->next;
    }

    return count;
}

// Get the total number of Jobs
int getTotalJb(Job* jb)
{
    int count = 0;

    if (!jb) return count;

    while (jb)
    {
        count++;
        jb = jb->next;
    }

    return count;
}

// Get total number of Operations
int getTotalOp(Operation* op)
{
    int count = 0;

    if (!op) return count;

    while (op)
    {
        count++;
        op = op->next;
    }

    return count;
}

// Get the highest number of Operations from a list of jobs
int getTotalOpJb(Job* jb)
{
    Operation *op;
    int count, total = 0;

    if (!jb) return total;

    while (jb)
    {
        op = jb->op;
        count = 0;

        while (op)
        {
            count++;
            op = op->next;
        }

        if (count > total) total = count;

        jb = jb->next;
    }  

    return total;
}

// Get the Highest number of Jobs from a Process Plan
int getMaxJb(ProcessPlan* pplan)
{
    Job *jb;
    int count, total = 0;

    if (!pplan) return count;

    while (pplan)
    {
        jb = pplan->jb;
        count = 0;

        while (jb)
        {
            count++;
            jb = jb->next;
        }

        if (total < count)
            total = count;   

        pplan = pplan->next;
    }

    return total;
}

// Get the Highest number of Operaions from a Job and idJob
int getMaxOp(Job* jb, int idJob)
{
    Operation *op;
    int count, total = 0;

    if (!jb) return count;

    while (jb)
    {
        if (jb->id == idJob)
        {
            count = 0;

            op = jb->op;

            while (op)
            {
                count++;
                op = op->next;
            }

            if (total < count)
                total = count; 
        }    

        jb = jb->next;
    }

    return total;
}

// Get the total time to complete a Operaion
int getTotalTimeOp(Operation* op)
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

// Verify if exists a Job in the list of Job
bool existsJb(Job* pplanJb, Job* jb)
{
    Job *tempJb = pplanJb;
    bool exists = false;

    while (tempJb)
    {
        if (tempJb->id == jb->id)
            exists = true;
        
        tempJb = tempJb->next;
    }

    return exists;
}

// Verify if there is an Operation with the same id on the list
bool existsOp(Operation* pplanOp, Operation* op)
{
    Operation *tempOp = pplanOp;
    bool exists = false;

    while (tempOp)
    {
        if (tempOp->id == op->id)
            exists = true;
        
        tempOp = tempOp->next;
    }

    return exists;
}


/*--------------------- Get Combinations by Job -----------------------*/
// Get the pointer of the process plan 
Job* getJobOp(Job* jb, int idJob, Operation* op1, Operation* op2)
{
    Operation *tempOp;
    bool exists;

    // If the list is NULL then return NULL
    if (!jb) return NULL;

    while (jb)
    {
        // Verify if the id of the job is equals to the id of the job received
        if (jb->id == idJob)
        {
            tempOp = jb->op;

            // Verify if the id of the Operation and the id Machine are equals in the list
            if (tempOp->id == op1->id && tempOp->idMachine == op1->idMachine)
            {
                exists = false;

                // Goes Operation by Operation
                while (tempOp)
                {
                    // If the Operation id is the same of the Operation id received by op2, means that has alredy an operation with the same id
                    // or if the next element on the list is NULL and the subtraction of the id on the list and 
                    // the id of the Operation on op2 are diferent then 1,then its means that the id of the Operatiob by op2 is greater the 1
                    if (tempOp->id == op2->id || (!tempOp->next && abs(op2->id - tempOp->id) != 1))
                        exists = true;                        

                    tempOp = tempOp->next;
                }

                // After traversing the entire list and not returning true, then returns the list at that pointer position
                if (!exists) return jb;   
            }
        }

        jb = jb->next;
    }
    
    return NULL;
}

// Remove in the list of Jobs the job than is imcomplet, doenst contain all the Operations, 
Job* removeGarbagedOp(Job* jb)
{
    Job *temp = jb, *ant = NULL, *aux;
    int totalOp = 0, maxOp = 0, idJob = 0;

    if (!jb) return NULL;

    while (temp)
    {
        // If the id of the Job change, then it gets the max of Operation by that job id
        if (temp->id != idJob)
        {
            idJob = temp->id;
            maxOp = getMaxOp(temp, idJob);
        }

        // Get the total of number of Operations
        totalOp = getTotalOp(temp->op);        


        // If the total of Operation and the Max Operations are diferents, then it's removed
        if (totalOp != maxOp)
        {
            aux = temp;

            // If the ant is NULL, this mean that is the first position on the list
            if (!ant)
            {
                temp = temp->next;
                jb = temp;
            }
            else
            {
                ant->next = temp->next;
                temp = temp->next;
            }
            
            free(aux);
        }
        else
        {
            ant = temp;
            temp = temp->next;
        }
    }
    
    return jb;
}

// Verify if the next jb has the same id and return if its true or not
bool verifyIsRepeatedOp(Job* jb)
{
    Operation *op;
    int idOp = 0;
    bool isRepeated = false;

    while (jb && !isRepeated)
    {
        idOp = 0;
        op = jb->op;

        while (op)
        {
            if (op->id == idOp) isRepeated = true;
            else idOp = op->id;

            op = op->next;
        }

        jb = jb->next;
    }

    return isRepeated;
}

// Gets all the combinations by Operation
Job* getCombinations(Job* jb)
{
    Job *combJb = NULL, *resultJob = NULL;
    Operation *op1, *op2, *tempOp;
    int totalJob;

    // If list is NULL, then return NULL
    if (!jb) return NULL;

    // Verify if there is Operations with the same id in the job
    if (!verifyIsRepeatedOp(jb))  return jb;

    // Goes Job by Job
    while (jb)
    {
        op1 = jb->op;

        // Goes Operation by Operation while th id of Operation is equals to 1
        while (op1 && op1->id == 1)
        {
            // Creates a Process Plan with the id of the job and the operation
            combJb = createJob(combJb, jb->id, op1);

            // Gets the next element and puts it into the variable op2
            op2 = op1->next;

            // Goes through the whole list
            while (op2)
            {
                // If the Ids are diferent, then continous
                if (op2->id > op1->id)
                {
                    // Get the pointer of the first element on the list thats doesn't have the Operation 2
                    resultJob = getJobOp(combJb, jb->id, op1, op2);
                    // Get the total number of Process Plan 
                    totalJob = getTotalJb(resultJob);

                    // Goes through the whole list get in the previous step
                    for (int i = 1; i <= totalJob; i++)
                    {
                        tempOp = resultJob->op;

                        // Verify if exists doesn't have Operation 2
                        if (!existsOp(tempOp, op2))
                        {
                            // Creates a Process Plan with the id of the job and the operation
                            combJb = createJobOp(combJb, jb->id, tempOp);
                            
                            // All the Operation 2 into the list as last element
                            combJb = addJobOp(combJb, jb->id, op2);
                        }

                        resultJob = resultJob->next;
                    }
                }

                op2 = op2->next;
            }

            op1 = op1->next;
        }

        jb = jb->next;
    }

    // Remove the elements that are incompleted
    combJb = removeGarbagedOp(combJb);

    return combJb;
}

/*------------------------------- Lower --------------------------------------------*/
int getTotalMachineJb(Job* jb)
{
    Operation *op;
    int total = 0;

    while (jb)
    {
        op = jb->op;

        while (op)
        {
            if (op->idMachine > total) total = op->idMachine;

            op = op->next;
        }

        jb = jb->next;
    }
    
    return total;
}

int getLowestTime(Job* jb, int idJob)
{
    Operation *op;
    int lower = 999, time = 0;

    if (!jb) return lower;
    
    while (jb)
    {
        if (jb->id == idJob)
        {
            op = jb->op;
            time = getTotalTimeOp(op);

            if (time < lower)
                lower = time;
        }

        jb = jb->next;
    }

    return lower;
}

Job* getLowerCombinations(Job* jb)
{
    Job *temp, *combJb = NULL;
    Operation *tempOp;
    int time, idJob = 0, lower = 0, totalMac = getTotalMachineJb(jb);

    printf("MAc: %d\n", totalMac);

    temp = jb;
    while (temp)
    {   
        if (temp->id != idJob)
        {
            idJob = temp->id;
            lower = getLowestTime(jb, idJob);
        }

        tempOp = temp->op;
        time = getTotalTimeOp(tempOp);

        if (time == lower) combJb = createJobOp(combJb, idJob, tempOp);

        temp = temp->next; 
    }
    
    return combJb;
}

/*------------------------------- Higher --------------------------------------------*/
int getHighestTime(Job* jb, int idJob)
{
    Operation *op;
    int higher = 0, time = 0;

    if (!jb) return higher;
    
    while (jb)
    {
        if (jb->id == idJob)
        {
            op = jb->op;
            time = getTotalTimeOp(op);

            if (time > higher)
                higher = time;
        }

        jb = jb->next;
    }

    return higher;
}

Job* getHighestCombinations(Job* jb)
{
    Job *temp = jb, *combJb = NULL;
    Operation *tempOp;
    int time, idJob = 0, higher = 0;


    while (temp)
    {
        if (temp->id != idJob)
        {
            idJob = temp->id;
            higher = getHighestTime(jb, idJob);
        }

        tempOp = temp->op;
        time = getTotalTimeOp(tempOp);

        if (time == higher) combJb = createJobOp(combJb, idJob, tempOp);
        
        temp = temp->next;
    }
    
    return combJb;
}

/*------------------------------- Best --------------------------------------------*/

bool verifyIsComp(Job* comb)
{
    Job* temp;
    Operation *op;
    bool isComp = true;
    int totalM, count = 0;

    if (!comb) return false;

    totalM = getTotalMachineJb(comb);

    for (int i = 1; i <= totalM && isComp; i++)
    {
        isComp = false;
        count = 0;
        temp = comb;
        while (temp)
        {
            op = temp->op;

            while (op)
            {
                if (op->idMachine == i)
                {
                    isComp = true;
                    count++;
                }

                op = op->next;
            }
            
            temp = temp->next;
        }

        if (count > 5) isComp = false;
    }

    return isComp;
}

// Verify if the next jb has the same id and return if its true or not
bool verifyIsRepeatedJb(Job* jb)
{
    int idJb = 0;
    bool isRepeated = false;

    while (jb && !isRepeated)
    {
        if (jb->id == idJb) isRepeated = true;
        else idJb = jb->id;

        jb = jb->next;
    }

    return isRepeated;
}

Job* getBestCombinations(Job* jb)
{
    Job *combJb = NULL, *temp, *ant;
    Operation *tempOp;
    int time, idJob = 0, average = 0, higher = 0;

    if (!jb) return NULL;

    // Check if there is a job with repeated id, because of the combinations received previously
    if (!verifyIsRepeatedJb(jb))
    {
        while (jb)
        {
            if (jb->id != idJob)
            {
                idJob = jb->id;
                combJb = createJobOp(combJb, jb->id, jb->op);
            }

            jb = jb->next;
        }
    }
    else
    {
        while (jb)
        {
            if (jb->id != idJob)
            {
                //idJob = jb->id;
                combJb = createJobOp(combJb, jb->id, jb->op);

                if (verifyIsComp(combJb)) idJob = jb->id;
                else
                {
                    temp = combJb;
                    while (temp->next)
                    {
                        ant = temp;
                        temp = temp->next;
                    }

                    ant->next = NULL;
                    free(temp);
                }
            }

            jb = jb->next;
        }
    }
    
    return combJb;
}

/*--------------------- Get Combinations for PPlan -----------------------*/

// Get the process plan that has jb1 and job2
ProcessPlan* getPPlanJb(ProcessPlan* pplan, Job* jb1, Job* jb2)
{
    Job *tempJb;
    bool exists;

    // If the list is NULL then return NULL
    if (!pplan) return NULL;

    while (pplan)
    {
        tempJb = pplan->jb;

        // Verify if the id Of jb and the Operaion and the Machine are equals in the process plan
        if (tempJb->id == jb1->id && tempJb->op->id == jb1->op->id && tempJb->op->idMachine == jb1->op->idMachine)
        {
            exists = false;

            // Goes job a job
            while (tempJb)
            {
                // Verify if the id of job is equal or if the next element is NULL and the diference beten the id of job2 and tempJb are diferent then 1
                if (tempJb->id == jb2->id || (!tempJb->next && abs(jb2->id - tempJb->id) != 1))
                    exists = true;

                tempJb = tempJb->next;
            }

            if (!exists) return pplan;
        }

        pplan = pplan->next;
    }
    
    return NULL;
}

// Remove the Elements that are incompleted
ProcessPlan* removeGarbagedJb(ProcessPlan* pplan)
{
    ProcessPlan *temp = pplan, *ant = NULL, *aux;
    int totalJb = 0, maxJb = 0;

    if (!pplan) return NULL;

    maxJb = getMaxJb(temp);

    while (temp)
    {
        totalJb = getTotalJb(temp->jb);

        // If the total of Operation and the Max Operations are diferents, then it's removed
        if (totalJb != maxJb)
        {
            aux = temp;

            // If the ant is NULL, this mean that is the first position on the list
            if (!ant)
            {
                temp = temp->next;
                pplan = temp;
            }
            else
            {
                ant->next = temp->next;
                temp = temp->next;
            }
            
            free(aux);
        }
        else
        {
            ant = temp;
            temp = temp->next;
        }
    }
    
    return pplan;
}

// Get all the Combninations creating a process plan
ProcessPlan* getCombinationsJb(Job* jb)
{
    ProcessPlan *pplan = NULL, *resultPPlan = NULL;
    Job *temp1 = jb, *temp2, *tempJb;
    Operation *tempOp;
    int totalPPlan;

    // Goes job a job until the job id is diferent then 1
    while (temp1 && temp1->id == 1)
    {
        // Create a new Process Plan with the temp1
        pplan = createPPlanOp(pplan, temp1);

        // Get the next job and set into temp2
        temp2 = temp1->next;

        while (temp2)
        {
            // Verify if the id of temp1 is higher then temp1
            if (temp2->id > temp1->id)
            {
                // Get the Process Plan and get the total of process plan that exists
                resultPPlan = getPPlanJb(pplan, temp1, temp2);
                totalPPlan = getTotalPPlan(resultPPlan);

                for (int i = 1; i <= totalPPlan; i++)
                {
                    tempJb = resultPPlan->jb;

                    // Verify if exists temp2 in inside on tempJb
                    if (!existsJb(tempJb, temp2))
                    {
                        // If not, then create a new Process Plan whit tempJb and add the new job, temp2
                        pplan = createPPlanJb(pplan, tempJb);
                        pplan = addPPlanJb(pplan, temp2);
                    }

                    resultPPlan = resultPPlan->next;
                }
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    // Remove the elements that are incompleted
    pplan = removeGarbagedJb(pplan);

    return pplan;
}


/*--------------------- Get Possibilities -----------------------*/

// Verify if the id Machine is alredy inserted in the list done
bool isDone(int* done, int idM, int size)
{
    bool isdone = false;

    for (int i = 0; i < size; i++)
    {
        if (done[i] == idM) isdone = true;
    }
    
    return isdone;
}

// Get the LowerBone for Machine
int* getLowerBoneM(Job* jb, int totalM, int* done)
{
    Job *temp;
    Operation *op;
    static int total[2];
    int time = 0;

    total[0] = 0;
    total[1] = 0;

    if (!jb) return total;

    // Goes all the numbers that Machines exists 
    for (int i = 1; i <= totalM; i++)
    {
        temp = jb;
        time = 0;

        // Goes job a job
        while (temp)
        {
            op = temp->op;

            while (op)
            {
                // Verify if the machine is equal to the i and if so increase the time
                if (op->idMachine == i) time += op->time;

                op = op->next;
            }

            temp = temp->next;
        }        

        // Save the highest time and if machine hasnt alredy be saved
        if (time > total[1] && !isDone(done, i, totalM))
        {
            total[0] = i;
            total[1] = time;
        }
    }
    
    // Return the lowerBone
    return total;
}

// Get the total Machine by Process Plan
int getTotalMachine(ProcessPlan* pplan)
{
    Job *jb;
    Operation *op;
    int total = 0;

    if (!pplan) return total;

    while (pplan)
    {
        jb = pplan->jb;

        while (jb)
        {
            op = jb->op;

            while (op)
            {
                // Verify if the id Machine os higher then total, then save it
                if (op->idMachine > total) total = op->idMachine;

                op = op->next;
            }

            jb = jb->next;
        }

        pplan = pplan->next;
    }

    // Return the total
    return total;
    
}

// Get the total size of order
int getTotalSh(ShiftingBottleneck* data)
{
    int count = 0;

    while (data)
    {
        count++;

        data = data->next;
    }

    return count;
}

// Get the total Machine that are inside of Operation by id
int getTotalMacbyIdMac(Operation* op, int id)
{
    int total = 0;

    if (!op) return total;

    while (op)
    {
        if (op->idMachine == id) total++;

        op = op->next;
    }

    return total;
}

// Verify if the data exists in the list of ShiftingBottleneck
bool existsSh(ShiftingBottleneck* data, ShiftingBottleneck* temp)
{
    bool exists = false;

    while (data)
    {
        if (temp->idJb == data->idJb && 
            temp->waitTime == data->waitTime &&
            temp->time == data->time &&
            temp->timeFinish == data->timeFinish) exists = true;

        data = data->next;
    }

    return exists;
}

// Verify if inside the list there is a better time
bool hasBetter(ShiftingBottleneck* data, int time)
{
    bool exists = false;
    int total = 0;

    while (data)
    {
        if (data->waitTime > 0) total = data->waitTime + data->time;
        else total = data->time;

        if (total < time) exists = true;

        data = data->next;
    }

    return exists;
}

// Verify if exists alredy a order inside the list ShiftingBottleneck
bool existsOrde(ShiftingBottleneck** order, ShiftingBottleneck** order2, int loc)
{
    bool exists = true;

    for (int i = 0; i < loc && order[i]; i++) 
        if (order[i]->idJb != order2[i]->idJb || 
            order[i]->time != order2[i]->time || 
            order[i]->waitTime != order2[i]->waitTime ||
            order[i]->timeFinish != order2[i]->timeFinish) exists = false;

    if (order[loc] && (order[loc]->idJb != order2[loc]->idJb || 
        order[loc]->time != order2[loc]->time || 
        order[loc]->waitTime != order2[loc]->waitTime ||
        order[loc]->timeFinish != order2[loc]->timeFinish)) exists = false;

    return exists;
}

// Verify if the exists alredy a element inside the list ShiftingBottleneck order
bool existsValue(ShiftingBottleneck** order, ShiftingBottleneck* value, int size)
{
    bool exists = false;

    for (int i = 0; i < size && order[i]; i++)
    {
        if (order[i]->idJb == value->idJb && 
            order[i]->time == value->time && 
            order[i]->waitTime == value->waitTime &&
            order[i]->timeFinish == value->timeFinish) exists = true;
    }
    
    return exists;
}

// Gets All the elements of a list that has the same id Machine
ShiftingBottleneck* getData(Job* jb, int idMachine, int maxTime)
{
    ShiftingBottleneck *data, *list = NULL, *temp;
    Operation *op;
    int time, waitTime, timeFinish, totalMac, count, idOp;

    if (!jb) return NULL;

    while (jb)
    {
        // Gets the total machine that exists inside of Operation by idMachine
        totalMac = getTotalMacbyIdMac(jb->op, idMachine);

        for (int i = 0; i < totalMac; i++)
        {
            op = jb->op;
            time = 0;
            waitTime = 0;
            timeFinish = 0;
            count = 0;
            data = malloc(sizeof(ShiftingBottleneck));

            while (op)
            {
                // Verify od the id MAchine and count is equal to the i and save the time and the id of Operation
                if (op->idMachine == idMachine && count == i)
                { 
                    idOp = op->id;
                    time = op->time;
                    count++;
                }
                else if (time == 0) waitTime += op->time; // if time is 0 then encrease with time
                else if (time != 0) timeFinish += op->time; // if time is !0 then encrease with time

                // If the id machine is equal to id MAchine and the count is diferent i increase count
                if (op->idMachine == idMachine && count != i) count++;

                op = op->next;
            }

            // if time is diferent != 0, then save the data
            if (time != 0)
            {
                data->idMachine = idMachine;
                data->idJb = jb->id;
                data->idOp = idOp;
                data->time = time;
                data->waitTime = waitTime;
                data->timeFinish = maxTime - timeFinish;
                data->next = NULL;

                if (!list) list = data;
                else
                {
                    temp = list;
                    while (temp->next) temp = temp->next;
                    temp->next = data;
                }
            }
        }        

        jb = jb->next;
    }
    
    // return the list of ShiftingBottleneck
    return list;
}

// Receives a list data and a list init for the order and order the list data and then order the reste by time in order cres
ShiftingBottleneck* orderData(ShiftingBottleneck* data, ShiftingBottleneck** init, int loc)
{
    ShiftingBottleneck *temp, *newData, *list = NULL, *tempList, *ant;
    int sizeList = 0;

    if (!data) return NULL;

    // Goes all the elements until the location of array init
    for (int i = 0; i <= loc; i++)
    {
        temp = data;
        while (temp)
        {
            // Verify if the values are equal
            if (temp->idJb == init[i]->idJb && 
                temp->time == init[i]->time && 
                temp->waitTime == init[i]->waitTime &&
                temp->timeFinish == init[i]->timeFinish)
            {
                // Allocate a new ShiftingBottleneck
                newData = malloc(sizeof(ShiftingBottleneck));   

                // save the data
                newData->idMachine = temp->idMachine;
                newData->idJb = temp->idJb;
                newData->time = temp->time;
                newData->waitTime = temp->waitTime;
                newData->timeFinish = temp->timeFinish;
                
                
                if (!list)
                {
                    newData->next = NULL;
                    list = newData;    
                }
                else
                {
                    tempList = list;
                    for (int j = 0; j < i && tempList->next; j++) tempList = tempList->next;
                    
                    newData->next = tempList->next;
                    tempList->next = newData;
                }

                sizeList++;
            }

            temp = temp->next;
        }
    }

    // Goes all the rest elements and order cres
    temp = data;
    while (temp)
    {
        // Verify if doesnt exists alredy in the list the element
        if (!existsSh(list, temp))
        {
            // Save the element
            newData = malloc(sizeof(ShiftingBottleneck));

            newData->idMachine = temp->idMachine;
            newData->idJb = temp->idJb;
            newData->time = temp->time;
            newData->waitTime = temp->waitTime;
            newData->timeFinish = temp->timeFinish;

            tempList = list;
            for (int j = 1; j < sizeList && tempList->next; j++) tempList = tempList->next;

            if (!tempList->next)
            {
                newData->next = NULL;
                tempList->next = newData;
            }
            else
            {
                ant = tempList;
                tempList = tempList->next;

                // Saves the list in Order
                while (tempList && !existsSh(list, newData))
                {                   
                    if (newData->timeFinish < tempList->timeFinish)
                    {
                        newData->next = tempList;
                        ant->next = newData;
                    }
                    else if (!tempList->next)
                    {
                        newData->next = NULL;
                        tempList->next = newData;
                    }

                    ant = tempList;
                    tempList = tempList->next;
                }
            }
        }

        temp = temp->next;
    }

    // Return the list
    return list;
}

/**
 * @brief Add a new Order.
 * Receive an Orders and the new order to insert and put in the position of the correct machine.
 * @param orders List of Orders.
 * @param order Element order.
 * @param size The size of list, the number of machines.
 * @param loc The location of the element.
 * @param compTime The total time o complete until that job.
 * @param lowerBone The ofset time of the 
 * @return Orders* Return the list Orders.
 */
Orders* addOrder(Orders* orders, ShiftingBottleneck** order, int size, int loc, int compTime, int lowerBone)
{
    Orders *temp, *ant, *newOrder = malloc(sizeof(Orders));

    if (!newOrder) return NULL;

    newOrder->data = malloc(size * sizeof(ShiftingBottleneck));

    // Save the new Order
    for (int i = 0; i <= loc; i++) 
    {
        newOrder->data[i] = malloc(sizeof(ShiftingBottleneck));
        newOrder->data[i]->idJb = order[i]->idJb;
        newOrder->data[i]->idMachine = order[i]->idMachine;
        newOrder->data[i]->idOp = order[i]->idOp;
        newOrder->data[i]->time = order[i]->time;
        newOrder->data[i]->waitTime = order[i]->waitTime;
        newOrder->data[i]->timeFinish = order[i]->timeFinish;
        newOrder->data[i]->next = NULL;
    }

    newOrder->time = compTime;
    newOrder->lowerBone = lowerBone;
    newOrder->size = size;
    newOrder->next = NULL;

    // Save the new order into the list
    if (!orders) orders = newOrder;
    else
    {
        temp = orders;
        while (temp && !existsOrde(temp->data, order, loc))
        {
            ant = temp;
            temp = temp->next;
        }        

        // verify if the new order has a better lower bone and/or a better time
        if (temp && (lowerBone < temp->lowerBone || lowerBone <= temp->lowerBone && compTime <= temp->time))
        {
            temp->time = compTime;
            temp->lowerBone = lowerBone;

            temp->data[loc] = malloc(sizeof(ShiftingBottleneck));
            temp->data[loc]->idJb = order[loc]->idJb;
            temp->data[loc]->idMachine = order[loc]->idMachine;
            temp->data[loc]->idOp = order[loc]->idOp;
            temp->data[loc]->time = order[loc]->time;
            temp->data[loc]->waitTime = order[loc]->waitTime;
            temp->data[loc]->timeFinish = order[loc]->timeFinish;
            temp->data[loc]->next = NULL;
        }
        else if (!temp && lowerBone <= ant->lowerBone) 
            ant->next = newOrder; // if not, then add as the next
    }

    // return the list
    return orders;
}

/**
 * @brief Get the Best Lower Bone object.
 * Remove the orders that has the higher lowerBone.
 * @param orders The list of Orders.
 * @return Orders* Return the list of Orders.
 */
Orders* getBestLowerBone(Orders* orders)
{
    Orders *temp = orders, *temp2, *ant = temp, *aux;

    if (!orders) return NULL;

    while (temp)
    {
        temp2 = temp->next;

        while (temp2)
        {
            // verify which one, order1 or order2 has the lower bone and then remove it
            if (temp->lowerBone < temp2->lowerBone)
            {
                aux = temp2;
                temp->next = temp2->next;
                temp2 = temp2->next;
                free(aux);
            }
            else if (temp->lowerBone > temp2->lowerBone)
            {
                aux = temp;

                if (temp == orders)
                {    
                    orders = temp2;
                    temp = orders;
                }
                else
                {
                    ant->next = temp->next;
                    temp = temp->next;
                }

                free(aux);
                temp2 = temp2->next;
            }
            else
            {
                temp2 = temp2->next;
            }
        }

        ant = temp;
        temp = temp->next;
    }
    
    // return the list
    return orders;
}

/**
 * @brief Get the Best Order object
 * After getting the data by machine, calls this fucntion and send the data, the idMachine and the total Jobs.
 * This function goes data a data and gets the best escalation for that id Machine .
 * @param data The data of all the jobs in machine.
 * @param idMachine The id Machine.
 * @param totalJb The total of Jobs.
 * @return Orders* return the list of Orders.
 */
Orders* getBestOrder(ShiftingBottleneck* data, int idMachine, int totalJb)
{
    int lowerBone, compTime, totalSh = getTotalSh(data);
    ShiftingBottleneck *temp, *dataO = NULL, **order = malloc (totalSh * sizeof(*order));
    Orders *bestOrder = NULL, *tempOr, *tempOr2;

    if (!data) return NULL;
    
    temp = data;
    while (temp)
    {
        compTime = 0;
        lowerBone = 0;

        // Put the element on data as first element
        order[0] = temp;

        // Order the data with the element
        dataO = orderData(data, order, 0);
            
        // Verify if the wait time if higher then 0, if so increse with the time
        if (dataO->waitTime > 0) compTime = dataO->waitTime + dataO->time;
        else compTime = dataO->time;

        // If the completion time is higher then the time to finish, increse the lower Bone
        if (compTime > dataO->timeFinish) lowerBone = compTime - dataO->timeFinish;
        
        // Verify in the list of data here is an element that has better time then the current element
        if (!hasBetter(data, compTime))
        {   
            // If there isnt, then goes all the element and calculate the completion tine and lowerBone
            dataO = dataO->next;
            while (dataO)
            {
                if (compTime < dataO->waitTime) compTime = dataO->waitTime + dataO->time;
                else compTime += dataO->time;

                if (compTime > dataO->timeFinish && lowerBone < (compTime - dataO->timeFinish))
                    lowerBone = compTime - dataO->timeFinish;
                
                dataO = dataO->next;
            }

            // Save the element and the completion time
            bestOrder = addOrder(bestOrder, order, totalSh, 0, compTime, lowerBone);
        }

        temp = temp->next;
    }

    // Remove the elements that have longer lowerbone
    bestOrder = getBestLowerBone(bestOrder); 

    tempOr = bestOrder;
    while (tempOr)
    {
        // Goes to all the size of elements that exists for the machine 
        for (int i = 1; i < totalSh; i++)
        {
            // Get all the elements and put in the order
            for (int j = 0; j < totalSh; j++)  order[j] = tempOr->data[j];

            temp = data;
            while (temp)
            {
                // Verify if the element is alredy in the order
                if (!existsValue(order, temp, totalSh))
                {
                    compTime = 0;
                    lowerBone = 0;
                    order[i] = temp;

                    // Order the elements with the new order
                    dataO = orderData(data, order, i);

                    // Calculate the completion Time and lowerBone
                    if (dataO->waitTime > 0) compTime = dataO->waitTime + dataO->time;
                    else compTime = dataO->time;

                    if (compTime > dataO->timeFinish) lowerBone = compTime - dataO->timeFinish;
                    
                    dataO = dataO->next;
                    while (dataO)
                    {
                        if (compTime < dataO->waitTime) compTime = dataO->waitTime + dataO->time;
                        else compTime += dataO->time;

                        if (compTime > dataO->timeFinish && lowerBone < (compTime - dataO->timeFinish))
                            lowerBone = compTime - dataO->timeFinish;
                        
                        dataO = dataO->next;
                    }
                    // Save the element
                    bestOrder = addOrder(bestOrder, order, totalSh, i, compTime, lowerBone);
                }

                temp = temp->next;
            }
        }
        tempOr = tempOr->next;
    }

    // Remove the elements that have longer lowerbone
    bestOrder = getBestLowerBone(bestOrder);

    return bestOrder;
}

/**
 * @brief Saves all the orders.
 * Saves all the the orders previous done and save into this category, by machine.
 * @param topOrders The list of TopOrders.
 * @param orders The list of orders.
 * @param jb The job of that order.
 * @param loc The id of Machine.
 * @param size The total of Machine.
 * @param time The completion Time.
 * @return TopOrders* return the list of TopOrders.
 */
TopOrders* saveTopOrders(TopOrders* topOrders, Orders* orders, Job* jb, int loc, int size, int time)
{
    TopOrders *newTopOrder = malloc(sizeof(TopOrders)), *temp, *ant;

    if (!newTopOrder) return NULL;

    // Save the order
    newTopOrder->orders = malloc(size * sizeof(ShiftingBottleneck));
    newTopOrder->orders[loc] = orders;

    newTopOrder->jb = jb;
    newTopOrder->time = time;
    newTopOrder->next = NULL;

    // Save into the list
    if (!topOrders) topOrders = newTopOrder;
    else
    {
        temp = topOrders;
        while (temp && temp->jb != jb)
        {
            ant = temp;
            temp = temp->next;
        }

        if (temp) temp->orders[loc] = orders;
        else if (time <= ant->time) ant->next = newTopOrder;
    }   

    // return the list
    return topOrders;
}

// Verify if the data1 and dat2 are equals
bool equalData(TopOrders* data1, ShiftingBottleneck* data2, int locM, int loc)
{
    bool exists = false;

    while (data1)
    {
        // Verify if the location in the list is not NULL
        if (data1->orders[locM] && data1->orders[locM]->data[loc])
        {
            // Verify if the data1 and data2 are equals
            if (data1->orders[locM]->data[loc]->idJb == data2->idJb &&
                data1->orders[locM]->data[loc]->idMachine == data2->idMachine &&
                data1->orders[locM]->data[loc]->idOp == data2->idOp) exists = true;   
        }
        else exists = true;

        data1 = data1->next;
    }
    
    // return verification
    return exists;
}

// Verify if the data1 and dat2 are equals
bool hasData(ShiftingBottleneck* data1, ShiftingBottleneck* data2)
{
    bool res = false;

    if ((data1->idJb == data2->idJb &&
        data1->idMachine == data2->idMachine &&
        data1->idOp == data2->idOp) ||
        (data1->idMachine == data2->idMachine &&
        data1->idOp == data2->idOp)) res = true;
    
    return res;
}

// Get the completion time of an order in certain location
int getTimeOrder(Orders* order, int loc)
{
    int time = 0;
    ShiftingBottleneck *temp = order->data[0];

    if (temp->waitTime > 0) time = temp->waitTime + temp->time;
    else time = temp->time;

    for (int i = 1; i <= loc; i++)
    {
        temp = order->data[i];

        if (time < temp->waitTime) time = temp->waitTime;
        else if (i < loc) time += temp->time;
    }
    
    return time;
}

// Verify if exists an Order inside of Top Orders
bool existsOrder(TopOrders* finalTopOrders, Orders* order, int locM, int loc)
{
    TopOrders* tempTopOr;
    Orders *tempOrd;
    ShiftingBottleneck *tempData;
    bool exists = false, isWrong = false, wrongPos = false;
    int totalMac = getTotalMachineJb(finalTopOrders->jb);

    for (int i = 0; i < totalMac; i++)
    {
        tempOrd = finalTopOrders->orders[i];

        if (tempOrd)
        {
            for (int j = 0; j < tempOrd->size; j++)
            {
                tempData = tempOrd->data[j];

                if (!exists && tempData)
                {
                    // Verify if the data are equals
                    if (hasData(tempData, order->data[loc]) && i == locM && j == loc) exists = true;

                    // Verify if the time of the new order is lower then previous operation
                    if (!exists && (order->data[loc]->idOp - tempData->idOp) == 1 && tempData->idJb == order->data[loc]->idJb && tempData->time > getTimeOrder(order, loc)) isWrong = true;

                    // Verify if the position on that order and the new position of the order, the diference bettwe then 2 has to be 1
                    if (tempData->idMachine == order->data[loc]->idMachine && abs(j-loc) > 1) wrongPos = true;
                    else if (tempData->idMachine == order->data[loc]->idMachine && abs(j-loc) == 1) wrongPos = false;
                }
            }
        }
    }

    // Return combination of the results
    return exists || isWrong || wrongPos;
}

/**
 * @brief Save the Final Orders.
 * 
 * @param finalTopOrders The list of final Orders.
 * @param topOrders The list of top orders.
 * @param orders The list of orders.
 * @param locM The Location of the machine.
 * @param loc The location of Job.
 * @return TopOrders* The list of top orders.
 */
TopOrders* saveFinalOrders(TopOrders* finalTopOrders, TopOrders* topOrders, Orders* orders, int locM, int loc)
{
    TopOrders *newTopOrder = malloc(sizeof(TopOrders)), *temp, *ant, *tempTopOr;
    int result;

    if (!finalTopOrders)
    {
        newTopOrder->orders = malloc(getTotalMachineJb(topOrders->jb) * sizeof(Orders));

        newTopOrder->orders[locM] = malloc(sizeof(Orders));
        newTopOrder->orders[locM]->data = malloc(orders->size * sizeof(ShiftingBottleneck));

        newTopOrder->orders[locM]->data[loc] = malloc(sizeof(ShiftingBottleneck));
        newTopOrder->orders[locM]->data[loc]->idJb = orders->data[loc]->idJb;
        newTopOrder->orders[locM]->data[loc]->idMachine = orders->data[loc]->idMachine;
        newTopOrder->orders[locM]->data[loc]->idOp = orders->data[loc]->idOp;
        newTopOrder->orders[locM]->data[loc]->time = orders->data[loc]->time;
        newTopOrder->orders[locM]->data[loc]->waitTime = orders->data[loc]->waitTime;
        newTopOrder->orders[locM]->data[loc]->timeFinish = orders->data[loc]->timeFinish;
        newTopOrder->orders[locM]->data[loc]->next = NULL;

        newTopOrder->orders[locM]->time = getTimeOrder(orders, loc) + orders->data[loc]->time;
        newTopOrder->orders[locM]->size = orders->size;
        newTopOrder->orders[locM]->next = NULL;

        newTopOrder->jb = topOrders->jb;
        newTopOrder->time = topOrders->time;
        newTopOrder->next = NULL;
        
        finalTopOrders = newTopOrder;
    }
    else
    {
        temp = finalTopOrders;
        while (temp && temp->jb == topOrders->jb && existsOrder(temp, orders, locM, loc))
        {
            ant = temp;
            temp = temp->next;
        }

        if (temp)
        {
            if (!temp->orders[locM]) temp->orders[locM] = malloc(sizeof(Orders));
            if (!temp->orders[locM]->data) temp->orders[locM]->data = malloc(orders->size * sizeof(ShiftingBottleneck));
            temp->orders[locM]->data[loc] = malloc(sizeof(ShiftingBottleneck));
            temp->orders[locM]->data[loc]->idJb = orders->data[loc]->idJb;
            temp->orders[locM]->data[loc]->idMachine = orders->data[loc]->idMachine;
            temp->orders[locM]->data[loc]->idOp = orders->data[loc]->idOp;
            temp->orders[locM]->data[loc]->time = orders->data[loc]->time;

            if (loc-1 >= 0 && temp->orders[locM]->data[loc-1] && orders->data[loc]->waitTime < (temp->orders[locM]->data[loc-1]->waitTime + temp->orders[locM]->data[loc-1]->time))
                temp->orders[locM]->data[loc]->waitTime = (temp->orders[locM]->data[loc-1]->waitTime + temp->orders[locM]->data[loc-1]->time);
            else 
                temp->orders[locM]->data[loc]->waitTime = orders->data[loc]->waitTime;

            temp->orders[locM]->data[loc]->timeFinish = orders->data[loc]->timeFinish;
            temp->orders[locM]->data[loc]->next = NULL;

            temp->orders[locM]->time = getTimeOrder(orders, loc) + orders->data[loc]->time;
            temp->orders[locM]->size = orders->size;
            temp->orders[locM]->next = NULL;
        }
    }

    return finalTopOrders;
}

/**
 * @brief Get the Best Escalation object.
 * 
 * @param topOrders The list of top Orders.
 */
void getBestEscalation(TopOrders* topOrders)
{
    TopOrders* finalOrders = NULL;
    Job *tempJb;
    Orders *tempOr;
    int totalJb, totalMac;
    
    tempJb = topOrders->jb;
    totalJb = getTotalJb(tempJb);
    totalMac = getTotalMachineJb(tempJb);

    // Save element in order by machine
    for (int i = 1; i <= totalMac; i++)
    {
        for (int j = 0; j < totalMac; j++)
        {
            tempOr = topOrders->orders[j];

            for (int k = 0; k < tempOr->size && tempOr->data[k]; k++)
            {
                if (tempOr->data[k]->idMachine == i)
                    finalOrders = saveFinalOrders(finalOrders, topOrders, tempOr, j, k);
            }
        }
    }

    // Save escalation to file
    saveEscalation(finalOrders, totalMac, totalJb);   
}

/**
 * @brief Get the Possibilities object.
 * 
 * @param pplan The list of Process Plan.
 */
void getPossibilities(ProcessPlan* pplan)
{
    Job *jb;
    ShiftingBottleneck *data = NULL;
    Orders *bestOrders;
    TopOrders *topOrders = NULL;

    int *lowerBoneM, *done;
    int totalMachine, totalJb, timeSpan = 0;

    if (!pplan) return;

    // Get total jobs and machines
    totalJb = getTotalJb(pplan->jb);
    totalMachine = getTotalMachine(pplan);

    // Allocate in memory a array for save all jobs that has been done
    done = malloc(totalMachine * sizeof(int));
    
    // Gets the Job
    jb = pplan->jb;

    for (int i = 0; i < totalMachine; i++)
    {
        // Get lower Bone 
        lowerBoneM = getLowerBoneM(jb, totalMachine, done);
        done[i] = lowerBoneM[0];
        if (timeSpan < lowerBoneM[1]) timeSpan = lowerBoneM[1];

        // Get all the Jobs that has the machine
        data = getData(jb, lowerBoneM[0], timeSpan);
        
        // Get best order for escalation
        bestOrders = getBestOrder(data, lowerBoneM[0], totalJb);
        timeSpan += bestOrders->lowerBone;

        // Save order
        topOrders = saveTopOrders(topOrders, bestOrders, jb, i, totalMachine, timeSpan);

    }

    // Get best escalation
    getBestEscalation(topOrders);
}