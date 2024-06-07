void security_msg_queue_free(struct msg_queue *msq)
{
	security_ops->msg_queue_free_security(msq);
}