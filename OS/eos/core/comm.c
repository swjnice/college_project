/********************************************************
 * Filename: core/comm.c
 *  
 * Author: jtlim, RTOSLab. SNU.
 * 
 * Description: message queue management. 
 ********************************************************/
#include <core/eos.h>

void eos_init_mqueue(eos_mqueue_t *mq, void *queue_start, int16u_t queue_size, int8u_t msg_size, int8u_t queue_type) {
    mq->queue_start = queue_start;
    mq->queue_size = queue_size;
    mq->msg_size = msg_size;
    mq->queue_type = queue_type;
    mq->front = queue_start;
    mq->rear = (int8u_t*)queue_start - 1;
    eos_init_semaphore(&mq->putsem, queue_size, queue_type);
    eos_init_semaphore(&mq->getsem, 0, queue_type);
}

int8u_t eos_send_message(eos_mqueue_t *mq, void *message, int32s_t timeout) {
    if(eos_acquire_semaphore(&mq->putsem, timeout)){
        //copy message
        //PRINT("PUT MESSAGE\n");
        int8u_t* rear = (int8u_t*)mq->rear;
        int8u_t* msg = (int8u_t*)message;
        //PRINT("rear : %x, msg : %x\n", rear, msg);

        for(int8u_t i = 0 ; i< mq->msg_size; i++){
            ++rear;
            *rear = msg[i];
            if(rear >= (int8u_t*)mq->queue_start + mq->queue_size*mq->msg_size){
                rear = (int8u_t*)mq->queue_start - 1;
            }
        }
        mq->rear = rear;
        //PRINT("Put Message done.\n");
        eos_release_semaphore(&mq->getsem);
    }
    else{
        return;
    }
}

int8u_t eos_receive_message(eos_mqueue_t *mq, void *message, int32s_t timeout) {
    if(eos_acquire_semaphore(&mq->getsem, timeout)){
        //PRINT("acquire_semaphore succeed.\n");
        int8u_t* front = (int8u_t*)mq->front;
        int8u_t* msg = (int8u_t*)message;

        for(int8u_t i = 0; i< mq->msg_size; i++){
            msg[i] = *front;
            front++;
            if(front > (int8u_t*)mq->queue_start + mq->queue_size*mq->msg_size){
                front = (int8u_t*)mq->queue_start;
            }
        }

        mq->front = front;
        eos_release_semaphore(&mq->putsem);
    }
    else{
        return;
    }
}
