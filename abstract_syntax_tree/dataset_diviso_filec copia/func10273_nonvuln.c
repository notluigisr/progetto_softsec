static inline void vring_used_flags_set_bit(VirtQueue *vq, int mask)
{
    hwaddr pa;
    pa = vq->vring.used + offsetof(VRingUsed, flags);
    stw_phys(pa, lduw_phys(pa) | mask);
}