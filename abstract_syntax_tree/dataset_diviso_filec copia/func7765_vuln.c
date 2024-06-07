static int xenvif_poll(struct napi_struct *napi, int budget)
{
	struct xenvif *vif = container_of(napi, struct xenvif, napi);
	int work_done;

	work_done = xenvif_tx_action(vif, budget);

	if (work_done < budget) {
		int more_to_do = 0;
		unsigned long flags;

		

		local_irq_save(flags);

		RING_FINAL_CHECK_FOR_REQUESTS(&vif->tx, more_to_do);
		if (!more_to_do)
			__napi_complete(napi);

		local_irq_restore(flags);
	}

	return work_done;
}