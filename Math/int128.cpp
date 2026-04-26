typedef __int128 lll;

void print128(lll x) {
    if (x < 0) { cout << '-'; x = -x; }
    if (x > 9) print128(x / 10);
    cout << (char)('0' + x % 10);
}

lll read128() {
    string s; cin >> s;
    lll res = 0;
    int i = (s[0] == '-') ? 1 : 0;
    for (; i < s.size(); i++) res = res * 10 + (s[i] - '0');
    return (s[0] == '-') ? -res : res;
}

/*
  int n; cin >> n;
  vector<lll> a(n), b(n, 0);
  for(int i = 0; i < n; i++) a[i] = read128();
  lll yes = 0;
  print128(yes);
*/
