USE Spotify
GO

--ALTER TABLE Artists
--ADD foo INT;
--create table NUMAIAMIDEI(
--	id int not null) 
--ALTER TABLE NUMAIAMIDEI
--ADD CONSTRAINT PK_NU PRIMARY KEY (id);
--alter table NUMAIAMIDEI 
--add prid int not null
--ALTER TABLE NUMAIAMIDEI
--ADD CONSTRAINT FK_NU
--FOREIGN KEY (prid) REFERENCES Producers(prid);


-- a. modify the type of column

CREATE OR ALTER PROCEDURE changeUserAgeType                                          --1
AS
BEGIN
	ALTER TABLE Users
	ALTER COLUMN age VARCHAR(10)
	PRINT 'ALTER TABLE Users FROM INT TO VARCHAR'
END
GO

-- a. undo


CREATE OR ALTER PROCEDURE UNDOchangeUserAgeType
AS
BEGIN
	ALTER TABLE Users
	ALTER COLUMN age INT
	PRINT 'ALTER TABLE Users FROM VARCHAR TO INT'
END
GO


-- b. add/remove a column

CREATE OR ALTER PROCEDURE removeArtistsfoo                                                 --2
AS
BEGIN
	ALTER TABLE Artists
	DROP COLUMN foo
	PRINT 'ALTER TABLE Artists DROP COLUMN foo from Artists'
END
GO

-- b. undo

CREATE OR ALTER PROCEDURE UNDOremoveArtistsfoo
AS
BEGIN
	ALTER TABLE Artists
	ADD foo INT
	PRINT 'ALTER TABLE Artists ADD COLUMN foo to Artists'
END
GO


CREATE OR ALTER PROCEDURE addDefaultConstraintArtistsfoo                                    --3
AS
BEGIN
	ALTER TABLE Artists
	ADD CONSTRAINT default_foo DEFAULT 1 FOR default_foo
	PRINT 'ALTER TABLE Artists ADD CONSTRAINT DEFAULT 1 FOR foo'
END
GO


-- c. undo

CREATE OR ALTER PROCEDURE UNDOaddDefaultConstraintArtistsfoo
AS
BEGIN
	ALTER TABLE Artists
	DROP CONSTRAINT default_foo
	PRINT 'ALTER TABLE Artists DROP CONSTRAINT DEFAULT 1 FOR foo'
END
GO


CREATE OR ALTER PROCEDURE removePrimaryKeyNU                                               --4
AS
BEGIN
	ALTER TABLE NUMAIAMIDEI
	DROP CONSTRAINT PK_NU
	PRINT 'ALTER TABLE NUMAIAMIDEI DROP CONSTRAINT NU from NUMAIAMIDEI'
END
GO

-- d. undo

CREATE OR ALTER PROCEDURE UNDOremovePrimaryKeyNU
AS
BEGIN
	ALTER TABLE NUMAIAMIDEI
	ADD CONSTRAINT PK_NU PRIMARY KEY (id)
	PRINT 'ALTER TABLE NUMAIAMIDEI ADD CONSTRAINT PK_NU PRIMARY KEY (id)'
END
GO


-- e. add/remove a candidate key

CREATE OR ALTER PROCEDURE addCandidateKeyNUMAIAMIDEIfoo                                           --5
AS
BEGIN
	ALTER TABLE NUMAIAMIDEI
	ADD CONSTRAINT UQ_foo UNIQUE(foo)
	PRINT 'ALTER TABLE Artists ADD CONSTRAINT UQ_foo UNIQUE(foo)'
END
GO

-- e. undo

CREATE OR ALTER PROCEDURE UNDOaddCandidateKeyNUMAIAMIDEIfoo
AS
BEGIN
	ALTER TABLE NUMAIAMIDEI
	DROP CONSTRAINT UQ_foo
	PRINT 'ALTER TABLE Artists DROP CONSTRAINT UQ_foo'
END
GO


-- f. add/remove a foreign key

CREATE OR ALTER PROCEDURE removeForeignKeyPodcastsprid                                       --6
AS
BEGIN 
	ALTER TABLE NUMAIAMIDEI
	DROP CONSTRAINT FK_NU
	PRINT 'ALTER TABLE NUMAIAMIDEI DROP CONSTRAINT prid'
