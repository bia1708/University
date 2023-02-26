create database Cinema
go

use Cinema
go

create table Company(
	cid int not null identity(1,1),
	constraint PK_C primary key(cid),
	name varchar(100)
)

create table StageDirectors(
	sdid int not null identity(1, 1),
	constraint PK_SD primary key(sdid),
	name varchar(100),
	awards int
)

create table Movies(
	mid int not null identity(1, 1),
	constraint PK_M primary key(mid),
	name varchar(100),
	release date,
	cid int not null,
	constraint FK_C foreign key(cid) references Company(cid),
	sdid int not null,
	constraint FK_SD foreign key(sdid) references StageDirectors(sdid)
)

drop table CpActors
drop table Actors
drop table CinemaProductions
create table Actors(
	aid int not null identity(1, 1),
	constraint PK_A primary key(aid),
	name varchar(100),
	ranking int
)

create table CinemaProductions(
	cpid int not null identity(1, 1),
	constraint PK_CP primary key(cpid),
	title varchar(100),
	mid int not null,
	constraint FK_M foreign key(mid) references Movies(mid),
)

create table CPActors(
	cpid int foreign key references CinemaProductions(cpid) not null,
	aid int foreign key references Actors(aid) not null,
	constraint PK_CPA primary key (cpid, aid),
	entry_moment int
)


--b)
go
create or alter procedure AddActor @aid int, @entry int, @cpid int
as
begin
	insert into CPActors values(@cpid, @aid, @entry) 
end

insert into Actors values('name1', 1);
insert into Actors values('name2', 3);
insert into Actors values('name3', 4);
insert into StageDirectors values ('name1', 12)
insert into Company values('c1')
insert into Movies values('m1', '2022/02/13', 1, 1)
insert into CinemaProductions values('cp1', 1)
insert into CPActors values(1, 1, 20)
insert into CPActors values(1, 2, 34)

go
exec AddActor @aid = 3, @entry = 23, @cpid = 1
select * from CPActors

--c)
go
create or alter view ShowActors as
select distinct Actors.name from (Actors 
inner join CPActors on Actors.aid = CPActors.aid)
group by Actors.name
having count(CPActors.cpid) = (select count(*) from CinemaProductions)

go
select * from ShowActors

--d)
go
create or alter function movies_with_release(@P int) returns table
as
return
	select distinct Movies.name from (Movies
	inner join CinemaProductions on Movies.mid = CinemaProductions.cpid)
	group by Movies.name, Movies.release
	having Movies.release > '2018/01/01' and count(CinemaProductions.cpid) > @P

go
select * from dbo.movies_with_release(0)