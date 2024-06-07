xfs_alloc_ag_max_usable(
	struct xfs_mount	*mp)
{
	unsigned int		blocks;

	blocks = XFS_BB_TO_FSB(mp, XFS_FSS_TO_BB(mp, 4)); 
	blocks += XFS_ALLOC_AGFL_RESERVE;
	blocks += 3;			
	if (xfs_sb_version_hasfinobt(&mp->m_sb))
		blocks++;		
	if (xfs_sb_version_hasrmapbt(&mp->m_sb))
		blocks++; 		
	if (xfs_sb_version_hasreflink(&mp->m_sb))
		blocks++;		

	return mp->m_sb.sb_agblocks - blocks;
}