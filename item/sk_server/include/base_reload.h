#ifndef __BASE_RELOAD_H_
#define __BASE_RELOAD_H_

#include "base_def.h"
#include "log_helper.h"


/**
 * @brief ��Ҫ�ṩLoad��Reload���ܵ����ͣ���Ҫ�̳д˽ӿڡ�
 * ��ReloadMgr����ʱ��Ҫ����Load��Reload����
 * */
class reload_inf {
public:
    virtual ~reload_inf() {}
    virtual int init(const char * path) = 0;
    virtual int load() = 0;
    virtual int reload() = 0;
    virtual int dump() = 0;
    virtual int destroy() = 0;
};

/**
 *@brief ���ع����ж��Ƿ���Ҫ����
 */
template<typename ClassT>
class reload_mgr {
public:
    reload_mgr() {}
    ~reload_mgr() {}

    int init(const char * path){
        _objects[0].init(path);
        _objects[1].init(path);
        set_path(path);
        return 0;
    }

    /**
     *@brief ��������
     */
    int load() {
        if( _objects[0].load() == 0 ) {
            struct stat st;
            stat(_fullpath, &st);
            last_load_ = st.st_mtime;
            _curr = 0;
            return 0;
        }

        LOG_WARNING("load data failed, %s", _fullpath);
        return -1;
    }

    /**
     * @brief ��������
     */
     //��鵱ǰ�����ļ����޸�ʱ���Ƿ���ϴμ�¼��ʱ��һ�£� ��һ�����¼���, �����¼�¼���ļ��޸�ʱ�䣬�Լ�curr_ ֵ
    int reload() {
        struct stat st;
        if (stat(_fullpath, &st) == 0 && S_ISREG(st.st_mode) && st.st_mtime != _last_load) {
            LOG_DEBUG("reload thread check time. file time[%lu],last load time[%lu]\n",st.st_mtime,_last_load);
            if ( _objects[1 - _curr].reload() == 0 ) {
                _last_load = st.st_mtime;
                _curr = 1 - _curr;
                return 0;
            } else {
                LOG_WARNING("reload data failed, %s,%d", _fullpath, _curr);
                return -1;
            }
        }

        return 0;
    }
	//��Ϊÿһ��ReloadMgr ģ����� ��߾��������汾���Ա�� ����ֻ��һ���ǵ�ǰ���õģ� curr_
	//���Ǽ�¼��ǰ���õ�ģ������� ��Load �� Reload �о�����¸ı�־ֵ, �ķ������ص�ǰ��Ч��
	//ģ�������
    ClassT* current() {
        if( _curr == 0 || _curr == 1){
            return &(_objects[_curr]);
        }

        return NULL;
    }

    void dump(){
        ClassT* obj = current();
        obj->dump(path,fname);
    }

    int destroy(){
    	_objects[0].destroy();
		_objects[1].destroy();
    	return 0;
    }
private:
    /**����·�����ļ���*/
    void set_path (const char* path) {
        snprintf(_fullpath, sizeof(_fullpath), "%s", path);
    }
private:
    char _fullpath[SIZE_LEN_512];
    ClassT _objects[2];
    int16_t _curr;
    time_t _last_load;
};


#endif
