#ifndef __HTTP_RES_PROCESS_H__
#define __HTTP_RES_PROCESS_H__

#include "base_def.h"
#include "base_connect.h"
#include "base_singleton.h"
#include "base_data_process.h"
#include "common_exception.h"
#include "common_def.h"
#include "log_helper.h"
#include "http_base_msg.h"


class http_res_process:public http_base_process
{
    public:
        http_res_process(base_connect *p);

        virtual ~http_res_process();

        http_head_para &get_req_head_para();

        http_res_head_para &get_res_head_para();

		void set_res_head_para(const http_res_head_para &para);

		void reset();
		
		string gen_res_head();

        void add_header(const char *key, const char *value);

        void add_send_reply(int http_code);

    protected:
		virtual size_t process_recv_body(char *buf, size_t len, int &result);
        
        virtual void parse_first_line(const string & line);

        void parse_header()
		
        void gen_send_head();

        void recv_finish();

        void send_finish();

		size_t get_boundary(char *buf, size_t len, int &result);
      
    protected:
		enum BOUNDARY_STATUS
		{
			BOUNDARY_RECV_HEAD = 0,
			BOUNDARY_RECV_BODY = 1,
			BOUNDARY_RECV_TAIL = 2
		};
		string _recv_boundary_head;
		boundary_para _boundary_para;		
		BOUNDARY_STATUS _recv_boundary_status;
		uint32_t _recv_body_length;
		
        http_head_para _req_head_para;
        http_res_head_para _res_head_para;
        map<string, string> _send_headers;
};


#endif
