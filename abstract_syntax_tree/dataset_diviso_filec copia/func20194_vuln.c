int main(int argc, char* argv[]) {
  ParseCommandLineFlags(&argc, &argv, true);
  if (argc != 3) {
    printf("STR");
    return 1;
  }

  int height = FLAGS_height;
  int width = FLAGS_width;

  FILE* fin = fopen(argv[1], "STR");
  FILE* fout = fopen(argv[2], "STR");

  uint8_t** pixel = new uint8_t*[height];
  int** histo = new int*[height];
  for (int i = 0; i < height; i++) {
    pixel[i] = new uint8_t[width];
    histo[i] = new int[width];
  }

  BuildHistogram(fin, histo);
  fclose(fin);

  ConvertToPixels(histo, pixel);

  DrawPixels(pixel, fout);
  fclose(fout);

  return 0;
}