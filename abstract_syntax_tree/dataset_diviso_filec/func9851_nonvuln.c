static bool bnx2x_trylock_hw_lock(struct bnx2x *bp, u32 resource)
{
	u32 lock_status;
	u32 resource_bit = (1 << resource);
	int func = BP_FUNC(bp);
	u32 hw_lock_control_reg;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
	   "STR", resource);

	
	if (resource > HW_LOCK_MAX_RESOURCE_VALUE) {
		DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
		   "STR",
		   resource, HW_LOCK_MAX_RESOURCE_VALUE);
		return false;
	}

	if (func <= 5)
		hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + func*8);
	else
		hw_lock_control_reg =
				(MISC_REG_DRIVER_CONTROL_7 + (func - 6)*8);

	
	REG_WR(bp, hw_lock_control_reg + 4, resource_bit);
	lock_status = REG_RD(bp, hw_lock_control_reg);
	if (lock_status & resource_bit)
		return true;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
	   "STR", resource);
	return false;
}