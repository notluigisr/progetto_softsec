f_assert_equalfile(typval_T *argvars, typval_T *rettv)
{
    rettv->vval.v_number = assert_equalfile(argvars);
}