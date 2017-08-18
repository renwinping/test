#ifndef __MYBASE64_H
#define __MYBASE64_H

#include "base_def.h"

/**
* �����ṩ��׼��Base64�ı������
*/
class CBase64
{
public:
    /**
    * ���ַ�������base64����
    * @param data :       ��Ҫ���������
    * @param bChangeLine: �Ƿ���Ҫ�����ձ������ݼ��뻻�з�(RFC�н���ÿ76���ַ������س�����)��Ĭ��Ϊ����ӻ���
    * @return string :    ����������
    */
    static string encode(const string &data, bool bChangeLine = false);
    
    /**
    * ���ַ�������base64����
    * @param data :    ��Ҫ���������
    * @return string : ����������
    */    
    static string decode(const string &data);

    /**
    * ���ַ�������base64���� 
    * @param pSrc :        ��Ҫ���������
    * @param nSrcLen :     ��Ҫ��������ݳ���
    * @param pDst :        ����������      
    * @param bChangeLine:  �Ƿ���Ҫ�����ձ������ݼ��뻻�з�(RFC�н���ÿ76���ַ������س�����)��Ĭ��Ϊ����ӻ���
    * @return �������ַ����ĳ���
    */
    static int encode(const unsigned char* pSrc, int nSrcLen, char* pDst, bool bChangeLine = false);
    
    /**
    * ���ַ�������base64����
    * @param pSrc :        ��Ҫ���������    
    * @param nSrcLen :     ��Ҫ��������ݳ���
    * @param pDst :        ����������
    * @return �������ַ����ĳ���
    */    
    static int decode(const char* pSrc, int nSrcLen, unsigned char* pDst);
    
protected:

    /**
    * base64�����
    */
    static const char EnBase64Tab[];
    /**
    * base64�����
    */
    static const char DeBase64Tab[];
};

#endif
