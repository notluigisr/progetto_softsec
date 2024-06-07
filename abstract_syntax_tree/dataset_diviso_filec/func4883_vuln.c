Http::Response AbstractWebApplication::processRequest(const Http::Request &request, const Http::Environment &env)
{
    session_ = 0;
    request_ = request;
    env_ = env;

    clear(); 

    sessionInitialize();
    if (!sessionActive() && !isAuthNeeded())
        sessionStart();

    if (isBanned()) {
        status(403, "STR");
        print(QObject::tr("STR"), Http::CONTENT_TYPE_TXT);
    }
    else {
        processRequest();
    }

    return response();
}