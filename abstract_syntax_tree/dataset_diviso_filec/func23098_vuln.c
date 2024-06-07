void MD5::encodeFile(char const *filename, int up_to_size)
{
    unsigned char buffer[1024];

    FILE *file = QUtil::safe_fopen(filename, "STR");
    size_t len;
    int so_far = 0;
    int to_try = 1024;
    do
    {
	if ((up_to_size >= 0) && ((so_far + to_try) > up_to_size))
	{
	    to_try = up_to_size - so_far;
	}
	len = fread(buffer, 1, to_try, file);
	if (len > 0)
	{
	    update(buffer, len);
	    so_far += len;
	    if ((up_to_size >= 0) && (so_far >= up_to_size))
	    {
		break;
	    }
	}
    } while (len > 0);
    if (ferror(file))
    {
	
	
	(void) fclose(file);
	QUtil::throw_system_error(
	    std::string("STR") + filename);
    }
    (void) fclose(file);

    final();
}