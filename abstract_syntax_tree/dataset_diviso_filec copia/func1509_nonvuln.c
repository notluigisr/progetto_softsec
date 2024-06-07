static irqreturn_t ioat_dma_do_interrupt_msix(int irq, void *data)
{
	struct ioat_chan_common *chan = data;

	if (test_bit(IOAT_RUN, &chan->state))
		tasklet_schedule(&chan->cleanup_task);

	return IRQ_HANDLED;
}