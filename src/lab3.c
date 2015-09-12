/* Author: Garrett Scholtes
 * Date:   2015-09-09
 *
 * Lab3 - CS4029
 * 
 * This module uses multiple synchronous threads
 * to increment some values in an array.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>

#define ARR_SIZE 1000000

static struct task_struct *t1;
static struct task_struct *t2;
static int arr[ARR_SIZE];
static int idx = 0;

static int stat[ARR_SIZE] = { 0 };
static int cs1 = 0;
static int cs2 = 0;

MODULE_LICENSE("GPL");

int incrementer( void *ptr_void ) {
    long ptr;
    ptr = (long)ptr_void;

    printk(KERN_INFO "Consumer TID %ld\n", ptr);

    while(idx < ARR_SIZE) {
        arr[idx++] += 1;
        schedule();

        // Do a stats test (described in part 1)
        if(ptr == 1) {
            cs1++;
        } else {
            cs2++;
        }
    }
    return 0;
}

int init_module( void ) {
    long id1;
    long id2;

    printk("lab3 module installing\n");

    id1 = 1;
    id2 = 2;
    t1 = kthread_create(incrementer, (void*)id1, "inc1");
    t2 = kthread_create(incrementer, (void*)id2, "inc2");
    if(t1 && t2) {
        printk(KERN_INFO "Starting...\n");
        wake_up_process(t1);
        wake_up_process(t2);
    } else {
        printk(KERN_EMERG "Error\n");
    }

    return 0;
}

void cleanup_module( void ) {
    int i;

    printk("lab3 module uninstalling\n");

    for(i = 0; i < ARR_SIZE; i++) {
        stat[arr[i]] += 1;
    }

    for(i = 0; i < ARR_SIZE; i++) {
        if(stat[i] > 0) {
            printk("[HIT] stat[%d] = %d\n", i, stat[i]);
        }
    }

    printk("cs1 =     %d\n", cs1);
    printk("cs2 =     %d\n", cs2);
    printk("cs1+cs2 = %d\n", cs1+cs2);

    printk("lab3 module uninstalled\n");
    return;
}