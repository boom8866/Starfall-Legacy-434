11598
44329
47630

-- Twilight Jailer
SET @ENTRY := 47630;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,30,0,500,1000,600000,600000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text OOC"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,4500,12000,13000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,9000,18000,22000,11,11971,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Sunder Armor"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,0,0,1,0,0,0,0,11,47621,30,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Prisoner"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,0,0,1,0,0,0,0,15,206742,30,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Cage"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,0,0,1,0,0,0,0,15,206743,30,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Cage");

-- Stickbone Berserker
SET @ENTRY := 44329;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,14,82595,204966,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Animus"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,0,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Random Move"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,0,0,1,0,0,0,0,14,82618,204966,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Animus");

-- Risen Guardian
SET @ENTRY := 11598;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,37600,71200,14300,32700,11,7068,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - Combat - Cast Veil of Shadow"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,2,12500,28100,11900,37000,11,16583,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - Combat - Cast Shadow Shock"),
(@ENTRY,@SOURCETYPE,2,0,0,0,60,2,12300,45800,6000,34100,11,7289,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - Combat - Cast Shrink"),
(@ENTRY,@SOURCETYPE,3,0,0,0,60,2,24100,41300,20300,38100,11,11443,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - Combat - Cast Cripple"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,3,0,40,0,0,11,4974,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - 40% HP - Cast Wither Touch"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,2,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Data Set 0 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,2,0,2,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Data Set 0 1 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,2,0,3,0,0,22,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Data Set 0 1 - Set Phase 3"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,2,0,4,0,0,22,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Data Set 0 1 - Set Phase 4"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,2,0,5,0,0,22,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Data Set 0 1 - Set Phase 5"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,2,0,6,0,0,22,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Data Set 0 1 - Set Phase 6"),
(@ENTRY,@SOURCETYPE,11,0,6,1,100,2,0,0,0,0,45,0,1,0,0,0,0,14,177372,100,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Death - Set Data on go"),
(@ENTRY,@SOURCETYPE,12,0,6,2,100,2,0,0,0,0,45,0,1,0,0,0,0,14,177377,100,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Death - Set Data on go"),
(@ENTRY,@SOURCETYPE,13,0,6,4,100,2,0,0,0,0,45,0,1,0,0,0,0,14,177371,100,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Death - Set Data on go"),
(@ENTRY,@SOURCETYPE,14,0,6,8,100,2,0,0,0,0,45,0,1,0,0,0,0,14,177375,100,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Death - Set Data on go"),
(@ENTRY,@SOURCETYPE,15,0,6,16,100,2,0,0,0,0,45,0,1,0,0,0,0,14,177373,100,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Death - Set Data on go"),
(@ENTRY,@SOURCETYPE,16,0,6,32,100,2,0,0,0,0,0,0,1,0,0,0,0,14,177376,100,0,0.0,0.0,0.0,0.0,"Risen Guardian - On Death - Set Data on go");