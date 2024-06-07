void mark_progress(struct st_command* command __attribute__((unused)),
                   int line)
{
  static ulonglong progress_start= 0; 
  DYNAMIC_STRING ds_progress;

  char buf[32], *end;
  ulonglong timer= timer_now();
  if (!progress_start)
    progress_start= timer;
  timer-= progress_start;

  if (init_dynamic_string(&ds_progress, "", 256, 256))
    die("STR");

  
  end= longlong2str(timer, buf, 10);
  dynstr_append_mem(&ds_progress, buf, (int)(end-buf));
  dynstr_append_mem(&ds_progress, "STR", 1);

  
  end= int10_to_str(line, buf, 10);
  dynstr_append_mem(&ds_progress, buf, (int)(end-buf));
  dynstr_append_mem(&ds_progress, "STR", 1);

  
  dynstr_append(&ds_progress, cur_file->file_name);
  dynstr_append_mem(&ds_progress, "STR", 1);

  
  end= int10_to_str(cur_file->lineno, buf, 10);
  dynstr_append_mem(&ds_progress, buf, (int)(end-buf));


  dynstr_append_mem(&ds_progress, "STR", 1);

  progress_file.write(&ds_progress);

  dynstr_free(&ds_progress);

}