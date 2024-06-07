struct sctp_transport *sctp_assoc_choose_shutdown_transport(
	struct sctp_association *asoc)
{
	
	if (!asoc->shutdown_last_sent_to)
		return asoc->peer.active_path;
	else {
		if (asoc->shutdown_last_sent_to == asoc->peer.retran_path)
			sctp_assoc_update_retran_path(asoc);
		return asoc->peer.retran_path;
	}

}