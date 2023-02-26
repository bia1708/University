
-- a)
create database Olympics
go

use Olympics
go

create table Countries(
	cid int not null,
	constraint PK_Countries primary key(cid),
	name varchar(100) not null
);

create table Athletes(
	aid int not null,
	constraint PK_Athletes primary key(aid),
	name varchar(100) not null,
	birth_date date,
	cid int not null,
	constraint FK_Countries foreign key (cid) references Countries(cid)
);

create table Venues(
	vid int not null,
	constraint PK_Venues primary key(vid),
	address varchar(100) not null,
	city varchar(100) not null
);

drop table Sports
create table Sports(
	sid int not null,
	constraint PK_Sports primary key(sid),
	name varchar(100),
	vid int not null,
	constraint FK_Venues foreign key (vid) references Venues(vid),
);

drop table SportEvents
create table SportEvents(
	seid int not null,
	constraint PK_SportEvents primary key(seid),
	sid int,
	constraint FK_Sports foreign key(sid) references Sports(sid),
	name varchar(100)
);

drop table Results; 
create table Results(
	rid int not null identity(1, 1), --auto incremented id
	constraint PK_Results primary key(rid),
	aid int not null,
	constraint FK_Athletes foreign key(aid) references Athletes(aid),
	seid int not null,
	constraint FK_SportEvent foreign key(seid) references SportEvents(seid),
	event_date date,
	athlete_rank int,
	value varchar(5)
);


-- b)
go
create or alter procedure AddResult @aid int, @seid int, @athlete_rank int, @value varchar(5), @event_date date
as
begin
	if not exists ( select 1 from Results where aid = @aid and seid = @seid )
		begin
			--declare @rid int
			--set @rid = (select top 1 rid from Results order by rid DESC)
			insert into Results VALUES (@aid, @seid, @event_date, @athlete_rank, @value)
		end
	else
		begin
			update Results
			set event_date = @event_date, value = @value
			WHERE aid = @aid and seid = @seid
		end
end

insert into Countries values (1, 'Romania');
insert into Athletes values (1, 'ion', '2000-02-12', 1); 
insert into Athletes values (2, 'nelu', '2000-02-13', 1);
insert into Athletes values (3, 'ana', '2000-02-12', 1); 
insert into Venues values (1, 'addr', 'city');
insert into Sports values(1, 'swimming', 1);
insert into Sports values(2, 'jumping', 1);
insert into SportEvents values (1, 1, '100m');
insert into SportEvents values (2, 1, '200m');
insert into SportEvents values (3, 2, '150m');

exec AddResult @aid=1, @seid=1, @athlete_rank=10, @value='PB', @event_date='2022-12-10'
select * from Results
exec AddResult @aid=1, @seid=1, @athlete_rank=10, @value='WR', @event_date='2022-12-10'

exec AddResult @aid=2, @seid=2, @athlete_rank=10, @value='PB', @event_date='2022-12-10'
exec AddResult @aid=3, @seid=3, @athlete_rank=10, @value='PB', @event_date='2022-12-10'


-- c)
go
create or alter view AthletesInEvents as
select distinct Athletes.name from (((Athletes
inner join Results on Athletes.aid = Results.aid)
inner join SportEvents on Results.seid = SportEvents.seid)
inner join Sports on SportEvents.sid = Sports.sid)
where Sports.name='swimming' 

go
select * from AthletesInEvents


-- d)

go
create or alter function no_of_athletes(@R int, @S int) returns int
as
begin
	DECLARE @counter int;
	set @counter = (select count(rid) from 
	((Results inner join SportEvents on Results.seid = SportEvents.seid) 
	inner join Sports on SportEvents.sid = Sports.sid)
	where athlete_rank = 10 and Sports.sid = @S)
	RETURN @counter
end

go
select dbo.no_of_athletes(1, 1);

