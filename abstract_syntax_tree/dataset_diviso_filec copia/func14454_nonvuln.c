static inline bool is_client_area_valid(const struct RESTART_HDR *rhdr,
					bool usa_error)
{
	u16 ro = le16_to_cpu(rhdr->ra_off);
	const struct RESTART_AREA *ra = Add2Ptr(rhdr, ro);
	u16 ra_len = le16_to_cpu(ra->ra_len);
	const struct CLIENT_REC *ca;
	u32 i;

	if (usa_error && ra_len + ro > SECTOR_SIZE - sizeof(short))
		return false;

	
	ca = Add2Ptr(ra, le16_to_cpu(ra->client_off));

	
	for (i = 0; i < 2; i++) {
		u16 client_idx = le16_to_cpu(ra->client_idx[i]);
		bool first_client = true;
		u16 clients = le16_to_cpu(ra->log_clients);

		while (client_idx != LFS_NO_CLIENT) {
			const struct CLIENT_REC *cr;

			if (!clients ||
			    client_idx >= le16_to_cpu(ra->log_clients))
				return false;

			clients -= 1;
			cr = ca + client_idx;

			client_idx = le16_to_cpu(cr->next_client);

			if (first_client) {
				first_client = false;
				if (cr->prev_client != LFS_NO_CLIENT_LE)
					return false;
			}
		}
	}

	return true;
}