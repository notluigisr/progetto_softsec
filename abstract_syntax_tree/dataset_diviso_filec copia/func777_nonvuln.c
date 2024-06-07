int ip6_dst_lookup(struct sock *sk, struct dst_entry **dst, struct flowi *fl)
{
	int err = 0;

	*dst = NULL;
	if (sk) {
		struct ipv6_pinfo *np = inet6_sk(sk);
	
		*dst = sk_dst_check(sk, np->dst_cookie);
		if (*dst) {
			struct rt6_info *rt = (struct rt6_info*)*dst;
	
				
	
			if (((rt->rt6i_dst.plen != 128 ||
			      !ipv6_addr_equal(&fl->fl6_dst, &rt->rt6i_dst.addr))
			     && (np->daddr_cache == NULL ||
				 !ipv6_addr_equal(&fl->fl6_dst, np->daddr_cache)))
			    || (fl->oif && fl->oif != (*dst)->dev->ifindex)) {
				dst_release(*dst);
				*dst = NULL;
			}
		}
	}

	if (*dst == NULL)
		*dst = ip6_route_output(sk, fl);

	if ((err = (*dst)->error))
		goto out_err_release;

	if (ipv6_addr_any(&fl->fl6_src)) {
		err = ipv6_get_saddr(*dst, &fl->fl6_dst, &fl->fl6_src);

		if (err)
			goto out_err_release;
	}

	return 0;

out_err_release:
	dst_release(*dst);
	*dst = NULL;
	return err;
}