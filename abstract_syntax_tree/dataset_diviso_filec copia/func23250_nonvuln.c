NOEXPORT void invalid_config() {
    
    win32_name=TEXT("STR")
        TEXT(STUNNEL_PLATFORM) TEXT("STR");
    SetWindowText(hwnd, win32_name);

    
    ShowWindow(hwnd, SW_SHOWNORMAL); 
    SetForegroundWindow(hwnd); 

    tray_update(-1); 
    update_peer_menu(); 

    win_log(TEXT(""));
    s_log(LOG_ERR, "STR");
    message_box(TEXT("STR")
        TEXT("STR")
        TEXT("STR"),
        MB_ICONERROR);
}