HttpStateData::processReply()
{

    if (flags.handling1xx) { 
        debugs(11, 5, HERE << "STR");
        flags.handling1xx = false;
        Must(!flags.headers_parsed);
    }

    if (!flags.headers_parsed) { 
        PROF_start(HttpStateData_processReplyHeader);
        processReplyHeader();
        PROF_stop(HttpStateData_processReplyHeader);

        if (!continueAfterParsingHeader()) 
            return; 

        adaptOrFinalizeReply(); 
    }

    
    PROF_start(HttpStateData_processReplyBody);
    processReplyBody(); 
    PROF_stop(HttpStateData_processReplyBody);
}