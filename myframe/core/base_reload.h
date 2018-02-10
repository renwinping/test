#ifndef __BASE_RELOAD_H_
#define __BASE_RELOAD_H_

#include "base_def.h"


/**
 * @brief ��Ҫ�ṩLoad��Reload���ܵ����ͣ���Ҫ�̳д˽ӿڡ�
 * ��ReloadMgr����ʱ��Ҫ����Load��Reload����
 * */
class reload_inf 
{
    public:
        virtual ~reload_inf() {}
        virtual int load() = 0;
        virtual int reload() = 0;
        virtual bool need_reload()=0;
        virtual int dump() = 0;
        virtual int destroy() = 0;
};

/**
 *@brief ���ع����ж��Ƿ���Ҫ����
 */
class reload_mgr 
{
    public:
        reload_mgr(reload_inf * T1, reload_inf *T2);
        ~reload_mgr();

        /**
         *@brief ��������
         */
        int load(); 

        /**
         * @brief ��������
         */
        //��鵱ǰ�����ļ����޸�ʱ���Ƿ���ϴμ�¼��ʱ��һ�£� ��һ�����¼���, �����¼�¼���ļ��޸�ʱ�䣬�Լ�curr_ ֵ
        int reload(); 
        //��Ϊÿһ��ReloadMgr ģ����� ��߾��������汾���Ա�� ����ֻ��һ���ǵ�ǰ���õģ� curr_
        //���Ǽ�¼��ǰ���õ�ģ������� ��Load �� Reload �о�����¸ı�־ֵ, �ķ������ص�ǰ��Ч��
        //ģ�������
        reload_inf* current(); 

        void dump();

        int destroy();

    private:
        reload_inf * _objects[2];
        int16_t _curr;
};


#endif
