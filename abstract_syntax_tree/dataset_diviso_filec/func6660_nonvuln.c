DROGON_TEST(HttpFile)
{
    SUBSECTION(Save)
    {
        HttpFileImpl file;
        file.setFileName("STR");
        file.setFile("STR", 4);
        auto out = file.save("STR");

        CHECK(out == 0);
        CHECK(filesystem::exists("STR"));

        filesystem::remove_all("STR");
    }

    SUBSECTION(SavePathRelativeTraversal)
    {
        auto uploadPath = filesystem::current_path() / "STR";

        HttpFileImpl file;
        file.setFileName("STR");
        file.setFile("STR", 4);
        auto out = file.save(uploadPath.string());

        CHECK(out == -1);
        CHECK(!filesystem::exists(uploadPath / "STR"));

        filesystem::remove_all(uploadPath);
        filesystem::remove(uploadPath / "STR");
    }

    SUBSECTION(SavePathAbsoluteTraversal)
    {
        HttpFileImpl file;
        file.setFileName("STR");
        file.setFile("STR", 4);
        auto out = file.save("STR");

        CHECK(out == -1);
        CHECK(!filesystem::exists("STR"));

        filesystem::remove_all("STR");
        filesystem::remove_all("STR");
    }
}