-- Earthguard Sentinel
SET @ENTRY := 42792;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,10000,10000,10000,10000,11,78154,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bloodlust"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,4000,3000,4000,11,78144,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Stormstrike"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,2,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,49,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Invoker");

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746177) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746177; DELETE FROM creature_addon WHERE guid = 746177;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746179) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746179; DELETE FROM creature_addon WHERE guid = 746179;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746187) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746187; DELETE FROM creature_addon WHERE guid = 746187;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746049) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746049; DELETE FROM creature_addon WHERE guid = 746049;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746214) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746214; DELETE FROM creature_addon WHERE guid = 746214;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746145) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746145; DELETE FROM creature_addon WHERE guid = 746145;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746122) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746122; DELETE FROM creature_addon WHERE guid = 746122;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746253) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746253; DELETE FROM creature_addon WHERE guid = 746253;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746102) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746102; DELETE FROM creature_addon WHERE guid = 746102;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746215) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746215; DELETE FROM creature_addon WHERE guid = 746215;