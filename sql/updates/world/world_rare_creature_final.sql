UPDATE `creature_template` SET `faction`=14 WHERE `entry`=56081;

DELETE FROM `creature` WHERE `guid` = '842952';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842952, 56081, 560, 3, 1, 0, 0, 2116.83, 708.681, 30.2834, 4.18662, 7200, 15, 0, 651, 0, 1, 0, 0, 0);

UPDATE `creature` SET `phaseMask`=1, `spawndist`=15, `MovementType`=1 WHERE `guid`=739051;

-- Caliph Scorpidsting
SET @ENTRY := 44750;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79443,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Sand Step"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,21000,21000,11,79443,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sand Step"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,20000,20000,11,744,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Poison");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=770386;

-- Two-Toes
SET @ENTRY := 44224;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,34827,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Water Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,12500,14500,11,78542,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Splash");