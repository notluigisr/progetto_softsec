STATIC kern_return_t GC_forward_exception(mach_port_t thread, mach_port_t task,
                                          exception_type_t exception,
                                          exception_data_t data,
                                          mach_msg_type_number_t data_count)
{
  unsigned int i;
  kern_return_t r;
  mach_port_t port;
  exception_behavior_t behavior;
  thread_state_flavor_t flavor;

  thread_state_data_t thread_state;
  mach_msg_type_number_t thread_state_count = THREAD_STATE_MAX;

  for (i=0; i < GC_old_exc_ports.count; i++)
    if (GC_old_exc_ports.masks[i] & (1 << exception))
      break;
  if (i == GC_old_exc_ports.count)
    ABORT("STR");

  port = GC_old_exc_ports.ports[i];
  behavior = GC_old_exc_ports.behaviors[i];
  flavor = GC_old_exc_ports.flavors[i];

  if (behavior == EXCEPTION_STATE || behavior == EXCEPTION_STATE_IDENTITY) {
    r = thread_get_state(thread, flavor, thread_state, &thread_state_count);
    if(r != KERN_SUCCESS)
      ABORT("STR");
    }

  switch(behavior) {
    case EXCEPTION_STATE:
      r = exception_raise_state(port, thread, task, exception, data, data_count,
                                &flavor, thread_state, thread_state_count,
                                thread_state, &thread_state_count);
      break;
    case EXCEPTION_STATE_IDENTITY:
      r = exception_raise_state_identity(port, thread, task, exception, data,
                                         data_count, &flavor, thread_state,
                                         thread_state_count, thread_state,
                                         &thread_state_count);
      break;
     
    default: 
      r = exception_raise(port, thread, task, exception, data, data_count);
  }

  if (behavior == EXCEPTION_STATE || behavior == EXCEPTION_STATE_IDENTITY) {
    r = thread_set_state(thread, flavor, thread_state, thread_state_count);
    if (r != KERN_SUCCESS)
      ABORT("STR");
  }
  return r;
}