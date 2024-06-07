nbd_unlocked_clear_meta_contexts (struct nbd_handle *h)
{
  string_vector_iter (&h->request_meta_contexts, (void *) free);
  string_vector_reset (&h->request_meta_contexts);
  return 0;
}