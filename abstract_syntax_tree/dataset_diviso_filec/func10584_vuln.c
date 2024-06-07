Http::Stream::socketState()
{
    switch (clientStreamStatus(getTail(), http)) {

    case STREAM_NONE:
        
        if (http->request->range) {
            
            assert(http->range_iter.valid);
            

            if (!canPackMoreRanges()) {
                debugs(33, 5, "STR" <<
                       "STR" << clientConnection);
                
                return STREAM_COMPLETE;
            }
        } else if (reply && reply->contentRange()) {
            
            const int64_t &bytesSent = http->out.offset;
            const int64_t &bytesExpected = reply->contentRange()->spec.length;

            debugs(33, 7, "STR" <<
                   bytesSent << "STR" <<
                   reply->contentRange()->spec.offset << "STR");

            

            if (bytesSent == bytesExpected) 
                return STREAM_COMPLETE;

            if (bytesSent > bytesExpected) 
                return STREAM_UNPLANNED_COMPLETE;
        }

        return STREAM_NONE;

    case STREAM_COMPLETE:
        return STREAM_COMPLETE;

    case STREAM_UNPLANNED_COMPLETE:
        return STREAM_UNPLANNED_COMPLETE;

    case STREAM_FAILED:
        return STREAM_FAILED;
    }

    fatal ("STR");
    return STREAM_NONE;
}