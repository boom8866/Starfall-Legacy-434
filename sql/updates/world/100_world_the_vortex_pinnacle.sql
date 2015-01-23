SET @OGUID := 781645;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+1;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
-- entrance portal visual
(@OGUID+0, 207372, 657, 3, 1, -325.592, 27.35414, 628.5861, 3.926996, 0, 0, 0.9238795, -0.3826835, 7200, 255, 1),
(@OGUID+1, 207373, 657, 3, 1, -325.592, 27.35414, 628.5861, 3.926996, 0, 0, 0.9238795, -0.3826835, 7200, 255, 1);
