void MainWindow::onMultitrackModified()
{
    setWindowModified(true);

    
    if (!m_timelineDock->selection().isEmpty()) {
        int trackIndex = m_timelineDock->selection().first().y();
        int clipIndex = m_timelineDock->selection().first().x();
        QScopedPointer<Mlt::ClipInfo> info(m_timelineDock->getClipInfo(trackIndex, clipIndex));
        if (info && info->producer && info->producer->is_valid()) {
            int expected = info->frame_in;
            QScopedPointer<Mlt::ClipInfo> info2(m_timelineDock->getClipInfo(trackIndex, clipIndex - 1));
            if (info2 && info2->producer && info2->producer->is_valid()
                      && info2->producer->get(kShotcutTransitionProperty)) {
                
                expected -= info2->frame_count;
                info->producer->set(kPlaylistStartProperty, info2->start);
            } else {
                info->producer->set(kPlaylistStartProperty, info->start);
            }
            if (expected != info->producer->get_int(kFilterInProperty)) {
                int delta = expected - info->producer->get_int(kFilterInProperty);
                info->producer->set(kFilterInProperty, expected);
                emit m_filtersDock->producerInChanged(delta);
            }
            expected = info->frame_out;
            info2.reset(m_timelineDock->getClipInfo(trackIndex, clipIndex + 1));
            if (info2 && info2->producer && info2->producer->is_valid()
                      && info2->producer->get(kShotcutTransitionProperty)) {
                
                expected += info2->frame_count;
            }
            if (expected != info->producer->get_int(kFilterOutProperty)) {
                int delta = expected - info->producer->get_int(kFilterOutProperty);
                info->producer->set(kFilterOutProperty, expected);
                emit m_filtersDock->producerOutChanged(delta);
            }
        }
    }
}