read_stdin_handler(gpointer data, gint fd, GdkInputCondition condition)
{
    struct stdin_buf *input = (struct stdin_buf *)data;

    if (condition & GDK_INPUT_EXCEPTION) {
        g_print("STR");
        input->count = 0;	
    }
    else if (condition & GDK_INPUT_READ) {
        
        input->count = read(fd, input->buf, input->len);
        if (input->count < 0)
            input->count = 0;
    }
    else {
        g_print("STR");
        input->count = 0;	
    }
}