# sqlite数据库操作

## 建表

```
create table xx if not exists(id integer primary key,name char(20) default 'xxx');
alter table xx add column yyy integer;
drop table xx;
```

## 插入数据

- select datetime('now');
- select strftime('%s','2017-05-27');`获取Unix时间戳
- date --date=20170527 +%s 与上相同
- select datetime(148xxxxxx,'unixepoch','localtime');

```
insert into movie(topic,actor,pressDate) values('ipz-899','上園ゆりか',strftime('%s','2017-02-18'));
```

## 修改数据

```
update xx set degree=5 where topic='my';
```

## 删除数据

```
delete from xx where topic='yy';
```
