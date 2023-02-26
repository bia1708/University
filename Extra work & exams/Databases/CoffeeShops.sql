create database CoffeeDB
go

use CoffeeDB
go

drop table Suppliers
drop table Employees
drop table CoffeeShops

create table CoffeeShops(
	csid int not null identity(1, 1),
	constraint PK_CS primary key(csid),
	name varchar(100) unique,
	city varchar(100),
	sid int not null,
	constraint FK_S foreign key(sid) references Suppliers(sid)
);

create table Employees(
	eid int not null identity(1, 1),
	constraint PK_E primary key(eid),
	csid int not null,
	constraint FK_CS foreign key(csid) references CoffeeShops(csid),
	first_name varchar(100),
	last_name varchar(100),
	job_title varchar(100),
	hire_date date
)

create table Coffees(
	cid int not null identity(1,1),
	constraint PK_C primary key(cid),
	name varchar(100),
	price int,
)

create table Suppliers(
	sid int not null identity(1, 1),
	constraint PK_S primary key(sid),
	name varchar(100),
	country varchar(100),
	email varchar(100)
)

create table SuppliersCoffee(
	sid int foreign key references Suppliers(sid) not null,
	cid int foreign key references Coffees(cid) not null,
	constraint PK_CCS primary key (sid, cid)
)

insert into Coffees values('name1', 10);
insert into Coffees values('name2', 20);
insert into Coffees values('name3', 30);
insert into Suppliers values('sup1', 'c1', 'em1');
insert into Suppliers values('sup2', 'c2', 'em2');
insert into Suppliers values('sup3', 'c3', 'em3');
insert into SuppliersCoffee values(1, 1)
insert into SuppliersCoffee values(1, 2)
insert into SuppliersCoffee values(1, 3)
insert into SuppliersCoffee values(2, 1)
insert into SuppliersCoffee values(2, 2)
insert into SuppliersCoffee values(3, 3)
insert into CoffeeShops values('Singing Beans', 'c1', 2)
insert into CoffeeShops values('name2', 'c2', 1)
insert into Employees values(1, 'ian', 'din', 'manager', '2007/03/01')
insert into Employees values(2, 'ion', 'din', 'manager', '2022/03/01')
insert into Employees values(1, 'iin', 'din', 'manager', '2018/03/01')


--b)
go
create or alter procedure AddCoffee @name varchar(5), @price int
as
begin
	insert into Coffees values (@name, @price)

	--get sid
	declare @sid int
	set @sid = (select top 1 Suppliers.sid from SuppliersCoffee join Suppliers on Suppliers.sid = SuppliersCoffee.sid
					group by Suppliers.sid
					order by count(SuppliersCoffee.cid) desc)
	
	--get cid
	declare @cid int
	set @cid = (select top 1 cid from Coffees order by cid DESC)

	insert into SuppliersCoffee values(@sid, @cid)

	update CoffeeShops
	set sid = @sid
	where name = 'Singing Beans'
end

exec AddCoffee @name='test2', @price=35
select * from Coffees
select * from SuppliersCoffee
select * from CoffeeShops

--c)
go
create or alter view testView as
select distinct top 3 Suppliers.country, Coffees.price from ((Coffees 
inner join SuppliersCoffee on Coffees.cid = SuppliersCoffee.cid)
inner join Suppliers on SuppliersCoffee.sid = Suppliers.sid)
group by Suppliers.country, Coffees.price
order by Coffees.price desc

go
select * from testView


--d)
go
create or alter function employees_with_xp(@xp int) returns table
as
return
	select concat(Employees.first_name, Employees.last_name) as name, Employees.hire_date from Employees
	group by Employees.first_name, Employees.last_name, Employees.hire_date
	having DATEDIFF(year, Employees.hire_date, '2022/01/21') > @xp

go
select * from dbo.employees_with_xp(0);
select * from Employees