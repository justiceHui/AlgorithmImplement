template<typename T, int mx_bit>
T xor_max(const vector<T> &V){
    T basis[mx_bit] = {0};
    for(auto i : V){
        for(int j=mx_bit-1; ~j; j--){
            if(~(i >> j) & 1) continue;
            if(!basis[j]){ basis[j] = i; break; }
            i ^= basis[j];
        }
    }
    T mx = 0;
    for(int i=mx_bit-1; ~i; i--) mx = max(mx, mx ^ basis[i]);
    return mx;
}
