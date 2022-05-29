#include <stdlib.h>

#include "../class.h"

Operation *errorOp;

Operation* opError() 
{
    if (!errorOp)
    {
        errorOp = malloc(sizeof(Operation));
        errorOp->id = -1;
    }

    return errorOp;
}

// Get the total of Operations in the list
int getSizeOp(Operation* op)
{
    int total = 0;

    while (op)
    {
        total++;
        op = op->next;
    }    

    return total;
}

// Verify if the id Machine alredy exists in Operation
bool verifyOperation(Operation* op, int id, int idMachine)
{
    bool exists = false;

    while (op)
    {
        if (op->id == id && op->idMachine == idMachine) exists = true;

        op = op->next;
    }
    
    return exists;
}

// Add new operation
Operation* addOperation(Operation* op, int id, int idMachine, int time)
{
    Operation *aux, *newOp = malloc(sizeof(Operation));
    bool exists = verifyOperation(op, id, idMachine);

    // Verify if can save a new operation into memory or alredy exists or if any value is lower then or equal to 0
    if (!newOp || exists || id <= 0 || idMachine <= 0 || time < 0) return opError();

    // Save the information
    newOp->id = id;
    newOp->idMachine = idMachine;
    newOp->time = time;

    // Save in the first position if list is null
    if (!op)
    {
        if (id > 1) return opError();

        newOp->next = NULL;
        op = newOp;
    }
    // Save in the first position if id is lower then the first id the list
    // or if id are equals but the idMachine is lower then the first idMachine
    else if (id > 0 && (id < op->id || (id == op->id && idMachine < op->idMachine)))
    {
        newOp->next = op;
        op = newOp;
    }
    else
    {
        aux = op;

        // While the id is higher then the id of element on the list gets the next element
        // or if the id is equal but the id machine is higher
        while (aux->next && (id > aux->next->id || (id == aux->next->id && idMachine > aux->next->idMachine))) aux = aux->next;

        // Verify if the subtration of the id operation and the element id operation of the list is higher then 1, then return NULL
        if (!aux || abs(aux->id - id) > 1) return opError();

        // The new operation gets the pointer from the previous operation pointer
        newOp->next = aux->next;
        // The next operation gets the the pointer from the new operation
        aux->next = newOp;
    }

    // Return the operation list
    return op;
}

// Add new operation without order, the order of the input of the operation is not important
Operation* addOperationNOrder(Operation* op, int id, int idMachine, int time)
{
    Operation *aux, *newOp = malloc(sizeof(Operation));
    bool exists = verifyOperation(op, id, idMachine);

    // Verify if can save a new operation into memory or alredy exists or if any value is lower then or equal to 0
    if (!newOp || exists || id <= 0 || idMachine <= 0 || time < 0) return opError();

    // Save the information
    newOp->id = id;
    newOp->idMachine = idMachine;
    newOp->time = time;

    // Save in the first position if list is null
    if (!op)
    {
        newOp->next = NULL;
        op = newOp;
    }
    // Save in the first position if id is lower then the first id the list
    // or if id are equals but the idMachine is lower then the first idMachine
    else if (id > 0 && (id < op->id || (id == op->id && idMachine < op->idMachine)))
    {
        newOp->next = op;
        op = newOp;
    }
    else
    {
        aux = op;

        // While the id is higher then the id of element on the list gets the next element
        // or if the id is equal but the id machine is higher
        while (aux->next && (id > aux->next->id || (id == aux->next->id && idMachine > aux->next->idMachine))) aux = aux->next;

        // The new operation gets the pointer from the previous operation pointer
        newOp->next = aux->next;
        // The next operation gets the the pointer from the new operation
        aux->next = newOp;
    }

    // Return the operation list
    return op;
}

// Edit the operation
Operation* editOperation(Operation* op, int index, int id, int idMachine, int time)
{
    Operation *temp = op;
    int total = getSizeOp(op), count = 1;

    // If the list is null or of the index is not bettween 1 and the total of operations or if the opration alredy exists then return NULL
    if (!op || index <= 0 && index > total || id <= 0 || idMachine <= 0 || time < 0) return opError();

    // Get the operation representing the index
    while (temp && count < index)
    {
        count++;
        temp = temp->next;
    }

    // If the id and id Machine are still equal to the element then just update the time
    if (temp->id == id && temp->idMachine == idMachine)
    {
        temp->time = time;
        
        // Return the new list of Operaion
        return op;
    }
    else
    {
        // Delete Operation
        temp = deleteOperation(op, index);

        // If result is not NULL then add the Operation
        if (temp && temp->id != -1) temp = addOperation(temp, id, idMachine, time);
    }

    // Return the new list of Operaion
    return temp;
}

// Delete the operation
Operation* deleteOperation(Operation* op, int index)
{
    Operation *temp = op, *aux;
    int total = getSizeOp(op);

    // If the list is null or of the index is not bettween 1 and the total of operations or if the opration alredy exists then return NULL
    if (!op || index <= 0 || index > total) return opError();

    // If the index is 1 then gets the next element and put it as first and deletes the first
    if (index == 1) 
    {
        op = temp->next;
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
        if (!temp) return opError();

        // Update the pointer so that the previous element goes to next element of the actual element so it can be free
        aux->next = temp->next;

        free(temp);
    }   

    return op;
}

// Free the list Operation.
void clean(Operation* op)
{
    Operation *aux;

    while (op)
    {
        aux = op;
        op = op->next;
        free(aux);
    }
}