/*
 * ビット操作の実践的応用（C99準拠版）
 * 
 * C99の機能を活用した効率的で
 * 保守性の高いビット操作の実装を示します。
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* ======================= */
/* 1. 高度なビットベクタ   */
/* ======================= */

typedef struct {
    uint64_t *bits;
    size_t size;  /* ビット数 */
} DynamicBitVector;

/* 動的ビットベクタの作成 */
DynamicBitVector* bitvec_create(size_t bit_count)
{
    size_t word_count = (bit_count + 63) / 64;
    DynamicBitVector *bv = malloc(sizeof(DynamicBitVector));
    if (!bv) return NULL;
    
    bv->bits = calloc(word_count, sizeof(uint64_t));
    if (!bv->bits) {
        free(bv);
        return NULL;
    }
    
    bv->size = bit_count;
    return bv;
}

/* ビットベクタの破棄 */
void bitvec_destroy(DynamicBitVector *bv)
{
    if (bv) {
        free(bv->bits);
        free(bv);
    }
}

/* ビット操作（インライン関数） */
static inline void bitvec_set(DynamicBitVector *bv, size_t bit)
{
    assert(bit < bv->size);
    bv->bits[bit / 64] |= (1ULL << (bit % 64));
}

static inline bool bitvec_test(const DynamicBitVector *bv, size_t bit)
{
    assert(bit < bv->size);
    return (bv->bits[bit / 64] & (1ULL << (bit % 64))) != 0;
}

/* ポピュレーションカウント（セットされたビット数） */
size_t bitvec_popcount(const DynamicBitVector *bv)
{
    size_t count = 0;
    size_t word_count = (bv->size + 63) / 64;
    
    for (size_t i = 0; i < word_count; i++) {
        uint64_t word = bv->bits[i];
        /* Brian Kernighanのアルゴリズム */
        while (word) {
            word &= word - 1;
            count++;
        }
    }
    
    return count;
}

/* ======================= */
/* 2. ハッシュ関数         */
/* ======================= */

/* MurmurHash2の簡易版（32ビット） */
uint32_t murmur_hash32(const void *key, size_t len, uint32_t seed)
{
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    
    uint32_t h = seed ^ (uint32_t)len;
    const uint8_t *data = (const uint8_t *)key;
    
    while (len >= 4) {
        uint32_t k = *(uint32_t *)data;
        
        k *= m;
        k ^= k >> r;
        k *= m;
        
        h *= m;
        h ^= k;
        
        data += 4;
        len -= 4;
    }
    
    /* 残りのバイト処理 */
    switch (len) {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
                h *= m;
    }
    
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    
    return h;
}

/* ======================= */
/* 3. ブルームフィルタ     */
/* ======================= */

typedef struct {
    DynamicBitVector *bits;
    size_t hash_count;
} BloomFilter;

/* ブルームフィルタの作成 */
BloomFilter* bloom_create(size_t bit_count, size_t hash_count)
{
    BloomFilter *bf = malloc(sizeof(BloomFilter));
    if (!bf) return NULL;
    
    bf->bits = bitvec_create(bit_count);
    if (!bf->bits) {
        free(bf);
        return NULL;
    }
    
    bf->hash_count = hash_count;
    return bf;
}

/* ブルームフィルタに要素を追加 */
void bloom_add(BloomFilter *bf, const void *item, size_t len)
{
    for (size_t i = 0; i < bf->hash_count; i++) {
        uint32_t hash = murmur_hash32(item, len, i);
        size_t bit = hash % bf->bits->size;
        bitvec_set(bf->bits, bit);
    }
}

/* ブルームフィルタで要素の存在確認 */
bool bloom_contains(const BloomFilter *bf, const void *item, size_t len)
{
    for (size_t i = 0; i < bf->hash_count; i++) {
        uint32_t hash = murmur_hash32(item, len, i);
        size_t bit = hash % bf->bits->size;
        if (!bitvec_test(bf->bits, bit)) {
            return false;
        }
    }
    return true;
}

/* ======================= */
/* 4. ビット圧縮整数       */
/* ======================= */

/* 可変長整数エンコード（VarInt） */
size_t encode_varint(uint64_t value, uint8_t *buffer)
{
    size_t i = 0;
    
    while (value >= 0x80) {
        buffer[i++] = (value & 0x7F) | 0x80;
        value >>= 7;
    }
    buffer[i++] = value & 0x7F;
    
    return i;
}

/* 可変長整数デコード */
size_t decode_varint(const uint8_t *buffer, uint64_t *value)
{
    size_t i = 0;
    uint64_t result = 0;
    int shift = 0;
    
    while (buffer[i] & 0x80) {
        result |= ((uint64_t)(buffer[i] & 0x7F)) << shift;
        shift += 7;
        i++;
    }
    result |= ((uint64_t)buffer[i]) << shift;
    i++;
    
    *value = result;
    return i;
}

/* ======================= */
/* 5. SIMD風ビット操作     */
/* ======================= */

