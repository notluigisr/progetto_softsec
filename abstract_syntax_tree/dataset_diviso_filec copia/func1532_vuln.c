static bool not_valid_time_file(const char *filename)
{
    
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        VERB2 perror_msg("STR", filename);
        return true;
    }

    
    char time_buf[sizeof(time_t) * 3 + 1];
    ssize_t rdsz = read(fd, time_buf, sizeof(time_buf));

    
    close(fd);

    if (rdsz == -1)
    {
        VERB2 perror_msg("STR", filename);
        return true;
    }

    
    
    
    
    if (rdsz == sizeof(time_buf))
    {
        VERB2 log("STR"
                  "STR", filename, sizeof(time_buf));
        return true;
    }

    
    if (rdsz > 0 && time_buf[rdsz - 1] == '\n')
        rdsz--;
    time_buf[rdsz] = '\0';

    
    
    if (!isdigit_str(time_buf))
    {
        VERB2 log("STR"
                  "STR", filename, time_buf);
        return true;
    }

    return false;
}