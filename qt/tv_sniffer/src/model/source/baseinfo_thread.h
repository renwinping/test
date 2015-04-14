#ifndef __BASETHREAD_H_
#define __BASETHREAD_H_
#include "data_struct.h"
#include <pthread.h>

class BaseThread
{
public:
		/**
		 * @brief �����ṩ��ȡ������Ϣ�ӿ�
		 *
		 * @param info ����ȡ�Ļ�����Ϣ�洢���ָ��ָ���ַ��
		 */
    void getBasic(BasicInfo * info);
    void start();
    BaseThread();
    ~BaseThread();
private:
	/**
	 * @brief �������������Ϣ��
	 *
	 * @param buf ���û������������Ϣbuf
	 */
    void getNetworkName();
    void getLocalIp();
	/**
	 * @brief ��ȡ���������Ϣ�� ������buf
	 *
	 * @param buf �洢��ȡ��������Ϣ
	 * @param size buf�Ĵ�С
	 */
    static void * getNetworkInfo(void * arg);
    /**
	 * @brief ����buf��haier���ӻ������Ϣ
	 *
	 * @param buf ���û�������û���Ϣ
	 */
    void prase_haier_info(char *buf);
	/**
	 * @brief ��ȡ�û���Ϣ������buf
	 *
	 * @param buf �洢�û���Ϣ
	 * @param size buf�Ĵ�С
	 */
    void getTvMacIp();
    void getHaierInfo(char *buf, size_t size);
    int prase_str(char *buf, const char *name, char *save);
    static void * getHaierTvInfo(void *arg);
    int getHaierTvInfobuf(char *buf, size_t size, char *net_name);
private:
	/**
	 * @brief �û�������Ϣ�洢
	 */
    pthread_t Local_tid;
    pthread_t Tv_tid;

    BasicInfo base;
    pthread_mutex_t Local_lock;
    pthread_mutex_t Tv_lock;
};

#endif

