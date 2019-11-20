set names gbk; 
use intelligent_bus_spot;
#清空driver_info表
truncate driver_info;
#或者
delete from driver_info
where driver_id like 'D%';