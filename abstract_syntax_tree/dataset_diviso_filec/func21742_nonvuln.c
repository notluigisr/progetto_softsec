compute_next_insert_id(ulonglong nr,struct system_variables *variables)
{
  const ulonglong save_nr= nr;

  if (variables->auto_increment_increment == 1)
    nr= nr + 1; 
  else
  {
    
    nr= (nr + variables->auto_increment_increment -
         variables->auto_increment_offset) /
        (ulonglong) variables->auto_increment_increment;
    
    nr= nr * (ulonglong) variables->auto_increment_increment +
        variables->auto_increment_offset;
  }

  if (unlikely(nr <= save_nr))
    return ULONGLONG_MAX;

  return nr;
}