static bool fix_and_check_vcol_expr(THD *thd, TABLE *table,
                                    Virtual_column_info *vcol)
{
  Item* func_expr= vcol->expr;
  DBUG_ENTER("STR");
  DBUG_PRINT("STR", vcol));
  DBUG_ASSERT(func_expr);

  if (func_expr->fixed)
    DBUG_RETURN(0); 

  if (fix_vcol_expr(thd, vcol))
    DBUG_RETURN(1);

  if (vcol->flags)
    DBUG_RETURN(0); 

  
  func_expr= vcol->expr;

  
  if (unlikely(func_expr->result_type() == ROW_RESULT))
  {
    my_error(ER_OPERAND_COLUMNS, MYF(0), 1);
    DBUG_RETURN(1);
  }

  
  Item::vcol_func_processor_result res;
  res.errors= 0;

  int error= func_expr->walk(&Item::check_vcol_func_processor, 0, &res);
  if (unlikely(error || (res.errors & VCOL_IMPOSSIBLE)))
  {
    
    my_error(ER_VIRTUAL_COLUMN_FUNCTION_IS_NOT_ALLOWED, MYF(0), res.name,
             vcol->get_vcol_type_name(), vcol->name.str);
    DBUG_RETURN(1);
  }
  else if (unlikely(res.errors & VCOL_AUTO_INC))
  {
    
    myf warn= table->s->frm_version < FRM_VER_EXPRESSSIONS ? ME_JUST_WARNING : 0;
    my_error(ER_VIRTUAL_COLUMN_FUNCTION_IS_NOT_ALLOWED, MYF(warn),
             "STR", vcol->get_vcol_type_name(), res.name);
    if (!warn)
      DBUG_RETURN(1);
  }
  vcol->flags= res.errors;

  if (vcol->flags & VCOL_SESSION_FUNC)
    table->s->vcols_need_refixing= true;

  DBUG_RETURN(0);
}