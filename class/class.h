#include <stdbool.h>

/**
 * @brief An struct type Operation.
 * 
 */
typedef struct oper
{
    int id;                 /**< id of operation */
    int idMachine;          /**< id Machine */
    int time;               /**< time of the Machine */
    struct oper *next;      /**< the next inserted*/
} Operation;

/**
 * @brief Add a new Operation.
 * Receives the list and the values and add a new operation.
 * After inserted into a operation, returns it with a pointer to the previous Operation.
 * @param op A list of operations.
 * @param id The value id int to add.
 * @param idMachine The value idMachine int to add.
 * @param time The value time int to add.
 * @return Operation* return the operation.
 */
Operation* addOperation(Operation* op, int id, int idMachine, int time);

/**
 * @brief Add a new Operation without order.
 * Receives the list and the values and add a new operation.
 * This Function is used to get all possibilities for processign the process plan.
 * @param op A list of operations.
 * @param id The value id int to add.
 * @param idMachine The value idMachine int to add.
 * @param time The value time int to add.
 * @return Operation* return the operation.
 */
Operation* addOperationNOrder(Operation* op, int id, int idMachine, int time);

/**
 * @brief Edit a Operation.
 * Receives the list and the values and edit the operation. 
 * @param op The list of operations.
 * @param index The index of the list to change.
 * @param id The value id int.
 * @param idMachine The value idMachine int.
 * @param time The value time int.
 * @return Operation* return the operation.
 */
Operation* editOperation(Operation* op, int index, int id, int idMachine, int time);

/**
 * @brief Delete a Operation.
 * Receives the list and the value index and delete the operation.
 * @param op The list of operations.
 * @param index The index of the list to change.
 * @return Operation* return the operation.
 */
Operation* deleteOperation(Operation* op, int index);

/**
 * @brief Clean the list Operation.
 * Use to free all the Operations from the memory.
 * @param op The list of operations.
 */
void clean(Operation* op);


typedef struct job
{
    int id;
    struct oper *op;
    struct job *next;
} Job;

Job* addJob(Job* jb, int id);

Job* deleteJob(Job* jb, int id);

Job* addOpJob(Job* jb, int idJob, int idOp, int idMachine, int time);

Job* addOpJobNOrder(Job* jb, int idJob, int idOp, int idMachine, int time);

Job* editOpJob(Job* jb, int idJob, int indexOp, int idOp, int idMachine, int time);

Job* deleteOpJob(Job* jb, int idJob, int indexOp);

Job* createJob(Job* jb, int idJob, Operation* op);

Job* createJobOp(Job* jb, int idJob, Operation* op);

Job* addJobOp(Job* jb, int idJob, Operation* op);

typedef struct pPlan
{
    struct job *jb;
    struct pPlan *next;
} ProcessPlan;

ProcessPlan* createPPlanOp(ProcessPlan* pplan, Job* jb);
ProcessPlan* createPPlanJb(ProcessPlan* pplan, Job* jb);

ProcessPlan* addPPlanJb(ProcessPlan* pplan, Job* jb);


typedef struct shiftingBottleneck 
{
    int idMachine;
    int idJb;
    int idOp;
    int time;
    int waitTime;
    int timeFinish;
    struct shiftingBottleneck *next;
} ShiftingBottleneck;

typedef struct orders
{
    struct shiftingBottleneck **data;
    int time;
    int lowerBone;
    int size;
    struct orders *next;
} Orders;
