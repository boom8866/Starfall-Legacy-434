UPDATE `creature_template` SET `flags_extra`=64 WHERE `entry` IN (39804, 40252, 48900, 48897);
UPDATE `creature_template` SET `DamageModifier`=6 WHERE `entry`=40998;

-- King Moltron
SET @ENTRY := 40998;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,8000,8000,16000,18000,11,80600,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Stomp"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,33,40998,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete AoE");

-- Azralon the Gatekeeper
SET @ENTRY := 40814;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4800,7900,12300,14900,11,80606,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Evil Cleave"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,50,0,0,12,40955,4,120000,0,0,0,8,0,0,0,4259.22,-3327.75,1019.49,4.85,"On Health 50% - Summon Goldrinn"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,33,0,1,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit AoE");