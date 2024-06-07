static int smack_msg_queue_associate(struct msg_queue *msq, int msqflg)
{
	int may;

	may = smack_flags_to_may(msqflg);
	return smk_curacc_msq(msq, may);
}