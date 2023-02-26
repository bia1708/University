-- a)

create database Poetry
go

use Poetry
go

create table Users(
	uid int not null identity(1, 1),
	constraint PK_Users primary key(uid),
	name varchar(100),
	pen_name varchar(50) unique,
	birth_year int
)

create table Awards(
	aid int not null identity(1, 1),
	constraint PK_Awards primary key(aid),
	name varchar(100),
	uid int not null,
	constraint FK_Users foreign key(uid) references Users(uid)
)

create table Competitions(
	cid int not null identity(1, 1),
	constraint PK_Competitions primary key(cid),
	year int,
	week int,
	unique (year, week)
)

create table Poems(
	pid int not null identity(1, 1),
	constraint PK_Poems primary key(pid),
	uid int not null, 
	constraint FK_Users2 foreign key(uid) references Users(uid),
	cid int not null,
	constraint FK_Competitions foreign key(cid) references Competitions(cid),
	title varchar(30),
	text varchar(200)
)

create table Judges(
	jid int not null identity(1, 1),
	constraint PK_Judges primary key(jid),
	name varchar(100)
)

create table JudgesPoems(
	jid int foreign key references Judges(jid) not null,
	pid int foreign key references Poems(pid) not null,
	constraint PK_JudgesPoems primary key (jid, pid),
	score int,
	constraint C_score check(1 <= score and score <= 10)
)


--b)
go
create or alter procedure RemoveJudge @name varchar(100)
as
begin
	delete from JudgesPoems 
	where JudgesPoems.jid in (select Judges.jid from 
		(Judges inner join JudgesPoems on JudgesPoems.jid = Judges.jid)
		where Judges.name = 'jude')

	delete from Judges where name = @name
end

insert into Judges values ('jude')
insert into Judges values ('jude')
insert into Judges values ('jane')
insert into Users values ('user1', 'pen1', 2002)
insert into Users values ('user2', 'pen2', 2002)
insert into Competitions values (2022, 1)
insert into Competitions values (2022, 2)
insert into Poems values (1, 1, 'title1', 'text1')
insert into Poems values (1, 2, 'title2', 'text2')
insert into Poems values (2, 1, 'title3', 'text3')
insert into JudgesPoems values (1, 1, 9)
insert into JudgesPoems values (2, 1, 1)
insert into JudgesPoems values (3, 1, 3)
insert into JudgesPoems values (1, 2, 7)
insert into JudgesPoems values (2, 2, 4)
insert into JudgesPoems values (3, 2, 8)
insert into JudgesPoems values (1, 3, 2)
insert into JudgesPoems values (2, 3, 6)
insert into JudgesPoems values (3, 3, 7)

delete from JudgesPoems;
delete from Judges;
delete from Competitions;
delete from Users;
delete from Poems;

DBCC CHECKIDENT ('Judges', RESEED, 0)
GO

DBCC CHECKIDENT ('Poems', RESEED, 0)
GO

DBCC CHECKIDENT ('Competitions', RESEED, 0)
GO

DBCC CHECKIDENT ('Users', RESEED, 0)
GO

select * from JudgesPoems
select * from Judges

exec RemoveJudge @name = 'jude'

--c)
go
create or alter view ShowCompetitions as
select Competitions.cid, Competitions.year, Competitions.week, count(Poems.pid) as no_of_poems from   
((Competitions
inner join Poems on Competitions.cid = Poems.cid)
inner join JudgesPoems on JudgesPoems.pid = Poems.pid)
where JudgesPoems.score < 5
group by Competitions.cid, Competitions.year, Competitions.week
having count(Poems.pid) > 0 

go
select * from ShowCompetitions

--d)

go
create or alter function users_with_poems(@P int) returns table
as
return
	select distinct Users.name, Users.pen_name from (Users
	inner join Poems on Poems.uid = Users.uid)
	group by Users.name, Users.pen_name
	having count(Poems.pid) > @P

go
select * from dbo.users_with_poems(1);