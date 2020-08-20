#include <linux/version.h>

// Inspired by: https://github.com/NixOS/nixpkgs/commit/90412f5fbc5448387c086b4cc42b7bac9d7ca238#diff-8707a59acd1c6375512d5de1f858d9e4R3
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,0)
#include <linux/sched/task_stack.h>
#else
#include <linux/sched.h>
#endif

#include <linux/module.h>
#include <linux/pid.h>
#include <asm/processor.h>

#include "task_state.h"

unsigned long KSTK_ESP_PRIVATE(struct task_struct *task) // Can't use KSTK_ESP, it's not available for this module - perhaps is kernel use only
{
	return task_pt_regs(task)->sp;
}

unsigned long KSTK_EBP_PRIVATE(struct task_struct *task)
{
	return task_pt_regs(task)->bp;
}

unsigned long KSTK_EIP_PRIVATE(struct task_struct *task)
{
	return task_pt_regs(task)->ip;
}

char *task_state(int pid, char* buf, size_t buf_size)
{
    struct task_struct *task = NULL;
    unsigned long esp, ebp, eip;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        return "TASK NOT FOUND";
    }
    esp = KSTK_ESP_PRIVATE(task);
    ebp = KSTK_EBP_PRIVATE(task);
    eip = KSTK_EIP_PRIVATE(task);
    snprintf(buf, buf_size, "TASK STATE SP:\n%016lX %016lX %016lX", esp, ebp, eip);
    return buf;
}