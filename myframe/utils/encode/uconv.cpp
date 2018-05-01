#include "uconv.h"
#include <stddef.h>
#include <string.h> 

#define MAX_GBK_LENGTH 24066
#define MAX_UNICODE_LENGTH 65536
#define FIRST_CHAR_OFFSET 0x0081
#define SECOND_CHAR_OFFSET 0x0040
#define MAX_PSEDO_UTF8 1024

uint16_t gGBKToUnicodeTable[MAX_GBK_LENGTH] = {
#include "cp936map.h"
};

uint16_t gUnicodeToGBKTable[MAX_UNICODE_LENGTH] = {
#include "un2gbkmap.h"
};

uint16_t gPsedoUtf8[MAX_PSEDO_UTF8] = {
#include "psedoutf8.h"
};

#define IS_PSEDOUTF8(x)  ( ((x) < MAX_PSEDO_UTF8) && ((x) > 0) && gPsedoUtf8[(x)])

static const char gHexArray[] = "0123456789ABCDEF";

inline uint16_t
unicode_char_to_gbk(uint16_t unicode, char *first_char,
                    char *second_char) {
    *first_char = gUnicodeToGBKTable[unicode] >> 8;
    *second_char = gUnicodeToGBKTable[unicode] & 0xff;
    return gUnicodeToGBKTable[unicode];
}

int
unicode_to_gbk(const uint16_t * src, unsigned int src_len, char *dest,
               unsigned int dst_size, int flags, uint16_t replace_char) {
    unsigned int di = 0, i = 0;
    char *dest_next = dest;
    
    if(!src || !dest || !dst_size)
        return  0;

    for (i = 0; i < src_len && di < dst_size - 1; ++i, ++src) {
        //ASCII��
        if (IS_ASCII(*src)) {
            *dest_next = CAST_UNICHAR_TO_CHAR(*src);
            ++di;
            ++dest_next;
        }
        //ת�������һ���ַ����ռ䲻���ڷ�һ�����֣�������֮
        else if ((di + 2) >= dst_size) {
            break;
        }
        //ת���ɹ�
        else if (unicode_char_to_gbk(*src, dest_next, dest_next + 1)) {
            di += 2;
            dest_next += 2;
        }
        // hack: for euro sign
        else if ((!(flags & UCONV_INVCHAR_GBK_EURO)) && IS_UCS2_EURO(*src)) {
            *dest_next = GBK_EURO;
            ++di;
            ++dest_next;
        }
        //ת��ʧ��
        else {
            switch (flags & ~UCONV_INVCHAR_GBK_EURO) {
                //ʹ��һ���ض��ַ��滻
            case UCONV_INVCHAR_REPLACE:
                if (replace_char < 256) {
                    *dest_next = CAST_UNICHAR_TO_CHAR(replace_char);
                    ++dest_next;
                    ++di;
                } else {
                    *dest_next = replace_char >> 8;
                    *(dest_next + 1) = replace_char & 0xff;
                    di += 2;
                    dest_next += 2;
                }
                break;
                //����ʧ��
            case UCONV_INVCHAR_ERROR:
/*
                ul_writelog(UL_LOG_DEBUG,
                            "[%s]: illegal unicode char %%%2.2X%%%2.2X",
                            __FUNCTION__, (uint8_t) ((*src) >> 8),
                            (uint8_t) ((*src) & 0xff));
*/
                return -1;
                //ʹ��ʵ���ַ�����
            case UCONV_INVCHAR_ENTITES:
                if ((di+8) >= dst_size) { //ʵ���ַ� &#xXXXX; 8���ַ�
                    break;
                }
                *dest_next++ = '&';
                *dest_next++ = '#';
                *dest_next++ = 'x';
                *dest_next++ = gHexArray[0x0f & (((*src)>>8) >> 4)];
                *dest_next++ = gHexArray[0x0f & ((*src)>>8)];
                *dest_next++ = gHexArray[0x0f & (((*src)&0xff) >> 4)];
                *dest_next++ = gHexArray[0x0f & ((*src)&0xff)];
                *dest_next++ = ';';
                di += 8;
                break;
            case UCONV_INVCHAR_DEC_ENTITES:
                {
                    //ת����Ϊʮ����html�ַ�.
                    uint16_t d=*src;
                    //64���ֽ�Ӧ��OK��..
                    char buf[64];
                    int off=0;
                    while(d){
                        buf[off++]=d%10;
                        d/=10;
                    }
                    if((di+off+3)>=dst_size){
                        break;
                    }
                    *dest_next++='&';
                    *dest_next++='#';
                    for(int i=off-1;i>=0;i--){
                        *dest_next++=buf[i]+'0';
                    }
                    *dest_next++=';';
                    di+=off+3;                    
                }
                break;
                //ȱʡ��ʽ�ͺ��Է�ʽ�����κ�����
            case UCONV_INVCHAR_IGNORE:
            default:
/*
                ul_writelog(UL_LOG_DEBUG,
                            "[%s]: illegal unicode char %%%2.2X%%%2.2X",
                            __FUNCTION__, (uint8_t) ((*src) >> 8),
                            (uint8_t) ((*src) & 0xff));
*/
                break;
            }
        }
    }
    //ǿ�Ƽ�\0�ַ�����Ϊǰ�����жϣ����ﲻ����ɰ�����ֵ������
    if (di >= dst_size) {
        di = dst_size - 1;
    }
    dest[di] = 0;
    return di;
}

