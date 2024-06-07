static void gen_prov_start(struct prov_rx *rx, struct net_buf_simple *buf)
{
	uint8_t seg = SEG_NVAL;

	if (rx->xact_id == link.rx.id) {
		if (!link.rx.seg) {
			if (!ack_pending()) {
				BT_DBG("STR");
				gen_prov_ack_send(rx->xact_id);
			}

			return;
		}

		if (!(link.rx.seg & BIT(0))) {
			BT_DBG("STR");
			return;
		}
	} else if (rx->xact_id != next_transaction_id(link.rx.id)) {
		BT_WARN("STR", rx->xact_id,
			next_transaction_id(link.rx.id));
		return;
	}

	net_buf_simple_reset(link.rx.buf);
	link.rx.buf->len = net_buf_simple_pull_be16(buf);
	link.rx.id = rx->xact_id;
	link.rx.fcs = net_buf_simple_pull_u8(buf);

	BT_DBG("STR", buf->len,
	       START_LAST_SEG(rx->gpc), link.rx.buf->len, link.rx.fcs);

	if (link.rx.buf->len < 1) {
		BT_ERR("STR");
		prov_failed(PROV_ERR_NVAL_FMT);
		return;
	}

	if (link.rx.buf->len > link.rx.buf->size) {
		BT_ERR("STR",
		       link.rx.buf->len);
		prov_failed(PROV_ERR_NVAL_FMT);
		return;
	}

	if (START_LAST_SEG(rx->gpc) > 0 && link.rx.buf->len <= 20U) {
		BT_ERR("STR");
		prov_failed(PROV_ERR_NVAL_FMT);
		return;
	}

	prov_clear_tx();

	link.rx.last_seg = START_LAST_SEG(rx->gpc);

	if ((link.rx.seg & BIT(0)) &&
	    (find_msb_set((~link.rx.seg) & SEG_NVAL) - 1 > link.rx.last_seg)) {
		BT_ERR("STR", seg);
		prov_failed(PROV_ERR_NVAL_FMT);
		return;
	}

	if (link.rx.seg) {
		seg = link.rx.seg;
	}

	link.rx.seg = seg & ((1 << (START_LAST_SEG(rx->gpc) + 1)) - 1);
	memcpy(link.rx.buf->data, buf->data, buf->len);
	XACT_SEG_RECV(0);

	if (!link.rx.seg) {
		prov_msg_recv();
	}
}