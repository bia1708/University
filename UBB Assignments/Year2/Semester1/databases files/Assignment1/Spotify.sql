create database Spotify
go

use Spotify
go


create table Artists (
	aid int primary key,
	name varchar(100) not null,
	monthly_listeners int,
	)

CREATE TABLE Albums (
	alid int primary key,
	title varchar(100) not null,
	aid int foreign key references Artists(aid) not null
	)
	

create table Genres (
	gid int primary key,
	name varchar(100) unique
	)
	

create table Songs (
	sid int primary key,
	title varchar(100) not null,
	length int not null,
	gid int foreign key references Genres(gid) not null
	)


create table ArtistsSong (
	aid int foreign key references Artists(aid) not null,
	sid int foreign key references Songs(sid) not null,
	constraint PK_ArtistsSong primary key(aid,sid)
	)


create table Users (
	uid int primary key,
	name varchar(100),
	age int not null
	)

create table Playlists (
	pid int primary key,
	title varchar(100) not null,
	uid int foreign key references Users(uid) not null
	)

create table SubscriptionPlan (
	uid int foreign key references Users(uid) not null,
	type varchar(100) not null default 'free',
	constraint PK_SubscriptionPlan primary key (uid)
	)

create table Credentials (
	uid int foreign key references Users(uid) not null,
	email varchar(50) not null,
	constraint PK_Credentials primary key (uid)
	)

create table Producers (
	prid int primary key,
	name varchar(100)
	)

create table Podcasts (
	poid int primary key,
	name varchar(100),
	prid int foreign key references Producers(prid) not null
	)


create table PlaylistsSongs (
	pid int foreign key references Playlists(pid) not null,
	sid int foreign key references Songs(sid) not null,
	constraint PK_PlaylistsSongs primary key(pid,sid)
	)





