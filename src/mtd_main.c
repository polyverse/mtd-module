#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

#include "task_state.h"

#define BUFSIZE 0x10000

MODULE_LICENSE("GPL"); // TODO need this for use of find_vpid in task_state.c, will need to reimplement using other means later
// MODULE_LICENSE("https://polyverse.com/eula/"); 
MODULE_AUTHOR("Mariusz Borsa");

static int thread_id = -1;
module_param(thread_id, int, 0660);

static struct proc_dir_entry *ent;
static char buf[BUFSIZE];
static char buf_task[BUFSIZE];

static ssize_t mtd_write(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos) 
{
	int n, c, t_id;
	// printk(KERN_ALERT "Polyverse MTD mtd_write\n");
	if(*ppos > 0 || count > BUFSIZE) {
		printk(KERN_ALERT "Polyverse MTD mtd_write (*ppos > 0 || count < BUFSIZE) *ppos: %lld, count: %ld\n", *ppos, count);
		return -EFAULT;
	}
	if(copy_from_user(buf, ubuf, count)) {
		printk(KERN_ERR "Polyverse MTD copy_from_user(buf, ubuf, count) failed - returning EFAULT\n");
		return -EFAULT;
	}
	n = sscanf(buf, "%d", &t_id);
	if(n != 1) {
		printk(KERN_ERR "Polyverse MTD sscanf(buf, \"d\", &t_id) != 1 - returning EFAULT\n");
		return -EFAULT;
	}
	// printk(KERN_ALERT "Polyverse MTD mtd_write set thread_id to %d\n", t_id);
	thread_id = t_id; 
	c = strlen(buf);
	*ppos = c;
	// printk(KERN_ALERT "Polyverse MTD mtd_write return\n");
	return c;
}

static ssize_t mtd_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) 
{
	int l = 0;
	char *ts = NULL;
	// printk(KERN_ALERT "Polyverse MTD mtd_read\n");
	if(*ppos > 0 || (*ppos + count) >= BUFSIZE) {
		// printk(KERN_ALERT "Polyverse MTD mtd_read *ppos > 0 || (*ppos + count) >= BUFSIZE -> EOF . *ppos: %lld, count: %ld\n", *ppos, count);
		return 0;
	}

	ts = task_state(thread_id, buf_task, BUFSIZE);
	if( ts == NULL) {
		printk(KERN_ERR "Polyverse MTD ts == NULL returning EFAULT\n");
		return -EFAULT;
	}
	// printk(KERN_ALERT "Polyverse MTD mtd_read task_state returned %s\n", ts);

	l += sprintf(buf, "THREAD_ID:\n%d\n%s\n", thread_id, ts);
	
	if(copy_to_user(ubuf, buf, l)) {
		printk(KERN_ERR "Polyverse MTD copy_to_user(ubuf, buf, l)) returning EFAULT\n");
		return -EFAULT;
	}
	*ppos = l;
	// printk(KERN_ALERT "Polyverse MTD mtd_read return %s\n", buf);
	return l;
}

static struct file_operations mtd_ops = 
{
	.owner = THIS_MODULE,
	.read = mtd_read,
	.write = mtd_write,
};

static int mtd_init(void)
{
	ent = proc_create("polyverse_mtd", 0660, NULL, &mtd_ops);
	printk(KERN_ALERT "Polyverse MTD up\n");
	return 0;
}

static void mtd_cleanup(void)
{
	proc_remove(ent);
	printk(KERN_WARNING "Polyverse MTD down\n");
}

module_init(mtd_init);
module_exit(mtd_cleanup);
