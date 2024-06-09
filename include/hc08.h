typedef unsigned char   byte_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

#if _MSC_VER >= 1933
    #define BSWAP_16(x) _byteswap_ushort(*(uint32_t*)(x))
    #define BSWAP_32(x) _byteswap_ulong(*(uint32_t*)(x))
#else 
    #define BSWAP_16(x) __builtin_bswap16(*(uint16_t*)(x))
    #define BSWAP_32(x) __builtin_bswap32(*(uint32_t*)(x))
#endif