inline uint16_t
gbk_char_to_unicode(char a, char b) {
    register uint16_t idx =
        ((uint8_t) a - FIRST_CHAR_OFFSET) * 0x00bf + (uint8_t) b -
        SECOND_CHAR_OFFSET;
    if (idx < MAX_GBK_LENGTH) {
        return gGBKToUnicodeTable[idx];
    } else {
        return UCS2_NO_MAPPING;
    }
}

// ��� flags
#define CHK_FLG do { \
	if (flags & UCONV_INVCHAR_ERROR) \
	return -1; \
	else if (flags & UCONV_INVCHAR_REPLACE) \
	*dst = UCS2_NO_MAPPING; \
} while (0)


int
gbk_to_unicode(const char *src, unsigned int src_length, uint16_t * dst,
               unsigned int dst_size, int flags) {
    unsigned int i = 0;
    unsigned int dl = 0;

    if (!src || !dst || !dst_size) {
        return 0;
    }
    for (i = 0; i < src_length && dl < dst_size; ++i) {
        //��һ���ֽ�Ϊ���ָ��ֽ�
        if (LEGAL_GBK_FIRST_BYTE(*src)) {
            // ���İ������
            if (i + 1 >= src_length) {
                break;
            }
            //��Ч��GBK
            if (LEGAL_GBK_SECOND_BYTE(src[1])) {
                *dst = gbk_char_to_unicode(src[0], src[1]);
                // here *dst must be a valid unicode char
                src += 2;
                i++;
            } else {
                // TODO
                // �ж� GB18030 �������
                CHK_FLG;
                src++;
            }
        } else {
            if (IS_ASCII(*src)) {
                *dst = CAST_CHAR_TO_UNICHAR(*src);
            } else if ((!(flags & UCONV_INVCHAR_GBK_EURO)) && IS_GBK_EURO(*src)) {
                *dst = UCS2_EURO;
            } else {
                CHK_FLG;
            }
            src++;
        }
        dst++;
        dl++;
    }
    return dl;
}

/**
 * ��һ��unicode�ַ�ת��Ϊutf8�ַ�
 *
 * @param dst Ŀ���ַ�����������Ҫ������5�ֽڳ�
 * @param src ԭ�ַ�
 *
 * @return ����utf8�ַ�������
 */
