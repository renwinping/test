#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__



namespace MZFRAME {
	
	
class to_string {
			public:
				to_string(){}
				virtual ~to_string(){}
				virtual const char * to_str(char * dst, size_t dst_len)=0;				
};
	
	
	
struct host_str {
    string  _ip;
    uint16_t _port;
};

typedef struct _msg_t
{		 
	   uint64_t _obj_id; //消s息id
     uint64_t _obj_op; //消息命令
     unsigned short version; //
     unsigned int reserved; //保留字段
     unsigned int body_len;
} msg_t;


struct obj_id_str : public to_string{
	obj_id_str()
	{
		_obj_id = 0;
		_thread_id = 0;
	}
	
	uint64_t _obj_id; //消息id
	pthread_t _thread_id;//线程id
	
	bool operator==(const obj_id_str &o1) const;
	
	bool operator<(const obj_id_str &o1) const;	
	
	virtual const char * to_str(char * dst, size_t dst_len);
};


int get_date_str(char dest[], size_t dest_len, const char * format);

uint64_t GetTickCount();






}




#endif