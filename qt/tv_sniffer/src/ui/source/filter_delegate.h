/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             filter_delegate.h
 * @brief            ����������
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef  _FILTER_DELEGATE_H_
#define  _FILTER_DELEGATE_H_

#include <QItemDelegate>

class CFilterDelegate : public QItemDelegate
{
public:
    CFilterDelegate (QObject * parent = 0);

    /** �����༭��
     * 
     * @param  parent
     * @param  option
     * @param  index
     * @return 
     * @see 
     * @note 
     */
    virtual QWidget *	createEditor(QWidget * parent, 
        const QStyleOptionViewItem & option,
        const QModelIndex & index) const;

    /** ����model����
     * 
     * @param  editor
     * @param  model
     * @param  index
     * @return 
     * @see 
     * @note 
     */
    virtual void	setModelData(QWidget * editor,
        QAbstractItemModel * model, 
        const QModelIndex & index) const;

    /** ���ñ༭������
     * 
     * @param  editor
     * @param  index
     * @return 
     * @see 
     * @note 
     */
    virtual void	setEditorData(QWidget * editor,
        const QModelIndex & index) const;
};


#endif