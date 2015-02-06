UPDATE `creature_template` SET `DamageModifier`=15.8 WHERE `entry` IN (39425, 39428, 39788, 39587, 39731, 39732, 39378);
UPDATE `creature_template` SET `DamageModifier`=6.7 WHERE `entry` IN (41208, 40715, 41371, 41148, 48140, 40808, 40450, 40787, 40311, 48143, 40252, 40251, 39804, 39801, 39800, 39802, 39803, 48143, 41371, 41148, 39373, 39366, 39370, 40033, 40106);
UPDATE `creature_template` SET `DamageModifier`=8.4 WHERE `entry` IN (39801, 39800, 39802, 39803);
UPDATE `creature_template` SET `DamageModifier`=1.4 WHERE `entry`=39444;
UPDATE `creature_template` SET `DamageModifier`=3.2 WHERE `entry`=40458;

-- Flame Warden
SET @ENTRY := 39800;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,77273,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Lava Eruption"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,8000,16000,11,77241,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Raging Inferno"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4500,15000,8500,11250,11,77241,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lava Eruption");

-- Water Warden
SET @ENTRY := 39802;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,8000,7500,12500,11,54399,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Bubble");

-- Earth Warden
SET @ENTRY := 39801;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,12500,12500,11,77234,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rockwave"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,7500,10000,11000,11,77235,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Impale");

-- Air Warden
SET @ENTRY := 39803;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,7000,6000,12500,11,77334,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wind Shear");

-- Lifewarden Nymph
SET @ENTRY := 40715;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,7000,8000,12000,11,75961,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Entangling Shot"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,10000,10000,20000,25000,11,75940,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Tranquillity");