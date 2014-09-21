UPDATE `creature_template` SET `spell2`=53110, `spell3`=0 WHERE `entry`=28670;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry` IN (193052, 193053);

DELETE FROM `spell_target_position` WHERE `id` = '58421';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(58421, 0, -9143.58, 375.103, 90.6907, 0.64);

UPDATE `creature_template` SET `InhabitType`=4, `HoverHeight`=1 WHERE `entry`=28534;