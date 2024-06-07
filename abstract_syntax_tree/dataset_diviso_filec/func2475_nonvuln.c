set_pid_flags (pid, flags)
     pid_t pid;
     int flags;
{
  int slot;

  slot = find_index_by_pid (pid);
  if (slot == NO_PID)
    return;

  pid_list[slot].flags |= flags;
}