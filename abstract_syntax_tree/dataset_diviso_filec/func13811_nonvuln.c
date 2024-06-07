_Pickler_FlushToFile(PicklerObject *self)
{
    PyObject *output, *result;

    assert(self->write != NULL);

    
    output = _Pickler_GetString(self);
    if (output == NULL)
        return -1;

    result = _Pickle_FastCall(self->write, output);
    Py_XDECREF(result);
    return (result == NULL) ? -1 : 0;
}