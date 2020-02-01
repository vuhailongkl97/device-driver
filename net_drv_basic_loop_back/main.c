#include <linux/init.h>  
#include <linux/module.h>  
#include <linux/netdevice.h>  
 
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/in.h>

#include <linux/uaccess.h>
#include <linux/io.h>

#include <linux/inet.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/ethtool.h>
#include <net/sock.h>
#include <net/checksum.h>
#include <linux/if_ether.h>	/* For the statistics structure. */
#include <linux/if_arp.h>	/* For ARPHRD_ETHER */
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/percpu.h>
#include <linux/net_tstamp.h>
#include <net/net_namespace.h>
#include <linux/u64_stats_sync.h>
static struct net_device *my_loopback ;
int my_loopback_open (struct net_device *dev)
{
	printk("my_loopback_open called\n");
	return 0;
}

int my_loopback_release (struct net_device *dev)
{
	printk ("my_loopback_release called\n");
	return 0;
}

static int my_loopback_xmit (struct sk_buff *skb, 
				struct net_device *dev)
{
	//struct pcpu_lstats *lb_stats; 
	int len;

	printk ("dummy xmit function called....\n");


	skb_tx_timestamp(skb);
	skb->tstamp = 0;

	skb_orphan(skb);
	skb_dst_force(skb);

	//lb_stats = dev->lstats;
	skb->protocol = eth_type_trans(skb, dev);

	///* it's OK to use per_cpu_ptr() because BHs are off */
	//lb_stats =(struct pcpu_lstats *) dev->lstats;

	//len = skb->len;
	//if( likely(netif_rx(skb) == NET_RX_SUCCESS)) {
	//	u64_stats_update_begin(&(lb_stats->syncp));
	//	lb_stats->bytes = len;
	//	lb_stats->packets  = 1;
	//	u64_stats_update_end(&(lb_stats->syncp));
	//}

	return NETDEV_TX_OK;
}

const static struct net_device_ops my_netdev = {
		.ndo_open = my_loopback_open, 
		.ndo_stop = my_loopback_release,
		.ndo_start_xmit = my_loopback_xmit,
} ;
static void  my_loopback_init(struct net_device *dev)
{
	dev->netdev_ops = &my_netdev;
	printk ("longvh device initialized\n");
}


int my_loopback_init_module (void)
{
	int result;
	my_loopback = alloc_netdev(0,"longvh",NET_NAME_UNKNOWN, my_loopback_init);
	if ((result = register_netdev (my_loopback))) {
		printk ("my_loopback: Error %d  initializing card rtl8139 card",result);
		return result;
	}
return 0;
}

void my_loopback_cleanup (void)
{
	printk ("<0> Cleaning Up the Module\n");
	unregister_netdev (my_loopback);
	return;
}

module_init (my_loopback_init_module);
module_exit (my_loopback_cleanup)
MODULE_AUTHOR("LONGVH");
MODULE_LICENSE("GPL");
