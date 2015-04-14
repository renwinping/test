
/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             packet_list_model.h
 * @brief            packetlist model
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef  _PACKET_LIST_MODEL_H_
#define  _PACKET_LIST_MODEL_H_
#include "data_struct.h"
#include <QAbstractTableModel>
#include <QStringList>
#include <QList>


class CPacketListModel : public  QAbstractTableModel
{
public:
    CPacketListModel (QObject *parent = 0);
    /** ����
     * 
     * @param  parent ������
     * @return ����
     * @see 
     * @note 
     */
    int rowCount(const QModelIndex &parent) const;  
    /** ����
     * 
     * @param  parent ������
     * @return ����
     * @see 
     * @note 
     */
    int columnCount(const QModelIndex &parent) const;  
    /** ����
     * 
     * @param  index ����
     * @param  role  ��ɫ
     * @return ����
     * @see 
     * @note 
     */
    QVariant data(const QModelIndex &index, int role) const;  
    /** ��������
     * 
     * @param  section     λ��
     * @param  orientation ����
     * @param  role        ��ɫ
     * @return ����
     * @see 
     * @note 
     */
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;
    /** ������ݰ�
     * 
     * @param  packet_record ���ݰ�
     * @return void
     * @see 
     * @note 
     */
    void add_packet (const Packet_Record & packet_record);
    /** ���
     * 
     * @return void
     * @see 
     * @note 
     */
    void clear ();
private:
    QStringList m_head_list;
    QList <Packet_Record>  m_recorder_list;
};


#endif