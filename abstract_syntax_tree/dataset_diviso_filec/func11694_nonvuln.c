static int rtas_error_rc(int rtas_rc)
{
	int rc;

	switch (rtas_rc) {
		case -1: 		
			rc = -EIO;
			break;
		case -3:		
			rc = -EINVAL;
			break;
		case -9000:		
			rc = -EFAULT;
			break;
		case -9001:		
			rc = -EEXIST;
			break;
		case -9002:		
			rc = -ENODEV;
			break;
		default:
			printk(KERN_ERR "STR",
					__func__, rtas_rc);
			rc = -ERANGE;
			break;
	}
	return rc;
}