#ifndef __UCONV_H__
#define __UCONV_H__

#ifndef uint16_t
#define uint16_t unsigned short
#endif //uint16_t             
#ifndef uint8_t
#define uint8_t unsigned char
#endif //uint8_t   

#ifdef __cplusplus
extern "C" {
#endif

#define UCS2_NO_MAPPING (( unsigned short ) 0xfffd)
#define IS_ASCII(a) (0 == (0xff80 & (a)))
    /*XXX: 0xa2e3 is euro sign in gbk standard but 0x80 in microsoft's cp936map*/
#define GBK_EURO  ((char)0x80)
#define IS_GBK_EURO(c) ((char)0x80 == (c)) //EURO SIGN
#define UCS2_EURO  (( unsigned short ) 0x20ac)
#define IS_UCS2_EURO(c) ((uint16_t)0x20ac == (c))

#define CAST_CHAR_TO_UNICHAR(a) (( unsigned short )((unsigned char)(a)))
#define CAST_UNICHAR_TO_CHAR(a) ((char)a)

#define UINT8_IN_RANGE(min, ch, max) \
    (((uint8_t)(ch) >= (uint8_t)(min)) && ((uint8_t)(ch) <= (uint8_t)(max)))


#define LEGAL_GBK_MULTIBYTE_FIRST_BYTE(c)  \
          (UINT8_IN_RANGE(0x81, (c), 0xFE))
#define FIRST_BYTE_IS_SURROGATE(c)  \
          (UINT8_IN_RANGE(0x90, (c), 0xFE))
#define LEGAL_GBK_2BYTE_SECOND_BYTE(c) \
          (UINT8_IN_RANGE(0x40, (c), 0x7E)|| UINT8_IN_RANGE(0x80, (c), 0xFE))
#define LEGAL_GBK_4BYTE_SECOND_BYTE(c) \
          (UINT8_IN_RANGE(0x30, (c), 0x39))
#define LEGAL_GBK_4BYTE_THIRD_BYTE(c)  \
          (UINT8_IN_RANGE(0x81, (c), 0xFE))
#define LEGAL_GBK_4BYTE_FORTH_BYTE(c) \
          (UINT8_IN_RANGE(0x30, (c), 0x39))

#define LEGAL_GBK_FIRST_BYTE(c)  \
          (UINT8_IN_RANGE(0x81, (c), 0xFE))
#define LEGAL_GBK_SECOND_BYTE(c) \
          (UINT8_IN_RANGE(0x40, (c), 0x7E)|| UINT8_IN_RANGE(0x80, (c), 0xFE))

    enum uconv_flags_t {
        UCONV_INVCHAR_IGNORE = 0x0,  ///< ������Ч���ַ�
        UCONV_INVCHAR_REPLACE = 0x1, ///< ʹ�������ַ�������Ч���ַ�
        UCONV_INVCHAR_ERROR = 0x2,    ///< ������Ч�ַ�ʱ����ʧ��
        UCONV_INVCHAR_ENTITES = 0x4, ///< ����Ч��unicode�ַ�ת��Ϊhtmlʵ���ַ�
        UCONV_INVCHAR_GBK_EURO = 0x8, ///< ��ŷԪ0x80����Ϊ��ЧGBK.[��֮ǰ�汾���ݵĻ�,ԭʼEUROΪ�Ϸ�GBK]
        UCONV_INVCHAR_DEC_ENTITES = 0x10, ///< ת����Ϊhtmlʵ���ַ���ʱ��,ʹ��ʮ����..
    };

    /*
     *  * UTF8 defines and macros
     *   */
#define ONE_OCTET_BASE          0x00    /* 0xxxxxxx */
#define ONE_OCTET_MASK          0x7F    /* x1111111 */
#define CONTINUING_OCTET_BASE   0x80    /* 10xxxxxx */
#define CONTINUING_OCTET_MASK   0x3F    /* 00111111 */
#define TWO_OCTET_BASE          0xC0    /* 110xxxxx */
#define TWO_OCTET_MASK          0x1F    /* 00011111 */
#define THREE_OCTET_BASE        0xE0    /* 1110xxxx */
#define THREE_OCTET_MASK        0x0F    /* 00001111 */
#define FOUR_OCTET_BASE         0xF0    /* 11110xxx */
#define FOUR_OCTET_MASK         0x07    /* 00000111 */
#define FIVE_OCTET_BASE         0xF8    /* 111110xx */
#define FIVE_OCTET_MASK         0x03    /* 00000011 */
#define SIX_OCTET_BASE          0xFC    /* 1111110x */
#define SIX_OCTET_MASK          0x01    /* 00000001 */

#define IS_UTF8_1ST_OF_1(x) (( (x)&~ONE_OCTET_MASK  ) == ONE_OCTET_BASE)
#define IS_UTF8_1ST_OF_2(x) \
((( (x)&~TWO_OCTET_MASK  ) == TWO_OCTET_BASE) && ( (x) != 0xC0 ) && ( (x) != 0xC1))
#define IS_UTF8_1ST_OF_3(x) (( (x)&~THREE_OCTET_MASK) == THREE_OCTET_BASE)
#define IS_UTF8_1ST_OF_4(x) (( (x)&~FOUR_OCTET_MASK ) == FOUR_OCTET_BASE)
#define IS_UTF8_1ST_OF_5(x) (( (x)&~FIVE_OCTET_MASK ) == FIVE_OCTET_BASE)
#define IS_UTF8_1ST_OF_6(x) (( (x)&~SIX_OCTET_MASK  ) == SIX_OCTET_BASE)
#define IS_UTF8_2ND_THRU_6TH(x) \
        (( (x)&~CONTINUING_OCTET_MASK  ) == CONTINUING_OCTET_BASE)
#define IS_UTF8_1ST_OF_UCS2(x) \
        IS_UTF8_1ST_OF_1(x) \
|| IS_UTF8_1ST_OF_2(x) \
|| IS_UTF8_1ST_OF_3(x)

    /**
     * @brief ��GBK�ַ�ת��ΪUnicode�ַ�
     *
     * @param a GBK�ַ��ĵ�һ���ֽ�
     * @param b GBK�ַ��ĵڶ����ֽ�
     * @return ����ת�����Unicode�ַ���ֵ����һ��16λ���޷���������
     * ���ת��ʧ�ܣ�������Ч��Unicodeֵ��0xfffd
     */
// unsigned short  gbk_char_to_unicode(char a, char b);

    /**
     * �� GBK ������ַ���ת��Ϊ Unicode ���룬��16λ��������ʽ��š�
     *
     * @param src   Դ�ַ���������ΪGBK
     * @param src_len    Դ�ַ�������
     * @param dst   Ŀ�����飬ת����� Unicode ��
     * @param dst_size    Ŀ���������󳤶ȡ�
     * @param flags �ο� uconv_flags_t
     * ֧��UCONV_INVCHAR_ERROR : ����ʱ����-1
     * ֧�� UCONV_INVCHAR_REPLACE: ��Ч�ַ��滻Ϊ UCS2_NO_MAPPING
     * ֧��UCONV_INVCHAR_GBK_EURO: GBK_EURO��Ϊ��Ч��GBK�ַ�.Ĭ�������������Ч��
     * @return �ɹ�����ת����Unicode�ַ�����ʧ�ܷ���-1
     * @see uconv_flags_t
     */
    int gbk_to_unicode(const char *src, unsigned int src_len,  unsigned short  *dst, unsigned int dst_size,
                       int flags);

    /**
      * @brief ����һ��Unicode������������Ӧ��GBK�ַ�������8λ�ַ���
      *
      * @param unicode Ҫת����Unicode�ַ���
      * @param first_char ָ��GBK�ַ���һ���ֽڵĴ洢λ��
      * @param second_char ָ��GBK�ַ��ڶ����ֽڵĴ洢λ��
      *
      * @return ��0��ʾת���ɹ���0��ʾת��ʧ�ܣ���û����ӦGBK�ַ�
      */
// unsigned short  unicode_char_to_gbk( unsigned short  unicode, char * first_char, char * second_char);

    /**
      * @brief ��Unicode�ַ�ת��ΪGBK�ַ������ǿ�Ƽ�\0�ַ�������˳��ְ�����֣����������ȫ��ɾ��
      *
      * @param src Ҫת����unicode�ַ���
      * @param src_len Ҫת����Ŀ�괮����
      * @param dest ת�����GBK�ַ����Ĵ洢λ��
      * @param size Ŀ�괮����󳤶�
      * @param flags ����ģʽ��ָʾ��������ЧUnicode�ַ�ʱ�Ķ�����IGNORE��ʾ���ԣ�REPLACE��ʾʹ��replace_char�滻֮��E
      *   NTITIES��ʾʹ��htmlʵ���ַ�����
      * ֧��UCONV_INVCHAR_GBK_EURO: GBK_EURO��Ϊ��Ч��GBK�ַ�.Ĭ�������������Ч��
      * @param replace_char ��PEPLACE����ģʽ�£������滻��Ч�ַ����ַ�, 0: ��ʾ���滻,1:��ʾ�滻.�Ƽ�0
      * @return �ɹ�ʱת����GBK�ַ��ĸ�����ʧ���򷵻�-1
     */
    int unicode_to_gbk(const  unsigned short  * src, unsigned int src_len, char * dest, unsigned int size,
                       int flags,  unsigned short  replace_char);

    /**
     * ��GBK�ַ���ת��Ϊutf8�ַ���
     *
     * @param src  gbk�ַ���
     * @param src_len ԭ�ַ�������
     * @param dst Ŀ�껺����
     * @param dst_size Ŀ�껺������󳤶�
     * @param flags ����ģʽ
     * ֧��UCONV_INVCHAR_ERROR : ����ʱ����-1
     * ֧��UCONV_INVCHAR_IGNORE : ���Գ�����ַ�,��ĳЩ����£�����gbk�ļ��а���������֣������ת��ʧ�ܵ������������ĩβ������ֵ������ĩβ�İ�����ֻ��Զ�����
     * ֧��UCONV_INVCHAR_GBK_EURO: GBK_EURO��Ϊ��Ч��GBK�ַ�.Ĭ�������������Ч��
     * @return �ɹ�����Ŀ�껺�������ȡ�ʧ�ܷ���-1
     */

    int gbk_to_utf8(const char *src, unsigned int src_len, char *dst, unsigned int dst_size,
                    int flags);


    /**
     * ��UTF8�ַ���ת��Ϊgbk�ַ���
     *
     * @param src ԭutf8�ַ���
     * @param src_len ԭ�ַ�������
     * @param dst Ŀ�껺����
     * @param dst_size Ŀ�껺������С
     * @param flags ����ģʽ,֧��4��ģʽ
     * ֧��UCONV_INVCHAR_GBK_EURO: GBK_EURO��Ϊ��Ч��GBK�ַ�.Ĭ�������������Ч��
     * @return �ɹ�����Ŀ�껺�������ȣ�ʧ�ܷ���-1
     */
    int utf8_to_gbk(const char *src, unsigned int src_len, char *dst, unsigned int dst_size,
                    int flags);


    /**
     * �ж��ַ����Ƿ���UTF-8����
     * ע�⣬����������Ϊȫ����Ӣ���ַ����ַ�����UTF-8����
     * @param str ԭ�ַ��� len ԭ�ַ����ĳ���
     *        check_last_char =1��������������һ���ַ�������utf8�Ĺ���,����ַ������ضϵ�����.
     *        �ò�����Ϊ�˽���Ѳ���url������������ضϵ����⣬������Ŀʹ��ʱ���Ƽ���Ϊ0.
     * @return �����UTF-8�����жϳɹ���utf8�ĸ�������������С���ַ����ĳ���, �������ַ������ضϵ������,
     * ������İ��utf8ȥ��.
     * ���򷵻�0
     */
    int is_utf8(const char *str, unsigned int len, int check_last_char);

    /**
     * @brief �ж��ַ��Ƿ�Ϊutf8���롣�����������ǣ�����������ж����utf8û�ж�Ӧ��unicodeӳ��Ļ�����ô��ʧ�ܡ�
     *
     * @param src Դ�ַ���
     * @param len Դ�ַ�������
     * @param is_ascii_utf8 ���ȫ��Ϊascii�ַ��Ļ�����ô�Ƿ�Ϊutf8����
     *
     * @return �����utf8�Ļ�����ô����1�����򷵻�0.
     */
    int is_utf8_strict(const char *src, unsigned int len, bool is_ascii_utf8);

    /**
     * �ж��ַ����Ƿ���gbk����, ���򷵻�1
     */
    int uconv_is_gbk(const char * src);

    /**
     * �ж��ַ����Ƿ���gbk����, ������length����
     * ���򷵻�1
     */
    int uconv_is_gbk_n(const char * src,
                       int length);


#ifndef uint32_t
#define uint32_t unsigned int
#endif
#define UCS4_NO_MAPPING ((uint32_t) 0xfffdffff)
#define CAST_UCS4_TO_UCHAR(a) ((unsigned char)a)

    /**
     * �� GB18030 ������ַ���ת��Ϊ UCS4 ���룬��32λ��������ʽ��š�
     *
     * @param src   Դ�ַ���������ΪGB18030
     * @param src_len    Դ�ַ�������
     * @param dst   Ŀ�����飬ת����� Ucs4 ��
     * @param dst_size    Ŀ���������󳤶ȡ�
     * @param flags �ο� uconv_flags_t
     * ֧��UCONV_INVCHAR_ERROR : ����ʱ����-1
     * ֧�� UCONV_INVCHAR_REPLACE: ��Ч�ַ��滻Ϊ UCS4_NO_MAPPING
     * ֧��UCONV_INVCHAR_IGNORE: ����ת�����ɹ����ַ�.
     * ֧��UCONV_GBK_EURO: GBK_EURO����Ч��GB18030�ַ�.Ĭ�������������Ч��
     * @return �ɹ�����ת����Ucs4�ַ�����ʧ�ܷ���-1
     * @see uconv_flags_t
     */
    int gb18030_to_ucs4(const unsigned char *src,
                        unsigned int src_len,
                        uint32_t *dst,
                        unsigned int dst_size,
                        int flags);

    /**
      * @brief ��Ucs4�ַ�ת��ΪGB18030�ַ������ǿ�Ƽ�\0�ַ�������˳��ְ�����֣����������ȫ��ɾ��
      *
      * @param src Ҫת����ucs4�ַ���
      * @param src_len Ҫת����Ŀ�괮����
      * @param dest ת�����GB18030�ַ����Ĵ洢λ��
      * @param size Ŀ�괮����󳤶�
      * @param flags ����ģʽ��ָʾ��������ЧUcs4�ַ�ʱ�Ķ�����
      * IGNORE��ʾ����
      * REPLACE��ʾʹ��replace_char�滻֮��
      * ENTITIES��ʾʹ��htmlʵ���ַ�����
      * @param replace_char ��PEPLACE����ģʽ�£������滻��Ч�ַ����ַ�.
      *
      * @return �ɹ�ʱת����GB18030�ַ��ĸ�����ʧ���򷵻�-1
      */
    int ucs4_to_gb18030(const uint32_t * src,
                        unsigned int src_len,
                        unsigned char * dst,
                        unsigned int dst_size,
                        int flags,
                        uint32_t replace_char);

    /**
     * ��GB18030�ַ���ת��Ϊutf8�ַ���
     *
     * @param src  gb18030�ַ���
     * @param src_len ԭ�ַ�������
     * @param dst Ŀ�껺����
     * @param dst_size Ŀ�껺������󳤶�
     * @param flags ����ģʽ
     * ֧��UCONV_INVCHAR_ERROR : ����ʱ����-1
     * ֧��UCONV_INVCHAR_IGNORE : ���Գ�����ַ�,��ĳЩ����£�����gb18030�ļ��а���������֣������ת��ʧ�ܵ����
     * ֧��UCONV_GBK_EURO: GBK_EURO����Ч��GB18030�ַ�.Ĭ�������������Ч��
     * ������ĩβ������ֵ������ĩβ�İ�����ֻ��Զ�����
     *
     * @return �ɹ�����Ŀ�껺�������ȡ�ʧ�ܷ���-1
     */

    int gb18030_to_utf8(const unsigned char *src,
                        unsigned int src_len,
                        unsigned char *dst,
                        unsigned int dst_size,
                        int flags);


    /**
     * ��UTF8�ַ���ת��Ϊgb18030�ַ���
     *
     * @param src ԭutf8�ַ���
     * @param src_len ԭ�ַ�������
     * @param dst Ŀ�껺����
     * @param dst_size Ŀ�껺������С
     * @param flags ����ģʽ,֧��4��ģʽ
     *
     * @return �ɹ�����Ŀ�껺�������ȣ�ʧ�ܷ���-1
     */
    int utf8_to_gb18030(const unsigned char *src,
                        unsigned int src_len,
                        unsigned char *dst,
                        unsigned int dst_size,
                        int flags);

#ifdef __cplusplus
}
#endif

#endif // __UCONV_H__
