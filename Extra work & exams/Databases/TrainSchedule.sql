
--a)
create database TrainSchedule
go

use TrainSchedule
go

create table TrainTypes(
	ttid int not null identity(1, 1),
	constraint PK_TrainTypes primary key(ttid),
	name varchar(100),
	description varchar(200)
);

create table Trains(
	tid int not null identity(1, 1),
	constraint PK_Trains primary key(tid),
	name varchar(100),
	ttid int not null,
	constraint FK_TrainTypes foreign key(ttid) references TrainTypes(ttid)
)

create table Stations(
	sid int not null identity(1, 1),
	constraint PK_Stations primary key(sid),
	name varchar(100) unique
)

create table Routes(
	rid int not null identity(1,1),
	constraint PK_Routes primary key(rid),
	name varchar(100) unique,
	tid int not null,
	constraint FK_Trains foreign key(tid) references Trains(tid)
)

create table RoutesStations(
	rid int foreign key references Routes(rid) not null,
	sid int foreign key references Stations(sid) not null,
	constraint PK_ArtistsSong primary key(rid, sid),
	arrival char(6),
	departure char(6)
)


--b)

go
create or alter procedure AddStation @rid int, @sid int, @arrival char(6), @departure char(6)
as
begin
	if not exists ( select 1 from RoutesStations where rid = @rid and sid = @sid )
		begin
			insert into RoutesStations VALUES (@rid, @sid, @arrival, @departure)
		end
	else
		begin
			update RoutesStations
			set arrival = @arrival, departure = @departure
			WHERE rid = @rid and sid = @sid
		end
end

insert into TrainTypes values('name1', 'descr');
insert into Trains values('train1', 1);
insert into Trains values('train2', 1);
insert into Stations values('station1');
insert into Stations values('station2');
insert into Stations values('station3');
insert into Routes values('route1', 1);
insert into Routes values('route2', 2);

exec AddStation @rid = 1, @sid = 1, @arrival = '14:20', @departure = '14:30'
select * from RoutesStations
exec AddStation @rid = 1, @sid = 1, @arrival = '15:20', @departure = '15:30'

exec AddStation @rid = 1, @sid = 2, @arrival = '16:20', @departure = '16:30'
exec AddStation @rid = 1, @sid = 3, @arrival = '18:20', @departure = '18:30'
exec AddStation @rid = 2, @sid = 1, @arrival = '12:20', @departure = '12:30'
exec AddStation @rid = 2, @sid = 2, @arrival = '16:20', @departure = '16:30'

-- c)
go
create or alter view RoutesInStations as
SELECT DISTINCT Routes.name
FROM Routes
WHERE Routes.rid IN (SELECT rid FROM RoutesStations GROUP BY rid HAVING COUNT(DISTINCT sid) = (SELECT COUNT(*) FROM Stations));
go

select * from RoutesInStations


-- d)
go
create or alter function stations_with_routes(@R int) returns table
as
return
	select distinct Stations.name
	FROM Stations
	WHERE Stations.sid IN (select sid from RoutesStations group by sid having count(distinct rid) > @R);


-- my version 
go
create or alter function stations_with_routes2(@R int) returns table
as
return
	select distinct Stations.name from ((Stations 
	inner join RoutesStations on Stations.sid = RoutesStations.sid)
	inner join Routes on Routes.rid = RoutesStations.rid)
	group by Stations.name
	having count(Routes.rid) > @R


go
select * from dbo.stations_with_routes(1);

go
select * from dbo.stations_with_routes2(1);
