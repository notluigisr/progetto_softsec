void PeerListWidget::clear()
{
    qDebug("STR");
    m_peerItems.clear();
    m_peerAddresses.clear();
    m_missingFlags.clear();
    int nbrows = m_listModel->rowCount();
    if (nbrows > 0) {
        qDebug("STR", nbrows);
        m_listModel->removeRows(0,  nbrows);
    }
}