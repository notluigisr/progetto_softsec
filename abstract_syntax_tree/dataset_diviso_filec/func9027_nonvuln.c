void GetGhostNum(GF_StscEntry *ent, u32 EntryIndex, u32 count, GF_SampleTableBox *stbl)
{
	GF_StscEntry *nextEnt;
	u32 ghostNum = 1;

	if (!ent) {
		stbl->SampleToChunk->ghostNumber = 0;
		return;
	}

	if (!ent->nextChunk) {
		if (EntryIndex+1 == count) {
			
			if (stbl->ChunkOffset->type == GF_ISOM_BOX_TYPE_STCO) {
				GF_ChunkOffsetBox *stco = (GF_ChunkOffsetBox *)stbl->ChunkOffset;
				ghostNum = (stco->nb_entries > ent->firstChunk) ? (1 + stco->nb_entries - ent->firstChunk) : 1;
			} else {
				GF_ChunkLargeOffsetBox *co64 = (GF_ChunkLargeOffsetBox *)stbl->ChunkOffset;
				ghostNum = (co64->nb_entries > ent->firstChunk) ? (1 + co64->nb_entries - ent->firstChunk) : 1;
			}
		} else {
			
			nextEnt = &stbl->SampleToChunk->entries[EntryIndex+1];
			ghostNum = nextEnt->firstChunk - ent->firstChunk;
		}
	} else {
		ghostNum = (ent->nextChunk > ent->firstChunk) ? (ent->nextChunk - ent->firstChunk) : 1;
	}
	stbl->SampleToChunk->ghostNumber = ghostNum;
}