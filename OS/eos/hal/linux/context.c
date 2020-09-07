#include <core/eos.h>
#include <core/eos_internal.h>
#include "emulator_asm.h"

typedef struct _os_context {
	/* low address */
	int32u_t edi;
	int32u_t esi;
	int32u_t ebx;
	int32u_t edx;
	int32u_t ecx;
	int32u_t eax;
	int32u_t context_eflags;
	int32u_t resume_eip;
	/* high address */	
} _os_context_t;

void print_context(addr_t context) {
	if(context == NULL) return;
	_os_context_t *ctx = (_os_context_t *)context;
	PRINT("reg1  =0x%x\n", ctx->edi);
	PRINT("reg2  =0x%x\n", ctx->esi);
	PRINT("reg3  =0x%x\n", ctx->ebx);
	PRINT("reg1  =0x%x\n", ctx->edx);
	PRINT("reg2  =0x%x\n", ctx->ecx);
	PRINT("reg3  =0x%x\n", ctx->eax);
}

addr_t _os_create_context(addr_t stack_base, size_t stack_size, void (*entry)(void *), void *arg) {
    
	int32u_t* stack_top = (int32u_t*)((int32u_t*)stack_base + stack_size/4);
	int32u_t ret_address = NULL;
	*(stack_top-1) = (int32u_t)arg;
	*(stack_top-2) = ret_address;
	*(stack_top-3) = (int32u_t)entry;
	*(stack_top-4) = 1; // _eflags
	for(int i = 0; i<6; i++){
		*(stack_top-5-i) = NULL;
	}
	return (addr_t)(stack_top-10);
}

void _os_restore_context(addr_t sp) {
    
    __asm__ __volatile__("\
	mov 8(%%ebp), %%esp;\
	pop %%edi;\
	pop %%esi;\
	pop %%ebx;\
	pop %%edx;\
	pop %%ecx;\
	pop %%eax;\
	pop _eflags;\
    mov %%esp, %%ebp;\
    addl $4, %%ebp;\
	ret;"
	::);
}

addr_t _os_save_context() {
    
	__asm__ __volatile__("\
		push $resume_eip;\
		push _eflags;\
		push %%eax;\
        push %%ecx;\
        push %%edx;\ 
        push %%ebx;\
        push %%esi;\
        push %%edi;\
		mov %%esp, %%eax;\
        movl $0, -12(%%ebp);\
		push 4(%%ebp);\
		push 0(%%ebp);\
		mov %%esp, %%ebp;\
		resume_eip:\
		leave;\
		ret;"
		::);

}
