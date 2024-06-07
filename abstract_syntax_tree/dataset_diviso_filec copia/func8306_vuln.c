static struct sk_buff *macsec_decrypt(struct sk_buff *skb,
				      struct net_device *dev,
				      struct macsec_rx_sa *rx_sa,
				      sci_t sci,
				      struct macsec_secy *secy)
{
	int ret;
	struct scatterlist *sg;
	unsigned char *iv;
	struct aead_request *req;
	struct macsec_eth_header *hdr;
	u16 icv_len = secy->icv_len;

	macsec_skb_cb(skb)->valid = false;
	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	req = macsec_alloc_req(rx_sa->key.tfm, &iv, &sg);
	if (!req) {
		kfree_skb(skb);
		return ERR_PTR(-ENOMEM);
	}

	hdr = (struct macsec_eth_header *)skb->data;
	macsec_fill_iv(iv, sci, ntohl(hdr->packet_number));

	sg_init_table(sg, MAX_SKB_FRAGS + 1);
	skb_to_sgvec(skb, sg, 0, skb->len);

	if (hdr->tci_an & MACSEC_TCI_E) {
		
		int len = skb->len - macsec_hdr_len(macsec_skb_cb(skb)->has_sci);

		aead_request_set_crypt(req, sg, sg, len, iv);
		aead_request_set_ad(req, macsec_hdr_len(macsec_skb_cb(skb)->has_sci));
		skb = skb_unshare(skb, GFP_ATOMIC);
		if (!skb) {
			aead_request_free(req);
			return ERR_PTR(-ENOMEM);
		}
	} else {
		
		aead_request_set_crypt(req, sg, sg, icv_len, iv);
		aead_request_set_ad(req, skb->len - icv_len);
	}

	macsec_skb_cb(skb)->req = req;
	skb->dev = dev;
	aead_request_set_callback(req, 0, macsec_decrypt_done, skb);

	dev_hold(dev);
	ret = crypto_aead_decrypt(req);
	if (ret == -EINPROGRESS) {
		return ERR_PTR(ret);
	} else if (ret != 0) {
		
		if (ret != -EBADMSG) {
			kfree_skb(skb);
			skb = ERR_PTR(ret);
		}
	} else {
		macsec_skb_cb(skb)->valid = true;
	}
	dev_put(dev);

	aead_request_free(req);

	return skb;
}