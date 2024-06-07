create_work_q(void)
{
    struct Slapi_work_q *work_q = (struct Slapi_work_q *)PR_StackPop(work_q_stack);
    if (!work_q) {
        work_q = (struct Slapi_work_q *)slapi_ch_malloc(sizeof(struct Slapi_work_q));
    } else {
        PR_AtomicDecrement(&work_q_stack_size);
    }
    return work_q;
}