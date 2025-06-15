#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Obulesh");
MODULE_DESCRIPTION("Timer Module using Jiffies");

static struct timer_list my_timer;
void timer_callback(struct timer_list *t);

void timer_callback(struct timer_list *t)
{
    pr_info("Obu Timer Callback executed at jiffies=%lu (~%lu sec)\n", jiffies, jiffies / HZ);

    mod_timer(&my_timer, jiffies + msecs_to_jiffies(2000));
}

static int __init timer_init(void)
{
    pr_info("Obu Timer Module Loaded\n");

    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(2000));
    return 0;
}

static void __exit timer_exit(void)
{
    del_timer(&my_timer);
    pr_info("Obu Timer Module Unloaded\n");
}

module_init(timer_init);
module_exit(timer_exit);

