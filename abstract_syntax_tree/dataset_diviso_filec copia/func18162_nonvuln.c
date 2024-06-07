static inline void __pack_control(struct l2cap_chan *chan,
				  struct l2cap_ctrl *control,
				  struct sk_buff *skb)
{
	if (test_bit(FLAG_EXT_CTRL, &chan->flags)) {
		put_unaligned_le32(__pack_extended_control(control),
				   skb->data + L2CAP_HDR_SIZE);
	} else {
		put_unaligned_le16(__pack_enhanced_control(control),
				   skb->data + L2CAP_HDR_SIZE);
	}
}