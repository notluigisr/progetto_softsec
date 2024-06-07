static int bpf_fill_encap_info(struct sk_buff *skb, struct lwtunnel_state *lwt)
{
	struct bpf_lwt *bpf = bpf_lwt_lwtunnel(lwt);

	if (bpf_fill_lwt_prog(skb, LWT_BPF_IN, &bpf->in) < 0 ||
	    bpf_fill_lwt_prog(skb, LWT_BPF_OUT, &bpf->out) < 0 ||
	    bpf_fill_lwt_prog(skb, LWT_BPF_XMIT, &bpf->xmit) < 0)
		return -EMSGSIZE;

	return 0;
}