static inline unsigned int
unicode_char_to_utf8(char *dst, uint16_t src) {
    char utf8_word[5];
    int len = 0, j;
    uint16_t val = 0;

    utf8_word[4] = 0;

    if (dst == NULL || src == 0)
        return 0;

    dst[0] = 0;
    // deal with one byte ascii
    if (src < 128) {
        dst[0] = src;
        dst[1] = 0;
        return 1;
    }
    // deal with multi byte word
    else {
        for (j = 3;; j--) {
            val = src & 0x3f;
            if (src == 0)
                break;
            utf8_word[j] = val | 0x80;
            src = src >> 6;
        }

        // add utf-8 header
        len = 3 - j;
        switch (len) {
        case 2:
            utf8_word[j + 1] |= 0xc0;
            break;
        case 3:
            utf8_word[j + 1] |= 0xe0;
            break;
        default:
/*
            ul_writelog(UL_LOG_DEBUG,
                        "[%s] illegal unicode char: %%%2.2X%%%2.2X",
                        __FUNCTION__, (uint8_t) (src >> 8),
                        (uint8_t) (src & 0xff));
*/
            return 0;
        }
        strcpy(dst, &utf8_word[j + 1]);
        return len;
    }
}

int
gbk_to_utf8(const char *src, unsigned int src_len, char *dst, unsigned int dst_size,
            int flags) {
    char utf8_word[6];
    unsigned int i = 0, dl = 0, len;
    uint16_t tmp = 0;

    if (!src || !dst || !dst_size)
        return 0;

    if (dst_size < src_len / 2 * 3 + 1) {
/*
        ul_writelog(UL_LOG_WARNING,
                    "[%s] dst_size[%u] must be larger than (src_len[%u]/2*3+1)",
                    __FUNCTION__, dst_size, src_len);
*/
        return -1;
    }

    for (i = 0; i < src_len && dl < dst_size; ++i) {
        //��һ���ֽ�Ϊ���ָ��ֽ�
        if (LEGAL_GBK_FIRST_BYTE(*src)) {
            // ���İ������
            if (i + 1 >= src_len) {
                break;
            }
            //��Ч��GBK
            if (LEGAL_GBK_SECOND_BYTE(src[1])) {
                tmp = gbk_char_to_unicode(src[0], src[1]);
                src += 2;
                i++;
            } else {
                // TODO
                // �ж� GB18030 �������
                if (flags & UCONV_INVCHAR_ERROR) {
/*
                    ul_writelog(UL_LOG_DEBUG,
                                "[%s]: illegal unicode char %%%2.2X%%%2.2X",
                                __FUNCTION__, (uint8_t) ((*src) >> 8),
                                (uint8_t) ((*src) & 0xff));
*/
                    return -1;
                }
                if (flags == UCONV_INVCHAR_IGNORE) {
                    src++;
                    continue;
                }
            }
        } else {
            if (IS_ASCII(*src)) {
                tmp = CAST_CHAR_TO_UNICHAR(*src);
                src++;
            } else if ((!(flags & UCONV_INVCHAR_GBK_EURO)) && IS_GBK_EURO(*src)) {
                tmp = UCS2_EURO;
                src++;
            } else {
                if (flags & UCONV_INVCHAR_ERROR) {
/*
                    ul_writelog(UL_LOG_DEBUG,
                                "[%s]: illegal gbk char %%%2.2X",
                                __FUNCTION__, (uint8_t) ((*src)));
*/
                    return -1;
                }
                if ((flags & ~UCONV_INVCHAR_GBK_EURO) == UCONV_INVCHAR_IGNORE) { /* ע��INGORE������&�ķ�ʽ�жϣ���Ϊ����ֵ0 */
                    src++;
                    continue;
                }
            }
        }

        len = unicode_char_to_utf8(utf8_word, tmp);
        if (dl + len >= dst_size)
            break;

        strncpy(dst, utf8_word, len);
        dst += len;
        dl += len;
    }
    return dl;
}



