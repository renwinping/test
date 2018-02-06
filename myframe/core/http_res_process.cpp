#include "base_def.h"
#include "base_net_obj.h"
#include "base_singleton.h"
#include "http_res_process.h"
#include "common_exception.h"
#include "common_def.h"
#include "log_helper.h"
#include "http_base_process.h"
#include "http_base_data_process.h"


http_res_process::http_res_process(base_net_obj * p):http_base_process(p)
{
    change_http_status(RECV_HEAD);
    _recv_body_length = 0;
    _recv_boundary_status = BOUNDARY_RECV_HEAD;
}

http_res_process::~http_res_process()
{		
}


void http_res_process::reset()
{
    http_base_process::reset();
    change_http_status(RECV_HEAD);

    _boundary_para.init();
    _recv_body_length = 0;
    _recv_boundary_status = BOUNDARY_RECV_HEAD;
}


size_t http_res_process::process_recv_body(const char *buf, size_t len, int &result)
{

    int ret = 0;
    if (strcasecmp(_req_head_para._method.c_str(), "GET") == 0 || strcasecmp(_req_head_para._method.c_str(), "HEAD") == 0)
    {
        result = 1;
        ret = len;
    }
    else
    {
        if (_boundary_para._boundary_str.length() == 0)
        {
            ret = _data_process->process_recv_body(buf, len, result);
            _recv_body_length += ret;


            uint64_t content_length = 0;
            string *tmp_str = _req_head_para.get_header("Content-Length");
            if (tmp_str) 
            {
                content_length = strtoull(tmp_str->c_str(), 0, 10);
            }


            if (_recv_body_length == content_length)
            {
                result = 1;
            }				
        }
        else //parse boundary
        {
            ret = get_boundary(buf, len, result);
        }
    }
    return ret;
}


void http_res_process::parse_first_line(const string & line)
{
    vector<string> tmp_vec;
    SplitString(line.c_str(), " ", &tmp_vec, SPLIT_MODE_ALL);
    if (tmp_vec.size() != 3) {
        THROW_COMMON_EXCEPT("http first line");
    }
    _req_head_para._method = tmp_vec[0];
    _req_head_para._version = tmp_vec[2];
    _req_head_para._url_path = tmp_vec[1];
}


void http_res_process::parse_header(string & recv_head)
{
    string &head_str = recv_head;
    vector<string> strList;
    SplitString(head_str.c_str(), CRLF, &strList, SPLIT_MODE_ALL);
    for (uint32_t i = 0; i < strList.size(); i++) {
        if (!i) {
            parse_first_line(strList[i]);
        }else {
            vector<string> tmp_vec;
            SplitString(strList[i].c_str(), ":", &tmp_vec, SPLIT_MODE_ONE);
            if (2 == tmp_vec.size()) {
                _req_head_para._headers.insert(make_pair(tmp_vec[0], tmp_vec[1]));
                LOG_DEBUG("%s: %s", tmp_vec[0].c_str(), tmp_vec[1].c_str());
            }
        }
    }

    string * cookie_str = _req_head_para.get_header("Cookie");
    if (cookie_str)
    {
        vector<string> cookie_vec;
        SplitString(cookie_str->c_str(), ";", &cookie_vec, SPLIT_MODE_ALL);
        size_t c_num = cookie_vec.size();
        for (size_t ii = 0; ii < c_num; ii++)
        {
            vector<string> c_tmp_vec;
            SplitString(cookie_vec[ii].c_str(), "=", &c_tmp_vec, SPLIT_MODE_ONE);
            if (c_tmp_vec.size() == 2)
            {
                StringTrim(c_tmp_vec[0]);
                StringTrim(c_tmp_vec[1]);
                _req_head_para._cookie_list.insert(make_pair(c_tmp_vec[0], c_tmp_vec[1]));
            }
        }
    }


    string *tmp_str = NULL;
    if (_req_head_para._method == "POST" || _req_head_para._method == "PUT")
    {
        //parse content_type
        tmp_str = _req_head_para.get_header("Content-Type");
        if (tmp_str)
        {
            if (strncasestr(tmp_str->c_str(), tmp_str->length(),  "multipart/form-data") != NULL)
            {
                GetCaseStringByLabel(*tmp_str, "boundary=", "", _boundary_para._boundary_str);
            }
        }
    }         
}

