#include "server_helper.h"



namespace MZFRAME {
	
	
	
	server_info_t & server_info_t::operator=(const server_info_t & ser_t)
		{
				_thread_num = ser_t._thread_num;
				_con_timeout = ser_t._con_timeout;
				_read_timeout = ser_t._read_timeout;
				_listen_port = ser_t._listen_port;
				_ip = ser_t._ip;
		}
	
	
	server_info_t & server_info_t::server_info_t()
	
	server_helper::server_helper():
		{
		}
		
		server_helper::~server_helper()
			{
			}
			
		void server_helper::init(const server_info_t & ser)
			{
				_server_info = ser;
			}
	
	
			void server_helper::run()
				{
						for (int i = 1; i <= _server_info._thread_num; i++){
								common_thread * tmp = new common_thread();
								_work_thread_mgr.push_back(tmp);	
						}
				}
	
}