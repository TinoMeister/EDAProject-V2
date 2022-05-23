#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "class/class.h"

// Listagem dos objetos
void showAll(Operation * obj)
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
}


int main(int argc, char const *argv[])
{
    // Variables
    Operation *op = NULL, *result;
    char option;

    // Load Operations from DB
    op = loadOpData(op);

    while (option != 'x')
    {
        // Variables
        int index, id, idMachine, time;

        system("clear");

        printf("------------------------------------------------------------------\n");
        printf("|                        WELCOME TO FJSSP                        |\n");
        printf("------------------------------------------------------------------\n\n");

        printf("Operations:\n");
        printf("a) Insert new Operation   b) Edit Operation    c) Delete Operation\n");
        printf("d) See All                e) Get lower time    f) Get higher time\n");
        printf("g) Get average time       x) Exit\n\n");

        // Ask for option to execute
        printf("Option: ");
        scanf(" %c", &option);
        option = tolower(option); // Put the result of the user to lower

        switch (option)
        {
            case 'a':

                system("clear");

                printf("---------------------------------------------------------------\n");
                printf("|                        Add Operation                        |\n");
                printf("---------------------------------------------------------------\n\n");

                // Ask for id, id of Machine and time
                printf("Insert id of operation: ");
                scanf("%d", &id);

                printf("Insert Machine number: ");
                scanf("%d", &idMachine);

                printf("Insert time of Machine: ");
                scanf("%d", &time);
                
                // Add a new operation and return True or False
                result = addOperation(op, id, idMachine, time);
                
                // Print if is Successfull or if there is a problem
                if (result != NULL)
                {
                    op = result;
                    printf("\nSuccessfully Inserted!!\n\n");
                }
                else
                    printf("\nSomething went wrong!!\n\n");

                break;
            
            case 'b':

                system("clear");

                printf("----------------------------------------------------------------\n");
                printf("|                        Edit Operation                        |\n");
                printf("----------------------------------------------------------------\n\n");

                // Show all operations
                showAll(op);

                // Ask for index, id, id of Machine and time
                printf("\nInsert index to update: ");
                scanf("%d", &index);

                printf("Insert id of operation to change: ");
                scanf("%d", &id);

                printf("Insert Machine number to change: ");
                scanf("%d", &idMachine);

                printf("Insert time of Machine to change: ");
                scanf("%d", &time);

                result = editOperation(op, index, id, idMachine, time);                

                if (result != NULL)
                {
                    op = result;
                    printf("Successfully Updated!!\n\n");
                }
                else
                    printf("Something went wrong!!\n\n");
                    
                break;

            case 'c':

                system("clear");

                printf("-----------------------------------------------------------------\n");
                printf("|                       Delete Operation                        |\n");
                printf("-----------------------------------------------------------------\n\n");

                // Show all operations
                showAll(op);

                // Ask for index
                printf("\nInsert index to delete: ");
                scanf("%d", &index);

                result = deleteOperation(op, index);

                if (result != NULL)
                {
                    op = result;
                    printf("Successfully Deleted!!\n\n");
                }
                else
                    printf("Something went wrong!!\n\n");
                    
                break;

            case 'd':

                system("clear");

                printf("----------------------------------------------------------------\n");
                printf("|                      See All Operation                        |\n");
                printf("----------------------------------------------------------------\n\n");

                // Show all operations
                showAll(op);
                break;

            case 'e':

                system("clear");

                printf("----------------------------------------------------------------\n");
                printf("|                   See All Operation by Lower Time            |\n");
                printf("----------------------------------------------------------------\n\n");

                // Get the lower time
                showShorter(op);
                
                break;

            case 'f':

                system("clear");

                printf("----------------------------------------------------------------\n");
                printf("|                   See All Operation by Higher Time            |\n");
                printf("----------------------------------------------------------------\n\n");

                showLonger(op);
                    
                break;

            case 'g':

                system("clear");

                printf("----------------------------------------------------------------\n");
                printf("|                 See All Operation by Average Time            |\n");
                printf("----------------------------------------------------------------\n\n");

                // Get Average by Operation
                showAverage(op);

                printf("\n\n");
                    
                break;

            case 'x':
                // Save Operations to DB
                saveOpData(op);
                // Clean List Operation
                clean(op);

                printf("See you next time!\n\n");  
                break;
            
            default:
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

/*
int main2(int argc, char const *argv[]) 
{
    int size = 20;
    Operation* operations = malloc(sizeof(Operation)*size);
    int total = 0;

    // Load Operations from DB
    loadOpData(operations, &total);

    // Show operations
    printf("After Loading:\n");
    for (int i = 0; i < total; i++)
    {
        Operation op = operations[i];
        printf("%d - %d - %d\n", op.id, op.idMachine, op.time);
    }
    printf("\n\n");

    // Get Lower 
    int n = operations[total-1].id;
    Operation* newOperations;
    newOperations = getShorter(operations, total, n);

    // Show operations
    printf("\nAfter getShorter:\n");
    for (int i = 0; i < n; i++)
    {
        Operation op = newOperations[i];
        printf("%d - %d - %d\n", op.id, op.idMachine, op.time);
    }

    free(newOperations);


    // Get Higher
    newOperations = getLonger(operations, total, n);

    // Show operations
    printf("\nAfter getLonger:\n");
    for (int i = 0; i < n; i++)
    {
        Operation op = newOperations[i];
        printf("%d - %d - %d\n", op.id, op.idMachine, op.time);
    }

    free(newOperations);


    // Get Average
    printf("\nAfter Average:\n");
    for (int i = 0; i < n; i++)
    {
        float average = getAverage(operations, total, (i+1));

        printf("Average: %d - %.2f\n", (i+1), average);
    }
    


    
    /*
    // Add Operations
    addOperation(operations, &total, size, 1, 1, 4);
    addOperation(operations, &total, size, 1, 3, 5);
    addOperation(operations, &total, size, 2, 2, 4);
    addOperation(operations, &total, size, 2, 4, 5);
    addOperation(operations, &total, size, 3, 3, 5);
    addOperation(operations, &total, size, 3, 5, 6);
    addOperation(operations, &total, size, 4, 4, 5);
    addOperation(operations, &total, size, 4, 5, 5);
    addOperation(operations, &total, size, 4, 6, 4);
    addOperation(operations, &total, size, 4, 7, 5);
    addOperation(operations, &total, size, 4, 8, 9);

    // Show operations
    printf("After Adding:\n");
    for (int i = 0; i < total; i++)
    {
        Operation op = operations[i];
        printf("%d - %d - %d\n", op.id, op.idMachine, op.time);
    }
    
    // Edit Operations
    editOperation(operations, 1, size, 1, 1, 2);
    editOperation(operations, 88, size, 2, 1, 2);
    editOperation(operations, 3, size, 3, 1, 2);

    // Show operations
    printf("\nAfter Editing:\n");
    for (int i = 0; i < total; i++)
    {
        Operation op = operations[i];
        printf("%d - %d - %d\n", op.id, op.idMachine, op.time);
    }

    
    // Delete Operations
    deleteOperation(operations, &total, 1, size);
    deleteOperation(operations, &total, 20, size);
    deleteOperation(operations, &total, 3, size);


    // Show operations
    printf("\nAfter Removing:\n");
    for (int i = 0; i < total; i++)
    {
        Operation op = operations[i];
        printf("%d - %d - %d\n", op.id, op.idMachine, op.time);
    }

    
    // Save Operations to DB
    saveOpData(operations, total);
    

    return 0;
}
*/