static int parse_station_flags(struct genl_info *info,
			       struct station_parameters *params)
{
	struct nlattr *flags[NL80211_STA_FLAG_MAX + 1];
	struct nlattr *nla;
	int flag;

	
	nla = info->attrs[NL80211_ATTR_STA_FLAGS2];
	if (nla) {
		struct nl80211_sta_flag_update *sta_flags;

		sta_flags = nla_data(nla);
		params->sta_flags_mask = sta_flags->mask;
		params->sta_flags_set = sta_flags->set;
		if ((params->sta_flags_mask |
		     params->sta_flags_set) & BIT(__NL80211_STA_FLAG_INVALID))
			return -EINVAL;
		return 0;
	}

	

	nla = info->attrs[NL80211_ATTR_STA_FLAGS];
	if (!nla)
		return 0;

	if (nla_parse_nested(flags, NL80211_STA_FLAG_MAX,
			     nla, sta_flags_policy))
		return -EINVAL;

	params->sta_flags_mask = (1 << __NL80211_STA_FLAG_AFTER_LAST) - 1;
	params->sta_flags_mask &= ~1;

	for (flag = 1; flag <= NL80211_STA_FLAG_MAX; flag++)
		if (flags[flag])
			params->sta_flags_set |= (1<<flag);

	return 0;
}