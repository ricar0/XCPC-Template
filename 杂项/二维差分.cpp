void Insert(int x1, int y1, int x2, int y2, int v) {
    c[x1][y1] += v;
    c[x1][y2+1] -= v;
    c[x2+1][y1] -= v;
    c[x2+1][y2+1] += v;
}