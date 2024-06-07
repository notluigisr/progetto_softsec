static inline void brcmf_fweh_process_skb(struct brcmf_pub *drvr,
					  struct sk_buff *skb)
{
	struct brcmf_event *event_packet;
	u16 usr_stype;

	
	if (skb->protocol != cpu_to_be16(ETH_P_LINK_CTL))
		return;

	if ((skb->len + ETH_HLEN) < sizeof(*event_packet))
		return;

	
	event_packet = (struct brcmf_event *)skb_mac_header(skb);
	if (memcmp(BRCM_OUI, &event_packet->hdr.oui[0],
		   sizeof(event_packet->hdr.oui)))
		return;

	
	usr_stype = get_unaligned_be16(&event_packet->hdr.usr_subtype);
	if (usr_stype != BCMILCP_BCM_SUBTYPE_EVENT)
		return;

	brcmf_fweh_process_event(drvr, event_packet, skb->len + ETH_HLEN);
}