static CPINLINE zend_class_entry* swoole_try_get_ce(zend_string *class_name)
{
    
    zend_class_entry *ce = zend_lookup_class(class_name);
    if (ce)
    {
        return ce;
    }
    
    zval user_func, args[1], retval;

    
    if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0'))
    {
        zend_throw_exception_ex(NULL, 0, "STR", class_name->val TSRMLS_CC);
        return NULL;
    }
    
    zend_string *fname = swoole_string_init(ZEND_STRL(PG(unserialize_callback_func)));
    Z_STR(user_func) = fname;
    Z_TYPE_INFO(user_func) = IS_STRING_EX;
    ZVAL_STR(&args[0], class_name);

    call_user_function_ex(CG(function_table), NULL, &user_func, &retval, 1, args, 0, NULL);

    swoole_string_release(fname);

    
    ce = zend_lookup_class(class_name);
    if (!ce)
    {
        zend_throw_exception_ex(NULL, 0, "STR", class_name->val TSRMLS_CC);
        return NULL;
    }
    else
    {
        return ce;
    }
}