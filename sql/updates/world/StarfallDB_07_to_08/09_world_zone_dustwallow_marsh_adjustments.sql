-- Deletes creature Zelfrax (id: 23864, guid: 738348) in zone: 15, area: 497
DELETE FROM `creature` WHERE `guid` = 738348; DELETE FROM creature_addon WHERE guid = 738348;

-- Deletes creature Zelfrax (id: 23864, guid: 738359) in zone: 15, area: 497
DELETE FROM `creature` WHERE `guid` = 738359; DELETE FROM creature_addon WHERE guid = 738359;

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=23864;