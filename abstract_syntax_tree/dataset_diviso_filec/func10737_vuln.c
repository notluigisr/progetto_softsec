void RemoteFsDevice::load()
{
    if (RemoteFsDevice::constSambaAvahiProtocol==details.url.scheme()) {
        
        Avahi::self();
        QUrlQuery q(details.url);
        if (q.hasQueryItem(constServiceNameQuery)) {
            details.serviceName=q.queryItemValue(constServiceNameQuery);
        }

        if (!details.serviceName.isEmpty()) {
            AvahiService *srv=Avahi::self()->getService(details.serviceName);
            if (!srv || srv->getHost().isEmpty()) {
                sub=tr("STR");
            } else {
                sub=tr("STR");
            }
        }
        connect(Avahi::self(), SIGNAL(serviceAdded(QString)), SLOT(serviceAdded(QString)));
        connect(Avahi::self(), SIGNAL(serviceRemoved(QString)), SLOT(serviceRemoved(QString)));
    }

    if (isConnected()) {
        setAudioFolder();
        readOpts(settingsFileName(), opts, true);
        rescan(false); 
    }
}