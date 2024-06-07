static int isdn_net_header(struct sk_buff *skb, struct net_device *dev,
			   unsigned short type,
			   const void *daddr, const void *saddr, unsigned plen)
{
	isdn_net_local *lp = dev->priv;
	unsigned char *p;
	ushort len = 0;

	switch (lp->p_encap) {
		case ISDN_NET_ENCAP_ETHER:
			len = eth_header(skb, dev, type, daddr, saddr, plen);
			break;
#ifdef CONFIG_ISDN_PPP
		case ISDN_NET_ENCAP_SYNCPPP:
			
			len = IPPP_MAX_HEADER;
			skb_push(skb,len);
			break;
#endif
		case ISDN_NET_ENCAP_RAWIP:
			printk(KERN_WARNING "STR");
			len = 0;
			break;
		case ISDN_NET_ENCAP_IPTYP:
			
			*((ushort *) skb_push(skb, 2)) = htons(type);
			len = 2;
			break;
		case ISDN_NET_ENCAP_UIHDLC:
			
			*((ushort *) skb_push(skb, 2)) = htons(0x0103);
			len = 2;
			break;
		case ISDN_NET_ENCAP_CISCOHDLC:
		case ISDN_NET_ENCAP_CISCOHDLCK:
			p = skb_push(skb, 4);
			p += put_u8 (p, CISCO_ADDR_UNICAST);
			p += put_u8 (p, CISCO_CTRL);
			p += put_u16(p, type);
			len = 4;
			break;
#ifdef CONFIG_ISDN_X25
		default:
		  
			if( lp-> netdev -> cprot ){
				printk(KERN_WARNING "STR");
				len = 0;
				break;
			}
			break;
#endif 
	}
	return len;
}