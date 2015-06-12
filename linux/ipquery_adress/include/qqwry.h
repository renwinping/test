#ifndef QQWRY_H
#define QQWRY_H

#define RECORD_LENGTH 0x07  //ip��¼����
#define AREA_FOLLOWED 0X01  //ģʽ1
#define NO_AREA       0x02  //ģʽ2

typedef struct ipInfo
{
    char ipBegin[15];            //ip�ο�ʼ��ַ
    char ipEnd[15];              //ip�ν�����ַ
    char countryAndArea[255];   //ip�ζ�Ӧ�Ĺ��Һ͵���
} ipInfo;

unsigned long stringIpToLong(char *ipString);
unsigned long seekIpBinarySearch(char *ipString);
void readString(char *string, unsigned long offset);
void readStringCur(char *string);
void seekCountryArea(char *string, unsigned long offset);
void readArea(char *string);
void checkCmdLine(int argc, char **argv);
void readIpString(char *string);
void exportData(char *fileName);
void searchIpByName(char *name);

#endif
