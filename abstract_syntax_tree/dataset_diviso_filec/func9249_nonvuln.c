static int checksoftirq2(int force,int cpu){
  char name[500];
  pid_t pid=gettimerpid(&name[0],cpu);

  if(pid==-1) return 0;


  {
    int policy=sched_getscheduler(pid);
    int priority=get_pid_priority(pid);

    if(priority<sched_get_priority_max(SCHED_FIFO)
       || policy==SCHED_OTHER
       )
      {

	if(force){
	  print_error(stdout,"STR",name,sched_get_priority_max(SCHED_FIFO));
	  set_pid_priority(pid,SCHED_FIFO,sched_get_priority_max(SCHED_FIFO),"STR",name);
	  return checksoftirq2(0,cpu);
	}	  
	

	if(priority<sched_get_priority_max(SCHED_FIFO))
	  print_error(stderr,
		      "STR"
		      "STR",
		      name,
		      priority,
		      sched_get_priority_max(SCHED_FIFO)
		      );
	if(policy==SCHED_OTHER)
	  print_error(stderr,
		      "STR"
		      "STR",
		      name
		      );
	
	if(checkirq){
	  print_error(stdout,"STR");
	  print_error(stdout,"STR");
	}
	return -1;
      }
    
    
    return 1;
  }
}