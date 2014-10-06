UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=51239;

DELETE FROM `creature_template_addon` WHERE `entry` = '51239';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(51239, '90351');