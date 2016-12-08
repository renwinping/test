#ifndef __MSG_HELPER_H__
#define __MSG_HELPER_H__



namespace MZFRAME {
	
struct obj_id_str;




//�̼߳䷢����Ϣʹ��
class base_net_msg {
	
	public:
		base_net_msg();
		virtual ~base_net_msg();
		virtual void event_process(const int32_t events) = 0;
		
	
	protected:
		int _sfd;
		uint64_t _obj_id;
		int _epoll_event;
		common_epoll *_epoll;
};


class add_net_msg {
		public:
			add_net_msg();
			virtual ~add_net_msg();
			virtual void event_process(const int32_t events);
}

enum MSG_OP {
		ADD_TO_EPOLL_IN,
		
		MSG_OP_SIZE
	};


typedef struct _msg_t
{		 
	   uint64_t _obj_id; //��Ϣid
     uint64_t _obj_op; //��Ϣ����
     unsigned short version; //
     unsigned int reserved; //�����ֶ�
     unsigned int body_len;
} msg_t;
	
// �̼߳�ͨ����Ϣ
struct obj_id_str : public to_string{
	obj_id_str()
	{
		_obj_op = 0;
		_obj_id = 0;
		_thread_id = 0;
		unsigned int obj_len;
	}
	
	uint64_t _obj_op; //��Ϣ����
	uint64_