bool KaxBlockBlob::ReplaceSimpleByGroup()
{
  if (SimpleBlockMode== BLOCK_BLOB_ALWAYS_SIMPLE)
    return false;

  if (!bUseSimpleBlock) {
    if (Block.group == NULL) {
      Block.group = new KaxBlockGroup();
    }
  }
#if MATROSKA_VERSION >= 2
  else {

    if (Block.simpleblock != NULL) {
      KaxSimpleBlock *old_simpleblock = Block.simpleblock;
      Block.group = new KaxBlockGroup();
      
      assert(false);
      
      delete old_simpleblock;
    } else {
      Block.group = new KaxBlockGroup();
    }
  }
#endif
  if (ParentCluster != NULL)
    Block.group->SetParent(*ParentCluster);

  bUseSimpleBlock = false;
  return true;
}