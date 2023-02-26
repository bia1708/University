exec addToTables 'Podcasts'
go
exec addToTables 'Producers'
go

create or alter view getProducers as
    select Podcasts.name, Podcasts.poid
        from Podcasts inner join Producers on Podcasts.prid = Producers.prid
        where Podcasts.name like '%Crime%'
go

exec addToViews 'getProducers'
go
exec addToTests 'test2'
go
exec connectTableToTest 'Podcasts', 'test2', 1200, 2
go
exec connectTableToTest 'Producers', 'test2', 600, 1
go
exec connectViewToTest 'getProducers', 'test2'
go

create or alter procedure populateTablePodcasts (@rows int) as
    while @rows > 0 begin
        insert into Podcasts(poid, name, prid) values
            (@rows,
			'Crime Show',
             (select top 1 prid from Producers order by newid())
             )
        set @rows = @rows - 1
    end
go

create or alter  procedure populateTableProducers (@rows int) as
    while @rows > 0 begin
        insert into Producers(prid, name) values
            (@rows,
             'Name'
             )
        set @rows = @rows - 1
    end
go

execute runTest 'test2'
select * from TestRuns