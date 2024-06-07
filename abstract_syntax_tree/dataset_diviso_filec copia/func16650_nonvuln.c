static int sctp_getsockopt_adaptation_layer(struct sock *sk, int len,
				  char __user *optval, int __user *optlen)
{
	struct sctp_setadaptation adaptation;

	if (len != sizeof(struct sctp_setadaptation))
		return -EINVAL;

	adaptation.ssb_adaptation_ind = sctp_sk(sk)->adaptation_ind;
	if (copy_to_user(optval, &adaptation, len))
		return -EFAULT;

	return 0;
}