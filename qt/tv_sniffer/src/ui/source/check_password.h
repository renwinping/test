
/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             check_password.h
 * @brief            ��������Ƿ���ȷ
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef _CHECK_PASSWORD_H_
#define _CHECK_PASSWORD_H_
#include <QString>

class CCheckPassword
{
public:

    /** ����û����������Ƿ���ȷ
     * 
     * @param  id
     * @param  password
     * @return 0 ��ȷ -1����ȷ
     * @see 
     * @note 
     */
    int check (const QString & id, const QString & password);
protected:
private:
};


#endif