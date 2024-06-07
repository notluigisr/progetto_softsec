int bpf_prog_array_copy_info(struct bpf_prog_array __rcu *array,
			     u32 *prog_ids, u32 request_cnt,
			     u32 *prog_cnt)
{
	struct bpf_prog **prog;
	u32 cnt = 0;

	if (array)
		cnt = bpf_prog_array_length(array);

	*prog_cnt = cnt;

	
	if (!request_cnt || !cnt)
		return 0;

	
	prog = rcu_dereference_check(array, 1)->progs;
	return bpf_prog_array_copy_core(prog, prog_ids, request_cnt) ? -ENOSPC
								     : 0;
}