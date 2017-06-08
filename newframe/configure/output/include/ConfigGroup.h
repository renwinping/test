/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: ConfigGroup.h,v 1.11 2010/04/13 09:59:41 scmpf Exp $ 
 * 
 **************************************************************************/



/**
 * @file ConfigGroup.h
 * @author yingxiang(com@baidu.com)
 * @date 2008/11/26 21:01:39
 * @version $Revision: 1.11 $ 
 * @brief 
 *  
 **/


#ifndef  __CONFIGGROUP_H_
#define  __CONFIGGROUP_H_

#include "ConfigUnit.h"
#include "ConfigError.h"
#include "vector"
namespace comcfg{

	//class ConfigError;
	class ConfigGroup : public ConfigError{
		public:
			ConfigGroup(){
				_name = "";
				_father = NULL;
				//create("GLOBAL");
			}
			ConfigGroup(const char * __name, ConfigGroup * __father = NULL){
				create(__name, __father);
			}
			virtual const ConfigUnit & operator[] (const char *) const;
			virtual const ConfigUnit & operator[] (const str_t &) const;
			virtual const ConfigUnit & operator[] (int idx) const;

			virtual  ConfigUnit & operator[] (const char *) ;
			virtual  ConfigUnit & operator[] (const str_t &) ;
			virtual  ConfigUnit & operator[] (int idx) ;

			virtual  ConfigUnit & operator= (ConfigUnit & unit){
				return ConfigUnit::operator=(unit);
			}

			virtual bsl::var::IVar& to_IVar(bsl::ResourcePool * vpool, ErrCode* errCode = NULL)const;

			virtual void print(int indent = 0) const;
			virtual ~ConfigGroup();
			virtual size_t size()const{
				return fieldMap.size();
			}

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
			virtual str_t to_raw_string(ErrCode * errCode = NULL)const;
			virtual const char * to_cstr(ErrCode * errCode = NULL)const;

			/**
			 * @brief ����Ĭ��ֵ��to_XXXϵ�к���
			 *        ����ֵ��to_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ���errCode��Ϊ0������������, ����defĬ��ֵ
			 *
			 * @param [out] errCode   : ErrCode* ������Ϣ
			 * @param [in] def   : const &  Ĭ��ֵ
			 * @return  
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
			virtual ErrCode get_raw_string(str_t * valueBuf) const;
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

			virtual const ConfigUnit & get_sub_unit(int index) const;
			virtual const bsl::string & get_key_name() const;

			/**
			 * @brief �Ƚ��Ƿ����
			 *
			 * @return  int 0��ʾ��� -1�����
			 * @author zhang_rui
			**/
			virtual int equals(const ConfigUnit & conf) const;
			/**
			 * @brief ����һ����unit
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int add_unit(const bsl_string & key, const bsl_string& value,  
				const int objtype=CONFIG_UNIT_TYPE,int except=0, ConfigUnit ** ref=NULL);
			
			/**
			 * @brief ɾ��һ��unit
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int del_unit(const bsl_string & key, int except=0);
			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ�������
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int copy_unit(const ConfigUnit & unit, int except=0);
		protected:
			friend class Reader;
			friend class Constraint;
			friend class Configure;
			friend class ConfigUnit;
			friend class CFdefault;
			void create(const char * __name, ConfigGroup * __father = NULL);
			ConfigUnit * relativeSection(str_t str, int * depth);
			int push(const str_t& key, ConfigUnit* unit);
			ConfigGroup * getFather() const{
				return _father;
			}
			const char * getName() const{
				return _name.c_str();
			}
			virtual int selfType() const{
				return CONFIG_GROUP_TYPE;
			}
			int getLevel() const{
				return _level;
			}

			int _level;

			//ConfigGroup * _father;
			str_t _name;
			std::vector <str_t > fieldList;
			typedef std::map <str_t, ConfigUnit*> :: iterator itr_t;
			typedef std::map <str_t, ConfigUnit*> :: const_iterator const_itr_t;
			std::map <str_t, ConfigUnit*> fieldMap;

			/**
			 * @brief �������
			 *
			 * @return  void
			 * @author zhang_rui
			**/
			virtual void clear();
			
		public:
			/**
			 * @brief ����һ��group����unit, ���
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int _append_unit(const ConfigUnit & unit,int check=1, int except=0);

	};

}
















#endif  //__CONFIGGROUP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
