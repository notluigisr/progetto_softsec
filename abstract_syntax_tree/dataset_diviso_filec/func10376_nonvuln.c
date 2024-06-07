flow_set_dl_vlan(struct flow *flow, ovs_be16 vid)
{
    if (vid == htons(OFP10_VLAN_NONE)) {
        flow->vlan_tci = htons(0);
    } else {
        vid &= htons(VLAN_VID_MASK);
        flow->vlan_tci &= ~htons(VLAN_VID_MASK);
        flow->vlan_tci |= htons(VLAN_CFI) | vid;
    }
}