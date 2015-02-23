DELETE FROM `spell_area` WHERE  `spell`=73523 AND `area`=5692 AND `quest_start`=0 AND `aura_spell`=0 AND `racemask`=16 AND `gender`=2;

-- Agatha
SET @ENTRY := 49044;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24959,0,0,0,11,73524,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Cast Valkyr Resurrection on Player"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24959,0,0,0,28,73523,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Remove Rigor Mortis");