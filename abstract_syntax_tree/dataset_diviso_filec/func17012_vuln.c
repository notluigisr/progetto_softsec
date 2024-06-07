static int nci_close_device(struct nci_dev *ndev)
{
	nci_req_cancel(ndev, ENODEV);
	mutex_lock(&ndev->req_lock);

	if (!test_and_clear_bit(NCI_UP, &ndev->flags)) {
		del_timer_sync(&ndev->cmd_timer);
		del_timer_sync(&ndev->data_timer);
		mutex_unlock(&ndev->req_lock);
		return 0;
	}

	
	skb_queue_purge(&ndev->rx_q);
	skb_queue_purge(&ndev->tx_q);

	
	flush_workqueue(ndev->rx_wq);
	flush_workqueue(ndev->tx_wq);

	
	skb_queue_purge(&ndev->cmd_q);
	atomic_set(&ndev->cmd_cnt, 1);

	set_bit(NCI_INIT, &ndev->flags);
	__nci_request(ndev, nci_reset_req, (void *)0,
		      msecs_to_jiffies(NCI_RESET_TIMEOUT));

	
	ndev->ops->close(ndev);

	clear_bit(NCI_INIT, &ndev->flags);

	
	flush_workqueue(ndev->cmd_wq);

	del_timer_sync(&ndev->cmd_timer);

	
	ndev->flags = 0;

	mutex_unlock(&ndev->req_lock);

	return 0;
}