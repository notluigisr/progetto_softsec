static int snd_seq_ioctl_set_client_info(struct snd_seq_client *client,
					 void __user *arg)
{
	struct snd_seq_client_info client_info;

	if (copy_from_user(&client_info, arg, sizeof(client_info)))
		return -EFAULT;

	
	if (client->number != client_info.client)
		return -EPERM;
	
	if (client->type != client_info.type)
		return -EINVAL;

	
	if (client_info.name[0])
		strlcpy(client->name, client_info.name, sizeof(client->name));

	client->filter = client_info.filter;
	client->event_lost = client_info.event_lost;
	memcpy(client->event_filter, client_info.event_filter, 32);

	return 0;
}