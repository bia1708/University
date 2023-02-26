exec addToTables 'STATION_TEST'
go

create or alter view getStateGroups as
    select state, count(*) as number_of_stations
    from STATION_TEST
    group by state
go

truncate table TestTables 

exec addToViews 'getStateGroups'
go
exec addToTests 'test1'
go
exec connectTableToTest 'Station_Test', 'test1', 1000, 1
go
exec connectViewToTest 'getStateGroups', 'test1'
go

create or alter procedure populateTableStation_Test (@rows int) as
    while @rows > 0 begin
        insert into STATION_TEST
			(id, city, state, lat_n, long_w) 
		values 
			(@rows, 'Testing', 'Name', floor(rand()*100), floor(rand()*100))
        set @rows = @rows-1
    end
go

exec populateTableState_Test 10
execute runTest 'test1'

select * from STATION_TEST
select * from getStateGroups
select * from TestRuns

