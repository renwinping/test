/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: Configure.h,v 1.15 2010/04/13 09:59:41 scmpf Exp $ 
 * 
 **************************************************************************/



/**
 * @file Configure.h
 * @author yingxiang(com@baidu.com)
 * @date 2008/12/21 17:59:12
 * @version $Revision: 1.15 $ 
 * @brief �µ�Configure��
 * 			����������μ���
 * 			http://com.baidu.com/twiki/bin/view/Main/LibConfig
 *  
 **/


#ifndef  __CONFIGURE_H_
#define  __CONFIGURE_H_

#include "ConfigGroup.h"
#include "sys/uio.h"
#include <vector>

#define CONFIG_GLOBAL "GLOBAL"
#define CONFIG_INCLUDE "$include"

namespace confIDL{
	struct idl_t;
}
namespace comcfg{
	const int MAX_INCLUDE_DEPTH = 1;
	class Reader;
	enum{
		CONFIG_VERSION_1_0,	//Config Version 1.0
	};
	/**
	 * @brief ���þ������ʵ��һ��ȫ�ֵ�[GLOBAL]������
	 *
	 * Configure��immutable�ģ������޷��޸ģ��޷�����
	 *  ����load, rebuild, loadIVar�����ӿڻ���
	 * Ҫ����load�����봴��һ���µ�Configure������в��� 
	 *
	 */
	class Configure : public ConfigGroup{
		public:
			/**
			 * @brief ��ָ�����ļ������������ļ���Լ���ļ�
			 *
			 * @param [in] path   : const char* �����ļ���·��
			 * @param [in] conf   : const char* �����ļ���
			 * @param [in] range   : const char* Լ���ļ�
			 * @param [in] version   : int �ļ���ʽ�İ汾����δʹ�ã�
			 * @return  int  0��ʾ�ɹ�������Ϊʧ��
			 * 				bsl::CONSTRAINT_ERROR  Լ�����������������Լ���������Ӵ˴���
			 * 				bsl::CONFIG_ERROR �����ļ���������
			 * 				bsl::ERROR ��������
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:36:54
			 **/
			int load(const char * path, const char * conf, const char * range = NULL, int version = CONFIG_VERSION_1_0);
			/**
			 * @brief �����ݴ��л���һ���ֽ��������Է�������
			 * 			���������ֽ���ֱ��д������ļ���������ֱ��load����������Ҫ��ȡ����rebuild
			 *
			 * @param [out] size_t * : ������ֽ�������
			 * @return  char* ������ֽ���
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:38:35
			 **/
			char * dump(size_t *);

			/**
			 * @brief ����dump���ֽ�������Configure
			 * 		�����ֽ����ؽ�һ��Configure�Ĳ����ǣ�
			 * 		1��getRebuildBuffer(size) ��ȡһ���ڲ�������
			 * 		2�����ֽ����е����ݿ��������������
			 * 		3������rebuild�ؽ�����
			 *
			 * 		���ñ��ӿڻ�������е����ݡ�
			 *
			 * @param [in] size   : size_t �ֽ�������
			 * @return  char* ������
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:39:38
			 **/
			char * getRebuildBuffer(size_t size);
			/**
			 * @brief ���ݻ�õ��ֽ����ؽ�Configure����
			 *
			 * @return  int 0Ϊ�ɹ�������Ϊʧ��
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2008/12/30 01:43:05
			 **/
			int rebuild();
			/**
			 * @brief ������������ļ���������ʱ�䣨������$include���������ļ�
			 *        $include ���Ʋ���Ϊ��MAX_INCLUDE_DEPTH
			 *        ��ִ��lastConfigModify()��Ӧȷ��ԭ���������ļ���û�б�ɾ��
			 *
			 * @return  time_t ���������ļ��е�������ʱ��
			 *                 ����0��ʾ����
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2009/03/10 14:23:47
			**/
			time_t lastConfigModify();
			/**
			 * @brief ��һ��IVar���������ļ�������
			 *        ���ӿ���load/rebuild����
			 *        ���IVar������һ��Dict����
			 *
			 * @return  int 0�ɹ�������ʧ��
			 * @retval   
			 * @see 
			 * @author yingxiang
			 * @date 2009/03/11 17:29:56
			**/
			int loadIVar(const bsl::var::IVar & );
			/**
			 * @brief ��Լ���ļ����һ��
			 * @param [in] range   : const char* Լ���ļ�
			 * @param [in] version   : int �ļ���ʽ�İ汾����δʹ�ã�
			 * @return  int  0��ʾ�ɹ�������Ϊʧ��
			 * 				bsl::CONSTRAINT_ERROR  Լ��������
			 * 				bsl::ERROR ��������
			 **/
			int check_once(const char * range, int version = CONFIG_VERSION_1_0);

			virtual  ConfigUnit & operator= (ConfigUnit & unit) {
				return ConfigUnit::operator=(unit);
			}

			Configure();
			~Configure();
		protected:

			int load_1_0(const char * path, const char * conf, const char *range);
			void pushSubReader(const char * conf, int level = -1);
			friend class Reader;
			friend class Constraint;
			friend class ConfigGroup;
			friend class ConfigUnit;

			struct ReaderNode{//ÿһ��conf�ļ�
				str_t filename;
				Reader * reader;
				int level;
			};
			std::vector <ReaderNode *> _readers;
			str_t _path;
			Reader * _cur_reader;//��ǰ�ڴ�����ļ�
			int _cur_level;//��ǰ�ļ������($include�Ĳ��)
			char * _dump_buffer;
			size_t _dump_size;
			confIDL::idl_t * _idl;
			void changeSection(str_t str);
			void pushPair(const str_t& key, const str_t& value);

			ConfigGroup* _section;
			//depth��һ�����Ա���
			int _depth;
	};
}



#endif  //__CONFIGURE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
