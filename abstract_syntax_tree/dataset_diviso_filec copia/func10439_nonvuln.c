static void iwl_sta_ucode_deactivate(struct iwl_priv *priv, u8 sta_id)
{
	
	if ((priv->stations[sta_id].used &
	     (IWL_STA_UCODE_ACTIVE | IWL_STA_DRIVER_ACTIVE)) !=
	      IWL_STA_UCODE_ACTIVE)
		IWL_ERR(priv, "STR", sta_id);

	priv->stations[sta_id].used &= ~IWL_STA_UCODE_ACTIVE;

	memset(&priv->stations[sta_id], 0, sizeof(struct iwl_station_entry));
	IWL_DEBUG_ASSOC(priv, "STR", sta_id);
}