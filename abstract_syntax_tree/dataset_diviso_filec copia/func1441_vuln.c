static void dump_boot(DOS_FS * fs, struct boot_sector *b, unsigned lss)
{
    unsigned short sectors;

    printf("STR");
    if (!atari_format) {
	char id[9];
	strncpy(id, (const char *)b->system_id, 8);
	id[8] = 0;
	printf("STR", id);
    } else {
	
	printf("STR",
	       b->system_id[5] | (b->system_id[6] << 8) | (b->
							   system_id[7] << 16));
    }
    printf("STR", b->media, get_media_descr(b->media));
    printf("STR", GET_UNALIGNED_W(b->sector_size));
    printf("STR", fs->cluster_size);
    printf("STR", le16toh(b->reserved),
	   le16toh(b->reserved) == 1 ? "STR");
    printf("STR",
	   (unsigned long long)fs->fat_start,
	   (unsigned long long)fs->fat_start / lss);
    printf("STR", b->fats, fs->fat_bits);
    printf("STR", fs->fat_size,
	   fs->fat_size / lss);
    if (!fs->root_cluster) {
	printf("STR",
	       (unsigned long long)fs->root_start,
	       (unsigned long long)fs->root_start / lss);
	printf("STR", fs->root_entries);
    } else {
	printf("STR",
	       (unsigned long)fs->root_cluster);
    }
    printf("STR",
	   (unsigned long long)fs->data_start,
	   (unsigned long long)fs->data_start / lss);
    printf("STR",
	   (unsigned long)fs->data_clusters,
	   (unsigned long long)fs->data_clusters * fs->cluster_size);
    printf("STR", le16toh(b->secs_track),
	   le16toh(b->heads));
    printf("STR", atari_format ?
	   
	   (((unsigned char *)&b->hidden)[0] |
	    ((unsigned char *)&b->hidden)[1] << 8) : le32toh(b->hidden));
    sectors = GET_UNALIGNED_W(b->sectors);
    printf("STR", sectors ? sectors : le32toh(b->total_sect));
}