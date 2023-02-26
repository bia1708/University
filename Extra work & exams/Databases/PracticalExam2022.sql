create database Test
go

use Test
go

create table ActivityType(
	tid int not null identity(1, 1),
	constraint PK_T primary key(tid),
	name varchar(100),
	description varchar(100)
)

create table Activities(
	aid int not null identity(1, 1),
	constraint PK_A primary key(aid),
	name varchar(100),
	description varchar(100),
	tid int not null,
	constraint FK_T foreign key(tid) references ActivityType(tid)
)

create table Companies(
	cid int not null identity(1, 1),
	constraint PK_C primary key (cid),
	name varchar (100) unique,
	address varchar(100)
)

drop table AgentsActivities
drop table Agents
create table Agents(
	agid int not null identity(1, 1),
	constraint PK_Ag primary key(agid),
	name varchar(100) unique,
	cid int not null,
	constraint FK_C foreign key(cid) references Companies(cid)
)

create table AgentsActivities(
	agid int foreign key references Agents(agid) not null,
	aid int foreign key references Activities(aid) not null,
	constraint PK_AA primary key(agid, aid),
	start time,
	ending time
)


--b)
go
create or alter procedure AddActivity @agid int, @aid int, @start time, @ending time
as 
begin
	if not exists ( select 1 from AgentsActivities where aid = @aid and agid = @agid )
		begin
			insert into AgentsActivities values (@agid, @aid, @start, @ending)
		end
	else
		begin
			update AgentsActivities
			set start = @start, ending = @ending
			WHERE aid = @aid and agid = @agid
		end
end

insert into ActivityType values('act1', 'descr1');
insert into ActivityType values('act2', 'descr2');
insert into ActivityType values('act3', 'descr3');
insert into Activities values('name1', 'descr1', 1);
insert into Activities values('name2', 'descr2', 1);
insert into Activities values('name3', 'descr3', 2);
insert into Activities values('name4', 'descr4', 3);
insert into Companies values('name1', 'addr1');
insert into Companies values('name2', 'addr2');
insert into Agents values('name1', 1);
insert into Agents values('name2', 2);
insert into Agents values('name3', 1);
insert into Agents values('name4', 2);
insert into AgentsActivities values(1, 1, '12:35', '13:10');
insert into AgentsActivities values(1, 2, '12:35', '13:10');
insert into AgentsActivities values(1, 3, '12:35', '13:10');
insert into AgentsActivities values(1, 4, '12:35', '13:10');
insert into AgentsActivities values(2, 1, '12:35', '13:10');
insert into AgentsActivities values(3, 2, '12:35', '13:10');

go
exec AddActivity @agid=2, @aid=4, @start='12:20', @ending='13:20'
select * from AgentsActivities
go
exec AddActivity @agid=2, @aid=4, @start='16:20', @ending='17:20'

--c)
go
create or alter view ShowAgents as
select Agents.name as agname, Companies.name as cname from Companies
inner join Agents on Companies.cid = Agents.cid
inner join AgentsActivities as ag on Agents.agid = ag.agid
group by  Agents.name, Companies.name
having count(ag.aid) = (select count(*) from Activities)

go
select * from ShowAgents

--d)
go
create or alter function activities_with_duration(@R int) returns table
as
return
	select distinct a.name as acname from (Activities as a
	inner join AgentsActivities on a.aid = AgentsActivities.aid)
	group by a.name, AgentsActivities.start, AgentsActivities.ending
	having datediff(minute, AgentsActivities.start, AgentsActivities.ending) > @R

go
select * from activities_with_duration(65)
