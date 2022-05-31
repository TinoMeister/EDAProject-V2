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
 * @brief An struct type Job.
 * 
 */
typedef struct job
{
    int id;
    struct oper *op;
    struct job *next;
} Job;

/**
 * @brief Add a new Job
 * Receives the list and the id and create a new job.
 * @param jb The list of jobs.
 * @param id The value id job int.
 * @return Job* return the list of jobs.
 */
Job* addJob(Job* jb, int id);

/**
 * @brief Delete a Job
 * Receives the list and the id and delete a job.
 * @param jb The list of jobs.
 * @param id The value id job int.
 * @return Job* return the list of jobs.
 */
Job* deleteJob(Job* jb, int id);

/**
 * @brief Clean the list Job.
 * Use to free all the Operations and Jobs from the memory.
 * @param jb The list of Jobs.
 */
void clean(Job* jb);

/**
 * @brief Add Operation to a job.
 * Receives the list and the id of Job, id of Operation and the id of Machine
 * and time and add a new Operation to a Job by that id in order.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param idOp The value id of Operation int.
 * @param idMachine The value id of Machine int.
 * @param time The value time of Operation int.
 * @return Job* return the list Job.
 */
Job* addOpJob(Job* jb, int idJob, int idOp, int idMachine, int time);

/**
 * @brief Add Operation to a job.
 * Receives the list and the id of Job, id of Operation and the id of Machine
 * and time and add a new Operation to a Job by that id without order.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param idOp The value id of Operation int.
 * @param idMachine The value id of Machine int.
 * @param time The value time of Operation int.
 * @return Job* return the list Job.
 */
Job* addOpJobNOrder(Job* jb, int idJob, int idOp, int idMachine, int time);

/**
 * @brief Edit a Operation by a certain Job.
 * Receives the list and the id of Job, id of Operation and the id of Machine
 * and time and edit the Operation to a Job by id in that index.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param indexOp The value index for the position of the Operation in the list Operation.
 * @param idOp The value id of Operation int.
 * @param idMachine The value id of Machine int.
 * @param time The value time of Operation int.
 * @return Job* return the list Job.
 */
Job* editOpJob(Job* jb, int idJob, int indexOp, int idOp, int idMachine, int time);

/**
 * @brief 
 * Receives the list and the id of Job and removes the Operation 
 * to a Job by id in that index.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param indexOp The value index for the position of the Operation in the list Operation.
  * @return Job* return the list Job.
 */
Job* deleteOpJob(Job* jb, int idJob, int indexOp);

/**
 * @brief Create a Job object and saves the Operation
 * Create a Job object and saves the first element on the list Operation 
 * to that job without order.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param op The list of Operations.
 * @return Job* return the list Job.
 */
Job* createJob(Job* jb, int idJob, Operation* op);

/**
 * @brief Create a Job object and saves the list Operation
 * Create a Job object and saves the list Operation to that job without order.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param op The list of Operations.
 * @return Job* return the list Job.
 */
Job* createJobOp(Job* jb, int idJob, Operation* op);

/**
 * @brief Add a new Operation.
 * Add a new Operation into the last element on the list Job.
 * @param jb The list of jobs.
 * @param idJob The value id of job int.
 * @param op The list of Operations.
 * @return Job* return the list Job.
 */
Job* addJobOp(Job* jb, int idJob, Operation* op);

/**
 * @brief A struct of Process Plan.
 * A list of all the jobs.
 */
typedef struct pPlan
{
    struct job *jb;
    struct pPlan *next;
} ProcessPlan;

/**
 * @brief Create a Process Plan.
 * Create a Process Plan with the first Job.
 * @param pplan The listt of Process Plan.
 * @param jb The list of Jobs.
 * @return ProcessPlan* return the list of Process Plan.
 */
ProcessPlan* createPPlanOp(ProcessPlan* pplan, Job* jb);

/**
 * @brief Create a Process Plan.
 * Create a Process Plan with all Jobs.
 * @param pplan The listt of Process Plan.
 * @param jb The list of Jobs.
 * @return ProcessPlan* return the list of Process Plan.
 */
ProcessPlan* createPPlanJb(ProcessPlan* pplan, Job* jb);

/**
 * @brief Create a Process Plan.
 * Add a new Job to the last element on the list Process Plan.
 * @param pplan The listt of Process Plan.
 * @param jb The list of Jobs.
 * @return ProcessPlan* return the list of Process Plan.
 */
ProcessPlan* addPPlanJb(ProcessPlan* pplan, Job* jb);

/**
 * @brief A struct shiftingBottleneck.
 * Used to do the technique of shiftingBottleneck.
 */
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

/**
 * @brief A struct of Orders
 * Saves all the information of the technique shiftingBottleneck and the total time also the lowerBone.
 */
typedef struct orders
{
    struct shiftingBottleneck **data;
    int time;
    int lowerBone;
    int size;
    struct orders *next;
} Orders;

/**
 * @brief A struct of the best Orders.
 * Used to save the best escalations.
 */
typedef struct toporders
{
    struct orders **orders;
    struct job *jb;
    int time;
    struct toporders *next;
} TopOrders;
