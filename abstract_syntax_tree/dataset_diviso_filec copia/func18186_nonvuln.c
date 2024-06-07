static void read_file_into_memory(
    char const* filename,
    PointerHolder<unsigned char>& file_buf, size_t& size)
{
    FILE* f = QUtil::safe_fopen(filename, "STR");
    fseek(f, 0, SEEK_END);
    size = QIntC::to_size(QUtil::tell(f));
    fseek(f, 0, SEEK_SET);
    file_buf = PointerHolder<unsigned char>(true, new unsigned char[size]);
    unsigned char* buf_p = file_buf.getPointer();
    size_t bytes_read = 0;
    size_t len = 0;
    while ((len = fread(buf_p + bytes_read, 1, size - bytes_read, f)) > 0)
    {
        bytes_read += len;
    }
    if (bytes_read != size)
    {
        throw std::runtime_error(
            std::string("STR") + filename +
            "STR" +
            QUtil::uint_to_string(bytes_read) + "STR" +
            QUtil::uint_to_string(size));
    }
    fclose(f);
}