bool ioat_cleanup_preamble(struct ioat_chan_common *chan,
			   dma_addr_t *phys_complete)
{
	*phys_complete = ioat_get_current_completion(chan);
	if (*phys_complete == chan->last_completion)
		return false;
	clear_bit(IOAT_COMPLETION_ACK, &chan->state);
	mod_timer(&chan->timer, jiffies + COMPLETION_TIMEOUT);

	return true;
}