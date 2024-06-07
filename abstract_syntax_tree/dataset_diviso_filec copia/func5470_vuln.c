static inline int get_v4l2_input32(struct v4l2_input *kp, struct v4l2_input32 __user *up)
{
	if (copy_from_user(kp, up, sizeof(*up)))
		return -EFAULT;
	return 0;
}