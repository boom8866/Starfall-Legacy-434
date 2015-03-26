UPDATE `gameobject` SET `spawnMask`=1 WHERE `id` IN (203133, 203136);

DELETE FROM `gameobject` WHERE `guid` IN (164853, 164854);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(164853, 207219, 644, 2, 1, -677.708, 339.788, 54.2874, 6.21337, 0, 0, 0, 1, 7200, 255, 1),
(164854, 207218, 644, 2, 1, -603.212, 339.951, 54.5611, 3.14159, 0, 0, 0, 1, 7200, 255, 1);