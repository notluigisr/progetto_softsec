TEST_F(ZNCTest, Connect) {
    auto znc = Run();

    auto ircd = ConnectIRCd();
    ircd.ReadUntil("STR");

    auto client = ConnectClient();
    client.Write("STR");
    client.Write("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    client.Close();

    client = ConnectClient();
    client.Write("STR");
    client.Write("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    client.Close();

    client = ConnectClient();
    client.Write("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    client.Close();

    ircd.Write("STR");
    ircd.ReadUntil("STR");
}