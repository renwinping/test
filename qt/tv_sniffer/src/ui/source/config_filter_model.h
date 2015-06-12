/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             config_filter_model.h
 * @brief            ������model
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef  _CONFIG_FILTER_MIDEL_H_
#define  _CONFIG_FILTER_MIDEL_H_

#include "data_struct.h"
#include <QAbstractTableModel>
#include <QStringList>
#include <QList>

class CConfigFilterModel : public  QAbstractTableModel
{
    Q_OBJECT

public:
    
    CConfigFilterModel (QObject *parent = 0);
    /** ��ȡ����
     * 
     * @param  parent
     * @return ����
     * @see 
     * @note 
     */
    int rowCount(const QModelIndex &parent) const;  
    /** ��ȡ����
     * 
     * @param  parent
     * @return ����
     * @see 
     * @note 
     */
    int columnCount(const QModelIndex &parent) const;  
    /** ��ȡ����
     * 
     * @param  index
     * @param  role ��ɫ
     * @return ����
     * @see 
     * @note 
     */
    QVariant data(const QModelIndex &index, int role) const;  
    /** ��������
     * 
     * @param  index ����
     * @param  value ֵ
     * @param  role  ��ɫ
     * @return  bool
     * @see 
     * @note 
     */
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    /** ��ȡ���ͷ
     * 
     * @param  section
     * @param  orientation ����
     * @param  role        ��ɫ
     * @return 
     * @see 
     * @note 
     */
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;
    /** ��ʶ
     * 
     * @param  index ����
     * @return 
     * @see 
     * @note 
     */
    virtual Qt::ItemFlags flags(const QModelIndex & index) const;
    /** ��Ӽ�¼
     * 
     * @param  record ��¼
     * @return 
     * @see 
     * @note 
     */
    void add_record (const FilterRecord & record);
    /** ɾ����¼
     * 
     * @param  row
     * @return 
     * @see 
     * @note 
     */
    void delete_record (int row);
    /** ���
     * 
     * @return 
     * @see 
     * @note 
     */
    void clear ();
    /** �Ƿ��п�����
     * 
     * @return 
     * @see 
     * @note 
     */
    bool has_empty_data ();
    /** ��ȡ������������
     * 
     * @param  recorder_list
     * @return 
     * @see 
     * @note 
     */
    int get_filter_data (QList <FilterRecord> & recorder_list);
    /** ���ù�����������
     * 
     * @param  recorder_list
     * @return 
     * @see 
     * @note 
     */
    int set_filter_data (const QList <FilterRecord> & recorder_list);
private:
    QStringList m_head_list;
    QList <FilterRecord>  m_recorder_list;

private slots:

    /** ���ݷ����仯����Ӧ
     * 
     * @param  topLeft
     * @param  bottomRight
     * @param  roles
     * @return 
     * @see 
     * @note 
     */
    void slot_data_changed(const QModelIndex & topLeft, 
        const QModelIndex & bottomRight, 
        const QVector<int> & roles);
};

#endif