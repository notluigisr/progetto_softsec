unsigned int get_random_int(void)
{
	
	return secure_ip_id((__force __be32)(current->pid + jiffies));
}