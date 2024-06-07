load_get(UnpicklerObject *self)
{
    PyObject *key, *value;
    Py_ssize_t idx;
    Py_ssize_t len;
    char *s;

    if ((len = _Unpickler_Readline(self, &s)) < 0)
        return -1;
    if (len < 2)
        return bad_readline();

    key = PyLong_FromString(s, NULL, 10);
    if (key == NULL)
        return -1;
    idx = PyLong_AsSsize_t(key);
    if (idx == -1 && PyErr_Occurred()) {
        Py_DECREF(key);
        return -1;
    }

    value = _Unpickler_MemoGet(self, idx);
    if (value == NULL) {
        if (!PyErr_Occurred())
            PyErr_SetObject(PyExc_KeyError, key);
        Py_DECREF(key);
        return -1;
    }
    Py_DECREF(key);

    PDATA_APPEND(self->stack, value, -1);
    return 0;
}