
SET @OGUID := 778966;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+10;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 188215, 0, 1, 1, -8771.236, 422.2639, 104.004, 4.24115, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+1, 188215, 0, 1, 1, -8779.444, 432.4097, 105.3157, 4.869471, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+2, 188215, 0, 1, 1, -8775.976, 424.4566, 105.3157, 4.799657, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+3, 188215, 0, 1, 1, -8781.12, 420.3802, 105.3157, 5.98648, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+4, 188215, 0, 1, 1, -8788.16, 425.4879, 105.3157, 5.93412, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+5, 188215, 0, 1, 1, -8802.316, 343.9184, 107.1326, 3.106652, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+6, 188215, 0, 1, 1, -8814.497, 354.9618, 107.1324, 4.852017, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: Old Town)
(@OGUID+7, 188215, 0, 1, 1, -8699.701, 838.5643, 99.2015, 2.129301, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: The Canals)
(@OGUID+8, 188215, 0, 1, 1, -8693.524, 843.6129, 99.00308, 2.809975, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: The Canals)
(@OGUID+9, 188215, 0, 1, 1, -8705.297, 842.8941, 98.76855, 0.4886912, 0, 0, 0, 1, 120, 255, 1), -- Collision PC Size (Area: The Canals)
(@OGUID+10, 188215, 0, 1, 1, -8696.643, 841.1823, 98.76855, 2.251473, 0, 0, 0, 1, 120, 255, 1); -- Collision PC Size (Area: The Canals)
