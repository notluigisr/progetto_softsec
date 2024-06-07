_Unpickler_NewMemo(Py_ssize_t new_size)
{
    PyObject **memo = PyMem_NEW(PyObject *, new_size);
    if (memo == NULL) {
        PyErr_NoMemory();
        return NULL;
    }
    memset(memo, 0, new_size * sizeof(PyObject *));
    return memo;
}