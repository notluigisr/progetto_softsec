static int vxlan_fdb_update(struct vxlan_dev *vxlan,
			    const u8 *mac, union vxlan_addr *ip,
			    __u16 state, __u16 flags,
			    __be16 port, __be32 src_vni, __be32 vni,
			    __u32 ifindex, __u16 ndm_flags,
			    bool swdev_notify,
			    struct netlink_ext_ack *extack)
{
	struct vxlan_fdb *f;

	f = __vxlan_find_mac(vxlan, mac, src_vni);
	if (f) {
		if (flags & NLM_F_EXCL) {
			netdev_dbg(vxlan->dev,
				   "STR", mac);
			return -EEXIST;
		}

		return vxlan_fdb_update_existing(vxlan, ip, state, flags, port,
						 vni, ifindex, ndm_flags, f,
						 swdev_notify, extack);
	} else {
		if (!(flags & NLM_F_CREATE))
			return -ENOENT;

		return vxlan_fdb_update_create(vxlan, mac, ip, state, flags,
					       port, src_vni, vni, ifindex,
					       ndm_flags, swdev_notify, extack);
	}
}