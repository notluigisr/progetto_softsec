viminfo_readline(vir_T *virp)
{
    return vim_fgets(virp->vir_line, LSIZE, virp->vir_fd);
}