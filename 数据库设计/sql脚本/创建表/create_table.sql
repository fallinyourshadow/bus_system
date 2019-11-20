set names gbk; 
use intelligent_bus_spot;

create table spot_info(
	terminal_id char(10) primary key, #终端id 主键 10个字符
	spot_name char(100) not null #站点名 100个字符 不能为空
	
)engine=InnoDB default charset=gbk;

create table driver_info(
	driver_id char(10) primary key,#司机id 主键 10个字符
	driver_name char(20) not null,#司机姓名 20个字符 不能为空
	driver_contaction char(20) not null#司机电话 20个字符 不能为空

)engine=InnoDB default charset=gbk;

create table bus_info(
	bus_id char(10) primary key,#公交id 10个字符 主键
	bus_num char(10) not null,#公交路数 10个字符 不能为空
	driver_id char(10) not null,#司机id 10个字符 不能为空
	constraint bus_driver_fk foreign key(driver_id) references driver_info(driver_id)
)engine=InnoDB default charset=gbk;

create table immediate_bus_location(
	relationship_id int unsigned auto_increment primary key,#关系id 无符号整型 自增 主键
	bus_id  char(10) not null,#公交id 10个字符 不能为空
	terminal_id char(10) not null,#终端id 10个字符 不能为空
	sequence_position int unsigned not null,#站位 无符号整型 不能为空
	is_arrive bit default 0 not null,#是否到达 bit 默认为0 不能为空
	constraint bus_location_fk foreign key(bus_id) references bus_info(bus_id),
	constraint terminal_location_fk foreign key(terminal_id) references spot_info(terminal_id)
)engine=InnoDB default charset=gbk;

create table main_notice(
	notice_id int unsigned auto_increment primary key,#公告id 无符号整型 自增 主键
	terminal_id char(10) not null,#终端id 10个字符 不能为空
	insert_date datetime default now() not null,#编写时间 datetime 默认为插入时间 不能为空
	notice_content text not null,#公告内容 text 不能为空
	publish_date datetime default now() not null,#公告发布时间 datetime  默认为插入时间 不能为空
	weather enum('cloudy','sunny','rainy','none') default 'none',#天气 枚举 默认为none
	map_source mediumblob,#地图资源  mediumblob 可以为空
	constraint terminal_notice_fk foreign key(terminal_id) references spot_info(terminal_id)
)engine=InnoDB default charset=gbk;

create table ad_source(
	ad_id char(10) primary key,
	ad_company char(48),
	contact_person_name char(32) not null,
	contaction_num char(20) not null,
	publish_date datetime,
	expiration_date datetime,
	terminal_id char(10),
	constraint ad_terminal_fk foreign key(terminal_id) references spot_info(terminal_id)
)engine=InnoDB default charset=gbk;