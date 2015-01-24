DELETE FROM `conditions` WHERE `SourceEntry` = '101847';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 101847, 0, 0, 31, 0, 3, 54510, 0, 0, 0, '', 'Targeting -> Baby');

-- Baby
SET @ENTRY := 54510;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,101847,1,0,0,33,54510,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,5,388,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Play Emote");

#UPDATE `quest_template` SET `RequiredSkillId` = '' WHERE `rewardskillid` ='';

-- Sig Nicious
SET @ENTRY := 23626;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,13000,13000,0,0,11,37718,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Cast Clear Target Auras"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,13000,13000,13000,13000,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,1,22700,22700,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,1,38600,38600,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,1,49700,49700,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,1,63600,63600,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,1,89700,89700,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,1,102600,102600,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,1,114900,114900,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,1,129500,129500,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,155800,155800,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,1,170800,170800,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,1,182300,182300,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,1,196100,196100,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,1,223500,223500,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,1,239200,239200,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,16,0,1,0,100,1,251000,251000,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,1,264600,264600,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,18,0,1,0,100,1,280000,280000,0,0,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,19,0,1,0,100,1,280800,280800,0,0,11,16380,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sig Nicious - Out Of Combat - Cast Greater Invisibility");

-- Mai'Kyl
SET @ENTRY := 23624;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,13000,13000,0,0,11,37718,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Cast Clear Target Auras"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,13000,13000,13000,13000,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,1,24700,24700,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,1,38600,38600,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,1,52700,52700,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,1,73700,73700,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,1,90000,90000,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,1,105200,105200,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,1,108000,108000,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,1,146400,146400,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,160000,160000,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,1,182000,182000,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,1,199400,199400,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,1,215200,215200,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,1,234700,234700,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,1,251200,251200,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,16,0,1,0,100,1,265400,265400,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,1,280000,280000,0,0,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,18,0,1,0,100,1,280800,280800,0,0,11,16380,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Mai'Kyl - Out Of Combat - Cast Greater Invisibility");

-- Chief Thunder-Skins
SET @ENTRY := 23623;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,24000,24000,0,0,11,37718,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Cast Clear Target Auras"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,24000,24000,24000,24000,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,1,34200,34200,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,1,48700,48700,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,1,61000,61000,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,1,73000,73000,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,1,95700,95700,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,1,120100,120100,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,1,132000,132000,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,1,152500,152500,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,165600,165600,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,1,178900,178900,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,1,190300,190300,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,1,209800,209800,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,1,223600,223600,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,1,237000,237000,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,16,0,1,0,100,1,251300,251300,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,1,271400,271400,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,18,0,1,0,100,1,280000,280000,0,0,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,19,0,1,0,100,1,280800,280800,0,0,11,16380,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chief Thunder-Skins - Out Of Combat - Cast Greater Invisibility");

-- Samuro
SET @ENTRY := 23625;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,10000,10000,0,0,11,37718,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Cast Clear Target Auras"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,10000,10000,10000,10000,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,1,29400,29400,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,1,49500,49500,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,1,72000,72000,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,1,86400,86400,0,0,5,406,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 406"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,1,95200,95200,0,0,5,407,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 407"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,1,117400,117400,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,1,124500,124500,0,0,11,42510,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Cast L70ETC Call Lightning"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,1,128400,128400,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,148000,148000,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,1,171800,171800,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,1,184500,184500,0,0,5,406,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 406"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,1,196100,196100,0,0,5,407,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 407"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,1,227500,227500,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,1,246300,246300,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,16,0,1,0,100,1,272800,272800,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,1,280000,280000,0,0,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,18,0,1,0,100,1,280800,280800,0,0,11,16380,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Samuro - Out Of Combat - Cast Greater Invisibility");

