f_reg_executing(typval_T *argvars UNUSED, typval_T *rettv)
{
    return_register(reg_executing, rettv);
}