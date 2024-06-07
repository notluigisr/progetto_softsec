static void l2cap_streaming_send(struct l2cap_chan *chan,
				 struct sk_buff_head *skbs)
{
	struct sk_buff *skb;
	struct l2cap_ctrl *control;

	BT_DBG("STR", chan, skbs);

	if (__chan_is_moving(chan))
		return;

	skb_queue_splice_tail_init(skbs, &chan->tx_q);

	while (!skb_queue_empty(&chan->tx_q)) {

		skb = skb_dequeue(&chan->tx_q);

		bt_cb(skb)->l2cap.retries = 1;
		control = &bt_cb(skb)->l2cap;

		control->reqseq = 0;
		control->txseq = chan->next_tx_seq;

		__pack_control(chan, control, skb);

		if (chan->fcs == L2CAP_FCS_CRC16) {
			u16 fcs = crc16(0, (u8 *) skb->data, skb->len);
			put_unaligned_le16(fcs, skb_put(skb, L2CAP_FCS_SIZE));
		}

		l2cap_do_send(chan, skb);

		BT_DBG("STR", control->txseq);

		chan->next_tx_seq = __next_seq(chan, chan->next_tx_seq);
		chan->frames_sent++;
	}
}