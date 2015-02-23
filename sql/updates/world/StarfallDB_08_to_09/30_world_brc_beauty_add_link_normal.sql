-- Position update for Spot (id: 40011) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 133.381, `position_y` = 566.720, `position_z` = 76.393, `orientation`= 2.366 WHERE `guid` = 778504;

-- Position update for Beauty (id: 39700) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 86.942, `position_y` = 583.007, `position_z` = 76.480, `orientation`= 6.180 WHERE `guid` = 778476;

-- Position update for Lucky (id: 40008) in zone: 4926, area: 4926
UPDATE `creature` SET `position_x` = 121.645, `position_y` = 578.372, `position_z` = 76.436, `orientation`= 0.417 WHERE `guid` = 778502;

UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid` IN (778502, 778504);
