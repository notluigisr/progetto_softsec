void iscsi_host_remove(struct Scsi_Host *shost)
{
	struct iscsi_host *ihost = shost_priv(shost);
	unsigned long flags;

	spin_lock_irqsave(&ihost->lock, flags);
	ihost->state = ISCSI_HOST_REMOVED;
	spin_unlock_irqrestore(&ihost->lock, flags);

	iscsi_host_for_each_session(shost, iscsi_notify_host_removed);
	wait_event_interruptible(ihost->session_removal_wq,
				 ihost->num_sessions == 0);
	if (signal_pending(current))
		flush_signals(current);

	scsi_remove_host(shost);
}