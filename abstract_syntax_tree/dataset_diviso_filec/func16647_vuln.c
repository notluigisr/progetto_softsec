_Unpickler_MemoGet(UnpicklerObject *self, Py_ssize_t idx)
{
    if (idx < 0 || idx >= self->memo_size)
        return NULL;

    return self->memo[idx];
}