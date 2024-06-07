void Monitor::apply_monmap_to_compatset_features()
{
  CompatSet new_features(features);
  mon_feature_t monmap_features = monmap->get_required_features();

  
  if (monmap_features.contains_all(ceph::features::mon::FEATURE_KRAKEN)) {
    assert(ceph::features::mon::get_persistent().contains_all(
           ceph::features::mon::FEATURE_KRAKEN));
    
    assert(HAVE_FEATURE(quorum_con_features, SERVER_KRAKEN));
    new_features.incompat.insert(CEPH_MON_FEATURE_INCOMPAT_KRAKEN);
  }
  if (monmap_features.contains_all(ceph::features::mon::FEATURE_LUMINOUS)) {
    assert(ceph::features::mon::get_persistent().contains_all(
           ceph::features::mon::FEATURE_LUMINOUS));
    
    assert(HAVE_FEATURE(quorum_con_features, SERVER_LUMINOUS));
    new_features.incompat.insert(CEPH_MON_FEATURE_INCOMPAT_LUMINOUS);
  }

  dout(5) << __func__ << dendl;
  _apply_compatset_features(new_features);
}