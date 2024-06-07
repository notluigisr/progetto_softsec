void v4l_printk_ioctl(const char *prefix, unsigned int cmd)
{
	const char *dir, *type;

	if (prefix)
		printk(KERN_DEBUG "STR", prefix);

	switch (_IOC_TYPE(cmd)) {
	case 'd':
		type = "STR";
		break;
	case 'V':
		if (_IOC_NR(cmd) >= V4L2_IOCTLS) {
			type = "STR";
			break;
		}
		pr_cont("STR", v4l2_ioctls[_IOC_NR(cmd)].name);
		return;
	default:
		type = "STR";
		break;
	}

	switch (_IOC_DIR(cmd)) {
	case _IOC_NONE:              dir = "STR"; break;
	case _IOC_READ:              dir = "STR"; break;
	case _IOC_WRITE:             dir = "STR"; break;
	case _IOC_READ | _IOC_WRITE: dir = "STR"; break;
	default:                     dir = "STR"; break;
	}
	pr_cont("STR",
		type, _IOC_TYPE(cmd), dir, _IOC_NR(cmd), cmd);
}