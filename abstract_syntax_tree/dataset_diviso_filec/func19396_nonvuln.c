static int tx_wait_done(struct snd_sof_ipc *ipc, struct snd_sof_ipc_msg *msg,
			void *reply_data)
{
	struct snd_sof_dev *sdev = ipc->sdev;
	struct sof_ipc_cmd_hdr *hdr = msg->msg_data;
	int ret;

	
	ret = wait_event_timeout(msg->waitq, msg->ipc_complete,
				 msecs_to_jiffies(sdev->ipc_timeout));

	if (ret == 0) {
		dev_err(sdev->dev, "STR",
			hdr->cmd, hdr->size);
		snd_sof_dsp_dbg_dump(ipc->sdev, SOF_DBG_REGS | SOF_DBG_MBOX);
		snd_sof_ipc_dump(ipc->sdev);
		snd_sof_trace_notify_for_error(ipc->sdev);
		ret = -ETIMEDOUT;
	} else {
		
		ret = msg->reply_error;
		if (msg->reply_size)
			memcpy(reply_data, msg->reply_data, msg->reply_size);
		if (ret < 0)
			dev_err(sdev->dev, "STR",
				hdr->cmd, msg->reply_size);
		else
			ipc_log_header(sdev->dev, "STR", hdr->cmd);
	}

	return ret;
}