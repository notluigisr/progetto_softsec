static struct sk_buff *udp_gro_receive_segment(struct list_head *head,
					       struct sk_buff *skb)
{
	struct udphdr *uh = udp_hdr(skb);
	struct sk_buff *pp = NULL;
	struct udphdr *uh2;
	struct sk_buff *p;

	
	if (!uh->check) {
		NAPI_GRO_CB(skb)->flush = 1;
		return NULL;
	}

	
	skb_gro_pull(skb, sizeof(struct udphdr));
	skb_gro_postpull_rcsum(skb, uh, sizeof(struct udphdr));

	list_for_each_entry(p, head, list) {
		if (!NAPI_GRO_CB(p)->same_flow)
			continue;

		uh2 = udp_hdr(p);

		
		if ((*(u32 *)&uh->source != *(u32 *)&uh2->source)) {
			NAPI_GRO_CB(p)->same_flow = 0;
			continue;
		}

		
		if (uh->len > uh2->len || skb_gro_receive(p, skb) ||
		    uh->len != uh2->len ||
		    NAPI_GRO_CB(p)->count >= UDP_GRO_CNT_MAX)
			pp = p;

		return pp;
	}

	
	return NULL;
}