END 
GO

-- f. undo

CREATE OR ALTER PROCEDURE UNDOremoveForeignKeyPodcastsprid
AS
BEGIN
	ALTER TABLE NUMAIAMIDEI
	ADD CONSTRAINT FK_NU FOREIGN KEY (prid) REFERENCES Producers(prid)
	PRINT 'ALTER TABLE NUMAIAMIDEI ADD CONSTRAINT prid FOREIGN KEY (prid) REFERENCES Producers(prid)'
END
GO


-- g. create/drop a table

CREATE OR ALTER PROCEDURE createTable                                                   --7
AS
BEGIN
	CREATE TABLE Something(
	SID int NOT NULL PRIMARY KEY)
	PRINT 'CREATE TABLE Something'
END
GO

-- g. undo

CREATE OR ALTER PROCEDURE UNDOcreateTable
AS
BEGIN
	DROP TABLE IF EXISTS Something
	PRINT 'DROP TABLE IF EXISTS Something'
END
GO



CREATE TABLE VersionHistory
(
    VERSION INT
)
INSERT INTO VersionHistory VALUES (0) -- first version

CREATE TABLE ProcedureTable
(
    DoProcedure VARCHAR(100),
    UndoProcedure VARCHAR(100),
    Version INT PRIMARY KEY
)
GO


INSERT INTO ProcedureTable(DoProcedure,UndoProcedure,Version)
VALUES ('changeUserAgeType', 'UNDOchangeUserAgeType', 1),
('removeArtistsfoo', 'UNDOremoveArtistsfoo', 2),
('addDefaultConstraintArtistsfoo','UNDOaddDefaultConstraintArtistsfoo', 3),
('removePrimaryKeyNU','UNDOremovePrimaryKeyNU', 4),
('addCandidateKeyNUMAIAMIDEIfoo', 'UNDOaddCandidateKeyNUMAIAMIDEIfoo', 5),
('removeForeignKeyPodcastsprid', 'UNDOremoveForeignKeyPodcastsprid', 6),
('createTable', 'UNDOcreateTable', 7)


GO
CREATE OR ALTER PROCEDURE goToVersion(@version INT)
AS
BEGIN
	DECLARE @currentVersion INT
	IF @version < 0 OR @version > 7   -- validate input
		BEGIN
			PRINT 'Version number must be smaller than 7 and greater or equal to 0!'
			RETURN
		END
	ELSE
		IF @version = @currentVersion -- check whether we are at the current version
			BEGIN
				PRINT 'This is the current version.'
				RETURN
			END
		ELSE -- we are at a random version
		DECLARE @currentProcedure NVARCHAR(50)
		SET @currentVersion = (SELECT version FROM VersionHistory)  -- get the current version of the database
		IF @currentVersion < @version -- if we are lower, exec the DOProcedures
			BEGIN
				WHILE @currentVersion < @version
					BEGIN
						PRINT 'Current version: ' +  CONVERT(varchar(10), @currentVersion)

						SET @currentProcedure = (SELECT DoProcedure
												FROM ProcedureTable
												WHERE Version = @currentVersion + 1)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion + 1
					END
			END
		ELSE -- if we are higher, exec the UndoProcedures
		IF @currentVersion > @version
			BEGIN
				WHILE @currentVersion > @version
					BEGIN
						PRINT 'Current version: ' + CONVERT(varchar(10), @currentVersion)

						SET @currentProcedure = (SELECT UndoProcedure
												FROM ProcedureTable
												WHERE version = @currentVersion)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion - 1

					END
			END
		UPDATE VersionHistory
			SET VERSION = @currentVersion
		PRINT 'Current version updated!'
		PRINT 'Reached desired version: ' + CONVERT(varchar(10), @currentVersion)
END

Select * FROM ProcedureTable

GO
EXEC goToVersion 7
EXEC goToVersion 7
EXEC goToVersion 5
EXEC goToVersion 2
EXEC goToVersion 0
EXEC goToVersion -1