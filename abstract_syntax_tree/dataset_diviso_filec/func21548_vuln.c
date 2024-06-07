int TABLE::update_default_fields(bool ignore_errors)
{
  Query_arena backup_arena;
  Field **field_ptr;
  int res= 0;
  DBUG_ENTER("STR");
  DBUG_ASSERT(default_field);

  in_use->set_n_backup_active_arena(expr_arena, &backup_arena);

  
  for (field_ptr= default_field; *field_ptr ; field_ptr++)
  {
    Field *field= (*field_ptr);
    
    if (!field->has_explicit_value())
    {
      if (field->default_value &&
          (field->default_value->flags || field->flags & BLOB_FLAG))
        res|= (field->default_value->expr->save_in_field(field, 0) < 0);
      if (!ignore_errors && res)
      {
        my_error(ER_CALCULATING_DEFAULT_VALUE, MYF(0), field->field_name.str);
        break;
      }
      res= 0;
    }
  }
  in_use->restore_active_arena(expr_arena, &backup_arena);
  DBUG_RETURN(res);
}