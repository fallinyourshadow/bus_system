#include "widget.h"
#include "ui_widget.h"
#include "updatecurrrentbuslocation.h"

void Widget::updateCurrentBusLocation()
{
   QSqlTableModel *model;
   model = new QSqlTableModel;
   model->setTable("immediate_bus_location");
   model->select();
   int len;

   Bus *bus_list;
   Bus *bus_head;
   bus_head = new Bus;
   Bus *temp = NULL;
   QString str;
   QString str_text1;
   QString str_text2;
   QStringList bnum_similar;
   int bus_count;
   bus_count = 0;
   int se_num;
   int se_spot_se;
   int se_current_se;
   int se_is_arrive;
   int i,j;
   int max_temp;
   max_temp =0;
   i=0;
   j=0;
   QSqlQuery query(*db);
   QSqlRecord rec;   
   str = QString("select b.bus_num,i.sequence_position from bus_info b,immediate_bus_location i where b.bus_id=i.bus_id and i.terminal_id = '%1';").arg(my_id);
   query.exec(str);
   rec = query.record();
   len = query.numRowsAffected();
   while(i<len)
   {
       query.seek(bus_count);
       temp = new Bus;
       se_num = rec.indexOf("bus_num");
       temp->bnum = query.value(se_num).toString();
       if(!bnum_similar.contains(temp->bnum))
       {
           bnum_similar.append(temp->bnum);
           bus_count++;
       }
       se_spot_se = rec.indexOf("sequence_position");
       temp->spot_se = query.value(se_spot_se).toUInt();
       temp->next = bus_head->next;
       bus_head->next = temp;
       i++;
   }
   query.clear();
   bus_list = new Bus[bus_count];
   bus_list = bus_head->next;
   i=0;
   while(i<bus_count)
   {
       str = QString("select i.sequence_position,i.is_arrive from bus_info b,immediate_bus_location i where b.bus_id=i.bus_id and bus_num = '%1' and sequence_position<'%2' and i.is_arrive=1;").arg(bus_list->bnum).arg(bus_list->spot_se);
       query.exec(str);
       rec = query.record();
       se_current_se = rec.indexOf("sequence_position");
       se_is_arrive = rec.indexOf("is_arrive");
       j = query.numRowsAffected();
       if(j==0)
       {
           break;
       }
       //j = j-1;
       while(j>0)
       {
           query.seek(j-1);
           if(query.value(se_current_se) > max_temp)
           {
               max_temp = query.value(se_current_se).toUInt();
           }
//           if(query.value(se_is_arrive).toUInt()==1)
//           {
//               bus_list->current_se = query.value(se_current_se).toUInt();
//               break;
//           }
           j--;
       }
       //qDebug() << max_temp;
       bus_list->current_se = max_temp;
       bus_list = bus_list->next;
       i++;
   }
   i=0;
   bus_list = bus_head->next;
   while(i<bus_count)
   {
       if(bus_list->current_se != 0)
       {
           bus_list->spot_count = bus_list->spot_se - bus_list->current_se;
       }
       bus_list = bus_list->next;
       i++;
   }
   i=0;
   bus_list = bus_head->next;
   ui->textBrowser->clear();
   while(i<bus_count)
   {
       if(bus_list->spot_count >=0)
       {
           str_text1 = QString(" %1 还有%2到站！").arg(bus_list->bnum).arg(bus_list->spot_count);
           ui->textBrowser->append(str_text1);
           //qDebug() << bus_list->bnum << bus_list->spot_count;
       }
       else {
           str_text2 = QString(" %1 没车来了！").arg(bus_list->bnum);
           ui->textBrowser->append(str_text2);
           //qDebug() << bus_list->bnum << "NO BUS";
       }
       bus_list = bus_list->next;
       i++;
   }

}
