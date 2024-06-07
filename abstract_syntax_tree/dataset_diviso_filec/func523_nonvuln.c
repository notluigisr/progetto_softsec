NOEXPORT int service_uninstall(void) {
    SC_HANDLE scm, service;
    SERVICE_STATUS serviceStatus;

    scm=OpenSCManager(0, 0, SC_MANAGER_CONNECT);
    if(!scm) {
        error_box(TEXT("STR"));
        return 1;
    }
    service=OpenService(scm, SERVICE_NAME, SERVICE_QUERY_STATUS|DELETE);
    if(!service) {
        error_box(TEXT("STR"));
        CloseServiceHandle(scm);
        return 1;
    }
    if(!QueryServiceStatus(service, &serviceStatus)) {
        error_box(TEXT("STR"));
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }
    if(serviceStatus.dwCurrentState!=SERVICE_STOPPED) {
        message_box(TEXT("STR"), MB_ICONERROR);
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }
    if(!DeleteService(service)) {
        error_box(TEXT("STR"));
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }
    message_box(TEXT("STR"), MB_ICONINFORMATION);
    CloseServiceHandle(service);
    CloseServiceHandle(scm);
    return 0;
}