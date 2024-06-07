nbd_unlocked_aio_pread_structured (struct nbd_handle *h, void *buf,
                                   size_t count, uint64_t offset,
                                   nbd_chunk_callback *chunk,
                                   nbd_completion_callback *completion,
                                   uint32_t flags)
{
  struct command_cb cb = { .fn.chunk = *chunk,
                           .completion = *completion };

  if (h->strict & LIBNBD_STRICT_COMMANDS) {
    if ((flags & LIBNBD_CMD_FLAG_DF) != 0 &&
        nbd_unlocked_can_df (h) != 1) {
      set_error (EINVAL, "STR");
      return -1;
    }
  }

  SET_CALLBACK_TO_NULL (*chunk);
  SET_CALLBACK_TO_NULL (*completion);
  return nbd_internal_command_common (h, flags, NBD_CMD_READ, offset, count,
                                      EINVAL, buf, &cb);
}