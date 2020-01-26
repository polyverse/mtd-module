#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

#define BUFSIZE  100

MODULE_LICENSE("https://polyverse.com/eula/");
MODULE_AUTHOR("Mariusz Borsa");

static int thread_id = -1;
module_param(thread_id, int, 0660);

static struct proc_dir_entry *ent;

static ssize_t mtd_write(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos) 
{
	int n, c, t_id;
	char buf[BUFSIZE];
	if(*ppos > 0 || count > BUFSIZE)
		return -EFAULT;
	if(copy_from_user(buf, ubuf, count))
		return -EFAULT;
	n = sscanf(buf, "%d", &t_id);
	if(n != 1)
		return -EFAULT;
	thread_id = t_id; 
	c = strlen(buf);
	*ppos = c;
	return c;
}

static ssize_t mtd_read(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	char buf[BUFSIZE];
	int l = 0;
	if(*ppos > 0 || count < BUFSIZE)
		return 0;
	l += sprintf(buf, "thread_id = %d\n", thread_id);
	
	if(copy_to_user(ubuf, buf, l))
		return -EFAULT;
	*ppos = l;
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
	ent = proc_create("polyverse_mtd",0660,NULL,&mtd_ops);
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
