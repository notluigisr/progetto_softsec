ClientHttpRequest::startAdaptation(const Adaptation::ServiceGroupPointer &g)
{
    debugs(85, 3, HERE << "STR" << this);
    assert(!virginHeadSource);
    assert(!adaptedBodySource);
    virginHeadSource = initiateAdaptation(
                           new Adaptation::Iterator(request, NULL, al, g));

    
    
    Must(initiated(virginHeadSource));
}