psutil_disk_partitions(PyObject *self, PyObject *args) {
    FILE *file = NULL;
    struct mntent *entry;
    const char *mtab_path;
    PyObject *py_dev = NULL;
    PyObject *py_mountp = NULL;
    PyObject *py_tuple = NULL;
    PyObject *py_retlist = PyList_New(0);

    if (py_retlist == NULL)
        return NULL;

    if (!PyArg_ParseTuple(args, "STR", &mtab_path))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    file = setmntent(mtab_path, "STR");
    Py_END_ALLOW_THREADS
    if ((file == 0) || (file == NULL)) {
        psutil_debug("STR");
        PyErr_SetFromErrnoWithFilename(PyExc_OSError, mtab_path);
        goto error;
    }

    while ((entry = getmntent(file))) {
        if (entry == NULL) {
            PyErr_Format(PyExc_RuntimeError, "STR");
            goto error;
        }
        py_dev = PyUnicode_DecodeFSDefault(entry->mnt_fsname);
        if (! py_dev)
            goto error;
        py_mountp = PyUnicode_DecodeFSDefault(entry->mnt_dir);
        if (! py_mountp)
            goto error;
        py_tuple = Py_BuildValue("STR",
                                 py_dev,             
                                 py_mountp,          
                                 entry->mnt_type,    
                                 entry->mnt_opts);   
        if (! py_tuple)
            goto error;
        if (PyList_Append(py_retlist, py_tuple))
            goto error;
        Py_DECREF(py_dev);
        Py_DECREF(py_mountp);
        Py_DECREF(py_tuple);
    }
    endmntent(file);
    return py_retlist;

error:
    if (file != NULL)
        endmntent(file);
    Py_XDECREF(py_dev);
    Py_XDECREF(py_mountp);
    Py_XDECREF(py_tuple);
    Py_DECREF(py_retlist);
    return NULL;
}