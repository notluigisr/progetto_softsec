void OSD::write_superblock(ObjectStore::Transaction& t)
{
  dout(10) << "STR" << superblock << dendl;

  
  if (!superblock.compat_features.incompat.contains(CEPH_OSD_FEATURE_INCOMPAT_BASE))
    superblock.compat_features.incompat.insert(CEPH_OSD_FEATURE_INCOMPAT_BASE);

  bufferlist bl;
  ::encode(superblock, bl);
  t.write(coll_t::meta(), OSD_SUPERBLOCK_GOBJECT, 0, bl.length(), bl);
}