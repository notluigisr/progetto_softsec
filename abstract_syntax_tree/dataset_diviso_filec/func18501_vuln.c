Http::Stream::getNextRangeOffset() const
{
    debugs (33, 5, "STR" << http->request->range <<
            "STR" << http->out.offset <<
            "STR" << reply);

    
    
    

    if (http->request->range) {
        
        
        assert(http->range_iter.valid);
        
        assert(canPackMoreRanges());
        {
            assert(http->range_iter.currentSpec());
            
            int64_t start = http->range_iter.currentSpec()->offset +
                            http->range_iter.currentSpec()->length -
                            http->range_iter.debt();
            debugs(33, 3, "STR" << http->out.offset);
            debugs(33, 3, "STR"
                   "STR" << start <<
                   "STR" <<
                   "STR" << http->range_iter.currentSpec()->offset <<
                   "STR" << http->range_iter.currentSpec()->offset +
                   http->range_iter.currentSpec()->length << "STR"
                   "STR" << http->range_iter.currentSpec()->length <<
                   "STR" << http->range_iter.debt());
            if (http->range_iter.currentSpec()->length != -1)
                assert(http->out.offset <= start);  

            return start;
        }

    } else if (reply && reply->contentRange()) {
        
        
        return http->out.offset + reply->contentRange()->spec.offset;
    }

    return http->out.offset;
}