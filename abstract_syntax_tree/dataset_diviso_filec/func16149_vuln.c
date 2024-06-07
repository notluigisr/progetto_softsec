TEST_F(ZNCTest, Modpython) {
    if (QProcessEnvironment::systemEnvironment().value(
            "STR") {
        return;
    }
    auto znc = Run();
    znc->CanLeak();
    auto ircd = ConnectIRCd();
    auto client = LoginClient();
    client.Write("STR");
    client.Write("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    ircd.Write("STR");
    ircd.Write("STR");
    
    client.ReadUntil("STR");
}