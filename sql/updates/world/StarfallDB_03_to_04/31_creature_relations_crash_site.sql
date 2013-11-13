DELETE FROM `creature_questrelation` WHERE `quest` = '9289';
DELETE FROM `creature_questrelation` WHERE `quest` = '9287';
DELETE FROM `creature_questrelation` WHERE `quest` = '9288';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
(16503, 9289),
(16501, 9287),
(16499, 9288);

DELETE FROM `creature_involvedrelation` WHERE `quest` = '9289';
DELETE FROM `creature_involvedrelation` WHERE `quest` = '9287';
DELETE FROM `creature_involvedrelation` WHERE `quest` = '9288';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
(16503, 9289),
(16501, 9287),
(16499, 9288);

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE  `entry`=16971;