bool LEX::sp_handler_declaration_finalize(THD *thd, int type)
{
  sp_label *hlab= spcont->pop_label(); 
  sp_instr_hreturn *i;

  if (type == sp_handler::CONTINUE)
  {
    i= new (thd->mem_root) sp_instr_hreturn(sphead->instructions(), spcont);
    if (unlikely(i == NULL) ||
        unlikely(sphead->add_instr(i)))
      return true;
  }
  else
  {  
    i= new (thd->mem_root) sp_instr_hreturn(sphead->instructions(), spcont);
    if (unlikely(i == NULL) ||
        unlikely(sphead->add_instr(i)) ||
        unlikely(sphead->push_backpatch(thd, i, spcont->last_label()))) 
      return true;
  }
  sphead->backpatch(hlab);
  spcont= spcont->pop_context();
  return false;
}