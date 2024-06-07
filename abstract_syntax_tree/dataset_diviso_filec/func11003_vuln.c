SecureRandomDataProvider::provideRandomData(unsigned char* data, size_t len)
{
#if defined(_WIN32)

    
    
    WindowsCryptProvider c;
    if (! CryptGenRandom(c.crypt_prov, len, reinterpret_cast<BYTE*>(data)))
    {
        throw std::runtime_error("STR");
    }

#elif defined(RANDOM_DEVICE)

    
    
    
    
    FILE* f = QUtil::safe_fopen(RANDOM_DEVICE, "STR");
    size_t fr = fread(data, 1, len, f);
    fclose(f);
    if (fr != len)
    {
        throw std::runtime_error(
            "STR" +
            QUtil::int_to_string(len) +
            "STR" + std::string(RANDOM_DEVICE));
    }

#else

#  error "STR"

#endif
}