-- Bergrisst
SET @ENTRY := 23619;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,28000,28000,0,0,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,28000,28000,28000,28000,11,37718,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Cast Clear Target Auras"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,1,36500,36500,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,1,42505,42505,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,1,80500,80500,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,1,94000,94000,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,1,113500,113500,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,1,137100,137100,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,1,149000,149000,0,0,11,34126,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Cast Spotlight"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,1,158300,158300,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,172700,172700,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,1,197500,197500,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,1,213000,213000,0,0,11,41347,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Cast Spotlight"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,1,220500,220500,0,0,5,403,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 403"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,1,240500,240500,0,0,5,404,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 404"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,1,256500,256500,0,0,5,405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 405"),
(@ENTRY,@SOURCETYPE,16,0,1,0,100,1,275500,275500,0,0,5,402,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Play Emote 402"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,1,280000,280000,0,0,11,42505,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Cast L70ETC Flare Effect"),
(@ENTRY,@SOURCETYPE,18,0,1,0,100,1,280800,280800,0,0,11,16380,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bergrisst - Out Of Combat - Cast Greater Invisibility");

DELETE FROM `fishing_loot_template` WHERE `entry` = '5861';
INSERT INTO `fishing_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5861, 73269, -20.8722, 1, 0, 1, 1),
(5861, 73953, 0.5761, 1, 0, 1, 1),
(5861, 78930, 5, 1, 0, 1, 1);

DELETE FROM `disables` WHERE `sourceType`=0 AND `entry`=101883;
UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`='54518';

DELETE FROM `spell_script_names` WHERE `spell_id` = '101883';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(101883, 'spell_df_heal_injured_carnie');

DELETE FROM `creature_text` WHERE `entry`=54518;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(54518,0,0,'I can\'t thank you enough!',12,0,100,0,0,0,'Comment'),
(54518,0,1,'I\'m feeling better already.',12,0,100,0,0,0,'Comment'),
(54518,0,2,'It doesn\'t hurt so much anymore.',12,0,100,0,0,0,'Comment'),
(54518,0,3,'Time to get back to work!',12,0,100,0,0,0,'Comment'),
(54518,0,4,'Thank you, $C.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_df_injured_carnie', `RegenHealth`=0 WHERE `entry`=54518;

DELETE FROM `skill_fishing_base_level` WHERE `entry` = '5904';
INSERT INTO `skill_fishing_base_level` (`entry`, `skill`) VALUES
(5904, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '102053';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 102053, 0, 0, 31, 0, 3, 54551, 0, 0, 0, '', 'Targeting -> Cooking Pot');

-- Darkmoon Cookpot
SET @ENTRY := 54551;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,102053,1,0,0,56,72058,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Froggs");

DELETE FROM `spell_script_names` WHERE `spell_id` = '101992';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(101992, 'spell_df_put_up_darkmoon_banner');

UPDATE `creature_template` SET `modelid1`=17188 WHERE `entry`=54545;

SET @CGUID := 842903;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 54504, 974, 1, 1, 15381, 0, -4133.97, 6326.1, 13.2084, 1.69297, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+1, 54504, 974, 1, 1, 15381, 0, -4165.78, 6329.17, 13.2001, 1.78024, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+2, 54504, 974, 1, 1, 15381, 0, -4226.92, 6232, 13.2467, 1.76278, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+3, 54504, 974, 1, 1, 15381, 0, -4099.02, 6372.39, 13.2001, 1.85005, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+4, 54504, 974, 1, 1, 15381, 0, -4082.47, 6392.81, 13.2346, 3.52556, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+5, 54504, 974, 1, 1, 15381, 0, -4268.2, 6371.27, 13.2001, 3.66519, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+6, 54504, 974, 1, 1, 15381, 0, -4145.65, 6324.41, 13.2001, 1.09956, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+7, 54504, 974, 1, 1, 15381, 0, -4112.22, 6386.49, 13.2001, 0.0523599, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+8, 54504, 974, 1, 1, 15381, 0, -4117.59, 6311.72, 13.2024, 0.191986, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+9, 54504, 974, 1, 1, 15381, 0, -4096.26, 6404.28, 13.2001, 4.99164, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+10, 54504, 974, 1, 1, 15381, 0, -4106.99, 6396.72, 13.2001, 5.58505, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+11, 54504, 974, 1, 1, 15381, 0, -4086.44, 6375.21, 13.2273, 2.25148, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+12, 54504, 974, 1, 1, 15381, 0, -4138.57, 6387.13, 13.2001, 5.48033, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+13, 54504, 974, 1, 1, 15381, 0, -4121.74, 6381.7, 13.1607, 4.55531, 15, 0, 0, 100, 100, 0, 0, 0, 0),
(@CGUID+14, 54504, 974, 1, 1, 15381, 0, -4316.97, 6317.85, 13.1495, 0.802851, 15, 0, 0, 100, 100, 0, 0, 0, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` = '101838';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(101838, 'spell_repair_damaged_tonk');

DELETE FROM `disables` WHERE `sourceType` = '1' AND `entry` = '29761';
INSERT INTO `disables` (`sourceType`, `entry`, `comment`) VALUES
(1, 29761, 'Darkmoon Faire: Master Pit Fighter (Disable till script)');

DELETE FROM `item_loot_template` WHERE `entry` = '78898';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78898, 71083, 100, 1, 0, 20, 20),
(78898, 53038, 0.3, 1, 1, 6, 7),
(78898, 52185, 0.18, 1, 1, 7, 7),
(78898, 53010, 0.18, 1, 1, 11, 11),
(78898, 58263, 0.18, 1, 1, 6, 6),
(78898, 58259, 0.15, 1, 1, 6, 6),
(78898, 2595, 0.15, 1, 1, 1, 1);

DELETE FROM `item_loot_template` WHERE `entry` = '78909';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78909, 71083, 100, 1, 0, 20, 20);

DELETE FROM `item_loot_template` WHERE `entry` = '78908';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78908, 71083, 100, 1, 0, 20, 20);

DELETE FROM `item_loot_template` WHERE `entry` = '78910';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78910, 71083, 100, 1, 0, 20, 20);

DELETE FROM `item_loot_template` WHERE `entry` = '78907';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78907, 71083, 100, 1, 0, 20, 20);

DELETE FROM `item_loot_template` WHERE `entry` = '78906';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78906, 71083, 100, 1, 0, 20, 20);

DELETE FROM `item_loot_template` WHERE `entry` = '78905';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78905, 71083, 100, 1, 0, 20, 20);

DELETE FROM `item_loot_template` WHERE `entry` = '78900';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78900, 71083, 100, 1, 0, 5, 5);

DELETE FROM `item_loot_template` WHERE `entry` = '78903';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78903, 71083, 100, 1, 0, 5, 5);

DELETE FROM `item_loot_template` WHERE `entry` = '78904';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78904, 71083, 100, 1, 0, 5, 5);

DELETE FROM `item_loot_template` WHERE `entry` = '78902';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78902, 71083, 100, 1, 0, 5, 5);

DELETE FROM `item_loot_template` WHERE `entry` = '78899';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78899, 71083, 100, 1, 0, 5, 5);

DELETE FROM `item_loot_template` WHERE `entry` = '78897';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78897, 71083, 100, 1, 0, 5, 5);

DELETE FROM `item_loot_template` WHERE `entry` = '78901';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(78901, 71083, 100, 1, 0, 5, 5);

DELETE FROM `npc_vendor` WHERE `entry` = '55264';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(55264, 0, 78897, 0, 0, 0, 1),
(55264, 0, 78898, 0, 0, 0, 1),
(55264, 0, 78899, 0, 0, 0, 1),
(55264, 0, 78900, 0, 0, 0, 1),
(55264, 0, 78901, 0, 0, 0, 1),
(55264, 0, 78902, 0, 0, 0, 1),
(55264, 0, 78903, 0, 0, 0, 1),
(55264, 0, 78905, 0, 0, 0, 1),
(55264, 0, 78906, 0, 0, 0, 1),
(55264, 0, 78907, 0, 0, 0, 1),
(55264, 0, 78908, 0, 0, 0, 1),
(55264, 0, 78909, 0, 0, 0, 1);

DELETE FROM `npc_vendor` WHERE `entry` = '55339';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(55339, 0, 78897, 0, 0, 0, 1),
(55339, 0, 78898, 0, 0, 0, 1),
(55339, 0, 78899, 0, 0, 0, 1),
(55339, 0, 78900, 0, 0, 0, 1),
(55339, 0, 78901, 0, 0, 0, 1),
(55339, 0, 78902, 0, 0, 0, 1),
(55339, 0, 78903, 0, 0, 0, 1),
(55339, 0, 78905, 0, 0, 0, 1),
(55339, 0, 78906, 0, 0, 0, 1),
(55339, 0, 78907, 0, 0, 0, 1),
(55339, 0, 78908, 0, 0, 0, 1),
(55339, 0, 78909, 0, 0, 0, 1);

DELETE FROM `npc_vendor` WHERE `entry` = '55266';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(55266, 0, 78897, 0, 0, 0, 1),
(55266, 0, 78898, 0, 0, 0, 1),
(55266, 0, 78899, 0, 0, 0, 1),
(55266, 0, 78900, 0, 0, 0, 1),
(55266, 0, 78901, 0, 0, 0, 1),
(55266, 0, 78902, 0, 0, 0, 1),
(55266, 0, 78903, 0, 0, 0, 1),
(55266, 0, 78905, 0, 0, 0, 1),
(55266, 0, 78906, 0, 0, 0, 1),
(55266, 0, 78907, 0, 0, 0, 1),
(55266, 0, 78908, 0, 0, 0, 1),
(55266, 0, 78909, 0, 0, 0, 1);

SET @OGUID := 781645;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+18;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 209276, 974, 1, 1, -4346.4, 6415.98, 13.6616, 1.62316, 0, 0, 0.725374, 0.688355, 120, 255, 1),
(@OGUID+1, 209276, 974, 1, 1, -4275.71, 6443.97, 13.1168, 0.90757, 0, 0, 0.438371, 0.898794, 120, 255, 1),
(@OGUID+2, 209276, 974, 1, 1, -4308.87, 6453.31, 13.1168, 1.51844, 0, 0, 0.688354, 0.725375, 120, 255, 1),
(@OGUID+3, 209276, 974, 1, 1, -4334.24, 6438.25, 13.1878, 5.77704, 0, 0, -0.25038, 0.968148, 120, 255, 1),
(@OGUID+4, 209276, 974, 1, 1, -4260.54, 6269.06, 12.9112, 5.11382, 0, 0, -0.551936, 0.833886, 120, 255, 1),
(@OGUID+5, 209276, 974, 1, 1, -4319.45, 6238.27, 13.3989, 3.56047, 0, 0, -0.978148, 0.207912, 120, 255, 1),
(@OGUID+6, 209276, 974, 1, 1, -4229.63, 6433.12, 13.1167, 4.86947, 0, 0, -0.649447, 0.760406, 120, 255, 1),
(@OGUID+7, 209276, 974, 1, 1, -4115.99, 6236.83, 13.1534, 2.94959, 0, 0, 0.995396, 0.0958513, 120, 255, 1),
(@OGUID+8, 209276, 974, 1, 1, -4130.75, 6275.18, 13.1167, 4.92183, 0, 0, -0.62932, 0.777146, 120, 255, 1),
(@OGUID+9, 209276, 974, 1, 1, -4186.8, 6216.29, 13.1496, 5.07891, 0, 0, -0.566406, 0.824126, 120, 255, 1),
(@OGUID+10, 209276, 974, 1, 1, -4131.66, 6270.66, 13.1167, 0.872664, 0, 0, 0.422618, 0.906308, 120, 255, 1),
(@OGUID+11, 209276, 974, 1, 1, -4159.9, 6272.49, 13.1168, 5.3058, 0, 0, -0.469471, 0.882948, 120, 255, 1),
(@OGUID+12, 209276, 974, 1, 1, -4184.72, 6275.23, 13.1167, 6.10865, 0, 0, -0.0871553, 0.996195, 120, 255, 1),
(@OGUID+13, 209276, 974, 1, 1, -4120.79, 6410.37, 13.1167, 3.10665, 0, 0, 0.999847, 0.0174686, 120, 255, 1),
(@OGUID+14, 209276, 974, 1, 1, -4309, 6267.4, 13.1428, 1.53589, 0, 0, 0.694658, 0.71934, 120, 255, 1),
(@OGUID+15, 209276, 974, 1, 1, -4275.75, 6269.54, 13.359, 2.00713, 0, 0, 0.843391, 0.5373, 120, 255, 1),
(@OGUID+16, 209276, 974, 1, 1, -4117.73, 6266.5, 13.1167, 5.68977, 0, 0, -0.292372, 0.956305, 120, 255, 1),
(@OGUID+17, 209276, 974, 1, 1, -4210.82, 6212.87, 13.361, 1.62316, 0, 0, 0.725374, 0.688355, 120, 255, 1),
(@OGUID+18, 209276, 974, 1, 1, -4203.4, 6253.64, 13.1167, 5.3058, 0, 0, -0.469471, 0.882948, 120, 255, 1);