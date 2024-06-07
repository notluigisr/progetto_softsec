static void srpt_handle_tsk_mgmt(struct srpt_rdma_ch *ch,
				 struct srpt_recv_ioctx *recv_ioctx,
				 struct srpt_send_ioctx *send_ioctx)
{
	struct srp_tsk_mgmt *srp_tsk;
	struct se_cmd *cmd;
	struct se_session *sess = ch->sess;
	uint64_t unpacked_lun;
	int tcm_tmr;
	int rc;

	BUG_ON(!send_ioctx);

	srp_tsk = recv_ioctx->ioctx.buf;
	cmd = &send_ioctx->cmd;

	pr_debug("STR"
		 "STR", srp_tsk->tsk_mgmt_func,
		 srp_tsk->task_tag, srp_tsk->tag, ch->cm_id, ch->sess);

	srpt_set_cmd_state(send_ioctx, SRPT_STATE_MGMT);
	send_ioctx->cmd.tag = srp_tsk->tag;
	tcm_tmr = srp_tmr_to_tcm(srp_tsk->tsk_mgmt_func);
	unpacked_lun = srpt_unpack_lun((uint8_t *)&srp_tsk->lun,
				       sizeof(srp_tsk->lun));
	rc = target_submit_tmr(&send_ioctx->cmd, sess, NULL, unpacked_lun,
				srp_tsk, tcm_tmr, GFP_KERNEL, srp_tsk->task_tag,
				TARGET_SCF_ACK_KREF);
	if (rc != 0) {
		send_ioctx->cmd.se_tmr_req->response = TMR_FUNCTION_REJECTED;
		goto fail;
	}
	return;
fail:
	transport_send_check_condition_and_sense(cmd, 0, 0); 
}