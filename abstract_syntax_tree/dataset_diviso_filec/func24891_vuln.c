psutil_proc_threads(PyObject *self, PyObject *args) {
    long pid;
    int err, ret;
    kern_return_t kr;
    unsigned int info_count = TASK_BASIC_INFO_COUNT;
    mach_port_t task = MACH_PORT_NULL;
    struct task_basic_info tasks_info;
    thread_act_port_array_t thread_list = NULL;
    thread_info_data_t thinfo_basic;
    thread_basic_info_t basic_info_th;
    mach_msg_type_number_t thread_count, thread_info_count, j;

    PyObject *py_tuple = NULL;
    PyObject *py_retlist = PyList_New(0);

    if (py_retlist == NULL)
        return NULL;

    if (! PyArg_ParseTuple(args, "STR", &pid))
        goto error;

    if (psutil_task_for_pid(pid, &task) != 0)
        goto error;

    info_count = TASK_BASIC_INFO_COUNT;
    err = task_info(task, TASK_BASIC_INFO, (task_info_t)&tasks_info,
                    &info_count);
    if (err != KERN_SUCCESS) {
        
        if (err == 4) {
            AccessDenied("");
        }
        else {
            
            PyErr_Format(PyExc_RuntimeError,
                         "STR");
        }
        goto error;
    }

    err = task_threads(task, &thread_list, &thread_count);
    if (err != KERN_SUCCESS) {
        PyErr_Format(PyExc_RuntimeError, "STR");
        goto error;
    }

    for (j = 0; j < thread_count; j++) {
        py_tuple = NULL;
        thread_info_count = THREAD_INFO_MAX;
        kr = thread_info(thread_list[j], THREAD_BASIC_INFO,
                         (thread_info_t)thinfo_basic, &thread_info_count);
        if (kr != KERN_SUCCESS) {
            PyErr_Format(PyExc_RuntimeError,
                         "STR");
            goto error;
        }

        basic_info_th = (thread_basic_info_t)thinfo_basic;
        py_tuple = Py_BuildValue(
            "STR",
            j + 1,
            basic_info_th->user_time.seconds + \
                (float)basic_info_th->user_time.microseconds / 1000000.0,
            basic_info_th->system_time.seconds + \
                (float)basic_info_th->system_time.microseconds / 1000000.0
        );
        if (!py_tuple)
            goto error;
        if (PyList_Append(py_retlist, py_tuple))
            goto error;
        Py_DECREF(py_tuple);
    }

    ret = vm_deallocate(task, (vm_address_t)thread_list,
                        thread_count * sizeof(int));
    if (ret != KERN_SUCCESS)
        PyErr_WarnEx(PyExc_RuntimeWarning, "STR", 2);

    mach_port_deallocate(mach_task_self(), task);

    return py_retlist;

error:
    if (task != MACH_PORT_NULL)
        mach_port_deallocate(mach_task_self(), task);
    Py_XDECREF(py_tuple);
    Py_DECREF(py_retlist);
    if (thread_list != NULL) {
        ret = vm_deallocate(task, (vm_address_t)thread_list,
                            thread_count * sizeof(int));
        if (ret != KERN_SUCCESS)
            PyErr_WarnEx(PyExc_RuntimeWarning, "STR", 2);
    }
    return NULL;
}