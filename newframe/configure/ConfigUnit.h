/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: ConfigUnit.h,v 1.19 2010/04/13 09:59:41 scmpf Exp $ 
 * 
 **************************************************************************/



/**
 * @file ConfigUnit.h
 * @author yingxiang(com@baidu.com)
 * @date 2008/11/26 20:53:09
 * @version $Revision: 1.19 $ 
 * @brief 
 *  
 **/

 
#ifndef  __CONFIGUNIT_H_
#define  __CONFIGUNIT_H_

#include "utils/cc_utils.h"
#include "bsl/var/IVar.h"
#include "bsl/var/Ref.h"
#include "bsl/ResourcePool.h"
#include <vector>

namespace comcfg{
	enum{
		CONFIG_UNIT_TYPE = 0,
		CONFIG_GROUP_TYPE,
		CONFIG_ARRAY_TYPE,
		CONFIG_ERROR_TYPE
	};
	class Reader;
	class ConfigGroup;
	class ConfigUnit{
		public:
			/**
			 * @brief ���������أ�������������֧���Է����Ż�ȡ��Ӧ�ֶ�
			 * 			֧���ַ�����bsl::string��int�±ꡣint�±�Arrayר�á�
			 * 			�����������һ��ConfigError���͵ĳ���
			 * 			������ conf[""].selfType() != CONFIG_ERROR_TYPE���ж�
			 *
			 * @return  const ConfigUnit& [] 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:18:13
			**/
			virtual const ConfigUnit & operator[] (const char *) const;
			virtual const ConfigUnit & operator[] (const str_t &) const;
			virtual const ConfigUnit & operator[] (int) const;

			virtual  ConfigUnit & operator[] (const char *) ;
			virtual  ConfigUnit & operator[] (const str_t &) ;
			virtual  ConfigUnit & operator[] (int) ;
			virtual  ConfigUnit & operator= (ConfigUnit & unit) ;
			
			/**
			 * @brief ��һ��ErrCodeת��Ϊһ����Ӧ���ַ�����Ϣ
			 * 			ErrCode�ڲ�����һ��int, 0ΪOK����0Ϊ������Ϣ
			 *
			 * @return  const char* 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:21:07
			**/
			virtual const char * seeError(const ErrCode &) const;
			virtual ~ConfigUnit();

			/**
			 * @brief ��һ���ֶ��л�ȡ�ض����͵�����
			 * 			XXX to_XXX() ��ʾ��XXX���ͻ�ȡ��������
			 *
			 * @param [out] errCode   : ErrCode* ������Ϣ
			 * 				errCode��ΪNULLʱ������Ž���д��*errCode
			 * 				���˴�errCodeΪĬ��ֵNULLʱ�����������쳣����ʽ�׳�
			 * 				�׳����쳣Ϊ��ConfigException��������
			 * @return  char 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:22:07
			**/
			virtual char to_char(ErrCode * errCode = NULL)const;
			virtual unsigned char to_uchar(ErrCode * errCode = NULL)const;
			virtual int16_t to_int16(ErrCode * errCode = NULL)const;
			virtual u_int16_t to_uint16(ErrCode * errCode = NULL)const;
			virtual int to_int32(ErrCode * errCode = NULL)const;
			virtual u_int32_t to_uint32(ErrCode * errCode = NULL)const;
			virtual long long to_int64(ErrCode * errCode = NULL)const;
			virtual unsigned long long to_uint64(ErrCode * errCode = NULL)const;
			virtual float to_float(ErrCode * errCode = NULL)const;
			virtual double to_double(ErrCode * errCode = NULL)const;
			virtual bsl_string to_bsl_string(ErrCode * errCode = NULL)const;
			//to_std_string : ����ֵΪstd::string�������˫���ſ�ͷ�Ĵ���������ַ����Ǿ���ת��ģ�\'\x41\' -> 'A'
			//virtual std_string to_std_string(ErrCode * errCode = NULL)const;
			//to_raw_string : δ����ת�崦����ַ���
			virtual str_t to_raw_string(ErrCode * errCode = NULL)const;
			//��ȡC�����ַ�����������
			virtual const char * to_cstr(ErrCode * errCode = NULL)const;