int
utf8_to_gbk(const char *src, unsigned int src_len, char *dst, unsigned int dst_size,
            int flags) {
    static const uint8_t BytesFromHeader[256] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x00
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x10
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x20
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x30
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x40
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x50
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x60
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x70
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x80
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x90
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xA0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xB0
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	//0xC0
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	//0xD0
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,	//0xE0
        4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0	//0xF0
    };

    static const uint8_t UTF8_HEADER[] = {
        0x00,			/* unused */
        0x00,			/* 1 byte */
        0xC0,			/* 2 bytes */
        0xE0,			/* 3 bytes */
        0xF0,			/* 4 bytes */
        0xF8,			/* 5 bytes */
        0xFC,			/* 6 bytes */
    };

    unsigned int i = 0, dl = 0, len;
    uint8_t cur = 0;
    uint16_t tmp;
    char *dst_orig = dst;

    if (!src || !dst || !dst_size)
        return 0;

    if (dst_size < src_len) {
/*
        ul_writelog(UL_LOG_WARNING,
                    "[%s] dst_size[%u] should not less than src_len[%u]",
                    __FUNCTION__, dst_size, src_len);
*/
        return -1;
    }

    for (i = 0; i < src_len && dl < dst_size - 1;) {
        cur = src[i++];
        len = BytesFromHeader[cur];

        //skip illegal byte
        //bear in mind that UTF-8 never uses 0xFE or 0xFF
        if (len == 0)
            continue;

        // ignore the last uncomplete utf-8 word
        if (i + len - 1 > src_len)
            break;

        // translate the next word to unicode
        tmp = cur & ~UTF8_HEADER[len];
        for (; len > 1; len--) {
            cur = src[i++];
            tmp = (tmp << 6) | (cur & 0x3F);
        }

        if (IS_ASCII(tmp)) {
            *dst++ = CAST_UNICHAR_TO_CHAR(tmp);
            dl++;
        } else if (dl + 2 >= dst_size) {
            break;
        } else if (unicode_char_to_gbk(tmp, dst, dst + 1)) {
            dl += 2;
            dst += 2;
        } else if ((!(flags & UCONV_INVCHAR_GBK_EURO)) && IS_UCS2_EURO(tmp)) {
            *dst++ = GBK_EURO;
            dl++;
        } else {
            if (flags & UCONV_INVCHAR_ENTITES) {
                if ((dl + 8) >= dst_size) {	//ʵ���ַ� &#xXXXX; 8���ַ�
                    break;
                }
                *dst++ = '&';
                *dst++ = '#';
                *dst++ = 'x';
                *dst++ = gHexArray[0x0f & ((tmp >> 8) >> 4)];
                *dst++ = gHexArray[0x0f & (tmp >> 8)];
                *dst++ = gHexArray[0x0f & ((tmp & 0xff) >> 4)];
                *dst++ = gHexArray[0x0f & (tmp & 0xff)];
                *dst++ = ';';
                dl += 8;
            } else if( flags & UCONV_INVCHAR_DEC_ENTITES){
                //ת����Ϊʮ����html�ַ�.
                uint16_t d=tmp;
                //64���ֽ�Ӧ��OK��..
                char buf[64];
                int off=0;
                while(d){
                    buf[off++]=d%10;
                    d/=10;
                }
                if((dl+off+3)>=dst_size){
                    break;
                }
                *dst++='&';
                *dst++='#';
                for(int i=off-1;i>=0;i--){
                    *dst++=buf[i]+'0';
                }
                *dst++=';';
                dl+=off+3;                
            }else {
/*
				ul_writelog(UL_LOG_DEBUG,
                            "[%s]: illegal unicode char %%%2.2X%%%2.2X",
                            __FUNCTION__, (uint8_t) (tmp >> 8),
                            (uint8_t) (tmp & 0xff));
*/
                if (flags & UCONV_INVCHAR_ERROR)
                    return -1;
            }
        }
    }
    if (dl >= dst_size) {
        dl = dst_size - 1;
    }
    dst_orig[dl] = 0;
    return dl;

}

