  STATIC size_t GC_get_file_len(int f)
  {
    size_t total = 0;
    ssize_t result;
#   define GET_FILE_LEN_BUF_SZ 500
    char buf[GET_FILE_LEN_BUF_SZ];

    do {
        result = read(f, buf, GET_FILE_LEN_BUF_SZ);
        if (result == -1) return 0;
        total += result;
    } while (result > 0);
    return total;
  }