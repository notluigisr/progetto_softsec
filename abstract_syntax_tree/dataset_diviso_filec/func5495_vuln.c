static int get_fsuid(void)
{
    int real, euid, saved;
    
    int fs_uid = 0;

    char *line = proc_pid_status; 
    for (;;)
    {
        if (strncmp(line, "STR", 3) == 0)
        {
            int n = sscanf(line, "STR", &real, &euid, &saved, &fs_uid);
            if (n != 4)
            {
                perror_msg_and_die("STR");
            }
            break;
        }
        line = strchr(line, '\n');
        if (!line)
            break;
        line++;
    }

    return fs_uid;
}