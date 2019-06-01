#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>


struct my_data{
	int x,y,z;
	struct list_head mlist;
};

struct list_head *data_list;

struct my_data* createNode(int x, int y, int z) {
	struct 	my_data *mdata ;
	
	mdata = kzalloc(sizeof(struct my_data), GFP_KERNEL);
	if( mdata == NULL){
		pr_err("can't alloc in %s\n", __FUNCTION__);
		return NULL;
	}
	mdata->x = x;
	mdata->y = y;
	mdata->z = z;

	return mdata;

}
void showAllNode(struct list_head *head) {
	struct my_data *mdata_tmp;
	struct list_head *tmp_head = head;
	
	list_for_each_entry(mdata_tmp, tmp_head, mlist) {

		pr_info("x %d y: %d z :%d \n", mdata_tmp->x, mdata_tmp->y, mdata_tmp->z);	

		pr_info("mlist %p , tmp_head %p", &mdata_tmp->mlist, tmp_head);

	}

}
void freeAllNode(struct list_head *head) {
	struct my_data *tmp,*obj_tmp;
	struct list_head *new_pos ;
	int i = 0;
	
	tmp = list_entry(head->next, typeof(*tmp), mlist);
	do {
		pr_info("mx %d my: %d mz :%d \n", tmp->x, tmp->y, tmp->z);	
		new_pos = tmp->mlist.next;
		obj_tmp = list_entry(new_pos, typeof(*obj_tmp),mlist);
		pr_info("before del tmp prev %p, tmp->next %p\n", &tmp->mlist.prev,&tmp->mlist.next);

		list_del(&tmp->mlist);
		kfree(tmp);

		tmp = obj_tmp;
		pr_info("after del tmp prev %p, tmp->next %p\n", &tmp->mlist.prev,&tmp->mlist.next);
		i++;

	}
	while(&tmp->mlist != head && i < 10);


}
void testAddData(struct list_head *head){
	int i = 0;	
	struct my_data *tmpNode;
	
	for(i = 0; i< 4; i++ ){
		tmpNode = createNode(i, i+1, i+2);	
		list_add(&tmpNode->mlist, head);
	}
}

static int __init my_module_init(void) {


	pr_info("%s func start successfully\n", __FUNCTION__);
	data_list = kzalloc(sizeof(struct list_head), GFP_KERNEL);	

	if (data_list == NULL) { pr_err("can't allocate for data list\n");
		return -ENOMEM;
	}

	INIT_LIST_HEAD(data_list);
	testAddData(data_list);
	showAllNode(data_list);	
	freeAllNode(data_list);

	return 0;
}

static void __exit my_module_exit(void) {
	pr_info("%s func exit successfully\n", __FUNCTION__);

}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LONGVH");
MODULE_DESCRIPTION("Link list example");
