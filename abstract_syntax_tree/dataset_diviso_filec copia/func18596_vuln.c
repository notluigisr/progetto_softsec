GetStartupData(HANDLE pipe, STARTUP_DATA *sud)
{
    size_t size, len;
    BOOL ret = FALSE;
    WCHAR *data = NULL;
    DWORD bytes, read;

    bytes = PeekNamedPipeAsync(pipe, 1, &exit_event);
    if (bytes == 0)
    {
        MsgToEventLog(M_SYSERR, TEXT("STR"));
        ReturnLastError(pipe, L"STR");
        goto out;
    }

    size = bytes / sizeof(*data);
    if (size == 0)
    {
        MsgToEventLog(M_SYSERR, TEXT("STR"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"STR", 1, &exit_event);
        goto out;
    }

    data = malloc(bytes);
    if (data == NULL)
    {
        MsgToEventLog(M_SYSERR, TEXT("STR"));
        ReturnLastError(pipe, L"STR");
        goto out;
    }

    read = ReadPipeAsync(pipe, data, bytes, 1, &exit_event);
    if (bytes != read)
    {
        MsgToEventLog(M_SYSERR, TEXT("STR"));
        ReturnLastError(pipe, L"STR");
        goto out;
    }

    if (data[size - 1] != 0)
    {
        MsgToEventLog(M_ERR, TEXT("STR"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"STR", 1, &exit_event);
        goto out;
    }

    sud->directory = data;
    len = wcslen(sud->directory) + 1;
    size -= len;
    if (size <= 0)
    {
        MsgToEventLog(M_ERR, TEXT("STR"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"STR", 1, &exit_event);
        goto out;
    }

    sud->options = sud->directory + len;
    len = wcslen(sud->options) + 1;
    size -= len;
    if (size <= 0)
    {
        MsgToEventLog(M_ERR, TEXT("STR"));
        ReturnError(pipe, ERROR_STARTUP_DATA, L"STR", 1, &exit_event);
        goto out;
    }

    sud->std_input = sud->options + len;
    data = NULL; 
    ret = TRUE;

out:
    free(data);
    return ret;
}