int
is_utf8(const char *src, unsigned int len, int check_last_char) {
    int flag = 0;
    uint16_t gbk_or_utf8 = 0, idx = 0;
    const uint8_t *str = (const uint8_t *) src;
    unsigned int ascii_len = 0;

    if (src == NULL || *src == '\0')
        return 0;

    // XXX: ����ȫ��Ӣ���ַ����ַ�������Ϊ����UTF-8

    if ( check_last_char ) {
        while (*str) {
            if (IS_UTF8_1ST_OF_1(*str)) {
                str++;
                ascii_len++;
            } else if (IS_UTF8_1ST_OF_2(*str)) {
                str++;
                if (!IS_UTF8_2ND_THRU_6TH(*str)) {
                    if (!(*str)) flag = 2;
                    break;
                }
                flag = 1;
                str++;
                /* �ж��Ƿ���ò��utf8��gbk
                 * �ᱻ�ж�Ϊutf8��gbk���ַ�����������:
                 * first byte [C2, D1] ; second byte [80,bf]
                 * */
                if ( ( *(str -2 ) > 0xC1) && (*(str -2 ) < 0xD2)
                        && ( *(str - 1 ) > 0x7F) && (*(str - 1 ) < 0xC0)) {
                    /* 0xC0 - 0x80 = 64 */
                    idx =( *(str - 2) - 0xC2 ) * 64 + (*(str - 1) - 0x80);
                    if (IS_PSEDOUTF8(idx)) {
                        gbk_or_utf8++;
                    }
                }
            } else if (IS_UTF8_1ST_OF_3(*str)) {
                str++;
                if (!IS_UTF8_2ND_THRU_6TH(*str)) {
                    if (!(*str)) flag = 2;
                    break;
                }
                if( !IS_UTF8_2ND_THRU_6TH(*(str + 1))) {
                    if (!(*(str + 1))) flag = 2;
                    else flag = 3;
                    break; //return 0;
                }
                flag = 1;
                str += 2;
            } else if (IS_UTF8_1ST_OF_4(*str)) {
                str++;
                if (!IS_UTF8_2ND_THRU_6TH(*str)) {
                    if (!(*str)) flag = 2;
                    break; //return 0;
                }
                if( !IS_UTF8_2ND_THRU_6TH(*(str + 1))) {
                    if (!(*(str + 1))) flag = 2;
                    break; //return 0;
                }
                if( !IS_UTF8_2ND_THRU_6TH(*(str + 2))) {
                    if (!(*(str + 2))) flag = 2;
                    break; //return 0;
                }
                flag = 1;
                str += 3;
            } else {
                flag = 0;
                break; //return 0;
            }
        }
    } else {
        while (*str) {
            if (IS_UTF8_1ST_OF_1(*str)) {
                str++;
                ascii_len++;
            } else if (IS_UTF8_1ST_OF_2(*str)) {
                str++;
                if (!IS_UTF8_2ND_THRU_6TH(*str))
                    return 0;
                str++;
                flag = 1;
                /* �ж��Ƿ���ò��utf8��gbk
                 * �ᱻ�ж�Ϊutf8��gbk���ַ�����������:
                 * first byte [C2, D1] ; second byte [80,bf]
                 * */
                if ( ( *(str -2 ) > 0xC1) && (*(str -2 ) < 0xD2)
                        && ( *(str - 1 ) > 0x7F) && (*(str - 1 ) < 0xC0)) {
                    /* 0xC0 - 0x80 = 64 */
                    idx =( *(str - 2) - 0xC2 ) * 64 + (*(str - 1) - 0x80);
                    if (IS_PSEDOUTF8(idx)) {
                        gbk_or_utf8++;
                    }
                }
            } else if (IS_UTF8_1ST_OF_3(*str)) {
                str++;
                if (!IS_UTF8_2ND_THRU_6TH(*str) || !IS_UTF8_2ND_THRU_6TH(*(str + 1)))
                    return 0;
                str += 2;
                flag = 1;
            } else if (IS_UTF8_1ST_OF_4(*str)) {
                str++;
                if (!IS_UTF8_2ND_THRU_6TH(*str) ||  !IS_UTF8_2ND_THRU_6TH(*(str + 1))
                        || !IS_UTF8_2ND_THRU_6TH(*(str + 2)))
                    return 0;
                str += 3;
                flag = 1;
            } else return 0;
        }

    }

    if ( gbk_or_utf8 && ((unsigned int)gbk_or_utf8 << 1) == (len - ascii_len) ) {
/*
        ul_writelog(UL_LOG_WARNING,
                    "[%s]: string [%s] be considered as gbk ",__FUNCTION__, src);
*/
        return 0;
    }

    if ( (flag == 2) && ((len - ascii_len) > 4) && check_last_char) {
        if (str > (const uint8_t *)src)
            str--;
        if ( (unsigned int)((str-(const uint8_t *) src) + 4) >= len) {
/*
            ul_writelog(UL_LOG_NOTICE,
                        "[%s]: total_len[%d] cur_len[%ld]",
                        __FUNCTION__, len, (long)(str-(const uint8_t *) src));
*/
            flag = 1; /* �ж���utf8 */
        }
    }

    if (flag == 1)
        return str - (const uint8_t *) src; /* �����жϵ����ֽ������������ض� */
    else
        return 0;
}


