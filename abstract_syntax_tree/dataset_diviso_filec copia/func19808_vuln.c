psutil_pids(PyObject *self, PyObject *args) {
    kinfo_proc *proclist = NULL;
    kinfo_proc *orig_address = NULL;
    size_t num_processes;
    size_t idx;
    PyObject *py_pid = NULL;
    PyObject *py_retlist = PyList_New(0);

    if (py_retlist == NULL)
        return NULL;

    if (psutil_get_proc_list(&proclist, &num_processes) != 0)
        goto error;

    
    orig_address = proclist;
    for (idx = 0; idx < num_processes; idx++) {
        py_pid = Py_BuildValue("STR", proclist->kp_proc.p_pid);
        if (! py_pid)
            goto error;
        if (PyList_Append(py_retlist, py_pid))
            goto error;
        Py_DECREF(py_pid);
        proclist++;
    }
    free(orig_address);

    return py_retlist;

error:
    Py_XDECREF(py_pid);
    Py_DECREF(py_retlist);
    if (orig_address != NULL)
        free(orig_address);
    return NULL;
}