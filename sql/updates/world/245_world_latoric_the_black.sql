-- Lathoric the Black
SET @ENTRY := 8391;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,20000,20000,20000,20000,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corruption"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,4000,4000,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,8391,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,8391,0,0,45,0,1,0,0,0,0,10,763321,8400,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Obsidion"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,8391,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Hostile"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,8391,0,0,49,14,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Attack Player"),
(@ENTRY,@SOURCETYPE,8,0,7,0,100,0,0,0,0,0,0,0,0,0,0,0,0,11,0,150,0,0.0,0.0,0.0,0.0,"On Evade - Respawn All"),
(@ENTRY,@SOURCETYPE,9,0,7,0,100,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Respawn Self"),
(@ENTRY,@SOURCETYPE,10,0,7,0,100,0,0,0,0,0,2,120,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Faction");