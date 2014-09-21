REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(36797, 69196),
(36798, 69196),
(36698, 69196);

UPDATE `creature` SET `phaseMask`= 18432 WHERE `phaseMask`= 18408 AND `map`= 654;
UPDATE `gameobject` SET `phaseMask`= 18432 WHERE `phaseMask`= 18408 AND `map`= 654;

-- Deletes creature Lord Darius Crowley (id: 35566, guid: 801935) in zone: 4755, area: 4761
DELETE FROM `creature` WHERE `guid` = 801935; DELETE FROM creature_addon WHERE guid = 801935;

UPDATE `creature` SET `phaseMask`= 32768 WHERE `id` IN (28332, 38210, 38192, 38464, 38420, 38348, 38377, 38331, 38473, 38469, 38615, 44388) AND `map`= 654;
