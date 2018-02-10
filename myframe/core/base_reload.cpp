#include "base_reload.h"
#include "log_helper.h"


reload_mgr::reload_mgr(reload_inf * T1, reload_inf *T2) 
{
    _objects[0] = T1;
    _objects[1] = T2;
    _curr = 0;
}

reload_mgr::~reload_mgr() 
{
    if (_objects[0])
    {
        _objects[0]->destroy();
        delete _objects[0];
        _objects[0] = NULL;
    }

    if (_objects[1])
    {
        _objects[1]->destroy();
        delete _objects[1];
        _objects[1] = NULL;
    }
}

/**
 *@brief ��������
 */
int reload_mgr::load() 
{
    if( _objects[0]->load() == 0 ) 
    {
        _curr = 0;
        return 0;
    }

    return -1;
}

/**
 * @brief ��������
 */
//��鵱ǰ�����ļ����޸�ʱ���Ƿ���ϴμ�¼��ʱ��һ�£� ��һ�����¼���, �����¼�¼���ļ��޸�ʱ�䣬�Լ�curr_ ֵ
int reload_mgr::reload() 
{
    if (current()->need_reload()) 
    {
        if ( _objects[1 - _curr]->reload() == 0 ) 
        {
            _curr = 1 - _curr;
            return 0;
        } else 
        {
            LOG_WARNING("reload data failed,%d", _curr);
            return -1;
        }
    }

    return 0;
}
//��Ϊÿһ��ReloadMgr ģ����� ��߾��������汾���Ա�� ����ֻ��һ���ǵ�ǰ���õģ� curr_
//���Ǽ�¼��ǰ���õ�ģ������� ��Load �� Reload �о�����¸ı�־ֵ, �ķ������ص�ǰ��Ч��
//ģ�������
reload_inf* reload_mgr::current() {
    if( _curr == 0 || _curr == 1){
        return (_objects[_curr]);
    }

    return NULL;
}

void reload_mgr::dump()
{
    reload_inf* obj = current();
    obj->dump();
}

int reload_mgr::destroy()
{
    if (_objects[0])
        _objects[0]->destroy();

    if (_objects[1])
        _objects[1]->destroy();

    return 0;
}


