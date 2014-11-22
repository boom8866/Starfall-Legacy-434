UPDATE `creature_template` SET `mingold`=20000, `maxgold`=20100 WHERE `entry`=39705;
UPDATE `creature_template` SET `ScriptName`='npc_shadow_of_obsidius' WHERE `entry`=40817;

-- Position update for Ascendant Lord Obsidius (id: 39705) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 351.171, `position_y` = 561.383, `position_z` = 66.007, `orientation`= 3.229 WHERE `guid` = 778482;

-- Position update for Twilight Element Warden (id: 40017) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 344.654, `position_y` = 579.868, `position_z` = 66.006, `orientation`= 3.771 WHERE `guid` = 778510;

-- Position update for Twilight Element Warden (id: 40017) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 346.400, `position_y` = 539.569, `position_z` = 66.006, `orientation`= 2.703 WHERE `guid` = 778511;

-- Position update for Shadow of Obsidius (id: 40817) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 347.704, `position_y` = 551.845, `position_z` = 66.007, `orientation`= 3.193 WHERE `guid` = 778484;

-- Position update for Shadow of Obsidius (id: 40817) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 346.844, `position_y` = 568.503, `position_z` = 66.007, `orientation`= 3.429 WHERE `guid` = 778483;

-- Position update for Shadow of Obsidius (id: 40817) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 341.536, `position_y` = 560.037, `position_z` = 66.007, `orientation`= 3.256 WHERE `guid` = 778515;

UPDATE `creature_template_addon` SET `auras`='76164 76167' WHERE `entry` IN (40817);

DELETE FROM `creature_template_addon` WHERE `entry` = '40818';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(40818, '76164 76167');