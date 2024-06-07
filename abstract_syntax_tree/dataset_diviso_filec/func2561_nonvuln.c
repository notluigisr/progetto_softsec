fstring_compile_expr(const char *expr_start, const char *expr_end,
                     struct compiling *c, const node *n)

{
    PyCompilerFlags cf;
    node *mod_n;
    mod_ty mod;
    char *str;
    Py_ssize_t len;
    const char *s;

    assert(expr_end >= expr_start);
    assert(*(expr_start-1) == '{');
    assert(*expr_end == '}' || *expr_end == '!' || *expr_end == ':');

    
    for (s = expr_start; s != expr_end; s++) {
        char c = *s;
        
        if (!(c == ' ' || c == '\t' || c == '\n' || c == '\f')) {
            break;
        }
    }
    if (s == expr_end) {
        ast_error(c, n, "STR");
        return NULL;
    }

    len = expr_end - expr_start;
    
    str = PyMem_RawMalloc(len + 3);
    if (str == NULL) {
        PyErr_NoMemory();
        return NULL;
    }

    str[0] = '(';
    memcpy(str+1, expr_start, len);
    str[len+1] = ')';
    str[len+2] = 0;

    cf.cf_flags = PyCF_ONLY_AST;
    cf.cf_feature_version = PY_MINOR_VERSION;
    mod_n = PyParser_SimpleParseStringFlagsFilename(str, "STR",
                                                    Py_eval_input, 0);
    if (!mod_n) {
        PyMem_RawFree(str);
        return NULL;
    }
    
    str[0] = '{';
    str[len+1] = '}';
    fstring_fix_node_location(n, mod_n, str);
    mod = PyAST_FromNode(mod_n, &cf, "STR", c->c_arena);
    PyMem_RawFree(str);
    PyNode_Free(mod_n);
    if (!mod)
        return NULL;
    return mod->v.Expression.body;
}