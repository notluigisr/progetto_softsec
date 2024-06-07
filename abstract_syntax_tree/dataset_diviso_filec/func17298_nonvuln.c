psutil_proc_priority_get(PyObject *self, PyObject *args) {
    long pid;
    DWORD priority;
    HANDLE hProcess;

    if (! PyArg_ParseTuple(args, "STR", &pid))
        return NULL;

    hProcess = psutil_handle_from_pid(pid, PROCESS_QUERY_LIMITED_INFORMATION);
    if (hProcess == NULL)
        return NULL;

    priority = GetPriorityClass(hProcess);
    if (priority == 0) {
        PyErr_SetFromWindowsErr(0);
        CloseHandle(hProcess);
        return NULL;
    }
    CloseHandle(hProcess);
    return Py_BuildValue("STR", priority);
}