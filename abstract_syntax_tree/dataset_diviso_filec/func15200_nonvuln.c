ip_get_global_var(self, varname)
    VALUE self;
    VALUE varname;
{
    return ip_get_variable(self, varname,
                           INT2FIX(TCL_GLOBAL_ONLY | TCL_LEAVE_ERR_MSG));
}