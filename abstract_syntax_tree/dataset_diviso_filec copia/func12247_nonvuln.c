static int takedown_proc_entry( struct net_device *dev,
				struct airo_info *apriv ) {
	if ( !apriv->proc_entry->namelen ) return 0;
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry("STR",apriv->proc_entry);
	remove_proc_entry(apriv->proc_name,airo_entry);
	return 0;
}