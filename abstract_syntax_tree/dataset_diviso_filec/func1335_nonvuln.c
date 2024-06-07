static PyObject *Restricted_getattr(RestrictedObject *self, char *name)
{
    PyErr_Format(PyExc_IOError, "STR", self->s);

    return NULL;
}