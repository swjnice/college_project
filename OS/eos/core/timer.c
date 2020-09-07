/********************************************************
 * Filename: core/timer.c
 *
 * Author: wsyoo, RTOSLab. SNU.
 * 
 * Description: 
 ********************************************************/
#include <core/eos.h>

static eos_counter_t system_timer;

int8u_t eos_init_counter(eos_counter_t *counter, int32u_t init_value) {
	counter->tick = init_value;
	counter->alarm_queue = NULL;
	return 0;
}

void eos_set_alarm(eos_counter_t* counter, eos_alarm_t* alarm, int32u_t timeout, void (*entry)(void *arg), void *arg) {
    //PRINT("SETALARM Start\n");
	_os_remove_node(&(counter->alarm_queue), &(alarm->alarm_queue_node));
    //PRINT("remove pass\n");
	if(timeout == 0 || entry == NULL){
		return;
	}
	//PRINT("Alarm pointer : 0x%x\n", alarm);
	//PRINT("Set alarm - priority, alarm : %d, 0x%x\n", eos_get_current_task()->priority, alarm);
	alarm->timeout = timeout;
	alarm->handler = entry;
	alarm->arg = arg;
	alarm->alarm_queue_node.ptr_data = alarm;
    alarm->alarm_queue_node.priority = timeout;
	_os_add_node_priority(&(counter->alarm_queue), &(alarm->alarm_queue_node));
	//PRINT("Alarm queue : 0x%x -> 0x%x\n", (counter->alarm_queue)->ptr_data, (counter->alarm_queue)->next->ptr_data);
}

eos_counter_t* eos_get_system_timer() {
	return &system_timer;
}

void eos_trigger_counter(eos_counter_t* counter) {
	(counter->tick)++;
	PRINT("tick = %d\n", counter->tick);


	_os_node_t* alarm_node = counter->alarm_queue;
	int32u_t alarm_run = 0;
	//PRINT("Alarm_queue : 0x%x\n", alarm_node->ptr_data);
	
	
	if(alarm_node != NULL){
		while (alarm_node) {
			if((counter->tick)==(((eos_alarm_t*)(alarm_node->ptr_data))->timeout)){
				//PRINT("run alarm = 0x%x\n", alarm_pt);
				(*(((eos_alarm_t*)(alarm_node->ptr_data))->handler))(((eos_alarm_t*)(alarm_node->ptr_data))->arg);
				eos_set_alarm(counter, alarm_node->ptr_data, 0, NULL, NULL);
				alarm_run = 1;
				alarm_node = counter->alarm_queue;				
			}
			else{
				break;
			}
		}
	
		if(alarm_run == 1){
			eos_schedule();
		}	
	}
}

/* Timer interrupt handler */
static void timer_interrupt_handler(int8s_t irqnum, void *arg) {
	/* trigger alarms */
	eos_trigger_counter(&system_timer);
}

void _os_init_timer() {
	eos_init_counter(&system_timer, 0);

	/* register timer interrupt handler */
	eos_set_interrupt_handler(IRQ_INTERVAL_TIMER0, timer_interrupt_handler, NULL);
}
