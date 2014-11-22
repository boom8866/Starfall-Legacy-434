SET @CGUID := 701927;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+4;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 43460, 0, 1, 1, 0, 0, -9462.34, -2827.47, 65.2765, 2.99298, 300, 0, 0, 1780, 0, 0, 0, 0, 0),
(@CGUID+1, 43461, 0, 1, 1, 0, 0, -9462.81, -2825.72, 65.2779, 3.96295, 300, 0, 0, 1930, 0, 0, 0, 0, 0),
(@CGUID+2, 43459, 0, 1, 1, 0, 0, -9465.84, -2826.27, 65.2774, 5.47483, 300, 0, 0, 1930, 0, 0, 0, 0, 0),
(@CGUID+3, 43462, 0, 1, 1, 0, 0, -9466.22, -2828.85, 65.2772, 0.639062, 300, 0, 0, 1930, 0, 0, 0, 0, 0),
(@CGUID+4, 43458, 0, 1, 1, 0, 0, -9463.38, -2828.94, 65.2777, 2.27281, 300, 0, 0, 3495, 0, 0, 0, 0, 0);

UPDATE `creature_template_addon` SET `bytes1`=8, `emote`=0 WHERE `entry`=43458;