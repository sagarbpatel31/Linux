#include "header.h"

struct k_list {
struct list_head test_list;
int temp;
};
struct k_list *one,*two,*three,*entry;

struct list_head test_head;
struct list_head *ptr;
static __init int create_list_init(void) {

one=kmalloc(sizeof(struct k_list *),GFP_KERNEL);
two=kmalloc(sizeof(struct k_list *),GFP_KERNEL);
three=kmalloc(sizeof(struct k_list *),GFP_KERNEL);

one->temp=10;
two->temp=20;
three->temp=30;

INIT_LIST_HEAD(&test_head);
list_add(&one->test_list,&test_head);
list_add(&two->test_list,&test_head);
list_add(&three->test_list,&test_head);
list_for_each(ptr,&test_head){
entry=list_entry(ptr,struct k_list,test_list);


printk(KERN_INFO "\n Hello %d  \n ", entry->temp);

}
return 0;

}

static void __exit create_list_exit(void) {
	kfree(one);	
	kfree(two);
	kfree(three);
	printk(KERN_INFO"Removed...\n");
}

module_init(create_list_init);
module_exit(create_list_exit);

