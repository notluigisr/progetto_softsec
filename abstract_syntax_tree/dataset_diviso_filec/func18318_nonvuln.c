ConnStateData::finishDechunkingRequest(bool withSuccess)
{
    debugs(33, 5, HERE << "STR" << withSuccess);

    if (bodyPipe != NULL) {
        debugs(33, 7, HERE << "STR" << bodyPipe->status());
        BodyPipe::Pointer myPipe = bodyPipe;
        stopProducingFor(bodyPipe, withSuccess); 
        Must(!bodyPipe); 
        if (withSuccess) {
            Must(myPipe->bodySizeKnown());
            Http::StreamPointer context = pipeline.front();
            if (context != NULL && context->http && context->http->request)
                context->http->request->setContentLength(myPipe->bodySize());
        }
    }

    delete bodyParser;
    bodyParser = NULL;
}