builtin_globals_impl(PyObject *module)

{
    PyObject *d;

    d = PyEval_GetGlobals();
    Py_XINCREF(d);
    return d;
}