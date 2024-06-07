void PeerListWidget::loadPeers(BitTorrent::TorrentHandle *const torrent, bool forceHostnameResolution)
{
    if (!torrent) return;

    QList<BitTorrent::PeerInfo> peers = torrent->peers();
    QSet<QString> oldeersSet = m_peerItems.keys().toSet();

    foreach (const BitTorrent::PeerInfo &peer, peers) {
        BitTorrent::PeerAddress addr = peer.address();
        if (addr.ip.isNull()) continue;

        QString peerIp = addr.ip.toString();
        if (m_peerItems.contains(peerIp)) {
            
            updatePeer(peerIp, torrent, peer);
            oldeersSet.remove(peerIp);
            if (forceHostnameResolution && m_resolver)
                m_resolver->resolve(peerIp);
        }
        else {
            
            m_peerItems[peerIp] = addPeer(peerIp, torrent, peer);
            m_peerAddresses[peerIp] = addr;
            
            if (m_resolver)
                m_resolver->resolve(peerIp);
        }
    }
    
    QSetIterator<QString> it(oldeersSet);
    while (it.hasNext()) {
        const QString& ip = it.next();
        m_missingFlags.remove(ip);
        m_peerAddresses.remove(ip);
        QStandardItem *item = m_peerItems.take(ip);
        m_listModel->removeRow(item->row());
    }
}