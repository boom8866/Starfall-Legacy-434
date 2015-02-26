UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=771008;

SET @OGUID := 226662;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+5;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 207251, 0, 1, 128, -2773.67, -5345.86, 173.715, 0.932536, 0, 0, 0.449556, 0.893252, 300, 0, 1),
(@OGUID+1, 207251, 0, 1, 128, -2777.17, -5350.58, 174.066, 0.932536, 0, 0, 0.449556, 0.893252, 300, 0, 1),
(@OGUID+2, 207251, 0, 1, 128, -2780.29, -5338.71, 173.714, 0.527782, 0, 0, 0.260839, 0.965382, 300, 0, 1),
(@OGUID+3, 207251, 0, 1, 128, -2775.46, -5348.27, 173.913, 0.932536, 0, 0, 0.449556, 0.893252, 300, 0, 1),
(@OGUID+4, 207251, 0, 1, 128, -2785.27, -5341.61, 173.802, 0.527782, 0, 0, 0.260839, 0.965382, 300, 0, 1),
(@OGUID+5, 207251, 0, 1, 128, -2782.85, -5340.2, 173.74, 0.527782, 0, 0, 0.260839, 0.965382, 300, 0, 1);