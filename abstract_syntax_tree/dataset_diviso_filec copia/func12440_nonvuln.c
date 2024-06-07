static void bnx2x_hw_enable_status(struct bnx2x *bp)
{
	u32 val;

	val = REG_RD(bp, CFC_REG_WEAK_ENABLE_PF);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, PBF_REG_DISABLE_PF);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSI_EN);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSIX_EN);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSIX_FUNC_MASK);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR);
	DP(BNX2X_MSG_SP, "STR", val);

	val = REG_RD(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER);
	DP(BNX2X_MSG_SP, "STR",
	   val);
}