static inline int put_v4l2_input32(struct v4l2_input *kp, struct v4l2_input32 __user *up)
{
	if (copy_to_user(up, kp, sizeof(*up)))
		return -EFAULT;
	return 0;
}