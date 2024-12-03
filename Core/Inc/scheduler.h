#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
} sTasks;

#define SCH_MAX_TASKS 40
#define TICK 10

void SCH_Add_Task(void(*pFunc)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Delete_Task(int index);
void SCH_Dispatch_Tasks(void);

#endif /* INC_SCHEDULER_H_ */
