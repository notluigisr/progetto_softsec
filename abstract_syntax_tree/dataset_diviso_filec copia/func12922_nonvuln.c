mlx5_tx_comp_flush(struct mlx5_txq_data *restrict txq,
		   volatile struct mlx5_cqe *last_cqe,
		   unsigned int olx __rte_unused)
{
	if (likely(last_cqe != NULL)) {
		uint16_t tail;

		txq->wqe_pi = rte_be_to_cpu_16(last_cqe->wqe_counter);
		tail = txq->fcqs[(txq->cq_ci - 1) & txq->cqe_m];
		if (likely(tail != txq->elts_tail)) {
			mlx5_tx_free_elts(txq, tail, olx);
			assert(tail == txq->elts_tail);
		}
	}
}