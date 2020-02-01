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

/* The higher levels take care of making this non-reentrant (it's
 * called with bh's disabled).
 */
static netdev_tx_t loopback_xmit(struct sk_buff *skb,
				 struct net_device *dev)
{
	return NETDEV_TX_OK;
}

static void loopback_get_stats64(struct net_device *dev,
				 struct rtnl_link_stats64 *stats)
{
}

static u32 always_on(struct net_device *dev)
{
	return 1;
}

static int loopback_get_ts_info(struct net_device *netdev,
				struct ethtool_ts_info *ts_info)
{
	return 0;
};

static const struct ethtool_ops loopback_ethtool_ops = {
	.get_link		= always_on,
	.get_ts_info		= loopback_get_ts_info,
};

static int loopback_dev_init(struct net_device *dev)
{
	return 0;
}

static void loopback_dev_free(struct net_device *dev)
{
}

static const struct net_device_ops loopback_ops = {
	.ndo_init        = loopback_dev_init,
	.ndo_start_xmit  = loopback_xmit,
	.ndo_get_stats64 = loopback_get_stats64,
	.ndo_set_mac_address = eth_mac_addr,
};

/* The loopback device is special. There is only one instance
 * per network namespace.
 */
static void loopback_setup(struct net_device *dev)
{
}

/* Setup and register the loopback device. */
static __net_init int loopback_net_init(struct net *net)
{
	struct net_device *dev;
	int err;

	err = -ENOMEM;
	dev = alloc_netdev(0, "longvh", NET_NAME_UNKNOWN, loopback_setup);
	if (!dev)
		goto out;

	dev_net_set(dev, net);
	err = register_netdev(dev);
	if (err)
		goto out_free_netdev;

	BUG_ON(dev->ifindex != LOOPBACK_IFINDEX);
	net->loopback_dev = dev;
	return 0;

out_free_netdev:
	free_netdev(dev);
out:
	if (net_eq(net, &init_net))
		panic("loopback: Failed to register netdevice: %d\n", err);
	return err;
}

/* Registered in net/core/dev.c */
struct pernet_operations __net_initdata loopback_net_ops = {
	.init = loopback_net_init,
};

