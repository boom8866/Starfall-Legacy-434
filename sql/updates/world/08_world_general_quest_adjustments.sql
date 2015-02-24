UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=77717;

DELETE FROM `creature_text` WHERE `entry`=44120;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44120,0,0,'Silence, idiot.',12,0,100,0,0,0,'Comment'),
(44120,1,0,'Hear anything interesting? Your little revelation about me is about to cost your life.',12,0,100,0,0,0,'Comment'),
(44120,2,0,'The Twilight\'s Hammer has agents everywhere! Kill me and a dozen take my place!',12,0,100,0,0,0,'Comment'),
(44120,3,0,'My powers of sight... I beheld the future... I have seen what is to come...',12,0,100,0,0,0,'Comment'),
(44120,4,0,'This world unravels. If you could see the horrors I have seen...',12,0,100,0,0,0,'Comment'),
(44120,5,0,'To serve is madness, but defiance ... impossible!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mechanic_immune_mask`=617299967 WHERE `entry`=42918;