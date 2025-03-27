#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

struct task_struct *child_task;
static int parent_pid;

static int child_function(void *data) {
    char *buffer;

    buffer = kmalloc(1024, GFP_KERNEL);
    if (!buffer) {
        printk(KERN_ERR "Memory allocation failed\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "├── Child PID: %d, Memory allocated at: %p\n", current->pid, buffer);
    kfree(buffer);

    return 0;
}

static int __init my_module_init(void) {
    int i;
    parent_pid = current->pid; // Get the parent PID
    printk(KERN_INFO "Loading module\n");
    printk(KERN_INFO "Parent PID: %d\n", parent_pid);

    for (i = 0; i < 3; i++) {
        child_task = kthread_create(child_function, NULL, "my_kthread%d", i);
        
        if (IS_ERR(child_task)) {
            printk(KERN_ERR "Failed to create kthread\n");
            return PTR_ERR(child_task);
        }
        
        wake_up_process(child_task);
    }

    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Removing module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple module to create child threads and allocate memory");
MODULE_AUTHOR("Your Name");
