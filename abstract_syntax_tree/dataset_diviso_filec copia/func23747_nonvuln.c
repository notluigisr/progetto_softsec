void iscsi_dump_sess_ops(struct iscsi_sess_ops *sess_ops)
{
	pr_debug("STR", sess_ops->InitiatorName);
	pr_debug("STR", sess_ops->InitiatorAlias);
	pr_debug("STR", sess_ops->TargetName);
	pr_debug("STR", sess_ops->TargetAlias);
	pr_debug("STR",
			sess_ops->TargetPortalGroupTag);
	pr_debug("STR", sess_ops->MaxConnections);
	pr_debug("STR",
			(sess_ops->InitialR2T) ? "STR");
	pr_debug("STR", (sess_ops->ImmediateData) ?
			"STR");
	pr_debug("STR", sess_ops->MaxBurstLength);
	pr_debug("STR", sess_ops->FirstBurstLength);
	pr_debug("STR", sess_ops->DefaultTime2Wait);
	pr_debug("STR",
			sess_ops->DefaultTime2Retain);
	pr_debug("STR",
			sess_ops->MaxOutstandingR2T);
	pr_debug("STR",
			(sess_ops->DataPDUInOrder) ? "STR");
	pr_debug("STR",
			(sess_ops->DataSequenceInOrder) ? "STR");
	pr_debug("STR",
			sess_ops->ErrorRecoveryLevel);
	pr_debug("STR", (sess_ops->SessionType) ?
			"STR");
}