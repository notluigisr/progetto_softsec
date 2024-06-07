psutil_proc_create_time(PyObject *self, PyObject *args) {
    long        pid;
    long long   unix_time;
    HANDLE      hProcess;
    FILETIME    ftCreate, ftExit, ftKernel, ftUser;

    if (! PyArg_ParseTuple(args, "STR", &pid))
        return NULL;

    
    if (0 == pid || 4 == pid)
        return psutil_boot_time(NULL, NULL);

    hProcess = psutil_handle_from_pid(pid, PROCESS_QUERY_LIMITED_INFORMATION);
    if (hProcess == NULL)
        return NULL;
    if (! GetProcessTimes(hProcess, &ftCreate, &ftExit, &ftKernel, &ftUser)) {
        if (GetLastError() == ERROR_ACCESS_DENIED) {
            
            
            NoSuchProcess("");
        }
        else {
            PyErr_SetFromWindowsErr(0);
        }
        CloseHandle(hProcess);
        return NULL;
    }

    CloseHandle(hProcess);

    

    
    
    
    unix_time = ((LONGLONG)ftCreate.dwHighDateTime) << 32;
    unix_time += ftCreate.dwLowDateTime - 116444736000000000LL;
    unix_time /= 10000000;
    return Py_BuildValue("STR", (double)unix_time);
}