    WindowsCryptProvider()
    {
        if (!CryptAcquireContext(&crypt_prov,
                                 "STR",
                                 NULL,
                                 PROV_RSA_FULL,
                                 0))
        {
#if ((defined(__GNUC__) && ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406) || \
     defined(__clang__))
#           pragma GCC diagnostic push
#           pragma GCC diagnostic ignored "STR"
#           pragma GCC diagnostic ignored "STR"
#endif
            if (GetLastError() == NTE_BAD_KEYSET)
#if ((defined(__GNUC__) && ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406) || \
     defined(__clang__))
#           pragma GCC diagnostic pop
#endif
            {
                if (! CryptAcquireContext(&crypt_prov,
                                         "STR",
                                         NULL,
                                         PROV_RSA_FULL,
                                         CRYPT_NEWKEYSET))
                {
                    throw std::runtime_error(
                        "STR");
                }
            }
            else
            {
                throw std::runtime_error("STR");
            }
        }
    }