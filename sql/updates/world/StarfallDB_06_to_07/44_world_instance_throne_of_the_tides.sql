UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry` IN (41139, 40584);
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry` IN (41096, 49090, 39616, 49085, 41139, 40584);

DELETE FROM `creature_text` WHERE `entry`=40586;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40586,0,0,'You have interfered with our plans for the last time, mortals!',14,0,0,5,0,18886,'SAY_AGGRO'),
(40586,1,0,'Take arms, minions! Rise from the icy depths!',14,0,0,5,0,18892,'SAY_66_PRECENT'),
(40586,2,0,'Destroy these intruders! Leave them for the great dark beyond!',14,0,0,5,0,18893,'SAY_33_PRECENT'),
(40586,3,0,'The abyss awaits!',14,0,0,5,0,18888,'SAY_KILL_1'),
(40586,4,0,'Depths take you!',14,0,0,5,0,18887,'SAY_KILL_2'),
(40586,5,0,'Ulthok... stop them... ',14,0,0,5,0,18889,'SAY_DEATH');

UPDATE `creature` SET `position_z`=807.94 WHERE `guid`=781206;
UPDATE `creature` SET `position_z`=245.27 WHERE `guid`=781240;
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry` IN (51395, 51391);