static unsigned int get_num_images(char *imgdirpath)
{
    DIR *dir;
    struct dirent* content;
    unsigned int num_images = 0;

    

    dir = opendir(imgdirpath);
    if (!dir) {
        fprintf(stderr, "STR", imgdirpath);
        return 0;
    }

    num_images = 0;
    while ((content = readdir(dir)) != NULL) {
        if (strcmp("STR", content->d_name) == 0) {
            continue;
        }
        num_images++;
    }
    closedir(dir);
    return num_images;
}