			/**
			 * @brief ����Ĭ��ֵ��to_XXXϵ�к���
			 *        ����ֵ��to_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ���errCode��Ϊ0������������, ����defĬ��ֵ
			 *
			 * @param [out] errCode   : ErrCode* ������Ϣ
			 * @param [in] def   : const &  Ĭ��ֵ
			 * @return  
			 * @author zhang_rui 
			 * @date 2009/03/11 22:37:46
			**/
			virtual char to_char(ErrCode * errCode, const char & def)const;
			virtual unsigned char to_uchar(ErrCode * errCode, const unsigned char & def)const;
			virtual int16_t to_int16(ErrCode * errCode, const int16_t & def)const;
			virtual u_int16_t to_uint16(ErrCode * errCode, const u_int16_t & def)const;
			virtual int to_int32(ErrCode * errCode, const int & def)const;
			virtual u_int32_t to_uint32(ErrCode * errCode, const u_int32_t & def)const;
			virtual long long to_int64(ErrCode * errCode, const long long & def)const;
			virtual unsigned long long to_uint64(ErrCode * errCode, const unsigned long long & def)const;
			virtual float to_float(ErrCode * errCode, const float & def)const;
			virtual double to_double(ErrCode * errCode, const double & def)const;
			virtual bsl_string to_bsl_string(ErrCode * errCode, const bsl_string & def)const;
			virtual str_t to_raw_string(ErrCode * errCode, const str_t & def)const;
			//��ȡC�����ַ�����������
			virtual const char * to_cstr(ErrCode * errCode, const char * def)const;



			/**
			 * @brief ��to_XXX������ͬ�ĺ���������get_XXXϵ��ΪC���
			 * 			����Ϊ���ڷ�ֵ��buffer������ֵ�Ǵ����
			 *
			 * @param [out] valueBuf   : char*
			 * @return  ErrCode 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:25:52
			**/
			virtual ErrCode get_char(char * valueBuf)const;
			virtual ErrCode get_uchar(unsigned char * valueBuf)const;
			virtual ErrCode get_int16(int16_t * valueBuf)const;
			virtual ErrCode get_uint16(u_int16_t * valueBuf)const;
			virtual ErrCode get_int32(int * valueBuf)const;
			virtual ErrCode get_uint32(u_int32_t * valueBuf)const;
			virtual ErrCode get_int64(long long * valueBuf)const;
			virtual ErrCode get_uint64(unsigned long long * valueBuf)const;
			virtual ErrCode get_float(float * valueBuf)const;
			virtual ErrCode get_double(double * valueBuf)const;
			virtual ErrCode get_bsl_string(bsl_string * valueBuf)const;
			//virtual ErrCode get_std_string(std_string * valueBuf) const;
			virtual ErrCode get_raw_string(str_t * valueBuf) const;
			//��ȡC�����ַ��������ַ�������valueBuf��len��valueBuf���ȣ��Զ���0��������len-1���ַ�
			virtual ErrCode get_cstr(char * valueBuf, size_t len) const;


			/**
			 * @brief ����Ĭ��ֵ��ge_XXXϵ�к���
			 *        ����ֵ��get_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ�������ֵ��Ϊ0������������valueBuf��ʹ��defĬ��ֵ
			 *
			 * @param [out] valueBuf   : char*  ������ֵ
			 * @param [in] def   : const char&  Ĭ��ֵ
			 * @return  ErrCode 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2009/03/11 22:37:46
			**/
			virtual ErrCode get_char(char * valueBuf, const char & def)const;
			virtual ErrCode get_uchar(unsigned char * valueBuf, const unsigned char & def)const;
			virtual ErrCode get_int16(int16_t * valueBuf, const int16_t & def)const;
			virtual ErrCode get_uint16(u_int16_t * valueBuf, const u_int16_t & def)const;
			virtual ErrCode get_int32(int * valueBuf, const int & def)const;
			virtual ErrCode get_uint32(u_int32_t * valueBuf, const u_int32_t & def)const;
			virtual ErrCode get_int64(long long * valueBuf, const long long & def)const;
			virtual ErrCode get_uint64(unsigned long long * valueBuf, const unsigned long long & def)const;
			virtual ErrCode get_float(float * valueBuf, const float & def)const;
			virtual ErrCode get_double(double * valueBuf, const double & def)const;
			virtual ErrCode get_bsl_string(bsl_string * valueBuf, const bsl_string & def)const;
			virtual ErrCode get_raw_string(str_t * valueBuf, const str_t & def)const;
			virtual ErrCode get_cstr(char * valueBuf, size_t len, const char * def)const;

			/**
			 * @brief ������ת��Ϊһ��IVar
			 *
			 * 		  �����쳣
			 *
			 * @param [in/out] vpool   : VarPool* IVar����������·����IVar��ע�ᵽVarPool
			 *                                    ����Ҫ�����Ҵ�����IVarʱ��ֻ��Ҫvpool->destroy();
			 * @param [in] errCode   : ErrCode* ����ţ�0Ϊ��ȷ�������ʾ����
			 * @return  IVar& 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2009/03/11 22:00:48
			**/
			virtual bsl::var::IVar& to_IVar(bsl::ResourcePool* vpool, ErrCode* errCode = NULL)const;
			/**
			 * @brief ��ȡ�Լ�������
			 *
			 * @return  int 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:35:27
			**/
			virtual int selfType()const{
				return CONFIG_UNIT_TYPE;
			}
			
			/**
			 * @brief ��ȡԪ�ظ���
			 *
			 * @return  size_t ����
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 02:00:28
			**/
			virtual size_t size()const{
				return 1;
			}

