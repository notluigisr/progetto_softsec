nbd_unlocked_pread (struct nbd_handle *h, void *buf,
                    size_t count, uint64_t offset, uint32_t flags)
{
  int64_t cookie;
  nbd_completion_callback c = NBD_NULL_COMPLETION;

  cookie = nbd_unlocked_aio_pread (h, buf, count, offset, &c, flags);
  if (cookie == -1)
    return -1;

  return wait_for_command (h, cookie);
}