UPDATE `creature_template` SET `InhabitType`=5 WHERE `entry`=43875;

-- Deletes creature Skyfall Star (id: 52019, guid: 778286) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778286; DELETE FROM creature_addon WHERE guid = 778286;

-- Deletes creature Skyfall Star (id: 52019, guid: 778283) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778283; DELETE FROM creature_addon WHERE guid = 778283;

-- Deletes creature Skyfall Star (id: 52019, guid: 778281) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778281; DELETE FROM creature_addon WHERE guid = 778281;

-- Deletes creature Skyfall Star (id: 52019, guid: 778288) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778288; DELETE FROM creature_addon WHERE guid = 778288;

-- Deletes creature Skyfall Star (id: 52019, guid: 778282) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778282; DELETE FROM creature_addon WHERE guid = 778282;

-- Deletes creature Skyfall Star (id: 52019, guid: 778284) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778284; DELETE FROM creature_addon WHERE guid = 778284;

-- Deletes creature Skyfall Star (id: 52019, guid: 778285) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778285; DELETE FROM creature_addon WHERE guid = 778285;

-- Deletes creature Skyfall Star (id: 52019, guid: 778280) in zone: 5035, area: 5035
DELETE FROM `creature` WHERE `guid` = 778280; DELETE FROM creature_addon WHERE guid = 778280;

UPDATE `creature_template` SET `InhabitType`=4, `flags_extra`=128 WHERE `entry`=47000;
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=46387;
UPDATE `creature_template` SET `exp`=3, `unit_class`=8, `ScriptName`='npc_vp_skyfall_star' WHERE `entry`=52019;