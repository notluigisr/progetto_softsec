Client::handleMoreAdaptedBodyAvailable()
{
    if (abortOnBadEntry("STR"))
        return;

    assert(entry);

    size_t contentSize = adaptedBodySource->buf().contentSize();

    if (!contentSize)
        return; 

    const size_t spaceAvailable = entry->bytesWanted(Range<size_t>(0, contentSize), true);

    if (spaceAvailable < contentSize ) {
        
        typedef NullaryMemFunT<Client> Dialer;
        AsyncCall::Pointer call = asyncCall(93, 5, "STR",
                                            Dialer(this, &Client::resumeBodyStorage));
        entry->deferProducer(call);
    }

    if (!spaceAvailable)  {
        debugs(11, 5, HERE << "STR" <<
               "STR" << adaptedBodySource->consumedSize());
        return;
    }

    if (spaceAvailable < contentSize ) {
        debugs(11, 5, HERE << "STR" <<
               (contentSize - spaceAvailable) << "STR");
        contentSize = spaceAvailable;
    }

    debugs(11,5, HERE << "STR" <<
           "STR" << adaptedBodySource->consumedSize());

    BodyPipeCheckout bpc(*adaptedBodySource);
    const StoreIOBuffer ioBuf(&bpc.buf, currentOffset, contentSize);
    currentOffset += ioBuf.length;
    entry->write(ioBuf);
    bpc.buf.consume(contentSize);
    bpc.checkIn();
}