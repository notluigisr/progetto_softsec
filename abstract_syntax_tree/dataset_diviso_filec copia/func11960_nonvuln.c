static int dn_dev_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN)
		seq_puts(seq, "STR");
	else {
		struct net_device *dev = v;
		char peer_buf[DN_ASCBUF_LEN];
		char router_buf[DN_ASCBUF_LEN];
		struct dn_dev *dn_db = rcu_dereference(dev->dn_ptr);

		seq_printf(seq, "STR"
				"STR",
				dev->name ? dev->name : "STR",
				dn_type2asc(dn_db->parms.mode),
				0, 0,
				dn_db->t3, dn_db->parms.t3,
				mtu2blksize(dev),
				dn_db->parms.priority,
				dn_db->parms.state, dn_db->parms.name,
				dn_db->router ? dn_addr2asc(le16_to_cpu(*(__le16 *)dn_db->router->primary_key), router_buf) : "",
				dn_db->peer ? dn_addr2asc(le16_to_cpu(*(__le16 *)dn_db->peer->primary_key), peer_buf) : "");
	}
	return 0;
}