#include "../class/class.h"

/**
 * @brief Load data of Object.
 * Open the file of jobs and get line by line and saves into the list.
 * @param jb A list of jobs.
 * @return Job* return the list Job.
 */
Job* loadData(Job* jb);

/**
 * @brief Load data of Object by location.
 * Open the file of jobs and get line by line and saves into the list.
 * @param jb A list of jobs.
 * @param loc The location of the file
 * @return Job* return the list Job.
 */
Job* loadDataByLoc(Job* jb, char* loc);

/**
 * @brief Save data of Object.
 * Open the file of operations and insert all the information.
 * @param op A list of jobs.
 */
void saveData(Job* jb);

/**
 * @brief Save the Escalation.
 * 
 * @param ord The list of orders.
 * @param totalM The total machine.
 * @param totalJb The total job.
 */
void saveEscalation(TopOrders* ord, int totalM, int totalJb);

//---------------- Function --------------------

/**
 * @brief Get the Combinations object.
 * Get all the combinations of Operations in jobs.
 * @param jb The list of Jobs.
 * @return Job* return the list Job.
 */
Job* getCombinations(Job* jb);

/**
 * @brief Get the Lower Combinations object.
 * Get the combinations of job with lowest time.
 * @param jb The list of Jobs.
 * @return Job* return the list Job.
 */
Job* getLowerCombinations(Job* jb);

/**
 * @brief Get the Best Combinations object.
 * 
 * @param jb The list of Jobs.
 * @return Job* return the list Job.
 */
Job* getBestCombinations(Job* jb);

/**
 * @brief Get the Combinations Jb object.
 * Get all the combinations of jobs.
 * @param jb The list of Jobs.
 * @return ProcessPlan* return the list Process Plan.
 */
ProcessPlan* getCombinationsJb(Job* jb);

/**
 * @brief Get the Possibilities object.
 * Get all the possibilities and save into escalation.
 * @param pplan The list Process Plan.
 */
void getPossibilities(ProcessPlan* pplan);

//ProcessPlan* getBestCombinations(ProcessPlan* pplan);
//Job* getHighestCombinations(Job* jb);
