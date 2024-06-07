static bool dma_chan_is_local(struct dma_chan *chan, int cpu)
{
	int node = dev_to_node(chan->device->dev);
	return node == -1 || cpumask_test_cpu(cpu, cpumask_of_node(node));
}