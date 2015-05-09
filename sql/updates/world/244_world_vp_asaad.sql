UPDATE `creature_template` SET `mechanic_immune_mask`=667893759 WHERE `entry` IN (43875, 43876);

DELETE FROM `creature_template_addon` WHERE `entry` = '47000';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(47000, '87514');