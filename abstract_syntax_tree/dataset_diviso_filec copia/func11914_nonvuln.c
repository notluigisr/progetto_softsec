static u32 bond_sk_hash_l34(struct sock *sk)
{
	struct flow_keys flow;
	u32 hash;

	bond_sk_to_flow(sk, &flow);

	
	memcpy(&hash, &flow.ports.ports, sizeof(hash));
	
	return bond_ip_hash(hash, &flow);
}