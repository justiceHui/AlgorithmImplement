// dependency :
// matrix multiply with avx
// Time Complexity : fast O(N^3)
// 500 : 59ms, 1000 : 300ms, 2000 : 2400ms, 3000 : 10000ms
// (normal) 500 : 120ms, 1000 : 830ms, 2000 : 5700ms

#include <immintrin.h>
#pragma GCC optimize("fast-math")
#pragma GCC target("avx,avx2,fma")
using namespace std;

struct Matrix{
    int n, m; float **v;
    void init(int N, int M){
        n = N; m = M; v = (float**)malloc(sizeof(float*) * n);
        #ifndef LOCAL
        for(int i=0; i<n; i++) v[i] = (float*)aligned_alloc(256/8, (sizeof(float)*m+15)>>4<<4); // for linux
        #else
        for(int i=0; i<n; i++) v[i] = (float*)_aligned_malloc((sizeof(float)*m+15)>>4<<4, 256/8); // for windows
        #endif
    }
    ~Matrix(){
        if(v) for(int i=0; i<n; i++) _aligned_free(v[i]);
        if(v) free(v);
    }
};

void multiply_avx(Matrix &a, Matrix &b, Matrix &c){
    for(int i=0; i<c.n; i++) memset(c.v[i], 0, sizeof(float)*c.m); // init
    for(int i=0; i<a.n; i++) for(int j=0; j<a.m; j++){
        __m256 now = _mm256_set1_ps(a.v[i][j]);
        int k = 0;
        for(; k+7<b.m; k+=8){
            __m256 *t1 = (__m256*)(b.v[j]+k);
            __m256 *t2 = (__m256*)(c.v[i]+k);
            *t2 = _mm256_add_ps(*t2, _mm256_mul_ps(now, *t1));
        }
        for(; k<b.m; k++) c.v[i][k] += a.v[i][j] * b.v[j][k];
    }
}

void multiply_normal(Matrix &a, Matrix &b, Matrix &c){
    for(int i=0; i<a.n; i++) for(int j=0; j<b.m; j++) c.v[i][j] = 0;
    for(int i=0; i<a.n; i++) for(int k=0; k<a.m; k++){
        for(int j=0; j<b.m; j++) c.v[i][j] += a.v[i][k] * b.v[k][j];
    }
}