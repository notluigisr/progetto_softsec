DefragRegisterTests(void)
{
#ifdef UNITTESTS
    UtRegisterTest("STR", DefragInOrderSimpleTest);
    UtRegisterTest("STR", DefragReverseSimpleTest);
    UtRegisterTest("STR", DefragSturgesNovakBsdTest);
    UtRegisterTest("STR", DefragSturgesNovakLinuxTest);
    UtRegisterTest("STR",
                   DefragSturgesNovakWindowsTest);
    UtRegisterTest("STR",
                   DefragSturgesNovakSolarisTest);
    UtRegisterTest("STR", DefragSturgesNovakFirstTest);
    UtRegisterTest("STR", DefragSturgesNovakLastTest);

    UtRegisterTest("STR", DefragIPv4NoDataTest);
    UtRegisterTest("STR", DefragIPv4TooLargeTest);

    UtRegisterTest("STR", IPV6DefragInOrderSimpleTest);
    UtRegisterTest("STR", IPV6DefragReverseSimpleTest);
    UtRegisterTest("STR",
                   IPV6DefragSturgesNovakBsdTest);
    UtRegisterTest("STR",
                   IPV6DefragSturgesNovakLinuxTest);
    UtRegisterTest("STR",
                   IPV6DefragSturgesNovakWindowsTest);
    UtRegisterTest("STR",
                   IPV6DefragSturgesNovakSolarisTest);
    UtRegisterTest("STR",
                   IPV6DefragSturgesNovakFirstTest);
    UtRegisterTest("STR",
                   IPV6DefragSturgesNovakLastTest);

    UtRegisterTest("STR", DefragVlanTest);
    UtRegisterTest("STR", DefragVlanQinQTest);
    UtRegisterTest("STR", DefragTrackerReuseTest);
    UtRegisterTest("STR", DefragTimeoutTest);
    UtRegisterTest("STR", DefragMfIpv4Test);
    UtRegisterTest("STR", DefragMfIpv6Test);
#endif 
}