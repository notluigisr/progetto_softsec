static void __device_link_free_srcu(struct rcu_head *rhead)
{
	device_link_free(container_of(rhead, struct device_link, rcu_head));
}