//�ж��Ƿ�Ϊ�ϸ��utf8�ַ���..
//����is_ascii_utf8��ʾ�����ȫΪascii�ַ��Ļ�����ô�Ƿ�Ϊutf8.
//�������Ϊ0�Ļ�����ô����0.
int is_utf8_strict(const char *src, unsigned int len, bool is_ascii_utf8) {
    //�ַ�����.
    static const uint8_t BytesFromHeader[256] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x00
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x10
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x20
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x30
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x40
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x50
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x60
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//0x70
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x80
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x90
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xA0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xB0
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	//0xC0
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	//0xD0
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,	//0xE0
        4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0	//0xF0
    };

    //��һ���ֽڵ�mask.
    static const uint8_t UTF8_HEADER[] = {
        0x00,			/* unused */
        0x00,			/* 1 byte */
        0xC0,			/* 2 bytes */
        0xE0,			/* 3 bytes */
        0xF0,			/* 4 bytes */
        0xF8,			/* 5 bytes */
        0xFC,			/* 6 bytes */
    };
    static const uint32_t MAX_LEGAL_UNICODE = 0x0010FFFF;
    const uint8_t *str = (const uint8_t *) src;
    const uint8_t *end = str + len;
    unsigned int ascii_len = 0;
    if(src==NULL || len<=0) {
        return 0;
    }
    //check BOM
    if(str[0]==0xEF && str[1]==0xBB && str[2]==0xBF) {
        str+=3;
    }
    while(str!=end) {
        uint8_t cur=*(str++);
        unsigned int curlen=BytesFromHeader[cur];
        //û��ӳ��������ַ�������...
        if(curlen==0 || (str+curlen-1)>end) {
            return 0;
        }
        //���Ϊascii�ַ�����ô+1.
        if(curlen==1) {
            ascii_len++;
        }
        uint32_t tmp=cur & ~UTF8_HEADER[curlen];
        for(; curlen>1; curlen--) {
            cur=*(str++);
            //�ж��Ƿ�10xxxxxģʽ
            if((cur & 0xC0) !=0x80) {
                return 0;
            }
            tmp=(tmp<<6)+(cur & 0x3F);
        }
        if(tmp>MAX_LEGAL_UNICODE) {
            return 0;
        }
    }
    //���ȫ��Ϊascii�ַ���������Ϊascii��utf8�Ļ�.
    if(ascii_len==len && !is_ascii_utf8) {
        return 0;
    }
    return 1;
}

int
is_gbk(const char *src) {
    if (src == NULL || *src == '\0')
        return 0;

    while (*src) {
        if (LEGAL_GBK_FIRST_BYTE(*src)) {
            /* ���İ������ */
            if (*(src + 1) == '\0')
                return 1;

            if (LEGAL_GBK_SECOND_BYTE(*(src + 1))) {
                src += 2;
            } else {
                return 0;
            }
        } else if (IS_ASCII(*src) || IS_GBK_EURO(*src))
            src++;
        else
            return 0;
    }
    return 1;

}

int uconv_is_gbk(const char *src) {
    return is_gbk(src);
}

int uconv_is_gbk_n(const char *src, int length) {
    if (src == NULL || *src == '\0')
        return 0;

    while (*src && length > 0) {
        if (LEGAL_GBK_FIRST_BYTE(*src)) {
            /* ���İ������ */
            if (*(src + 1) == '\0') {
                return 1;
            }
            if (LEGAL_GBK_SECOND_BYTE(*(src + 1))) {
                src += 2;
                length -= 2;
            } else {
                return 0;
            }
        } else if (IS_ASCII(*src) || IS_GBK_EURO(*src)) {
            src++;
            length--;
        } else {
            return 0;
        }
    }
    return 1;
}












