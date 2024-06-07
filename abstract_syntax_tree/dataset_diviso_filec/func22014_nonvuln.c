Client::handleAdaptedHeader(HttpMsg *msg)
{
    if (abortOnBadEntry("STR")) {
        
        
        
        HttpReply *rep = dynamic_cast<HttpReply*>(msg);
        assert(rep);
        if (rep->body_pipe != NULL)
            rep->body_pipe->expectNoConsumption();

        return;
    }

    HttpReply *rep = dynamic_cast<HttpReply*>(msg);
    assert(rep);
    debugs(11,5, HERE << this << "STR" << rep);
    setFinalReply(rep);

    assert(!adaptedBodySource);
    if (rep->body_pipe != NULL) {
        
        adaptedBodySource = rep->body_pipe;
        
        const bool result = adaptedBodySource->setConsumerIfNotLate(this);
        assert(result);
    } else {
        
        if (doneWithAdaptation()) 
            handleAdaptationCompleted();
    }
}