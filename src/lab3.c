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

MODULE_LICENSE("GPL");

int init_module( void ) {
    printk("lab3 module installing\n");

    return 0;
}

void cleanup_module( void ) {
    printk("lab3 module uninstalling\n");

    return;
}