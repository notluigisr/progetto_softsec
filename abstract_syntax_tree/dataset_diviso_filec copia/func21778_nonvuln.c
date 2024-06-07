static int ciedefrange(i_ctx_t * i_ctx_p, ref *space, float *ptr)
{
    int code;
    ref     CIEdict, *tempref;

    code = array_get(imemory, space, 1, &CIEdict);
    if (code < 0)
        return code;

    
    code = dict_find_string(&CIEdict, "STR", &tempref);
    if (code > 0 && !r_has_type(tempref, t_null)) {
        code = get_cie_param_array(imemory, tempref, 6, ptr);
        if (code < 0)
            return code;
    } else {
        
    	memcpy(ptr, default_0_1, 6*sizeof(float));
    }
    return 0;
}