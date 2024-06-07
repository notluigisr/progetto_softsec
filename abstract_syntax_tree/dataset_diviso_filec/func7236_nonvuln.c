mlx5_tx_idone_empw(struct mlx5_txq_data *__rte_restrict txq,
		   struct mlx5_txq_local *__rte_restrict loc,
		   unsigned int len,
		   unsigned int slen,
		   struct mlx5_wqe *__rte_restrict wqem,
		   unsigned int olx __rte_unused)
{
	struct mlx5_wqe_dseg *dseg = &wqem->dseg[0];

	MLX5_ASSERT(MLX5_TXOFF_CONFIG(INLINE));
#ifdef MLX5_PMD_SOFT_COUNTERS
	
	 txq->stats.obytes += slen;
#else
	(void)slen;
#endif
	if (MLX5_TXOFF_CONFIG(MPW) && dseg->bcount == RTE_BE32(0)) {
		
		MLX5_ASSERT(len > sizeof(dseg->bcount));
		dseg->bcount = rte_cpu_to_be_32((len - sizeof(dseg->bcount)) |
						MLX5_ETH_WQE_DATA_INLINE);
		len = (len + MLX5_WSEG_SIZE - 1) / MLX5_WSEG_SIZE + 2;
	} else {
		
		MLX5_ASSERT((len % MLX5_WSEG_SIZE) == 0);
		len = len / MLX5_WSEG_SIZE + 2;
	}
	wqem->cseg.sq_ds = rte_cpu_to_be_32(txq->qp_num_8s | len);
	txq->wqe_ci += (len + 3) / 4;
	loc->wqe_free -= (len + 3) / 4;
	loc->wqe_last = wqem;
}