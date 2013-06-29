void main () {
    int a[10][10];
    int i = 9;
    int j = 9;
    while (i >= 0) {
        while (j >= 0) {
            a[i][j] = (i * 10 + j);
            write(a[i][j]);
            write(" ");
            j = j - 1;
        }
        write("\n");
        i = i - 1;
        j = 9;
    }
}