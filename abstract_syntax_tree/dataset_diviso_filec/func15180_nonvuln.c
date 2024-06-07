Client::adjustBodyBytesRead(const int64_t delta)
{
    int64_t &bodyBytesRead = originalRequest()->hier.bodyBytesRead;

    
    if (bodyBytesRead < 0)
        bodyBytesRead = 0;

    bodyBytesRead += delta; 

    
    Must(bodyBytesRead >= 0);
}