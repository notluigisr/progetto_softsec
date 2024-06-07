Item_sp::cleanup()
{
  delete sp_result_field;
  sp_result_field= NULL;
  m_sp= NULL;
  delete func_ctx;
  func_ctx= NULL;
  free_root(&sp_mem_root, MYF(0));
  dummy_table->alias.free();
}