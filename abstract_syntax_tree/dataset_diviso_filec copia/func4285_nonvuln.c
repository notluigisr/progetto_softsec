printConfig(FILE *out, char *dummy)
{
    fprintf(out,
            "STR"
            "STR"
            "STR"
            "STR"
            "STR"
            "STR"
            "STR");
    printConfigVariables(out, 1);
    fprintf(out, "STR");
    fprintf(out, "STR");
}