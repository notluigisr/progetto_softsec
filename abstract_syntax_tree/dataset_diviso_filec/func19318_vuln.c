scsi_nl_rcv_msg(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	struct scsi_nl_hdr *hdr;
	u32 rlen;
	int err, tport;

	while (skb->len >= NLMSG_HDRLEN) {
		err = 0;

		nlh = nlmsg_hdr(skb);
		if ((nlh->nlmsg_len < (sizeof(*nlh) + sizeof(*hdr))) ||
		    (skb->len < nlh->nlmsg_len)) {
			printk(KERN_WARNING "STR",
				 __func__);
			return;
		}

		rlen = NLMSG_ALIGN(nlh->nlmsg_len);
		if (rlen > skb->len)
			rlen = skb->len;

		if (nlh->nlmsg_type != SCSI_TRANSPORT_MSG) {
			err = -EBADMSG;
			goto next_msg;
		}

		hdr = nlmsg_data(nlh);
		if ((hdr->version != SCSI_NL_VERSION) ||
		    (hdr->magic != SCSI_NL_MAGIC)) {
			err = -EPROTOTYPE;
			goto next_msg;
		}

		if (!capable(CAP_SYS_ADMIN)) {
			err = -EPERM;
			goto next_msg;
		}

		if (nlh->nlmsg_len < (sizeof(*nlh) + hdr->msglen)) {
			printk(KERN_WARNING "STR",
				 __func__);
			goto next_msg;
		}

		
		tport = hdr->transport;
		if (tport == SCSI_NL_TRANSPORT) {
			switch (hdr->msgtype) {
			case SCSI_NL_SHOST_VENDOR:
				
				err = -ESRCH;
				break;
			default:
				err = -EBADR;
				break;
			}
			if (err)
				printk(KERN_WARNING "STR",
				       __func__, hdr->msgtype, err);
		}
		else
			err = -ENOENT;

next_msg:
		if ((err) || (nlh->nlmsg_flags & NLM_F_ACK))
			netlink_ack(skb, nlh, err);

		skb_pull(skb, rlen);
	}
}