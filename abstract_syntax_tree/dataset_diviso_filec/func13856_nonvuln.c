isdn_net_force_hangup(char *name)
{
	isdn_net_dev *p = isdn_net_findif(name);
	struct net_device *q;

	if (p) {
		if (p->local->isdn_device < 0)
			return 1;
		q = p->local->slave;
		
		while (q) {
			isdn_net_hangup(q);
			q = (((isdn_net_local *) q->priv)->slave);
		}
		isdn_net_hangup(p->dev);
		return 0;
	}
	return -ENODEV;
}