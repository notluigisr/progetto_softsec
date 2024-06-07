void PlayerGeneric::setPatternPos(mp_uint32 pos, mp_uint32 row, bool resetChannels, bool resetFXMemory)
{
	if (player)
		player->setPatternPos(pos, row, resetChannels, resetFXMemory);
}