void http_res_process::recv_finish()
{
    _data_process->msg_recv_finish();
    change_http_status(SEND_HEAD);
}

void http_res_process::send_finish()
{        	
    reset();
}


size_t http_res_process::get_boundary(const char *buf, size_t len, int &result)
{	
    uint64_t content_length = 0;
    string *tmp_str = _req_head_para.get_header("Content-Length");
    if (tmp_str) 
    {
        content_length = strtoull(tmp_str->c_str(), 0, 10);
    }

    if (!content_length)
    {
        THROW_COMMON_EXCEPT("get boundary but content_len not found");
    }
    size_t ret = len;
    size_t p_len = 0;
    result = 0;
    _recv_body_length += len;
    //����Ҫ�ҵ�һ��boundary
    if (_recv_boundary_status == BOUNDARY_RECV_HEAD)
    {				
        _recv_boundary_head.append(buf, len);
        size_t pos = _recv_boundary_head.find("\r\n\r\n");
        if (pos != string::npos)
        {					
            _boundary_para._boundary_content_length = content_length - (_boundary_para._boundary_str.length() + BOUNDARY_EXTRA_LEN)
                - (pos+4);	
            string left_str;
            if (_recv_body_length == content_length)
            {											
                left_str = _recv_boundary_head.substr(pos+4, _boundary_para._boundary_content_length);
            }
            else if (_recv_body_length >= content_length - (_boundary_para._boundary_str.length() + BOUNDARY_EXTRA_LEN)) 
            {
                left_str = _recv_boundary_head.substr(pos+4, _boundary_para._boundary_content_length);
                _recv_boundary_status = BOUNDARY_RECV_TAIL;
            }
            else
            {
                left_str = _recv_boundary_head.substr(pos+4);
                _recv_boundary_status = BOUNDARY_RECV_BODY;
            }

            if (left_str.length() > 0)
            {
                p_len = _data_process->process_recv_body(left_str.c_str(), left_str.length(), result);
                if (_recv_body_length == content_length)
                    result = 1;
                p_len = left_str.length() - p_len;
            }
            else //ʲôҲ����
            {
            }
        }
        else //��Ҫ������ͷ
        {
            if (_recv_boundary_head.length() >= MAX_HTTP_HEAD_LEN)
                THROW_COMMON_EXCEPT("http boundary head too long (" << _recv_boundary_head.length() << ")");
        }
    }
    else if (_recv_boundary_status == BOUNDARY_RECV_BODY)//recv_body
    {		
        int tmp_len = len;
        if (_recv_body_length == content_length)
        {
            tmp_len = len - (_boundary_para._boundary_str.length() + BOUNDARY_EXTRA_LEN);

        }
        else if (_recv_body_length >= content_length - (_boundary_para._boundary_str.length() + BOUNDARY_EXTRA_LEN))
        {
            tmp_len = len - (_recv_body_length - (content_length - (_boundary_para._boundary_str.length() + BOUNDARY_EXTRA_LEN)));
            _recv_boundary_status = BOUNDARY_RECV_TAIL;
        }
        else //��Ҫ��body
        {
        }

        p_len = _data_process->process_recv_body(buf, tmp_len, result);
        p_len = tmp_len - p_len;

        if (_recv_body_length == content_length)
            result = 1; //������
    }
    else //recv tail
    {	
        //ʲôҲ���ɣ�ֻ������
        if (_recv_body_length == content_length)
            result = 1;				
    }
    _recv_body_length = _recv_body_length - p_len;
    return ret - p_len;
}



