#include "../class/class.h"

/**
 * @brief Load data of Object.
 * Open the file of operations and get line by line and saves into the list.
 * @param op A list of operations.
 * @return Operation* return the operation.
 */
Job* loadData(Job* jb);

/**
 * @brief Save data of Object.
 * Open the file of operations and insert all the information.
 * @param op A list of operations.
 */
void saveData(Job* jb);

Job* getCombinations(Job* jb);
Job* getLowerCombinations(Job* jb);
Job* getHighestCombinations(Job* jb);
Job* getBestCombinations(Job* jb);
//ProcessPlan* getBestCombinations(ProcessPlan* pplan);
ProcessPlan* getCombinationsJb(Job* jb);

void getPossibilities(ProcessPlan* pplan);