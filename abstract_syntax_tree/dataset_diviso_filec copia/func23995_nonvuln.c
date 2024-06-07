static int cmykvalidate(i_ctx_t *i_ctx_p, ref *space, float *values, int num_comps)
{
    os_ptr op = osp;
    int i;

    if (num_comps < 4)
        return_error(gs_error_stackunderflow);

    op -= 3;
    for (i=0;i < 4;i++) {
        if (!r_has_type(op, t_integer) && !r_has_type(op, t_real))
            return_error(gs_error_typecheck);
        op++;
    }

    for (i=0;i < 4; i++) {
        if (values[i] > 1.0)
            values[i] = 1.0;

        if (values[i] < 0.0)
            values[i] = 0.0;
    }

    return 0;
}