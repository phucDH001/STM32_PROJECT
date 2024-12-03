#include "scheduler.h"

sTasks SCH_Tasks[SCH_MAX_TASKS];
int size = 0;

void insert(sTasks data, int index) {
    for (int i = size; i > index; i--)
    	SCH_Tasks[i] = SCH_Tasks[i - 1];
    SCH_Tasks[index] = data;
    size++;
}

void SCH_Add_Task(void (*pFunc)(), uint32_t DELAY, uint32_t PERIOD) {
    sTasks tmp;
    tmp.pTask = pFunc;
    tmp.Delay = DELAY / TICK;
    tmp.Period = PERIOD / TICK;

    if (size == SCH_MAX_TASKS) return;
    else if (size == 0) insert(tmp, 0);
    else {
        int idx = 0, delay = 0;
        while (idx < size && delay <= tmp.Delay)
        	delay += SCH_Tasks[idx++].Delay;
        if (delay > tmp.Delay) {
            delay -= SCH_Tasks[--idx].Delay;
            tmp.Delay -= delay;
            insert(tmp, idx);
            int delay1 = delay;
            delay += SCH_Tasks[idx++].Delay;
            for (; idx < size; idx++) {
                delay1 += SCH_Tasks[idx].Delay;
                SCH_Tasks[idx].Delay = delay1 - delay;
                delay += SCH_Tasks[idx].Delay;
                delay1 = delay;
            }
            return;
        }
        if (idx < size) delay -= SCH_Tasks[idx].Delay;
        tmp.Delay -= delay;
        insert(tmp, idx);
    }
}

void SCH_Update(void) {
	if (size && SCH_Tasks[0].Delay > 0)
		SCH_Tasks[0].Delay--;
}

void SCH_Delete_Task(int index) {
    size--;
    for (int i = index; i < size; i++)
    	SCH_Tasks[i] = SCH_Tasks[i + 1];
}

void SCH_Dispatch_Tasks(void) {
	if (SCH_Tasks[0].Delay == 0) {
		SCH_Tasks[0].pTask();
		if (SCH_Tasks[0].Period == 0) SCH_Delete_Task(0);
		else {
			sTasks tmp = SCH_Tasks[0];
			SCH_Delete_Task(0);
			SCH_Add_Task(tmp.pTask, tmp.Period * TICK, tmp.Period * TICK);
		}
	}
}
