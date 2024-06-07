fast_save_enter(PicklerObject *self, PyObject *obj)
{
    
    if (++self->fast_nesting >= FAST_NESTING_LIMIT) {
        PyObject *key = NULL;
        if (self->fast_memo == NULL) {
            self->fast_memo = PyDict_New();
            if (self->fast_memo == NULL) {
                self->fast_nesting = -1;
                return 0;
            }
        }
        key = PyLong_FromVoidPtr(obj);
        if (key == NULL) {
            self->fast_nesting = -1;
            return 0;
        }
        if (PyDict_GetItemWithError(self->fast_memo, key)) {
            Py_DECREF(key);
            PyErr_Format(PyExc_ValueError,
                         "STR"
                         "STR",
                         obj->ob_type->tp_name, obj);
            self->fast_nesting = -1;
            return 0;
        }
        if (PyErr_Occurred()) {
            Py_DECREF(key);
            self->fast_nesting = -1;
            return 0;
        }
        if (PyDict_SetItem(self->fast_memo, key, Py_None) < 0) {
            Py_DECREF(key);
            self->fast_nesting = -1;
            return 0;
        }
        Py_DECREF(key);
    }
    return 1;
}