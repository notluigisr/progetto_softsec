session_key(
	sockaddr_u *srcadr, 	
	sockaddr_u *dstadr, 	
	keyid_t	keyno,		
	keyid_t	private,	
	u_long	lifetime 	
	)
{
	EVP_MD_CTX ctx;		
	u_char dgst[EVP_MAX_MD_SIZE]; 
	keyid_t	keyid;		
	u_int32	header[10];	
	u_int	hdlen, len;

	if (!dstadr)
		return 0;
	
	
	hdlen = 0;
	switch(AF(srcadr)) {
	case AF_INET:
		header[0] = NSRCADR(srcadr);
		header[1] = NSRCADR(dstadr);
		header[2] = htonl(keyno);
		header[3] = htonl(private);
		hdlen = 4 * sizeof(u_int32);
		break;

	case AF_INET6:
		memcpy(&header[0], PSOCK_ADDR6(srcadr),
		    sizeof(struct in6_addr));
		memcpy(&header[4], PSOCK_ADDR6(dstadr),
		    sizeof(struct in6_addr));
		header[8] = htonl(keyno);
		header[9] = htonl(private);
		hdlen = 10 * sizeof(u_int32);
		break;
	}
	EVP_DigestInit(&ctx, EVP_get_digestbynid(crypto_nid));
	EVP_DigestUpdate(&ctx, (u_char *)header, hdlen);
	EVP_DigestFinal(&ctx, dgst, &len);
	memcpy(&keyid, dgst, 4);
	keyid = ntohl(keyid);
	if (lifetime != 0) {
		MD5auth_setkey(keyno, crypto_nid, dgst, len);
		authtrust(keyno, lifetime);
	}
	DPRINTF(2, ("STR",
		    stoa(srcadr), stoa(dstadr), keyno,
		    private, keyid, lifetime));

	return (keyid);
}