unsigned int sequencer_poll(int dev, struct file *file, poll_table * wait)
{
	unsigned long flags;
	unsigned int mask = 0;

	dev = dev >> 4;

	spin_lock_irqsave(&lock,flags);
	
	poll_wait(file, &midi_sleeper, wait);
	if (iqlen)
		mask |= POLLIN | POLLRDNORM;

	
	poll_wait(file, &seq_sleeper, wait);
	if ((SEQ_MAX_QUEUE - qlen) >= output_threshold)
		mask |= POLLOUT | POLLWRNORM;
	spin_unlock_irqrestore(&lock,flags);
	return mask;
}