static void append_socket_pair(int *array, size_t *n, const int pair[static 2]) {
        assert(array);
        assert(n);

        if (!pair)
                return;

        if (pair[0] >= 0)
                array[(*n)++] = pair[0];
        if (pair[1] >= 0)
                array[(*n)++] = pair[1];
}