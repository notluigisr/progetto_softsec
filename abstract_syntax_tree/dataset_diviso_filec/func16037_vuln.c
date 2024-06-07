  GC_INNER void GC_setpagesize(void)
  {
    GetSystemInfo(&GC_sysinfo);
    GC_page_size = GC_sysinfo.dwPageSize;
#   if defined(MSWINCE) && !defined(_WIN32_WCE_EMULATION)
      {
        OSVERSIONINFO verInfo;
        
        verInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (!GetVersionEx(&verInfo))
          ABORT("STR");
        if (verInfo.dwPlatformId == VER_PLATFORM_WIN32_CE &&
            verInfo.dwMajorVersion < 6) {
          
          
          GC_sysinfo.lpMaximumApplicationAddress = (LPVOID)((word)32 << 20);
#         ifdef THREADS
            
            
            
            if (verInfo.dwMajorVersion < 5)
              GC_dont_query_stack_min = TRUE;
#         endif
        }
      }
#   endif
  }