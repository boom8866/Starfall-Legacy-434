DELETE FROM `creature_template_addon` WHERE `entry` = '34544';
INSERT INTO `creature_template_addon` (`entry`, `mount`) VALUES
(34544, 29254);

-- Deletes creature Fez (id: 34543, guid: 147708) in zone: 17, area: 1699
DELETE FROM `creature` WHERE `guid` = 147708; DELETE FROM creature_addon WHERE guid = 147708;