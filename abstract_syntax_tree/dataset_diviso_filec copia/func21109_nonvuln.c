static void smc_parse_options(const struct tcphdr *th,
			      struct tcp_options_received *opt_rx,
			      const unsigned char *ptr,
			      int opsize)
{
#if IS_ENABLED(CONFIG_SMC)
	if (static_branch_unlikely(&tcp_have_smc)) {
		if (th->syn && !(opsize & 1) &&
		    opsize >= TCPOLEN_EXP_SMC_BASE &&
		    get_unaligned_be32(ptr) == TCPOPT_SMC_MAGIC)
			opt_rx->smc_ok = 1;
	}
#endif
}