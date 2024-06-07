void rtps_util_add_liveliness_qos(proto_tree *tree, tvbuff_t *tvb, gint offset, const guint encoding) {

  proto_tree *subtree;

  subtree = proto_tree_add_subtree(tree, tvb, offset, 12, ett_rtps_liveliness, NULL, "STR");

  proto_tree_add_item(subtree, hf_rtps_liveliness_kind, tvb, offset, 4, encoding);
  rtps_util_add_timestamp_sec_and_fraction(subtree, tvb, offset+4, encoding, hf_rtps_liveliness_lease_duration);
}