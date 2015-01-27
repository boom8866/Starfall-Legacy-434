-- Crimsonborne Seer
SET @ENTRY := 39405;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,11,0,0,0,0,0,0,9,0,2,10,0.0,0.0,0.0,0.0,"IC - Cast Blazing Twilight Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,4,2000,2000,10000,10000,11,76332,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corrupted Flame");

UPDATE `creature_template` SET `mingold`=6367, `maxgold`=6367, `DamageModifier`=6 WHERE `entry`=39405;

-- Crimsonborne Warlord
SET @ENTRY := 39626;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,9500,14500,11,76679,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Disarming Blaze"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,76685,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Empowering Twilight");

-- Empowering Flames
SET @ENTRY := 41045;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,76692,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Empowering Twilight");

UPDATE `creature_template` SET `mingold`=6367, `maxgold`=6367, `DamageModifier`=12 WHERE `entry` IN (48652, 48610, 48667);
UPDATE `creature_template` SET `mingold`=6367, `maxgold`=6367 WHERE `entry`=48746;
