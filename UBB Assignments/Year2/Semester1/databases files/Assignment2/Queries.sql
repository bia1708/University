use Spotify
go

-- INSERTS

insert into Artists
values (1, 'Drake', 100000);

insert into Artists
values (2, 'Beyonce', 200000);

insert into Artists
values (3, 'Michael Jackson', 1200000);

insert into Artists
values (4, 'Lady Gaga', 300000);

insert into Artists
values (5, 'Bee Gees', 21000);



insert into Genres
values (1, 'Rap');

insert into Genres
values (2, 'Pop');

insert into Genres
values (3, 'Disco');

insert into Genres
values (4, 'Latin');



insert into Songs
values (1, 'Overdrive', 3200, 1);

insert into Songs
values (2, 'Chicago', 2400, 2);

insert into Songs
values (3, 'Just Dance', 2700, 2);

insert into Songs
values (4, 'Partition', 3100, 2);

insert into Songs
values (5, 'You Should Be Dancing', 3000, 3);

/*
insert into Songs
values (6, 'Telephone', 2700, 5);   -> violates referential integrity constraints
*/

insert into Songs
values (6, 'Telephone', 2700, 2);

insert into Songs
values (7, 'One Dance', 4100, 1);



insert into Albums
values (1, 'Certified Lover Boy', 1);

insert into Albums
values (2, 'Scream', 3);


insert into Users
values (1, 'Angela', 31);

insert into Users
values (2, 'Michael', 35);

insert into Users
values(3, 'Jim', 27);


insert into Playlists
values (1, 'daily vibes', 3)

insert into Playlists
values(2, 'gym sesh', 2)

insert into Playlists
values (3, 'rap nervos', 1)

insert into Playlists
values (4, 'no songs?', 2)


insert into PlaylistsSongs
values (1, 6)

insert into PlaylistsSongs
values (1, 7)

insert into PlaylistsSongs
values (2, 3)

insert into PlaylistsSongs
values (3, 1)

insert into PlaylistsSongs
values(1, 3)



insert into SubscriptionPlan
values (1, 'paid')

insert into SubscriptionPlan
values (2, 'free')

insert into SubscriptionPlan
values(3, 'paid')

insert into Credentials
values(1, 'angela@mail.com')

insert into Credentials
values(2, 'michael@email.com');

insert into Credentials
values(3, 'jim@mail.com')



insert into ArtistsSong
values (1, 1);

insert into ArtistsSong
values (2, 4);

insert into ArtistsSong
values (3, 2);

insert into ArtistsSong
values (4, 3);

insert into ArtistsSong
values (5, 5);

insert into ArtistsSong
values (2, 6);

insert into ArtistsSong
values (4, 6);

insert into ArtistsSong
values (1, 7);

--UPDATES

update Songs
set length=3300
WHERE sid = 1;

update Genres
set name='Latino'
WHERE gid = 4;

update Artists
set monthly_listeners=1300000
WHERE aid = 3;

--DELETS

delete from ArtistsSong where sid=2;
delete from Songs where length<=2500;

--a)
select title from Songs
union
select name from Artists
where Artists.monthly_listeners>300000 or Artists.name='Bee Gees';

select name from Genres
union
select title from Songs
where Songs.gid=1 or Songs.gid=2;

--b)
select title from Songs
where Songs.gid in (1,2)
intersect
select title from Songs
where Songs.length>=3000;

select name from Artists
where Artists.aid in (1,2)
intersect
select name from Artists
where Artists.monthly_listeners>=300000;

--c)
select title from Songs
where gid in (1,2)
except
select title from Songs 
where length>=3000;

select name from Artists
where Artists.aid not in (1,2)
except
select name from Artists
where Artists.monthly_listeners>=300000;

--d)
select Users.name, Credentials.email, SubscriptionPlan.type 
from ((Users
INNER JOIN Credentials ON Credentials.uid = Users.uid)
INNER JOIN SubscriptionPlan ON SubscriptionPlan.uid = Users.uid);

select Playlists.title, Songs.title, Artists.name
from (((( Playlists
LEFT JOIN PlaylistsSongs ON PlaylistsSongs.pid = Playlists.pid)
LEFT JOIN Songs ON Songs.sid=PlaylistsSongs.sid)
LEFT JOIN ArtistsSong ON ArtistsSong.sid = Songs.sid)
LEFT JOIN Artists ON Artists.aid = ArtistsSong.aid)

select Playlists.title, Songs.title
from (( Playlists
RIGHT JOIN PlaylistsSongs ON PlaylistsSongs.pid = Playlists.pid)
RIGHT JOIN Songs ON Songs.sid=PlaylistsSongs.sid)

select Users.name, Songs.title
from (((Users
FULL JOIN Playlists ON Playlists.uid = Users.uid)
FULL JOIN PlaylistsSongs ON PlaylistsSongs.pid = Playlists.pid)
FULL JOIN Songs ON Songs.sid=PlaylistsSongs.sid)

--e)
SELECT title FROM Songs WHERE gid IN 
	(SELECT gid FROM Genres WHERE gid = 2); -- show all pop songs

select title from Albums where alid IN
	(select alid from Albums where aid IN
	(select aid from Artists where monthly_listeners > 200000)); -- albums whose artists have more than 200000 listeners


--f)
SELECT name FROM Users
WHERE EXISTS
(SELECT type FROM SubscriptionPlan WHERE Users.uid = SubscriptionPlan.uid AND type = 'free'); -- shows users with free subscription

SELECT name, age FROM Users
WHERE EXISTS
(SELECT type FROM SubscriptionPlan WHERE Users.uid = SubscriptionPlan.uid AND type = 'paid');

--g)
select A.name from
(select avg(monthly_listeners) as avg_listeners from Artists) as avg, Artists as A
where  A.monthly_listeners > avg.avg_listeners; -- shows artists with more monthly listeners than the avg

select S.title from
(select avg(length) as avg_length from Songs) as avg, Songs as S
where  S.length < avg.avg_length; -- shows songs with smaller length than the avg

--h)
SELECT COUNT(uid), name FROM Users
GROUP BY name
HAVING COUNT(uid) = 1;

SELECT count(sid), title FROM (PlaylistsSongs
INNER JOIN Playlists ON Playlists.pid = PlaylistsSongs.pid)
GROUP BY Playlists.title
HAVING COUNT(sid) >= 2; --playlists with more than two songs

select count(PlaylistsSongs.sid), title FROM (PlaylistsSongs
INNER JOIN Songs ON Songs.sid = PlaylistsSongs.sid)
Group BY Songs.title
having count(PlaylistsSongs.sid) >= 2; -- songs that appear more than twice in playlists

select count(pid), name from(Users
INNER JOIN Playlists on Users.uid = Playlists.uid)
group by name
having count(Playlists.pid) > 1; --users with more than 1 playlist

--i)
select name, age from Users 
where age > any (
	select age from Users) -- users other than the youngest

select name, age from Users 
where age >= all (
	select age from Users) --oldest user

select name, age from Users 
where age < any (
	select age from Users) -- users other than the oldest

select name, age from Users 
where age <= all (
	select age from Users) --youngest user

select name, age from Users 
where age = (
	select min(age) from Users) --youngest user

select name, age from Users 
where age = (
	select max(age) from Users) -- oldest user

select name, age from Users 
where age not in (
	select min(age) from Users) -- users other than the youngest

select name, age from Users
where age not in (
	select max(age) from Users) -- users other than the oldest