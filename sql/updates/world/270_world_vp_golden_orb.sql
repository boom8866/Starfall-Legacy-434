SET @CGUID := 836000;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+6;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 51157, 657, 3, 1, 33553, 0, -763.62, 411.309, 682.691, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0),
(@CGUID+1, 51157, 657, 3, 1, 33553, 0, -1046.92, 419.465, 698.126, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0),
(@CGUID+2, 51157, 657, 3, 1, 33553, 0, -1002.1, 493.976, 662.576, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0),
(@CGUID+3, 51157, 657, 3, 1, 33553, 0, -595.188, -172.184, 616.613, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0),
(@CGUID+4, 51157, 657, 3, 1, 33553, 0, -749.472, 74.6823, 631.196, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0),
(@CGUID+5, 51157, 657, 3, 1, 33553, 0, -1032.68, -38.3854, 705.917, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0),
(@CGUID+6, 51157, 657, 3, 1, 33553, 0, -1054.7, -21.9479, 705.906, 0, 7200, 0, 0, 14921, 0, 0, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '51157';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(51157, '94316');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=51157 AND `spell_id`=94316;
UPDATE `creature_template` SET `modelid1`=33553, `npcflag`=1,  `InhabitType`=4, `ScriptName`='npc_vp_golden_orb' WHERE `entry`=51157;