/* 8バイトを並列処理する関数 */
typedef struct {
    uint8_t bytes[8];
} Vector8;

/* ベクトル全体にマスクを適用 */
Vector8 vector_and(Vector8 a, Vector8 b)
{
    Vector8 result;
    /* ループを展開して並列性を高める */
    result.bytes[0] = a.bytes[0] & b.bytes[0];
    result.bytes[1] = a.bytes[1] & b.bytes[1];
    result.bytes[2] = a.bytes[2] & b.bytes[2];
    result.bytes[3] = a.bytes[3] & b.bytes[3];
    result.bytes[4] = a.bytes[4] & b.bytes[4];
    result.bytes[5] = a.bytes[5] & b.bytes[5];
    result.bytes[6] = a.bytes[6] & b.bytes[6];
    result.bytes[7] = a.bytes[7] & b.bytes[7];
    return result;
}

/* 各バイトの最上位ビットを集める */
uint8_t vector_movemask(Vector8 v)
{
    uint8_t mask = 0;
    for (int i = 0; i < 8; i++) {
        if (v.bytes[i] & 0x80) {
            mask |= (1 << i);
        }
    }
    return mask;
}

/* ======================= */
/* メイン関数              */
/* ======================= */

int main(void)
{
    printf("=== ビット操作の実践的応用（C99版） ===\n\n");
    
    /* 動的ビットベクタ */
    printf("--- 動的ビットベクタ ---\n");
    DynamicBitVector *prime_bits = bitvec_create(100);
    
    /* エラトステネスの篩 */
    for (size_t i = 2; i < 100; i++) {
        bitvec_set(prime_bits, i);
    }
    
    for (size_t i = 2; i * i < 100; i++) {
        if (bitvec_test(prime_bits, i)) {
            for (size_t j = i * i; j < 100; j += i) {
                prime_bits->bits[j / 64] &= ~(1ULL << (j % 64));
            }
        }
    }
    
    printf("100以下の素数（%zu個）: ", bitvec_popcount(prime_bits) - 2);
    for (size_t i = 2; i < 100; i++) {
        if (bitvec_test(prime_bits, i)) {
            printf("%zu ", i);
        }
    }
    printf("\n\n");
    
    /* ブルームフィルタ */
    printf("--- ブルームフィルタ ---\n");
    BloomFilter *bf = bloom_create(1024, 3);
    
    const char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    
    /* 単語を追加 */
    for (size_t i = 0; i < 5; i++) {
        bloom_add(bf, words[i], strlen(words[i]));
    }
    
    /* 存在確認 */
    const char *test_words[] = {"apple", "orange", "banana", "grape"};
    for (size_t i = 0; i < 4; i++) {
        bool exists = bloom_contains(bf, test_words[i], strlen(test_words[i]));
        printf("\"%s\": %s\n", test_words[i], 
               exists ? "おそらく存在" : "確実に存在しない");
    }
    printf("\n");
    
    /* 可変長整数エンコード */
    printf("--- 可変長整数エンコード ---\n");
    uint64_t test_values[] = {0, 127, 128, 16383, 16384, 1000000};
    uint8_t buffer[10];
    
    for (size_t i = 0; i < sizeof(test_values)/sizeof(test_values[0]); i++) {
        size_t encoded_len = encode_varint(test_values[i], buffer);
        
        printf("%7llu: ", (unsigned long long)test_values[i]);
        for (size_t j = 0; j < encoded_len; j++) {
            printf("%02X ", buffer[j]);
        }
        printf("(%zu バイト)\n", encoded_len);
        
        /* デコードして確認 */
        uint64_t decoded;
        decode_varint(buffer, &decoded);
        assert(decoded == test_values[i]);
    }
    printf("\n");
    
    /* SIMD風ビット操作 */
    printf("--- SIMD風ビット操作 ---\n");
    Vector8 data = {{0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}};
    Vector8 mask = {{0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00}};
    
    Vector8 result = vector_and(data, mask);
    uint8_t msb_mask = vector_movemask(result);
    
    printf("データ: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", data.bytes[i]);
    }
    printf("\nマスク: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", mask.bytes[i]);
    }
    printf("\n結果:   ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", result.bytes[i]);
    }
    printf("\nMSBマスク: %02X\n", msb_mask);
    
    /* ハッシュ値の分布確認 */
    printf("\n--- ハッシュ値分布 ---\n");
    const char *strings[] = {"test1", "test2", "test3", "test4", "test5"};
    
    for (size_t i = 0; i < 5; i++) {
        uint32_t hash = murmur_hash32(strings[i], strlen(strings[i]), 0);
        printf("\"%s\" → 0x%08X\n", strings[i], hash);
    }
    
    /* クリーンアップ */
    bitvec_destroy(prime_bits);
    bloom_destroy(bf);
    
    return 0;
}

/* ブルームフィルタのクリーンアップ */
void bloom_destroy(BloomFilter *bf)
{
    if (bf) {
        bitvec_destroy(bf->bits);
        free(bf);
    }
}