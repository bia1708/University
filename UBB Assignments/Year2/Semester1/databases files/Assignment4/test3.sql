use Spotify
go

drop table AppVersion
create table AppVersion(
	vid int primary key,
	version char(20),
	downloads int);

drop table Platforms
create table Platforms(
	plid int primary key,
	OS char(100));

drop table AppVersionPlatforms
create table AppVersionPlatforms(
	vid int foreign key references AppVersion(vid) not null,
	plid int foreign key references Platforms(plid) not null,
	constraint PK_AppVersionPlatforms primary key(vid, plid));

insert into AppVersion values (1, '1.2', 1000);
insert into AppVersion values (2, '1.2.1', 1500);
insert into AppVersion values (3, '1.2.2', 3000);
insert into Platforms values (1, 'Win10');
insert into Platforms values (2, 'Win11');
insert into Platforms values (3, 'macOS');
insert into Platforms values (4, 'Ubuntu');
insert into AppVersionPlatforms values (1, 1);
insert into AppVersionPlatforms values (2, 1);
insert into AppVersionPlatforms values (3, 1);
insert into AppVersionPlatforms values (3, 2);
insert into AppVersionPlatforms values (2, 3);
insert into AppVersionPlatforms values (3, 3);
insert into AppVersionPlatforms values (1, 4);


exec addToTables 'AppVersion'
go
exec addToTables 'Platforms'
go
exec addToTables 'AppVersionPlatforms'
go

create or alter view getVersionsForPlatform as
    select av.version, sum(av.downloads) as downloads, p.OS
    from (AppVersion av
        inner join AppVersionPlatforms avp on av.vid = avp.vid
        inner join Platforms p on p.plid = avp.plid)
	group by p.OS, av.version
	having sum(av.downloads) > 1000;
        
go

exec addToViews 'getVersionsForPlatform'
go
exec addToTests 'test3'
go
exec connectTableToTest 'AppVersion', 'test3', 100, 1
go
exec connectTableToTest 'Platforms', 'test3', 100, 2
go
exec connectTableToTest 'AppVersionPlatforms', 'test3', 100, 3
go
exec connectViewToTest 'getVersionsForPlatform', 'test3'
go

create or alter procedure populateTableAppVersion (@rows int) as
    while @rows > 0 begin
        insert into AppVersion(vid, version, downloads) values (@rows, '1.5', floor(rand()*1000))
        set @rows = @rows - 1
    end
go

create or alter procedure populateTablePlatforms (@rows int) as
    while @rows > 0 begin
        insert into Platforms(plid, OS) values (@rows, 'os')
        set @rows = @rows - 1
    end
go

create or alter procedure populateTableAppVersionPlatforms (@rows int) as
    declare @vid int
    declare @plid int
    while @rows > 0 begin
        set @vid = (select top 1 vid from AppVersion order by newid())
        set @plid = (select top 1 plid from Platforms order by newid())
        while exists(select * from AppVersionPlatforms where vid = @vid and plid = @plid) begin
            set @vid = (select top 1 vid from AppVersion order by newid())
            set @plid = (select top 1 plid from Platforms order by newid())
        end
        insert into AppVersionPlatforms(vid, plid) values (@vid, @plid)
        set @rows = @rows - 1
    end
go

exec runTest 'test3'
select * from getVersionsForPlatform
select * from TestRuns
select * from TestRunTables
select * from TestRunViews