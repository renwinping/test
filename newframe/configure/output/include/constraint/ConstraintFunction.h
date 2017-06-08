/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: ConstraintFunction.h,v 1.9 2010/01/08 03:24:38 scmpf Exp $ 
 * 
 **************************************************************************/



/**
 * @file ConstraintFunction.h
 * @author yingxiang(com@baidu.com)
 * @date 2008/12/10 18:15:58
 * @version $Revision: 1.9 $ 
 * @brief 
 *  
 **/


#ifndef  __CONSTRAINTFUNCTION_H_
#define  __CONSTRAINTFUNCTION_H_

#include <string>
#include <list>
#include <map>
#include "Configure.h"
#include "ConfigGroup.h"
#include "ConfigUnit.h"

namespace confIDL{
	struct cons_func_t;
	struct var_t;
	struct idl_t;
}

namespace comcfg{
	//typedef std::string str_t;
	typedef std::list <str_t> param_list_t;

	//Constraint function pointer
	typedef int (* CF_T)(const confIDL::cons_func_t&, const confIDL::var_t &, ConfigGroup *, ConfigUnit*);

	enum CFLevel{
		CF_STRUCT = 0,	//��߼����Լ������������ִ�У���array��Լ��ĳ���ֶε�����
		CF_KEY,			//�ֶ�Լ������default��Լ��ĳ���ֶεĻ������
		CF_TYPE,		//����Լ����int16, int32, int64...,Ҳ��һ��ֵ��Լ��(CF_VALUE)
		CF_VALUE,		//��ͨ�����Լ������ip(), length()�ȣ�Լ��ĳ���ֶ�ֵ������
		CF_DEFAULT,
	};

	class ConstraintFunction{
		int _level;
		public:
			virtual int check(const confIDL::cons_func_t&, const confIDL::var_t &, ConfigGroup*, ConfigUnit*);
			void setLevel(int lv);
			int getLevel();
	};
	typedef std::map<str_t, ConstraintFunction*> CFMAP_T;

	//Constraint Library is Singleton
	class ConstraintLibrary{
		ConstraintLibrary();
		~ConstraintLibrary();
		static ConstraintLibrary * lib;
		public:
			/**
			 * @brief ��ȡLibrary��ʵ��
			 *			���û����ù��ı��ӿڡ�
			 * @return  ConstraintLibrary* 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/28 23:26:14
			**/
			static ConstraintLibrary* getInstance();
			/**
			 * @brief ��ȡĳ�������ļ��𣬶Բ����ڵĺ�������default
			 *			���û����ù��ı��ӿڡ�
			 *
			 * @param [in] function   : const str_t&
			 * @return  int 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/28 23:26:28
			**/
			int getLevel(const str_t& function);
			static int getLevel_static(const str_t& function);
			/**
			 * @brief ���ݺ������һ������ 
			 * 			�����Ը��ڵ����ʽ���루��Ϊ�������ֶβ�һ�����ڣ���default�����ڸ��ڵ����½��ӽ�㣩
			 * 			���û����ù��ı��ӿڡ�
			 *
			 * @param [in] function   : const str_t& Լ��������
			 * @param [in]    	: const confIDL::var_t& Լ����Ϣ
			 * @param [in] 		: ConfigGroup * ����ĸ��ڵ�
			 * @return  int 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/28 23:26:42
			**/
			int check(const confIDL::cons_func_t&, const confIDL::var_t &, ConfigGroup*, ConfigUnit*);
			/**
			 * @brief ע��һ��Լ������ �������û�����չ��
			 *
			 * @param [in] fname   : const str_t& Լ������������
			 * @param [in] cons   : const ConstraintFunction& Լ������ʵ�壬�൱�ڷº���
			 * 			��ע�⡿��new�����ٴ���ȥ��Ȼ��ConstraintLibrary��delete֮
			 * @param [in] overwrite   : bool �Ƿ񸲸�ͬ���ĺ���
			 * @return  int 
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/28 23:29:50
			**/
			int registConstraint(const str_t& fname, ConstraintFunction* cons, bool overwrite = false);

			int registConstraint(const str_t& fname, CF_T cf, bool overwrite = false){
				return registConstraint(fname, cf, CF_VALUE, overwrite);
			}
		private:
			friend class Constraint;
			friend class ConsUnitControl;
			int registConstraint(const str_t& fname, CF_T cf, int cfLevel, bool overwrite = false);
		protected:
			CFMAP_T cfMap;
			class WrapFunction : public ConstraintFunction{
				public:
					virtual int check(const confIDL::cons_func_t& cons, 
							const confIDL::var_t& param, ConfigGroup* father, ConfigUnit* self){
						return _cf(cons, param, father, self);
					}
					void setCF(CF_T cf){
						_cf = cf;
					}
					WrapFunction(){}
				protected:
					CF_T _cf;
			};
	};
}




#endif  //__CONSTRAINTFUNCTION_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
