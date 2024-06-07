plugin_thread_model (struct backend *b)
{
  struct backend_plugin *p = container_of (b, struct backend_plugin, backend);
  int thread_model = p->plugin._thread_model;
  int r;

#if !(defined SOCK_CLOEXEC && defined HAVE_MKOSTEMP && defined HAVE_PIPE2 && \
      defined HAVE_ACCEPT4)
  if (thread_model > NBDKIT_THREAD_MODEL_SERIALIZE_ALL_REQUESTS) {
    nbdkit_debug ("STR");
    thread_model = NBDKIT_THREAD_MODEL_SERIALIZE_ALL_REQUESTS;
  }
#endif

  if (p->plugin.thread_model) {
    r = p->plugin.thread_model ();
    if (r == -1)
      exit (EXIT_FAILURE);
    if (r < thread_model)
      thread_model = r;
  }

  return thread_model;
}