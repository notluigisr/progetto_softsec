int iscsi_eh_session_reset(struct scsi_cmnd *sc)
{
	struct iscsi_cls_session *cls_session;
	struct iscsi_session *session;
	struct iscsi_conn *conn;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;
	conn = session->leadconn;

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	if (session->state == ISCSI_STATE_TERMINATE) {
failed:
		ISCSI_DBG_EH(session,
			     "STR"
			     "STR", session->targetname,
			     session->age);
		spin_unlock_bh(&session->frwd_lock);
		mutex_unlock(&session->eh_mutex);
		return FAILED;
	}

	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);
	
	iscsi_conn_failure(conn, ISCSI_ERR_SCSI_EH_SESSION_RST);

	ISCSI_DBG_EH(session, "STR");
	wait_event_interruptible(conn->ehwait,
				 session->state == ISCSI_STATE_TERMINATE ||
				 session->state == ISCSI_STATE_LOGGED_IN ||
				 session->state == ISCSI_STATE_RECOVERY_FAILED);
	if (signal_pending(current))
		flush_signals(current);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	if (session->state == ISCSI_STATE_LOGGED_IN) {
		ISCSI_DBG_EH(session,
			     "STR",
			     session->targetname, conn->persistent_address);
	} else
		goto failed;
	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);
	return SUCCESS;
}