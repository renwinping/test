#ifndef __HTTP_BASE_PROCESS_H__
#define __HTTP_BASE_PROCESS_H__

#include "base_def.h"
#include "base_connect.h"
#include "base_singleton.h"
#include "base_data_process.h"
#include "common_exception.h"
#include "common_def.h"
#include "log_helper.h"
#include "http_base_msg.h"


class http_base_process: public base_data_process
{
    public:
        http_base_process(base_connect *p);

        virtual ~http_base_process();

        void set_process(http_base_data_process * data_process);

        virtual size_t process_recv_buf(char *buf, const size_t len);

        virtual string* get_send_buf();

        virtual bool process_recv_msg(ObjId & id, normal_msg * p_msg);
        
        virtual void reset();
		
		/****************************������������ӣ������ǹ��ײ����********************************************/
        string &get_head();

		void change_http_status(HTTP_STATUS status, bool if_change_send = true);
		
		void change_to_cansend();

		http_base_data_process *get_process()
		{
			return _data_process;
		}

        void add_header(const char *key, const char *value);

		static void parse_url_para(const string &url_para, map<string, string> &url_para_map);

    protected:		
		virtual size_t process_recv_body(char *buf, size_t len, int &result) = 0;	
		
        virtual void parse_header() = 0;
        virtual void recv_finish() = 0;
        virtual void send_finish() = 0;
        virtual void parse_first_line(const string & line) = 0;

        void check_head_finish(string &left_str);

        map<string, string> _send_headers;
        HTTP_STATUS _http_status;
        string _recv_head;
        string _send_head;
        size_t _send_head_len;
        http_base_data_process *_data_process;
		int _send_status;	
};


#endif
