ctnetlink_glue_build_size(const struct nf_conn *ct)
{
	return 3 * nla_total_size(0) 
	       + 3 * nla_total_size(0) 
	       + 3 * nla_total_size(0) 
	       + 3 * nla_total_size(sizeof(u_int8_t)) 
	       + nla_total_size(sizeof(u_int32_t)) 
	       + nla_total_size(sizeof(u_int32_t)) 
	       + nla_total_size(sizeof(u_int32_t)) 
	       + nla_total_size(0) 
	       + nla_total_size(0) 
	       + nla_total_size(NF_CT_HELPER_NAME_LEN) 
	       + ctnetlink_secctx_size(ct)
#if IS_ENABLED(CONFIG_NF_NAT)
	       + 2 * nla_total_size(0) 
	       + 6 * nla_total_size(sizeof(u_int32_t)) 
#endif
#ifdef CONFIG_NF_CONNTRACK_MARK
	       + nla_total_size(sizeof(u_int32_t)) 
#endif
#ifdef CONFIG_NF_CONNTRACK_ZONES
	       + nla_total_size(sizeof(u_int16_t)) 
#endif
	       + ctnetlink_proto_size(ct)
	       ;
}