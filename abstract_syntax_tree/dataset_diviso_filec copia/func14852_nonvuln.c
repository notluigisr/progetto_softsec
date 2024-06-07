static inline size_t xfrm_sa_len(struct xfrm_state *x)
{
	size_t l = 0;
	if (x->aead)
		l += nla_total_size(aead_len(x->aead));
	if (x->aalg) {
		l += nla_total_size(sizeof(struct xfrm_algo) +
				    (x->aalg->alg_key_len + 7) / 8);
		l += nla_total_size(xfrm_alg_auth_len(x->aalg));
	}
	if (x->ealg)
		l += nla_total_size(xfrm_alg_len(x->ealg));
	if (x->calg)
		l += nla_total_size(sizeof(*x->calg));
	if (x->encap)
		l += nla_total_size(sizeof(*x->encap));
	if (x->tfcpad)
		l += nla_total_size(sizeof(x->tfcpad));
	if (x->replay_esn)
		l += nla_total_size(xfrm_replay_state_esn_len(x->replay_esn));
	else
		l += nla_total_size(sizeof(struct xfrm_replay_state));
	if (x->security)
		l += nla_total_size(sizeof(struct xfrm_user_sec_ctx) +
				    x->security->ctx_len);
	if (x->coaddr)
		l += nla_total_size(sizeof(*x->coaddr));
	if (x->props.extra_flags)
		l += nla_total_size(sizeof(x->props.extra_flags));
	if (x->xso.dev)
		 l += nla_total_size(sizeof(x->xso));
	if (x->props.output_mark)
		l += nla_total_size(sizeof(x->props.output_mark));

	
	l += nla_total_size_64bit(sizeof(u64));

	return l;
}