UPDATE `creature` SET `orientation`= 3.141593 WHERE `id`= 53494;
UPDATE `creature` SET `orientation`= 3.193953 WHERE `id`= 53575;
UPDATE `creature` SET `position_z`= 88.42146, `orientation`= 3.735005 WHERE `id`= 52498;

UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry` IN (52498, 53545, 53617);
UPDATE `creature_template` SET `unit_flags`= unit_flags|0x00000004 WHERE `entry` IN (53545, 53617);
REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(52498, 0, 0x3000000, 0x1, ''); -- Beth'tilac
