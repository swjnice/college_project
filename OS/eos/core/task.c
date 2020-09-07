/********************************************************
 * Filename: core/task.c
 * 
 * Author: parkjy, RTOSLab. SNU.
 * 
 * Description: task management.
 ********************************************************/
#include <core/eos.h>

#define READY		1
#define RUNNING		2
#define WAITING		3

/*
 * Queue (list) of tasks that are ready to run.
 */
static _os_node_t *_os_ready_queue[LOWEST_PRIORITY + 1];

/*
 * Pointer to TCB of running task
 */
static eos_tcb_t *_os_current_task;

int32u_t eos_create_task(eos_tcb_t *task, addr_t sblock_start, size_t sblock_size, void (*entry)(void *arg), void *arg, int32u_t priority) {
	PRINT("task: 0x%x, priority: %d\n", (int32u_t)task, priority);
    task->priority = priority;
	task->stack_base = sblock_start;
	task->stack_size = sblock_size;
	task->stack_pointer = _os_create_context(sblock_start, sblock_size, entry, arg);
    task->state = READY;
    task->node.ptr_data = task;
    task->node.priority = priority;
    task->sem = NULL;
    _os_set_ready(priority);
	_os_add_node_tail(&(_os_ready_queue[priority]), &(task->node));
    //PRINT("_os_ready_queue[priority] = %x, ptr_data = %x\n", _os_ready_queue[priority], (int32u_t)_os_ready_queue[priority]->ptr_data);
    //PRINT("_os_ready_queue[priority]->next = %x, ptr_data = %x\n", _os_ready_queue[priority]->next, (int32u_t)_os_ready_queue[priority]->next->ptr_data);
    //PRINT("&(task->node) = %x\n", &(task->node));
    //PRINT("task = %x\n", task);
}

int32u_t eos_destroy_task(eos_tcb_t *task) {
}

void eos_schedule() {
	if(_os_current_task != NULL){
		addr_t stack_pointer = _os_save_context();
		if(stack_pointer != NULL){
			_os_current_task ->stack_pointer = stack_pointer;
            if(_os_current_task->state == RUNNING){
                _os_add_node_tail(&(_os_ready_queue[_os_current_task->priority]), &(_os_current_task->node));
                _os_set_ready(_os_current_task->priority);
            }    
        }
        else{
            //PRINT("SAVE RETURN = NULL\n");
            return;
        }
    }

    int next_priority = _os_get_highest_priority();
    //PRINT("next_priority : %d\n", next_priority);
        
    _os_node_t *next_task_node = _os_ready_queue[next_priority];
    _os_current_task = next_task_node->ptr_data;
	
    //PRINT("Restore task : 0x%x\n", _os_current_task);
    //PRINT("task->node.next->task : 0x%x\n)", _os_current_task->node.next->ptr_data);
    //PRINT("_os_ready_queue[next_priority] : 0x%x\n", _os_ready_queue[next_priority]);
    
    
    _os_remove_node(&(_os_ready_queue[next_priority]), &(_os_current_task->node));
    //PRINT("_os_ready_queue[next_priority] : 0x%x\n", _os_ready_queue[next_priority]);
    if(_os_ready_queue[next_priority] == NULL){
        _os_unset_ready(next_priority);
        //PRINT("unset priority : %d\n", next_priority);
    }
    _os_current_task->state = RUNNING;

    _os_restore_context(_os_current_task->stack_pointer);
	
	return;
}

eos_tcb_t *eos_get_current_task() {
	return _os_current_task;
}

void eos_change_priority(eos_tcb_t *task, int32u_t priority) {
}

int32u_t eos_get_priority(eos_tcb_t *task) {
}

void eos_set_period(eos_tcb_t *task, int32u_t period){
    task->period = period;
}

int32u_t eos_get_period(eos_tcb_t *task) {
}

int32u_t eos_suspend_task(eos_tcb_t *task) {
}

int32u_t eos_resume_task(eos_tcb_t *task) {
}

void eos_sleep(int32u_t tick) {
    eos_alarm_t new_alarm;
    //PRINT("Sleep task priority, alarm pt : %d, 0x%x\n", eos_get_current_task()->priority, &new_alarm);
    eos_set_alarm(eos_get_system_timer(), &new_alarm, eos_get_system_timer()->tick + _os_current_task->period - tick, _os_wakeup_sleeping_task, _os_current_task);
    _os_current_task->state = WAITING;
    eos_schedule();
}

void _os_init_task() {
	PRINT("initializing task module.\n");

	/* init current_task */
	_os_current_task = NULL;

	/* init multi-level ready_queue */
	int32u_t i;
	for (i = 0; i < LOWEST_PRIORITY; i++) {
		_os_ready_queue[i] = NULL;
	}
}

void _os_wait(_os_node_t **wait_queue) {
}

void _os_wakeup_single(_os_node_t **wait_queue, int32u_t queue_type) {
}

void _os_wakeup_all(_os_node_t **wait_queue, int32u_t queue_type) {
}

void _os_wakeup_sleeping_task(void *arg) {
    ((eos_tcb_t*)(arg))->state = READY;
    _os_set_ready(((eos_tcb_t*)(arg))->priority);
    _os_add_node_tail(&(_os_ready_queue[((eos_tcb_t*)(arg))->priority]), &(((eos_tcb_t*)(arg))->node));
}

void _os_getout_semaphore_wait_queue(void *arg){
	//PRINT("hanlder start\n");
    eos_tcb_t* task = (eos_tcb_t*)(arg);
    eos_semaphore_t* sem = task->sem;
    //PRINT("task = %x\n", task);
    //PRINT("sem = %x\n", sem);
    //PRINT("sem->wait_queue = %x\n", sem->wait_queue);
    //PRINT("&task->node = %x\n", &task->node);
    //_os_remove_node(&((eos_semaphore_t*)(((eos_tcb_t*)(arg))->sem))->wait_queue, &((eos_tcb_t*)(arg))->node);
    _os_remove_node(&sem->wait_queue, &task->node);
    //PRINT("handler remove\n");
	((eos_tcb_t*)(arg))->sem = NULL;
	_os_wakeup_sleeping_task(arg);
}
