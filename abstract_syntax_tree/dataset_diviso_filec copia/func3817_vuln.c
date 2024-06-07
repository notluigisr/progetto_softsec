static int iwl_process_add_sta_resp(struct iwl_priv *priv,
				    struct iwl_addsta_cmd *addsta,
				    struct iwl_rx_packet *pkt)
{
	u8 sta_id = addsta->sta.sta_id;
	unsigned long flags;
	int ret = -EIO;

	if (pkt->hdr.flags & IWL_CMD_FAILED_MSK) {
		IWL_ERR(priv, "STR",
			pkt->hdr.flags);
		return ret;
	}

	IWL_DEBUG_INFO(priv, "STR",
		       sta_id);

	spin_lock_irqsave(&priv->shrd->sta_lock, flags);

	switch (pkt->u.add_sta.status) {
	case ADD_STA_SUCCESS_MSK:
		IWL_DEBUG_INFO(priv, "STR");
		iwl_sta_ucode_activate(priv, sta_id);
		ret = 0;
		break;
	case ADD_STA_NO_ROOM_IN_TABLE:
		IWL_ERR(priv, "STR",
			sta_id);
		break;
	case ADD_STA_NO_BLOCK_ACK_RESOURCE:
		IWL_ERR(priv, "STR"
			"STR", sta_id);
		break;
	case ADD_STA_MODIFY_NON_EXIST_STA:
		IWL_ERR(priv, "STR",
			sta_id);
		break;
	default:
		IWL_DEBUG_ASSOC(priv, "STR",
				pkt->u.add_sta.status);
		break;
	}

	IWL_DEBUG_INFO(priv, "STR",
		       priv->stations[sta_id].sta.mode ==
		       STA_CONTROL_MODIFY_MSK ?  "STR",
		       sta_id, priv->stations[sta_id].sta.sta.addr);

	
	IWL_DEBUG_INFO(priv, "STR",
		       priv->stations[sta_id].sta.mode ==
		       STA_CONTROL_MODIFY_MSK ? "STR",
		       addsta->sta.addr);
	spin_unlock_irqrestore(&priv->shrd->sta_lock, flags);

	return ret;
}