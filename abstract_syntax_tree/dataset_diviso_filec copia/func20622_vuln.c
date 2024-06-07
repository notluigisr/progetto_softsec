psutil_proc_open_files(PyObject *self, PyObject *args) {
    long pid;
    int pidinfo_result;
    int iterations;
    int i;
    unsigned long nb;

    struct proc_fdinfo *fds_pointer = NULL;
    struct proc_fdinfo *fdp_pointer;
    struct vnode_fdinfowithpath vi;

    PyObject *py_retlist = PyList_New(0);
    PyObject *py_tuple = NULL;
    PyObject *py_path = NULL;

    if (py_retlist == NULL)
        return NULL;

    if (! PyArg_ParseTuple(args, "STR", &pid))
        goto error;

    pidinfo_result = psutil_proc_pidinfo(pid, PROC_PIDLISTFDS, 0, NULL, 0);
    if (pidinfo_result <= 0)
        goto error;

    fds_pointer = malloc(pidinfo_result);
    if (fds_pointer == NULL) {
        PyErr_NoMemory();
        goto error;
    }
    pidinfo_result = psutil_proc_pidinfo(
        pid, PROC_PIDLISTFDS, 0, fds_pointer, pidinfo_result);
    if (pidinfo_result <= 0)
        goto error;

    iterations = (pidinfo_result / PROC_PIDLISTFD_SIZE);

    for (i = 0; i < iterations; i++) {
        fdp_pointer = &fds_pointer[i];

        if (fdp_pointer->proc_fdtype == PROX_FDTYPE_VNODE) {
            errno = 0;
            nb = proc_pidfdinfo((pid_t)pid,
                                fdp_pointer->proc_fd,
                                PROC_PIDFDVNODEPATHINFO,
                                &vi,
                                sizeof(vi));

            
            if ((nb <= 0) || nb < sizeof(vi)) {
                if ((errno == ENOENT) || (errno == EBADF)) {
                    
                    
                    continue;
                }
                else {
                    psutil_raise_for_pid(
                        pid, "STR");
                    goto error;
                }
            }
            

            
            py_path = PyUnicode_DecodeFSDefault(vi.pvip.vip_path);
            if (! py_path)
                goto error;
            py_tuple = Py_BuildValue(
                "STR",
                py_path,
                (int)fdp_pointer->proc_fd);
            if (!py_tuple)
                goto error;
            if (PyList_Append(py_retlist, py_tuple))
                goto error;
            Py_DECREF(py_tuple);
            py_tuple = NULL;
            Py_DECREF(py_path);
            py_path = NULL;
            
        }
    }

    free(fds_pointer);
    return py_retlist;

error:
    Py_XDECREF(py_tuple);
    Py_XDECREF(py_path);
    Py_DECREF(py_retlist);
    if (fds_pointer != NULL)
        free(fds_pointer);
    return NULL;  
}