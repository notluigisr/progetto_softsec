crypto_send(
	struct exten *ep,	
	struct value *vp,	
	int	start		
	)
{
	u_int	len, vallen, siglen, opcode;
	u_int	i, j;

	
	len = 16;				
	vallen = ntohl(vp->vallen);
	INSIST(vallen <= MAX_VALLEN);
	len += ((vallen + 3) / 4 + 1) * 4; 
	siglen = ntohl(vp->siglen);
	len += ((siglen + 3) / 4 + 1) * 4; 
	if (start + len > sizeof(struct pkt) - MAX_MAC_LEN)
		return (0);

	
	ep->tstamp = vp->tstamp;
	ep->fstamp = vp->fstamp;
	ep->vallen = vp->vallen;

	
	i = 0;
	if (vallen > 0 && vp->ptr != NULL) {
		j = vallen / 4;
		if (j * 4 < vallen)
			ep->pkt[i + j++] = 0;
		memcpy(&ep->pkt[i], vp->ptr, vallen);
		i += j;
	}

	
	ep->pkt[i++] = vp->siglen;
	if (siglen > 0 && vp->sig != NULL) {
		j = siglen / 4;
		if (j * 4 < siglen)
			ep->pkt[i + j++] = 0;
		memcpy(&ep->pkt[i], vp->sig, siglen);
			
	}
	opcode = ntohl(ep->opcode);
	ep->opcode = htonl((opcode & 0xffff0000) | len); 
	ENSURE(len <= MAX_VALLEN);
	return (len);
}