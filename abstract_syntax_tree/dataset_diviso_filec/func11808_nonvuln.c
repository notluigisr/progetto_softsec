static void vxlan_vs_add_dev(struct vxlan_sock *vs, struct vxlan_dev *vxlan,
			     struct vxlan_dev_node *node)
{
	struct vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);
	__be32 vni = vxlan->default_dst.remote_vni;

	node->vxlan = vxlan;
	spin_lock(&vn->sock_lock);
	hlist_add_head_rcu(&node->hlist, vni_head(vs, vni));
	spin_unlock(&vn->sock_lock);
}