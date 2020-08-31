// dependency :
// how to use mt19937

int rand(mt19937 &rd, int l, int r){
    // mt19937 rd((unsigned)chrono::steady_clock::now().time_since_epoch().count());
    // mt19937 rd(0x917917);
    uniform_int_distribution<int> rnd(l, r);
    return rnd(rd);
}