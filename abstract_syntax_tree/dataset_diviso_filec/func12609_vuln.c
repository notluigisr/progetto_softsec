static int nfs_lookup_reply(uchar *pkt, unsigned len)
{
	struct rpc_t rpc_pkt;

	debug("STR", __func__);

	memcpy(&rpc_pkt.u.data[0], pkt, len);

	if (ntohl(rpc_pkt.u.reply.id) > rpc_id)
		return -NFS_RPC_ERR;
	else if (ntohl(rpc_pkt.u.reply.id) < rpc_id)
		return -NFS_RPC_DROP;

	if (rpc_pkt.u.reply.rstatus  ||
	    rpc_pkt.u.reply.verifier ||
	    rpc_pkt.u.reply.astatus  ||
	    rpc_pkt.u.reply.data[0]) {
		switch (ntohl(rpc_pkt.u.reply.astatus)) {
		case NFS_RPC_SUCCESS: 
			break;
		case NFS_RPC_PROG_MISMATCH:
			
			switch (ntohl(rpc_pkt.u.reply.data[0])) {
			
			case 3:
				debug("STR",
				      (supported_nfs_versions & NFSV2_FLAG) ?
						2 : 3,
				      ntohl(rpc_pkt.u.reply.data[0]),
				      ntohl(rpc_pkt.u.reply.data[1]));
				debug("STR");
				
				supported_nfs_versions &= ~NFSV2_FLAG;
				return -NFS_RPC_PROG_MISMATCH;
			case 4:
			default:
				puts("STR");
				debug("STR",
				      (supported_nfs_versions & NFSV2_FLAG) ?
						2 : 3,
				      ntohl(rpc_pkt.u.reply.data[0]),
				      ntohl(rpc_pkt.u.reply.data[1]));
				puts("STR");
			}
			break;
		case NFS_RPC_PROG_UNAVAIL:
		case NFS_RPC_PROC_UNAVAIL:
		case NFS_RPC_GARBAGE_ARGS:
		case NFS_RPC_SYSTEM_ERR:
		default: 
			debug("STR",
			      ntohl(rpc_pkt.u.reply.astatus));
			break;
		}
		return -1;
	}

	if (supported_nfs_versions & NFSV2_FLAG) {
		memcpy(filefh, rpc_pkt.u.reply.data + 1, NFS_FHSIZE);
	} else {  
		filefh3_length = ntohl(rpc_pkt.u.reply.data[1]);
		if (filefh3_length > NFS3_FHSIZE)
			filefh3_length  = NFS3_FHSIZE;
		memcpy(filefh, rpc_pkt.u.reply.data + 2, filefh3_length);
	}

	return 0;
}