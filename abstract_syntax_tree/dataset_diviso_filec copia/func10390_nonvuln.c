mlx5_tx_eseg_dmin(struct mlx5_txq_data *__rte_restrict txq __rte_unused,
		  struct mlx5_txq_local *__rte_restrict loc,
		  struct mlx5_wqe *__rte_restrict wqe,
		  unsigned int vlan,
		  unsigned int olx)
{
	struct mlx5_wqe_eseg *__rte_restrict es = &wqe->eseg;
	uint32_t csum;
	uint8_t *psrc, *pdst;

	
	csum = MLX5_TXOFF_CONFIG(CSUM) ? txq_ol_cksum_to_cs(loc->mbuf) : 0;
	es->flags = rte_cpu_to_le_32(csum);
	
	es->swp_offs = txq_mbuf_to_swp(loc, &es->swp_flags, olx);
	
	es->metadata = MLX5_TXOFF_CONFIG(METADATA) ?
		       loc->mbuf->ol_flags & PKT_TX_DYNF_METADATA ?
		       *RTE_FLOW_DYNF_METADATA(loc->mbuf) : 0 : 0;
	static_assert(MLX5_ESEG_MIN_INLINE_SIZE ==
				(sizeof(uint16_t) +
				 sizeof(rte_v128u32_t)),
		      "STR");
	static_assert(MLX5_ESEG_MIN_INLINE_SIZE ==
				(sizeof(uint16_t) +
				 sizeof(struct rte_vlan_hdr) +
				 2 * RTE_ETHER_ADDR_LEN),
		      "STR");
	psrc = rte_pktmbuf_mtod(loc->mbuf, uint8_t *);
	es->inline_hdr_sz = RTE_BE16(MLX5_ESEG_MIN_INLINE_SIZE);
	es->inline_data = *(unaligned_uint16_t *)psrc;
	psrc +=	sizeof(uint16_t);
	pdst = (uint8_t *)(es + 1);
	if (MLX5_TXOFF_CONFIG(VLAN) && vlan) {
		
		memcpy(pdst, psrc, 2 * RTE_ETHER_ADDR_LEN - sizeof(uint16_t));
		pdst += 2 * RTE_ETHER_ADDR_LEN - sizeof(uint16_t);
		psrc +=	2 * RTE_ETHER_ADDR_LEN - sizeof(uint16_t);
		
		*(unaligned_uint32_t *)pdst = rte_cpu_to_be_32
						((RTE_ETHER_TYPE_VLAN << 16) |
						 loc->mbuf->vlan_tci);
		pdst += sizeof(struct rte_vlan_hdr);
		
		MLX5_ASSERT(pdst == RTE_PTR_ALIGN(pdst, sizeof(uint16_t)));
		*(uint16_t *)pdst = *(unaligned_uint16_t *)psrc;
	} else {
		
		rte_mov16(pdst, psrc);
	}
}