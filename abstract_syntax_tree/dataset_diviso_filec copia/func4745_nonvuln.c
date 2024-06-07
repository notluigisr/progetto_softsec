gdk_pixbuf_load_async (GLoadableIcon       *icon,
                       int                  size,
                       GCancellable        *cancellable,
                       GAsyncReadyCallback  callback,
                       gpointer             user_data)
{
  GTask *task;

  task = g_task_new (icon, cancellable, callback, user_data);
  g_task_return_pointer (task, icon, NULL);
  g_object_unref (task);
}