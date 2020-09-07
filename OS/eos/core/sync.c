/********************************************************
 * Filename: core/sync.c
 * 
 * Author: wsyoo, RTOSLab. SNU.
 * 
 * Description: semaphore, condition variable management.
 ********************************************************/
#include <core/eos.h>

void eos_init_semaphore(eos_semaphore_t *sem, int32u_t initial_count, int8u_t queue_type) {
	/* initialization */
	sem->count = (int32s_t)initial_count;
	sem->queue_type = queue_type;
	sem->wait_queue = NULL;
}

int32u_t eos_acquire_semaphore(eos_semaphore_t *sem, int32s_t timeout) {
	//PRINT("sem : %x, timeout : %d\n", sem, timeout);
    eos_disable_interrupt();
	if(sem->count > 0){
		sem->count--;
		eos_enable_interrupt();
		return 1;
	}
	else{
		if(timeout == -1){
			//PRINT("Semaphore acquire failed.\n");
			eos_enable_interrupt();
			return 0;
		}
		else if(timeout == 0){					
			while(1){
            // set current task WAITING
			//PRINT("Go INTO WAITING QUEUE\n");
			eos_get_current_task()->state = 3;
			eos_get_current_task()->sem = sem;
            if(sem->queue_type == 0){
                _os_add_node_tail(&sem->wait_queue, &eos_get_current_task()->node);
            }
            else if(sem->queue_type == 1){
                _os_add_node_priority(&sem->wait_queue, &eos_get_current_task()->node);
            }
			eos_enable_interrupt();
			eos_schedule();
            eos_disable_interrupt();
            if(sem->count > 0){
                sem->count--;
                eos_enable_interrupt();
                return 1;
            }
			}
		}
		else{
			eos_alarm_t sem_alarm;
            sem_alarm.alarm_queue_node.next = NULL;
            sem_alarm.alarm_queue_node.previous = NULL;
			eos_set_alarm(eos_get_system_timer(), &sem_alarm, eos_get_system_timer()->tick + timeout, _os_getout_semaphore_wait_queue, eos_get_current_task());
            //PRINT("Alarm set\n");
			while(1){
            // set current task WAITING
			//PRINT("Go INTO WAITING QUEUE\n");
			eos_get_current_task()->state = 3;
			eos_get_current_task()->sem = sem;
            if(sem->queue_type == 0){
                _os_add_node_tail(&sem->wait_queue, &eos_get_current_task()->node);
            }
            else if(sem->queue_type == 1){
                _os_add_node_priority(&sem->wait_queue, &eos_get_current_task()->node);
            }
            //PRINT("go into queue\n");
			eos_enable_interrupt();
			eos_schedule();
            eos_disable_interrupt();
            if(sem->count > 0){
                sem->count--;
                eos_enable_interrupt();
                return 1;
            }
            if(eos_get_current_task()->sem == NULL){
                //PRINT("Get out from semaphore\n");
				return 0;
			}
			}
		}
	}
}

void eos_release_semaphore(eos_semaphore_t *sem) {
	eos_disable_interrupt();
	sem->count++;
	if(sem->wait_queue){
		// set READY
		eos_tcb_t* next_task = sem->wait_queue->ptr_data;
		next_task->sem = NULL;
        _os_remove_node(&sem->wait_queue, &next_task->node);
		_os_wakeup_sleeping_task(next_task);
		eos_enable_interrupt();
	}
	else{
		eos_enable_interrupt();
	}
}

void eos_init_condition(eos_condition_t *cond, int32u_t queue_type) {
	/* initialization */
	cond->wait_queue = NULL;
	cond->queue_type = queue_type;
}

void eos_wait_condition(eos_condition_t *cond, eos_semaphore_t *mutex) {
	/* release acquired semaphore */
	eos_release_semaphore(mutex);
	/* wait on condition's wait_queue */
	_os_wait(&cond->wait_queue);
	/* acquire semaphore before return */
	eos_acquire_semaphore(mutex, 0);
}

void eos_notify_condition(eos_condition_t *cond) {
	/* select a task that is waiting on this wait_queue */
	_os_wakeup_single(&cond->wait_queue, cond->queue_type);
}
