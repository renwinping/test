#ifndef __BASE_CONNECT_H__
#define __BASE_CONNECT_H__

#include "common_epoll.h"
#include "base_net_container.h"
#include "net_obj.h"
#include "log_helper.h"
#include "common_exception.h"


template<class PROCESS>
class base_connect:public NET_OBJ
{
    public:

        base_connect(const int32_t sock, EPOLL_TYPE epoll_type/*0:lt,  1:et*/)
        {
            init(epoll_type);
            _fd = sock;
        }

        ~base_connect()
        {
            //WRITE_WARN("delete the connect");
            close();

            if (_process != NULL)
                delete _process;

            if (_p_send_buf != NULL)
                delete _p_send_buf;
        }

        void init(EPOLL_TYPE epool_type = 0/*0:lt,  1:et*/)
        {
            _epoll_type = epool_type; //��ʼ��

            _connect_timeout = CONNECT_TIME_OUT;

            _recv_buf.resize(max_recv_data);		
            _p_send_buf = NULL;

            _recv_buf_len = 0;

            _epoll_event = EPOLLIN | EPOLLERR | EPOLLHUP;	

            _process = NULL;
            _p_epoll = NULL;
            _fd = 0;
        }


        void close()
        {
            if (_fd != 0)
            {
                if (_p_epoll != NULL)
                {
                    _p_epoll->del_from_epoll(this);
                }

                ::close(_fd);
                _fd = 0;
                _epoll_event = EPOLLIN | EPOLLERR | EPOLLHUP;
                if (_p_send_buf != NULL)
                {
                    delete _p_send_buf;
                    _p_send_buf = NULL;
                }
                _recv_buf_len = 0;
            }
        }

        void set_process(PROCESS *p)
        {
            if (_process != NULL)
                delete _process;
            _process = p;

            _process->set_para();
        }

        void event_process(int event)
        {
            if ((event & EPOLLERR) == EPOLLERR || (event & EPOLLHUP) == EPOLLHUP)
            {
                THROW_COMMON_EXCEPT("epoll error ");
            }

            if ((event & EPOLLIN) == EPOLLIN) //��
            {
                recv_process();
            }

            if ((event & EPOLLOUT) == EPOLLOUT ) //д
            {
                send_process();
            }		
        }	

        int32_t real_net_process()
        {
            int32_t ret = 0;

            real_recv();

            //real_send();

            return ret;
        }

        size_t process_recv(pass_msg* p_msg)
        {
            size_t p_ret =_process->process_recv(p_msg);
            return p_ret;
        }

        int get_sock()
        {
            return _fd;
        }

        int get_event()
        {
            return _epoll_event;
        }

        int destroy()
        {
            delete this;
            return 0;
        }

        void get_local_addr(sockaddr_in &addr)
        {
            socklen_t len = 0;
            getsockname(_fd, (sockaddr*)&addr, &len);
        }

    protected:
        virtual int RECV(void *buf, size_t len)
        {
            int ret = recv(_fd, buf, len, MSG_DONTWAIT);
            if (ret == 0)
            {
                _process->peer_close();
                PDEBUG("the client close the socket [%d]\n", _fd);
                THROW_COMMON_EXCEPT("the client close the socket(" << _fd << ")");
            }
            else if (ret < 0)
            {
                if (errno != EAGAIN)
                {
                    PDEBUG("this socket occur fatal error [%s]\n", strerror(errno));
                    THROW_COMMON_EXCEPT("this socket occur fatal error " << strerror(errno));
                }
                ret = 0;
            }

            return ret;
        }

        virtual ssize_t SEND(const void *buf, const size_t len)
        {
            if (len == 0) //�ϲ���һ������Ϊ0�����ݹ��� ,ֱ�ӹر�
            {
                THROW_COMMON_EXCEPT("close the socket " << _fd);
            }

            ssize_t ret =  send(_fd, buf, len, MSG_DONTWAIT);
            if (ret < 0)
            {
                if (errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    THROW_COMMON_EXCEPT("send data error " << strerror(errno));
                }
                ret = 0;
            }
            return ret;
        }


        virtual void recv_process()
        {	
            if ((_epoll_event & EPOLLET) != EPOLLET)
            {
                real_recv();
            }
        }

        virtual void send_process()
        {
            if((_epoll_event & EPOLLET) != EPOLLET)
            {
                real_send();
            }
        }


        void real_recv()
        {	
            size_t tmp_len = max_recv_data - _recv_buf_len; 	
            ssize_t ret = 0;
            if (tmp_len > 0) //���ջ�������Ҳ�����Ȳ�����
            {
                ret = RECV((void*)(_recv_buf.c_str() + _recv_buf_len), tmp_len);
                _recv_buf_len += ret;
            }

            if (_recv_buf_len > 0)
            {
                LOG_DEBUG("process_recv_buf _recv_buf_len[%d] fd[%d]\n", _recv_buf_len, _fd);
                size_t p_ret = _process->process_recv_buf((char*)_recv_buf.c_str(), _recv_buf_len);
                if (p_ret < _recv_buf_len)//�����ϲ㴦������������,ֹͣ��������
                {
                    string tmp_str = _recv_buf.substr(p_ret, _recv_buf_len - p_ret);
                    memcpy((void*)_recv_buf.c_str(), tmp_str.c_str(), tmp_str.length());
                }

                _recv_buf_len = _recv_buf_len - p_ret;			
                //PDEBUG("p_ret[%d] _recv_buf_len[%d]\n", p_ret, _recv_buf_len);
            }		
        }


        void real_send()
        {	
            int ii = 0; 	
            while (1)
            {
                if (ii >= max_send_num)
                    break;
                ii++;
                if (_p_send_buf == NULL)
                {
                    _p_send_buf = _process->get_send_buf();
                }

                if (_p_send_buf != NULL)
                {
                    bool is_break = false;
                    ssize_t ret = SEND(_p_send_buf->c_str(), _p_send_buf->length());				
                    if (ret == (ssize_t)_p_send_buf->length())
                    {
                        delete _p_send_buf;
                        _p_send_buf = NULL; 				
                    }
                    else if (ret >= 0)
                    {
                        _p_send_buf->erase(0, ret);
                        LOG_WARNING("_p_send_buf erase %d", ret);
                        is_break = true;
                    }
                    else //<0
                    {
                        is_break = true;
                    }

                    if (is_break)
                        break;
                }
            }
        }


    protected:
        PROCESS *_process;
        string _recv_buf;
        size_t _recv_buf_len;
        string* _p_send_buf;	
        uint64_t _connect_timeout;
        EPOLL_TYPE _epoll_type;
};


#endif