int c = 10;
for (int i = n; i > 0; i--) {
  for (int j = i+1; j <=n; j += c) {
    printf(".");
  }
}
