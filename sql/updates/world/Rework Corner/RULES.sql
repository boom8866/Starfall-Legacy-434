-- Default SQL usage

-- Spawnings
/*
Every spawning sql for creatures and gameobjects have a pre defined guid to prevent dynamic overstacking at multibatching
Followig default style is duty to use!
*/

-- For creatures:
SET @CGUID := xxxxx
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+X;
INSERT INTO `creature` (`guid`, bla, bla,...) VALUES
(@CGUID+0, xx, xx, xx, xx,...),
(@CGUID+1, xx, xx, xx, xx,...),
(@CGUID+2, xx, xx, xx, xx,...);

-- For gameobjects
SET @OGUID := xxxxx
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+X;
INSERT INTO `gameobject` (`guid`, bla, bla,...) VALUES
(@OGUID+0, xx, xx, xx, xx,...),
(@OGUID+1, xx, xx, xx, xx,...),
(@OGUID+2, xx, xx, xx, xx,...);

-- Update queries always use ` ` for column names. Values wont get any ' ' or "" (except strings like script_names)
-- Example:

UPDATE `creature_template` SET `speed_walk`= 1, `scriptname`= 'npc_this_is_an_example' WHERE `entry`= xxxx;

-- Insert queries always use a delete statement before.
DELETE FROM xxxx WHERE xxxxx = / IN (xxxxx) xxxx;
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES
(xxxx, xxx, xx, xxx);

-- Instead of using
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES (xxxx, xxx, xx, xxx);
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES (xxxx, xxx, xx, xxx);
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES (xxxx, xxx, xx, xxx);
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES (xxxx, xxx, xx, xxx);
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES (xxxx, xxx, xx, xxx);
INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES (xxxx, xxx, xx, xxx);

-- you will use following style to improve the performance:

INSERT INTO xxxx (xxx, xxx, xx, xx) VALUES
(xxxx, xxx, xx, xxx),
(xxxx, xxx, xx, xxx),
(xxxx, xxx, xx, xxx),
(xxxx, xxx, xx, xxx),
(xxxx, xxx, xx, xxx),
(xxxx, xxx, xx, xxx);

