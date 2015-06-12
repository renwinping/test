/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             histogram_widget.h
 * @brief            ֱ��ͼwidget
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_
#include <list>
class QWidget;
class QPaintEvent;
class QRect;

class CHistogram_Widget : public QWidget
{
public:
    CHistogram_Widget ();
    /** ���Ӱ�������
     * 
     * @param  packet_count
     * @return 
     * @see 
     * @note 
     */
    void add_packet_count (int packet_count);
    /** ���
     * 
     * @return 
     * @see 
     * @note 
     */
    void clear ();
protected:
    /** ��ͼ����
     * 
     * @param  event
     * @return 
     * @see 
     * @note 
     */
    virtual void paintEvent (QPaintEvent * event);
private:
    /** ��ȡ��������
     * 
     * @param  rect
     * @return 
     * @see 
     * @note 
     */
    void get_rect (QRect & rect);
private:

static const int EDGE;
static const int WIDTH_PER_COLUMN;
static const int MAX_PACKET_COUNT;
private:
    std::list<int>  m_packet_count_list;

};

#endif