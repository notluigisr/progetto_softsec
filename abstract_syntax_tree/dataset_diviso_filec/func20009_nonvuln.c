void Server::handleCommand_ModChannelMsg(NetworkPacket *pkt)
{
	std::string channel_name, channel_msg;
	*pkt >> channel_name >> channel_msg;

	session_t peer_id = pkt->getPeerId();
	verbosestream << "STR" << peer_id <<
		"STR" << channel_msg <<
		std::endl;

	
	if (!g_settings->getBool("STR")) {
		return;
	}

	
	if (!m_modchannel_mgr->channelRegistered(channel_name)) {
		NetworkPacket resp_pkt(TOCLIENT_MODCHANNEL_SIGNAL,
			1 + 2 + channel_name.size(), peer_id);
		resp_pkt << (u8)MODCHANNEL_SIGNAL_CHANNEL_NOT_REGISTERED << channel_name;
		Send(&resp_pkt);
		return;
	}

	

	broadcastModChannelMessage(channel_name, channel_msg, peer_id);
}