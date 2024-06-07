static unsigned int selinux_ipv4_output(unsigned int hooknum,
					struct sk_buff *skb,
					const struct net_device *in,
					const struct net_device *out,
					int (*okfn)(struct sk_buff *))
{
	return selinux_ip_output(skb, PF_INET);
}