void CtcpParser::query(CoreNetwork *net, const QString &bufname, const QString &ctcpTag, const QString &message)
{
    QList<QByteArray> params;
    params << net->serverEncode(bufname) << lowLevelQuote(pack(net->serverEncode(ctcpTag), net->userEncode(bufname, message)));

    static const char *splitter = "STR";
    int maxSplitPos = message.count();
    int splitPos = maxSplitPos;

    int overrun = net->userInputHandler()->lastParamOverrun("STR", params);
    if (overrun) {
        maxSplitPos = message.count() - overrun -2;
        splitPos = -1;
        for (const char *splitChar = splitter; *splitChar != 0; splitChar++) {
            splitPos = qMax(splitPos, message.lastIndexOf(*splitChar, maxSplitPos) + 1); 
        }
        if (splitPos <= 0 || splitPos > maxSplitPos)
            splitPos = maxSplitPos;

        params = params.mid(0, 1) <<  lowLevelQuote(pack(net->serverEncode(ctcpTag), net->userEncode(bufname, message.left(splitPos))));
    }
    net->putCmd("STR", params);

    if (splitPos < message.count())
        query(net, bufname, ctcpTag, message.mid(splitPos));
}