			/**
			 * @brief ��·��Unit��ֱ�ӻ�ȡ
			 *
			 * @param [in] path   : const str_t ��·�������� group.sub.key
			 * @return  const ConfigUnit& ��·����ȡ��ConfigUnit
			 * @date 2009/07/16 15:50:47
			**/
			virtual const ConfigUnit & deepGet(const str_t path) const;

			/**
			 * @brief ���ʲ����ڵ�key�󣬸��������ڵ�key�ľ���·�������� group.sub.nokey
			 *
			 * @return  const char*  �����ڵ�key��·��
			 * @author zhang_rui
			 * @date 2009/07/17 10:20:09
			**/
			const char * getErrKeyPath() const;

			/**
			 * @brief ��ȡ��unit��ConfigUnitֱ�ӷ���error unit
			 *
			 * @return  ConfigUnit &
			 * @author zhang_rui
			**/
			virtual const ConfigUnit & get_sub_unit(int index) const;
			/**
			 * @brief �Ƚ��Ƿ����
			 *
			 * @return  int 0��ʾ��� -1�����
			 * @author zhang_rui
			**/
			virtual int equals(const ConfigUnit & conf) const;

			//���º����Ĳ����У�exceptΪ0���ô���ű�ʾ����
			//exceptΪ1�����쳣��ʾ����
			/**
			 * @brief ����һ��unit, ���ӵ���unit���������
			 *
			 * @param [in] key   : ����unit��key
			 * @param [in] value : ����unit��value
			 * @param [in] objtype : unit���͡�
			 *    CONFIG_UNIT_TYPE��ʾunit;
			 *    CONFIG_GROUP_TYPE��ʾgroup;
			 *    CONFIG_ARRAY_TYPE��ʾarray;
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int add_unit(const bsl_string & key, const bsl_string& value, 
				const int objtype=CONFIG_UNIT_TYPE, int except=0, ConfigUnit ** ref=NULL);

			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit������׷�ӵ����������档
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * groupҪ���key�Ƿ��ظ������ظ���׷��
			 * arrayֱ��׷��
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int append_unit(const ConfigUnit & unit, int except=0);

			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ�������
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int copy_unit(const ConfigUnit & unit, int except=0);
			
			/**
			 * @brief ɾ��һ��unit
			 *
			 * key : Ҫɾ����unit��key
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int del_unit(const bsl_string & key, int except=0);
			/**
			 * @brief �޸�unit��value��ֵ
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int set_value(const bsl_string & value, int except=0);


			//-----------------���������µĶ����û�����Ҫ����-----------------

			//���캯����
			ConfigUnit();
			ConfigUnit(const str_t& __key, const str_t& __value, const Reader * __cur_reader = NULL, ConfigGroup * father = NULL);

			//���Դ�ӡʱ�ã�����
			void pindent(int ind)const{
				while(ind--){
					printf("    ");
				}
			}
			//��ӡ
			virtual void print(int indent = 0)const{
				pindent(indent);
				printf("=[%s], _value=[%s]\n", _key.c_str(), _value.c_str());
			}


			//for debug or writelog
			virtual str_t info() const{
				//const int INFO_BUF_SIZE = 256;
				//char buf[INFO_BUF_SIZE] = "";
				str_t buf;
				buf.appendf("[File:%s Line:%d Key:%s Value:%s]", 
						_at_file ? _at_file : "NULL", _at_line, _key.c_str(), _value.c_str());
				return buf;
			}
			//for child class
			virtual ConfigUnit * relativeSection(str_t, int* ){
				return NULL;
			}

			static ConfigUnit* get_err_unit();
			virtual const bsl::string & get_key_name() const;
		protected:
			virtual void popError(ErrCode *, ErrCode) const;
			void setErrorKeyPath(str_t str)const;
			const ConfigUnit & deepGetSegment(const str_t segment) const; 
			
			static const str_t g_unknown;
			str_t _key;
			str_t _value;
			str_t _cstr; //ר�ŵ�һ�����������string��ֻ�е�value��"Ϊ��ͷʱ��������
			int _cstr_err;
			str_t _vstring;
			const char * _at_file;
			int _at_line;
			ConfigGroup * _father;
			//mutable str_t _to_def_str;
			ConfigUnit * create_unit(const bsl_string & key, const bsl_string& value, 
				int objtype, ConfigGroup * father);

			/**
			 * @brief �������
			 *
			 * @return  void
			 * @author zhang_rui
			**/
			virtual void clear();
			
		public:
			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ����������档
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * groupҪ���key�Ƿ��ظ������ظ���׷��
			 * arrayֱ��׷��
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int _append_unit(const ConfigUnit & unit,int check=1, int except=0);
		private:
			int init_unit(const str_t& __key, const str_t& __value);
	};

}









#endif  //__CONFIGUNIT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
