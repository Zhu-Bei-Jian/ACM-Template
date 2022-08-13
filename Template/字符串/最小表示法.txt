//最小表示法
int getMin(int len) {
    int i = 0, j = 1;
    int l;
    while (i < len && j < len) {
        for (l = 0; l < len; l++)
            if (str[(i + l) % len] != str[(j + l) % len]) break;
        if (l >= len) break;
        if (str[(i + l) % len] > str[(j + l) % len]) {
            if (i + l + 1 > j) i = i + l + 1;
            else i = j + 1;
        }
        else if (j + l + 1 > i) j = j + l + 1; 
        else j = i + 1;
    }
    return i < j ? i : j;
}

int getMax(int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int t = str[(i + k) % len] - str[(j + k) % len];
        if (!t) k++;
        else {
            if (t > 0) {
                if (j + k + 1 > i) j = j + k + 1;
                else j = i + 1;
            }
            else if (i + k + 1 > j) i = i + k + 1;
            else i = j + 1;
            k = 0;
        }
    }
    return i < j ? i : j;

}