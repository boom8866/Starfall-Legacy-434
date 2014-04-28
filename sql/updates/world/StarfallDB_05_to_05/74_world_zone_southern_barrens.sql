UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (735062, 734963, 734964);
UPDATE `quest_template` SET `PrevQuestId`='0' WHERE `Id`=24504;

DELETE FROM `conditions` WHERE `SourceEntry` = '24504' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 24504, 28549, 0),
(20, 8, 24504, 26069, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '24504' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 24504, 28549, 0),
(19, 8, 24504, 26069, 1);

UPDATE `creature_template` SET `mindmg`=37, `maxdmg`=55, `attackpower`=14 WHERE `entry` IN
(37159, 37216, 37165, 37513, 37084, 37548, 37091, 37093, 37090, 37092, 37511, 37086, 37088, 37207,
37585, 37791, 37736, 37753, 37208, 37923, 37924, 37977, 37978, 37555, 37557, 37556, 37926, 37977, 
37978, 37837, 37811, 38018, 38015, 37553);

-- High Road Scout
SET @ENTRY := 37159;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,38557,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,100,100,10000,15500,89,25,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Random Move");

DELETE FROM `areatrigger_scripts` WHERE `ScriptName` = 'at_the_high_road';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5613, 'at_the_high_road'),
(5614, 'at_the_high_road'),
(5615, 'at_the_high_road');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10882 AND `id`=0;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid` IN (727873, 727872);

-- Coiled Rope
SET @ENTRY := 201707;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,85,87926,32,0,0,0,0,10,400900,37168,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Cast Rope");

-- Coiled Rope
SET @ENTRY := 201708;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,85,87926,32,0,0,0,0,10,400901,37168,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Cast Rope");

DELETE FROM `spell_script_names` WHERE `spell_id` = '87926';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87926, 'spell_gen_cosmetic_rope');

DELETE FROM `creature_template_addon` WHERE `entry` = '37167';
INSERT INTO `creature_template_addon` (`entry`, `emote`) VALUES
(37167, 455);

DELETE FROM `conditions` WHERE `SourceGroup`=10882 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10882, 0, 0, 0, 2, 0, 49769, 1, 0, 0, 0, 0, '', 'Show gossip only if item 49769 is in bag');

-- Stonetalon Prisoner
SET @ENTRY := 37167;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10882,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,10882,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Emote Stand UP"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,85,70011,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Give Confiscated Arms"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,5,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Play Emote"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,36,37171,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Update Template"),
(@ENTRY,@SOURCETYPE,5,8,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,4000,4000,60000,60000,69,0,0,0,0,0,0,8,0,0,0,-463.05,-1419.88,93.79,5.67,"Update - Run Away!"),
(@ENTRY,@SOURCETYPE,7,0,34,1,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,0,0,0,0,33,37176,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,9,10,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Immune");

DELETE FROM `creature` WHERE `guid` IN (400900, 400901);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(400901, 37168, 1, 1, 1, 0, 0, -560.591, -1407.75, 92.7425, 3.22207, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(400900, 37168, 1, 1, 1, 0, 0, -614.642, -1415.99, 157.557, 6.24846, 300, 0, 0, 42, 0, 0, 0, 33554432, 0);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=73.545 WHERE `entry`=37216 AND `item`=49776;

-- Honor's Stand Officer
SET @ENTRY := 37216;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,22120,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Charge on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,4000,120000,125000,11,80983,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Commanding Shout"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,56,49776,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest Item");

UPDATE `creature` SET `phaseMask`=1, `position_x`=-1861.02, `position_y`=-1834.76, `position_z`=90.74, `orientation`=0.01, `spawntimesecs`=120 WHERE `guid`=738318;

DELETE FROM `spell_script_names` WHERE `spell_id` = '70155';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70155, 'spell_blow_horn_of_challenge');

-- Sabersnout
SET @ENTRY := 37513;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,52,0,100,0,2,37513,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Remove Immunity"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,10000,10000,10000,10000,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Immune"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"Link - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,0,70171,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - DO NOTHING"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,8000,8000,19500,19500,11,70171,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fear"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,10000,10000,10000,10000,28,70166,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Remove Shield"),
(@ENTRY,@SOURCETYPE,6,14,2,0,100,1,0,20,0,0,11,70166,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health - 20% Add Shield"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,2000,2000,4500,4500,11,11976,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Strike"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,1,6,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 6"),
(@ENTRY,@SOURCETYPE,9,2,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,0,37513,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,1,37513,0,0,1,2,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,12,13,0,0,100,0,12500,12500,25500,32000,11,82610,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Quilboar Rush"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 5"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 3"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,3,37513,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4");

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=37513;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=37738;

-- Enervated Adder
SET @ENTRY := 37738;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,85,70441,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Cover"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,85,70442,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Adder"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `spell_script_names` WHERE `spell_id` = '70458';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70458, 'spell_soothing_seeds');

UPDATE `creature` SET `phaseMask`=2 WHERE `id`=37103;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10941 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10941 AND `id`=0;

DELETE FROM `spell_area` WHERE `spell` = '70593' AND `quest_start` = '24601';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(70593, 4888, 24601, 24601, 1, 10, 11);

DELETE FROM `conditions` WHERE `SourceGroup`=10941 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10941, 0, 0, 0, 1, 0, 70593, 1, 0, 0, 0, 0, '', 'Show gossip only if NIghtmare aura is active');

DELETE FROM `creature` WHERE `guid` = '400902';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(400902, 37570, 1, 1, 2, 0, 0, -1705.31, -2217.74, 98.7485, 2.83651, 300, 0, 0, 1029, 1067, 0, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry`=37570;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37570,0,0,'I will attempt to seal the scar. $n, Make sure nothing from the other side makes its way through!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=37522;
UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=152984;
UPDATE `creature` SET `position_z`=99.57 WHERE  `guid`=152984;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=37570;
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=37736;

-- Nightmare Stalker
SET @ENTRY := 37736;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,5000,12500,21000,11,82811,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corrupted Dreams");

-- Nightmare Mass
SET @ENTRY := 37753;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,6,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"On Death - Set Data 5 to Creatures"),
(@ENTRY,@SOURCETYPE,1,0,36,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"On Corpse Removed - Set Data 5 to Creatures"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,3500,3500,11,82812,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Insanity"),
(@ENTRY,@SOURCETYPE,4,2,6,0,100,0,0,0,0,0,33,37753,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Death - Killed Monster ");

UPDATE `creature` SET `spawntimesecs`=30 WHERE `guid`=400902;

-- Naralex
SET @ENTRY := 37570;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10941,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,152984,37522,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Trigger"),
(@ENTRY,@SOURCETYPE,4,5,52,0,100,0,0,37570,0,0,11,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Cast Banish State (Self)"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,11,82355,0,0,0,0,0,10,152984,37522,0,0.0,0.0,0.0,0.0,"Link - Cast Siphon to Target"),
(@ENTRY,@SOURCETYPE,6,13,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,7,0,60,1,100,0,6000,6000,120000,120000,12,37791,3,20000,0,0,0,8,0,0,0,-1715.74,-2215.34,99.1,6.12,"Update - Summon Nightmare Horror"),
(@ENTRY,@SOURCETYPE,8,0,60,1,100,0,6000,6000,120000,120000,12,37791,3,20000,0,0,0,8,0,0,0,-1717.27,-2213.18,99.49,6.12,"Update - Summon Nightmare Horror"),
(@ENTRY,@SOURCETYPE,9,0,60,1,100,0,6000,6000,120000,120000,12,37791,3,20000,0,0,0,8,0,0,0,-1717.88,-2217.0,99.03,6.12,"Update - Summon Nightmare Horror"),
(@ENTRY,@SOURCETYPE,10,0,60,1,100,0,20000,20000,120000,120000,12,37736,3,20000,0,0,0,8,0,0,0,-1717.66,-2213.05,99.58,6.15,"Update - Summon Nightmare Stalker"),
(@ENTRY,@SOURCETYPE,11,0,60,1,100,0,20000,20000,120000,120000,12,37736,3,20000,0,0,0,8,0,0,0,-1718.2,-2217.11,99.05,6.15,"Update - Summon Nightmare Stalker"),
(@ENTRY,@SOURCETYPE,12,14,38,0,100,0,0,5,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Evade"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive"),
(@ENTRY,@SOURCETYPE,15,0,60,1,100,0,40000,40000,120000,120000,12,37753,3,50000,0,0,0,8,0,0,0,-1718.34,-2215.04,99.31,0.19,"Update - Summon Nightmare Mass"),
(@ENTRY,@SOURCETYPE,16,0,7,0,100,0,0,0,0,0,28,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Banish"),
(@ENTRY,@SOURCETYPE,17,0,7,0,100,0,0,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Flags");

-- Romo's Standard Bunny
SET @ENTRY := 37522;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,11,46262,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Darkness"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,11,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Banish State"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,0,0,0,0,22,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On SpellHit - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,5,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Evade"),
(@ENTRY,@SOURCETYPE,5,0,7,0,100,0,0,0,0,0,28,46262,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Auras"),
(@ENTRY,@SOURCETYPE,6,0,7,0,100,0,0,0,0,0,28,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Auras"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,28,46265,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Auras");

DELETE FROM `spell_script_names` WHERE `spell_id` = '70365';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70365, 'spell_flag_capture');

-- Horde Field Banner
SET @ENTRY := 201744;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,85,0,5000,10000,35000,60000,12,37585,3,30000,0,0,0,8,0,0,0,-2142.48,-2031.21,91.8,4.83,"Update - Summon Northwatch Recon"),
(@ENTRY,@SOURCETYPE,2,0,60,1,85,0,5000,10000,35000,60000,12,37585,3,30000,0,0,0,8,0,0,0,-2089.33,-2064.77,92.02,3.57,"Update - Summon Northwatch Recon"),
(@ENTRY,@SOURCETYPE,3,0,60,1,85,0,5000,10000,35000,60000,12,37585,3,30000,0,0,0,8,0,0,0,-2144.36,-2122.07,92.59,1.14,"Update - Summon Northwatch Recon"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,41,75000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,0,65000,65000,65000,65000,33,37668,0,0,0,0,0,18,75,0,0,0.0,0.0,0.0,0.0,"Update - Quest Complete");

-- Alliance Field Banner
SET @ENTRY := 202460;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,85,0,5000,10000,35000,60000,12,37706,3,30000,0,0,0,8,0,0,0,-2412.69,-2315.6,92.77,2.97,"Update - Summon Desolation Grunt"),
(@ENTRY,@SOURCETYPE,2,0,60,1,85,0,5000,10000,35000,60000,12,37706,3,30000,0,0,0,8,0,0,0,-2454.67,-2263.28,95.37,4.58,"Update - Summon Desolation Grunt"),
(@ENTRY,@SOURCETYPE,3,0,60,1,85,0,5000,10000,35000,60000,12,37706,3,30000,0,0,0,8,0,0,0,-2501.6,-2329.76,93.77,0.52,"Update - Summon Desolation Grunt"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,41,75000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,0,65000,65000,65000,65000,33,39030,0,0,0,0,0,18,75,0,0,0.0,0.0,0.0,0.0,"Update - Quest Complete");

-- Northwatch Recon
SET @ENTRY := 37585;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5000,22000,28000,11,13730,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,5,12000,13000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Heroic Strike on Close"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,1000,1000,5000,5000,49,0,0,0,0,0,0,11,37659,150,0,0.0,0.0,0.0,0.0,"OOC - Attack Horde Defenders"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,1000,1000,5000,5000,49,0,0,0,0,0,0,11,39040,150,0,0.0,0.0,0.0,0.0,"OOC - Attack Alliance Defenders");

-- Alliance Field Defender
SET @ENTRY := 39040;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4500,4500,11,29426,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,6500,6500,11,70316,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave");

-- Desolation Grunt
SET @ENTRY := 37706;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Shout on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,2000,2000,5000,5000,49,0,0,0,0,0,0,11,39040,100,0,0.0,0.0,0.0,0.0,"OOC - Attack Alliance Field Defender");

-- Horde Field Barricade
SET @ENTRY := 201748;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,41,75000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Force Despawn");

-- Alliance Field Wall
SET @ENTRY := 202462;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,41,75000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Force Despawn");

DELETE FROM `gameobject` WHERE `id` IN (201744, 201748);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '37978';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(37978, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '37978';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(37978, 37977, 0, 'Triumph War Gryphon - Wildhammer Mercenary', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '37974';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(37974, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '37974';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(37974, 37922, 0, 'Desolation Windrider - Desolation Rider', 8, 0);

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry` IN (37977, 37922);

DELETE FROM `creature` WHERE `id`=37977;
DELETE FROM `creature` WHERE `id`=37922;
UPDATE `creature` SET `spawndist`=25, `MovementType`=1 WHERE `id`=37978;
UPDATE `creature` SET `spawndist`=25, `MovementType`=1 WHERE `id`=37974;

DELETE FROM `gameobject_loot_template` WHERE `item` = '49945';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27780, 49945, -100, 1, 0, 1, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` = '70813';

DELETE FROM `creature_template_addon` WHERE `entry` IN (37977, 37922);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70813, 'spell_dismembering');

-- Triumph War Gryphon
SET @ENTRY := 37978;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,70885,1,0,0,69,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Move To Invoker"),
(@ENTRY,@SOURCETYPE,1,2,34,0,100,0,8,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Remove Passengers"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Wildhammer Mercenary
SET @ENTRY := 37977;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,40,15000,16000,11,82837,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Stormhammer on Close"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,5,9000,11000,11,11978,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Kick on Close"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Players");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=38055;

DELETE FROM `spell_script_names` WHERE `spell_id` = '71030';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(71030, 'spell_burning_pitch');

UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=38055;

-- Silithid Mound Bunny
SET @ENTRY := 38055;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,71030,1,0,0,85,71062,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Summon Silithid Swarmer"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,71030,1,0,0,85,71062,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Summon Silithid Swarmer"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,71030,1,0,0,85,71062,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Summon Silithid Swarmer");

-- Silithid Swarmer
SET @ENTRY := 3252;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,12000,12000,8000,8000,11,6589,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Silithid Swarmer - In Combat - Cast Silithid Swarm"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,1000,1000,5000,5000,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Invoker");

DELETE FROM `creature_text` WHERE `entry`=37812;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37812,0,0,'Look at this land, Mankrik. The Horde and Alliance tear the earth apart just to claw at each other in spite.',12,0,100,0,0,0,'Comment'),
(37812,1,0,'Such hatred is only bringing us destruction. I can see it in you as you fight the quilboar... your anger does nothing but wear you away.',12,0,100,0,0,0,'Comment'),
(37812,2,0,'You\'re destroying yourself, Mankrik.',12,0,100,0,0,0,'Comment'),
(37812,3,0,'You seek escape, not glory. It\'s suicide.',12,0,100,0,0,0,'Comment'),
(37812,4,0,'Because...',12,0,100,0,0,0,'Comment'),
(37812,5,0,'Because despite what you think, there may be people in this world who would mourn your passing.',12,0,100,0,0,0,'Comment'),
(37812,6,0,'Please, Mankrik. Let go. Set down your blade.',12,0,100,0,0,0,'Comment'),
(37812,7,0,'Then... you do not need to bear it alone. Just sit next to me and forget your troubles, if only for a while.',12,0,100,0,0,0,'Comment'),
(37812,8,0,'Come see me whenever you are weary.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=37847;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37847,0,0,'There is nothing left for me. I seek a warrior\'s death. Is that wrong?',12,0,100,0,0,0,'Comment'),
(37847,1,0,'So what if it is? Why do you even care?',12,0,100,0,0,0,'Comment'),
(37847,2,0,'Mahka...',12,0,100,0,0,0,'Comment'),
(37847,3,0,'This hatred has burned in me for years, Mahka. Your words cannot lift it from me so easily.',12,0,100,0,0,0,'Comment'),
(37847,4,0,'Mankrik nods.',16,0,100,0,0,0,'Comment'),
(37847,5,0,'...thank you, Mahka.',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_target_position` WHERE `id` = '70977';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(70977, 1, -4018.47, -1989.87, 92.62, 1.26);

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=24633;

-- Mankrik
SET @ENTRY := 37847;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,17,455,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Emote Sit"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,37847,0,0,45,0,1,0,0,0,0,11,37812,10,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Mahka"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,37847,0,0,45,0,2,0,0,0,0,11,37812,10,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Mahka"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,2,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,37847,0,0,45,0,3,0,0,0,0,11,37812,10,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Mahka"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,4,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,37847,0,0,45,0,4,0,0,0,0,11,37812,10,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Mahka"),
(@ENTRY,@SOURCETYPE,9,11,38,0,100,0,0,5,0,0,1,4,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 4"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,4,37847,0,0,1,5,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,0,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Emote"),
(@ENTRY,@SOURCETYPE,12,13,52,0,100,0,5,37847,0,0,15,24633,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Quest Complete"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-4042.31,-1980.41,91.67,2.33,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,14,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,5,37847,0,0,45,0,10,0,0,0,0,11,37812,10,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 10 to Mahka");

-- Mahka
SET @ENTRY := 37812;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,19,0,100,0,24633,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,85,70977,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Mandrik"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,37812,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,37812,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,37812,0,0,45,0,1,0,0,0,0,11,37847,10,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Mankrik"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,1,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,37812,0,0,45,0,2,0,0,0,0,11,37847,10,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 2 to Mankrik"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,2,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,37812,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,37812,0,0,45,0,3,0,0,0,0,11,37847,10,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 3 to Mankrik"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,3,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 6"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,6,37812,0,0,45,0,4,0,0,0,0,11,37847,10,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 4 to Mankrik"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,4,0,0,1,7,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 7"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,7,37812,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,8,37812,0,0,45,0,5,0,0,0,0,11,37847,10,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 5 to Mankrik"),
(@ENTRY,@SOURCETYPE,16,0,38,0,100,0,0,10,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Reset NPC Flag");

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '24577';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`, `aura_spell`) VALUES
(49416, 4853, 24577, 24591, 1, 66, 11, -49417);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '24591';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 4853, 24591, 0, 1, 66, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '37811';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(37811, '49414');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6189';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6189, 'at_desolation_hold');

DELETE FROM `creature_text` WHERE `entry`=37811;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37811,0,0,'Thank you. I trust you will, ah, defer to my authority on this matter.',12,0,100,0,0,0,'Comment'),
(37811,1,0,'Hiding? Listen Bloodhilt - I\'ve, ah, reinforced our grip on the Barrens.',12,0,100,0,0,0,'Comment'),
(37811,2,0,'But they\'ve, ah, they\'ve gotten reinforcements! From the Eastern Kingdoms. Whereas I\'ve been, ah, cut off -',12,0,100,0,0,0,'Comment'),
(37811,3,0,'Relieved? Over my dead body!',12,0,100,0,0,0,'Comment'),
(37811,4,0,'Wait, ah - wait! I yield. I yield!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=37837;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37837,0,0,'So this is where you\'re hiding Gar\'dul.',12,0,100,0,0,0,'Comment'),
(37837,1,0,'You cower behind your walls! If it wasn\'t for you here the Alliance would be marching through Mulgore.',12,0,100,0,0,0,'Comment'),
(37837,2,0,'Your excuses sicken me! Consider yourself relieved from command.',12,0,100,0,0,0,'Comment'),
(37837,3,0,'So! You DO have a spine.',12,0,100,0,0,0,'Comment'),
(37837,4,0,'Yield? You ... YIELD?',12,0,100,0,0,0,'Comment'),
(37837,5,0,'What part of "Victory or Death" don\'t you understand?',12,0,100,0,0,0,'Comment'),
(37837,6,0,'Garrosh\'s Horde does not tolerate failure.',12,0,100,0,0,0,'Comment'),
(37837,7,0,'Meet me down below and we\'ll discuss our upcoming counter-attack.',12,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=24591;

DELETE FROM `waypoints` WHERE `entry` = '37811';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(37811, 1, -3223.43, -1666.91, 99.90, 'GarDul WP'),
(37811, 2, -3218.25, -1651.21, 131.23, 'GarDul WP'),
(37811, 3, -3212.68, -1668.19, 131.02, 'GarDul WP'),
(37811, 4, -3213.98, -1666.84, 131.00, 'GarDul WP');

DELETE FROM `waypoints` WHERE `entry` = '37837';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(37837, 1, -3223.43, -1666.91, 99.90, 'Bloodhilt WP'),
(37837, 2, -3218.25, -1651.21, 131.23, 'Bloodhilt WP'),
(37837, 3, -3224.20, -1656.27, 131.00, 'Bloodhilt WP'),
(37837, 4, -3223.83, -1657.36, 131.08, 'Bloodhilt WP');

UPDATE `creature_template` SET `VehicleId`=605, `mingold`=0 WHERE `entry`=37837;

-- Warlord Gar'dul
SET @ENTRY := 37811;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,37811,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,1,4,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,37811,0,0,45,0,1,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,37811,0,0,45,0,2,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,37811,0,0,45,0,3,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,10,11,38,0,100,0,0,4,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Set Aggressive"),
(@ENTRY,@SOURCETYPE,11,12,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Hostile"),
(@ENTRY,@SOURCETYPE,12,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"Link - Attack Player"),
(@ENTRY,@SOURCETYPE,13,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,14,15,2,0,100,1,0,25,120000,120000,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health - Still Hostile"),
(@ENTRY,@SOURCETYPE,15,18,61,0,100,0,0,0,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 4"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,4,37811,0,0,45,0,4,0,0,0,0,11,37837,25,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 4 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,17,0,38,0,100,0,0,5,0,0,11,46598,0,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Ride Bloodhilt"),
(@ENTRY,@SOURCETYPE,18,0,61,0,100,0,0,0,0,0,33,37811,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

-- Warlord Bloodhilt
SET @ENTRY := 37837;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,37837,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,4,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,28,49415,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Invisibility Auras"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,37837,0,0,45,0,1,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,37837,0,0,45,0,2,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,2,37837,0,0,45,0,3,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,3,37837,0,0,45,0,4,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,4,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,4,37837,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,5,37837,0,0,45,0,5,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 5 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,15,17,27,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-3212.99,-1669.75,131.22,5.48,"On Passenger Boarded - Move To Window"),
(@ENTRY,@SOURCETYPE,16,0,34,0,100,0,8,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Remove Passenger"),
(@ENTRY,@SOURCETYPE,17,0,61,0,100,0,0,0,0,0,41,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,18,0,54,0,100,0,0,0,0,0,28,49416,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Invisibility Aura");

-- Bloodhilt's Area Trigger and Carry Bunny
SET @ENTRY := 37866;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3000,3000,3000,3000,33,37843,0,0,0,0,0,18,5,0,0,0.0,0.0,0.0,0.0,"Update - Quest Credit");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738249;

DELETE FROM `creature_involvedrelation` WHERE `id` = '37837';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(37837, 24618),
(37837, 24634),
(37837, 24637);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10960 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=10960 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10960, 0, 0, 0, 9, 0, 24637, 1, 0, 0, 0, 0, '', 'Show gossip only if quest 24637 is active');

DELETE FROM `creature_text` WHERE `entry`=38015;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38015,0,0,'They come! Everyone, get ready...',12,0,100,0,0,0,'Comment'),
(38015,1,0,'We\'ll string his body from the trees and leave him swinging in the wind for the Alliance to discover. Go back and tell Warlord Bloodhill the news!',12,0,100,0,0,0,'Comment');

-- Horde Field Defender
SET @ENTRY := 37659;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,5,12000,13000,11,70316,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Cleave on Close"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,6000,16000,21000,11,29426,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,29,4,0,0,0,0,0,10,153520,38015,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Follow Karthog");

DELETE FROM `creature_text` WHERE `entry`=38018;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38018,0,0,'[Common] Agol regen ash veLd lo ealdor Ko lars',12,0,100,0,0,0,'Comment');

-- General Hawthorne
SET @ENTRY := 38018;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,46,100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,153520,38015,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Karthog");

-- Karthog
SET @ENTRY := 38015;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10960,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-2665.91,-2203.11,93.68,0.48,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,12,38018,3,120000,0,0,0,8,0,0,0,-2614.88,-2181.49,95.78,3.13,"Link - Summon Hawtorne"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,12,37926,3,120000,0,0,0,8,0,0,0,-2615.14,-2184.17,95.78,3.13,"Link - Summon Triumph Captain"),
(@ENTRY,@SOURCETYPE,5,10,61,0,100,0,0,0,0,0,12,37926,3,120000,0,0,0,8,0,0,0,-2615.09,-2179.04,95.78,3.13,"Link - Summon Triumph Captain"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,10960,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set NPC Flags"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,9,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,153519,37659,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Horde Field Defender"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,0,2500,2500,2500,2500,49,0,0,0,0,0,0,11,38018,25,0,0.0,0.0,0.0,0.0,"OOC - Attack Hawtorne in range");

UPDATE `creature_template` SET `VehicleId`=1513, `InhabitType`=4 WHERE `entry`=38259;
UPDATE `creature_template` SET `speed_walk`=0.45, `speed_run`=0.45 WHERE `entry` IN (38109, 38190);
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry` IN (38109, 38190);

DELETE FROM `spell_script_names` WHERE `spell_id` = '71225';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(71225, 'spell_sabotage_bael_dun');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=38212;

DELETE FROM `creature_text` WHERE `entry` IN (38109, 38190);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38109,0,0,'This whole place is gonna blow, Get to the exit!',42,0,100,0,0,9428,'Comment'),
(38190,0,0,'This whole place is gonna blow, Get to the exit!',42,0,100,0,0,9428,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5702';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5702, 'at_bael_dun_keep');

DELETE FROM `waypoints` WHERE `entry` = '38259';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(38259, 1, -4078.86, -2239.15, 165.15, 'BaelDun Camera WP');

UPDATE `creature` SET `phaseMask`=2 WHERE `id`= '39207';

-- Bael'dun Phase 2 Effects Bunny (Medium)
SET @ENTRY := 39207;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,5500,2500,5500,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Explosion");

UPDATE `creature_template` SET `modelid1`=11686 WHERE `entry`=38259;
UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=738272;
UPDATE `creature_template_addon` SET `auras`='46598 66110' WHERE `entry`=38212;

-- Twinbraid's Flying Machine
SET @ENTRY := 38212;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-4077.43,-2294.32,125.45,3.14,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,4,34,0,100,0,8,0,0,0,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Explode"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Explode Twice");

-- Bael'dun Explosion View Vehicle
SET @ENTRY := 38259;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,38259,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,1,2,40,0,100,0,1,0,0,0,45,0,1,0,0,0,0,10,738272,38212,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Data 1 to Airplane"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,3,4,60,1,100,0,12000,12000,90000,90000,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (12 secs) - Remove Passenger"),
(@ENTRY,@SOURCETYPE,4,0,61,1,100,0,0,0,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Dwarven Artillery Shell
SET @ENTRY := 38109;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,85,71225,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Sabotage");

-- Dwarven Artillery Shell
SET @ENTRY := 38190;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,85,71225,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Sabotage");

UPDATE `creature` SET `spawntimesecs`=30 WHERE `guid`=738272;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=154128;
UPDATE `creature_template` SET `speed_walk`=3.2, `speed_run`=3.38571 WHERE `entry`=38212;

UPDATE `quest_template` SET `PrevQuestId`='24934' WHERE `Id`=24938;
UPDATE `quest_template` SET `PrevQuestId`='24941' WHERE `Id`=24939;
UPDATE `quest_template` SET `PrevQuestId`='24938' WHERE `Id`=24939;
UPDATE `quest_template` SET `PrevQuestId`='24939' WHERE `Id`=24941;
UPDATE `quest_template` SET `PrevQuestId`='24941' WHERE `Id` IN (24944, 24943);

DELETE FROM `conditions` WHERE `SourceEntry` = '25036' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25036, 24948, 0),
(20, 8, 25036, 24956, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25036' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25036, 24948, 0),
(19, 8, 25036, 24956, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25000' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25000, 24948, 0),
(20, 8, 25000, 24956, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25000' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25000, 24948, 0),
(19, 8, 25000, 24956, 0);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56003';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56003, 'I am ready, to the Blackpool!', 1, 1);

UPDATE `creature_template` SET `gossip_menu_id`=56003 WHERE `entry`=38619;

DELETE FROM `conditions` WHERE `SourceGroup`=56003 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 56003, 0, 0, 0, 9, 0, 24934, 1, 0, 0, 0, 0, '', 'Show gossip only if quest 24934 is active');

UPDATE `creature_template` SET `VehicleId`=104, `speed_walk`=2, `speed_run`=2.14286, `InhabitType`=4 WHERE `entry` IN (38707, 38709);

DELETE FROM `waypoints` WHERE `entry` = '38707';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(38707, 1, -2212.29, -4011.83, 51.41, 'Northwatch Gryphon WP'),
(38707, 2, -2154.06, -4085.72, 21.01, 'Northwatch Gryphon WP');

-- Admiral Aubrey
SET @ENTRY := 38619;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,56003,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,85,72600,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Gryphon");

-- Northwatch Gryphon
SET @ENTRY := 38707;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,38707,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,2,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");

UPDATE `creature_template` SET `mindmg`=38, `maxdmg`=57, `attackpower`=14 WHERE `entry` IN
(38661,38658,38663,38826,37085,38884,38941,38940,37743,37925,37922,39280,39279,37660,37559,37560,37661,37940,39153,39174);

UPDATE `creature` SET `spawntimesecs`= '60' WHERE `id` = '38661';

DELETE FROM `waypoints` WHERE `entry` = '38709';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(38709, 1, -2196.94, -4064.40, 35.33, 'Northwatch Gryphon 2 WP'),
(38709, 2, -2231.54, -3860.20, 124.87, 'Northwatch Gryphon 2 WP'),
(38709, 3, -2219.12, -3782.29, 140.22, 'Northwatch Gryphon 2 WP'),
(38709, 4, -2221.46, -3772.79, 130.86, 'Northwatch Gryphon 2 WP');

-- Northwatch Gryphon
SET @ENTRY := 38709;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,38709,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,4,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");

-- Captain Fisher
SET @ENTRY := 38622;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,24934,0,0,0,85,72610,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Summon Gryphon");

DELETE FROM `waypoints` WHERE `entry` = '38709';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(38709, 1, -2196.94, -4064.40, 35.33, 'Northwatch Gryphon 2 WP'),
(38709, 2, -2231.54, -3860.20, 124.87, 'Northwatch Gryphon 2 WP'),
(38709, 3, -2219.12, -3782.29, 140.22, 'Northwatch Gryphon 2 WP'),
(38709, 4, -2221.46, -3772.79, 130.86, 'Northwatch Gryphon 2 WP');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (735026, 735025);
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=38754;
UPDATE `creature_template` SET `modelid1`=33265, `modelid2`=33265 WHERE `entry`=38747;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '38747';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(38747, 38661, 0, 1, 'Rageroar Rowboat', 8, 0),
(38747, 38661, 1, 1, 'Rageroar Rowboat', 8, 0),
(38747, 38661, 2, 1, 'Rageroar Rowboat', 8, 0),
(38747, 38661, 3, 1, 'Rageroar Rowboat', 8, 0),
(38747, 38661, 4, 1, 'Rageroar Rowboat', 8, 0),
(38747, 38661, 5, 1, 'Rageroar Rowboat', 8, 0),
(38747, 38661, 6, 1, 'Rageroar Rowboat', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '38747';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(38747, 46598, 0);

UPDATE `creature_template` SET `InhabitType`=4, `VehicleId`=964 WHERE `entry`=38747;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '38754';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(38754, 46598, 1);

UPDATE `creature_template` SET `spell1`=72741 WHERE `entry`=38754;
UPDATE `creature_template` SET `speed_walk`=0.001, `speed_run`=0.001 WHERE `entry`=38754;

-- Rageroar Rowboat
SET @ENTRY := 38747;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,72755,4,0,0,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Explosion"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,33,38747,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Die"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,46,300,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward");

-- Rageroar Sea Dog
SET @ENTRY := 38661;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,7000,12000,20000,11,82616,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Focused Strikes"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,72755,4,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die");

DELETE FROM `creature` WHERE `guid` IN (155567, 155568, 155569, 155570, 155571, 155572, 155573, 155559, 155558, 155560);
DELETE FROM `creature_addon` WHERE `guid` IN (155567, 155568, 155569, 155570, 155571, 155572, 155573, 155559, 155558, 155560);

-- Wounded Defender
SET @ENTRY := 38805;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,72925,1,0,0,33,38805,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

DELETE FROM `creature_template_addon` WHERE `entry` = '38805';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(38805, '75511');

-- Wounded Defender
SET @ENTRY := 38805;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,72925,1,0,0,33,38805,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,28,75511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Feign Death"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,46,50,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Move Forward"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `creature_text` WHERE `entry`=38805;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38805,0,0,'Thank you!',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=38805;

DELETE FROM `conditions` WHERE `SourceEntry` = '72940';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 72940, 0, 0, 31, 0, 3, 38818, 0, 0, 0, '', 'Targeting -> Catapults'),
(13, 1, 72940, 0, 1, 31, 0, 3, 38820, 0, 0, 0, '', 'Targeting -> Catapults');

DELETE FROM `creature` WHERE `guid`=155566;
DELETE FROM `creature` WHERE `guid`=155557;

-- Rageroar Catapult
SET @ENTRY := 38818;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73119,0,0,0,33,38818,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

DELETE FROM `creature_template_addon` WHERE `entry` = '38818';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(38818, '40790');

DELETE FROM `creature_template_addon` WHERE `entry` = '38820';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(38820, '40790');

-- Rageroar Catapult
SET @ENTRY := 38818;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,72940,1,0,0,33,38818,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,75,73119,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Apply Fire"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,28,40790,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Arrow"),
(@ENTRY,@SOURCETYPE,3,4,1,0,100,0,25000,25000,25000,25000,28,73119,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Fire"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,75,40790,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Arrow");

-- Rageroar Blade Thrower
SET @ENTRY := 38820;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,72940,1,0,0,33,38820,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,75,73119,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Apply Fire"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,28,40790,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Arrow"),
(@ENTRY,@SOURCETYPE,3,4,1,0,100,0,25000,25000,25000,25000,28,73119,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Fire"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,75,40790,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Arrow");

DELETE FROM `spell_script_names` WHERE `spell_id` = '72940';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72940, 'spell_throw_torch_catapult');

UPDATE `creature_template` SET `scale`=2.5, `flags_extra`=128 WHERE `entry`=38818;
UPDATE `creature_template` SET `scale`=4, `flags_extra`=128 WHERE `entry`=38820;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735022;

SET @CGUID := 400920;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+15;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 37084, 1, 1, 1, 0, 0, -1986.55, -3163.21, 92.2474, 1.75872, 300, 20, 0, 1006, 0, 1, 0, 0, 0),
(@CGUID+1, 37084, 1, 1, 1, 0, 0, -2013.32, -3180.7, 91.783, 3.06028, 300, 20, 0, 1006, 0, 1, 0, 0, 0),
(@CGUID+2, 37083, 1, 1, 1, 0, 0, -1892.39, -3155.92, 91.3266, 3.28805, 300, 20, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+3, 37083, 1, 1, 1, 0, 0, -1899.74, -3159.36, 91.1156, 2.17278, 300, 20, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+4, 37083, 1, 1, 1, 0, 0, -1919.5, -3190.3, 90.4586, 6.2647, 300, 0, 20, 955, 0, 1, 0, 0, 0),
(@CGUID+5, 37084, 1, 1, 1, 0, 0, -1948.83, -3179.27, 92.5565, 5.19656, 300, 20, 0, 1006, 0, 1, 0, 0, 0),
(@CGUID+6, 37084, 1, 1, 1, 0, 0, -1969.44, -3151.96, 92.9595, 1.15176, 300, 20, 0, 1006, 0, 1, 0, 0, 0),
(@CGUID+7, 37083, 1, 1, 1, 0, 0, -1977.43, -3193.85, 92.5562, 1.2735, 300, 20, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+8, 37083, 1, 1, 1, 0, 0, -1974.47, -3186.24, 92.0036, 4.76067, 300, 20, 0, 955, 0, 1, 0, 0, 0),
(@CGUID+9, 37084, 1, 1, 1, 0, 0, -1996.76, -3167.91, 92.8995, 1.15176, 300, 20, 0, 1006, 0, 1, 0, 0, 0),
(@CGUID+10, 37084, 1, 1, 1, 0, 0, -2023.99, -3197.13, 91.6407, 2.97782, 300, 20, 0, 955, 0, 1, 0, 0, 0),
(@CGUID+11, 37083, 1, 1, 1, 0, 0, -2011.13, -3208.57, 91.5586, 5.44397, 300, 20, 0, 955, 0, 1, 0, 0, 0),
(@CGUID+12, 37083, 1, 1, 1, 0, 0, -2038.51, -3228.2, 92.1145, 2.19635, 300, 20, 0, 955, 0, 1, 0, 0, 0),
(@CGUID+13, 37083, 1, 1, 1, 0, 0, -2038.04, -3255.14, 91.7195, 2.28667, 300, 20, 0, 905, 0, 1, 0, 0, 0),
(@CGUID+14, 37083, 1, 1, 1, 0, 0, -2031.9, -3260.45, 91.9035, 4.76852, 300, 20, 0, 955, 0, 1, 0, 0, 0),
(@CGUID+15, 37084, 1, 1, 1, 0, 0, -2020.75, -3245.38, 92.3376, 0.421345, 300, 20, 0, 955, 0, 1, 0, 0, 0);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `id`=202405;

DELETE FROM `conditions` WHERE `SourceEntry` = '25027' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25027, 25022, 0),
(20, 8, 25027, 25015, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25027' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25027, 25022, 0),
(19, 8, 25027, 25015, 0);

UPDATE `quest_template` SET `PrevQuestId`='25027' WHERE `Id`=25028;

DELETE FROM `creature_text` WHERE `entry`=38872;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38872,0,0,'Hey...you, I\'m here! Help me, please!',14,0,100,0,0,0,'Comment'),
(38872,1,0,'Thank you so much!',12,0,100,0,0,0,'Comment');

-- Ambassador Gaines
SET @ENTRY := 38872;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,45,0,1,0,0,0,0,15,202418,10,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 1 to Restraint"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,45,0,1,0,0,0,0,15,202419,10,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 1 to Restraint"),
(@ENTRY,@SOURCETYPE,3,8,62,0,100,0,56004,0,0,0,1,1,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1"),
(@ENTRY,@SOURCETYPE,4,5,52,0,100,0,1,38872,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Run"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,33,38872,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-2182.49,-2607.38,95.46,3.58,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,7,9,61,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,40931,15,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Trigger");

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5757';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5757, 'at_the_overgrowth');

-- Quilboar Restraint
SET @ENTRY := 202418;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,87926,0,0,0,0,0,11,38872,10,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Rope");

-- Quilboar Restraint
SET @ENTRY := 202418;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,87926,0,0,0,0,0,11,38872,10,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Rope");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56004';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56004, 'I am here to save you, run away now!', 1, 1);

-- Generic Trigger LAB 1.80
SET @ENTRY := 40931;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

UPDATE `creature_template` SET `gossip_menu_id`=56004, `npcflag`=1 WHERE `entry`=38872;
UPDATE `gameobject_template` SET `data1`=39335 WHERE `entry`=207487;

DELETE FROM `gameobject_loot_template` WHERE `entry` = '39335';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39335, 720, 0.3775, 1, 0, 1, 1),
(39335, 774, 0.2, 1, 0, 1, 1),
(39335, 791, 0.3791, 1, 0, 1, 1),
(39335, 818, 0.6394, 1, 0, 1, 1),
(39335, 858, 0.1864, 1, 0, 1, 1),
(39335, 890, 0.3615, 1, 0, 1, 1),
(39335, 929, 0.5125, 1, 0, 1, 1),
(39335, 934, 0.4305, 1, 0, 1, 1),
(39335, 936, 0.3904, 1, 0, 1, 1),
(39335, 937, 0.4016, 1, 0, 1, 1),
(39335, 1121, 0.3791, 1, 0, 1, 1),
(39335, 1203, 0.1815, 1, 0, 1, 1),
(39335, 1206, 0.784, 1, 0, 1, 1),
(39335, 1210, 0.792, 1, 0, 1, 1),
(39335, 1265, 0.4, 1, 0, 1, 1),
(39335, 1529, 1.0153, 1, 0, 1, 1),
(39335, 1607, 0.2, 1, 0, 1, 1),
(39335, 1705, 1.0008, 1, 0, 1, 1),
(39335, 1710, 0.347, 1, 0, 1, 1),
(39335, 1716, 0.3341, 1, 0, 1, 1),
(39335, 1717, 0.4016, 1, 0, 1, 1),
(39335, 1726, 0.3663, 1, 0, 1, 1),
(39335, 1973, 0.2088, 1, 0, 1, 1),
(39335, 2011, 0.3599, 1, 0, 1, 1),
(39335, 2059, 0.4289, 1, 0, 1, 1),
(39335, 2075, 0.1478, 1, 0, 1, 1),
(39335, 2098, 0.3518, 1, 0, 1, 1),
(39335, 2194, 0.3229, 1, 0, 1, 1),
(39335, 2236, 0.3566, 1, 0, 1, 1),
(39335, 2256, 0.3165, 1, 0, 1, 1),
(39335, 2276, 0.4337, 1, 0, 1, 1),
(39335, 2277, 0.3743, 1, 0, 1, 1),
(39335, 2278, 0.4032, 1, 0, 1, 1),
(39335, 2299, 0.4482, 1, 0, 1, 1),
(39335, 2455, 0.2024, 1, 0, 1, 1),
(39335, 2456, 0.188, 1, 0, 1, 1),
(39335, 2459, 0.2217, 1, 0, 1, 1),
(39335, 2565, 0.3775, 1, 0, 1, 1),
(39335, 2721, 0.4016, 1, 0, 1, 1),
(39335, 2800, 0.2956, 1, 0, 1, 1),
(39335, 2802, 0.2, 1, 0, 1, 1),
(39335, 2877, 0.3727, 1, 0, 1, 1),
(39335, 2878, 0.3261, 1, 0, 1, 1),
(39335, 2879, 0.392, 1, 0, 1, 1),
(39335, 2911, 0.3293, 1, 0, 1, 1),
(39335, 2912, 0.3518, 1, 0, 1, 1),
(39335, 2951, 0.4337, 1, 0, 1, 1),
(39335, 3020, 0.4209, 1, 0, 1, 1),
(39335, 3021, 0.3839, 1, 0, 1, 1),
(39335, 3040, 0.1, 1, 0, 1, 1),
(39335, 3192, 0.1382, 1, 0, 1, 1),
(39335, 3196, 0.2, 1, 0, 1, 1),
(39335, 3203, 0.3807, 1, 0, 1, 1),
(39335, 3283, 0.1735, 1, 0, 1, 1),
(39335, 3384, 0.4097, 1, 0, 1, 1),
(39335, 3385, 0.4209, 1, 0, 1, 1),
(39335, 3827, 0.3374, 1, 0, 1, 1),
(39335, 3864, 0.7502, 1, 0, 1, 1),
(39335, 4561, 0.2, 1, 0, 1, 1),
(39335, 4570, 0.151, 1, 0, 1, 1),
(39335, 4571, 0.2, 1, 0, 1, 1),
(39335, 4596, 0.1992, 1, 0, 1, 1),
(39335, 4696, 0.1767, 1, 0, 1, 1),
(39335, 5266, 0.2024, 1, 0, 1, 1),
(39335, 5631, 0.2233, 1, 0, 1, 1),
(39335, 5633, 0.3615, 1, 0, 1, 1),
(39335, 6048, 0.4562, 1, 0, 1, 1),
(39335, 6049, 0.3149, 1, 0, 1, 1),
(39335, 6050, 0.3502, 1, 0, 1, 1),
(39335, 6051, 0.2104, 1, 0, 1, 1),
(39335, 6052, 0.2972, 1, 0, 1, 1),
(39335, 6372, 0.204, 1, 0, 1, 1),
(39335, 6660, 0.1976, 1, 0, 1, 1),
(39335, 7734, 0.2281, 1, 0, 1, 1),
(39335, 7909, 0.8402, 1, 0, 1, 1),
(39335, 7910, 0.6506, 1, 0, 1, 1),
(39335, 8006, 0.4321, 1, 0, 1, 1),
(39335, 8190, 0.2056, 1, 0, 1, 1),
(39335, 9385, 0.3727, 1, 0, 1, 1),
(39335, 9395, 0.3486, 1, 0, 1, 1),
(39335, 9402, 0.2, 1, 0, 1, 1),
(39335, 9405, 0.4145, 1, 0, 1, 1),
(39335, 9435, 0.3261, 1, 0, 1, 1),
(39335, 11302, 0.2, 1, 0, 1, 1),
(39335, 12974, 0.3438, 1, 0, 1, 1),
(39335, 12979, 0.339, 1, 0, 1, 1),
(39335, 12982, 0.3518, 1, 0, 1, 1),
(39335, 12983, 0.4064, 1, 0, 1, 1),
(39335, 12984, 0.4546, 1, 0, 1, 1),
(39335, 12985, 0.3245, 1, 0, 1, 1),
(39335, 12987, 0.4755, 1, 0, 1, 1),
(39335, 12988, 0.3952, 1, 0, 1, 1),
(39335, 12989, 0.3502, 1, 0, 1, 1),
(39335, 12990, 0.4787, 1, 0, 1, 1),
(39335, 12992, 0.3454, 1, 0, 1, 1),
(39335, 12994, 0.3068, 1, 0, 1, 1),
(39335, 12996, 0.4113, 1, 0, 1, 1),
(39335, 12997, 0.3856, 1, 0, 1, 1),
(39335, 12998, 0.3615, 1, 0, 1, 1),
(39335, 12999, 0.4209, 1, 0, 1, 1),
(39335, 13002, 0.2554, 1, 0, 1, 1),
(39335, 13003, 0.2072, 1, 0, 1, 1),
(39335, 13004, 0.2265, 1, 0, 1, 1),
(39335, 13005, 0.3534, 1, 0, 1, 1),
(39335, 13007, 0.2056, 1, 0, 1, 1),
(39335, 13008, 0.1944, 1, 0, 1, 1),
(39335, 13010, 0.3582, 1, 0, 1, 1),
(39335, 13011, 0.3229, 1, 0, 1, 1),
(39335, 13012, 0.3807, 1, 0, 1, 1),
(39335, 13013, 0.2121, 1, 0, 1, 1),
(39335, 13016, 0.3036, 1, 0, 1, 1),
(39335, 13017, 0.4627, 1, 0, 1, 1),
(39335, 13019, 0.4, 1, 0, 1, 1),
(39335, 13020, 0.4835, 1, 0, 1, 1),
(39335, 13022, 0.2201, 1, 0, 1, 1),
(39335, 13024, 0.4097, 1, 0, 1, 1),
(39335, 13025, 0.3695, 1, 0, 1, 1),
(39335, 13027, 0.2121, 1, 0, 1, 1),
(39335, 13030, 0.1815, 1, 0, 1, 1),
(39335, 13031, 0.3454, 1, 0, 1, 1),
(39335, 13032, 0.3711, 1, 0, 1, 1),
(39335, 13033, 0.4643, 1, 0, 1, 1),
(39335, 13037, 0.5832, 1, 0, 1, 1),
(39335, 13038, 0.4482, 1, 0, 1, 1),
(39335, 13040, 0.1912, 1, 0, 1, 1),
(39335, 13041, 0.3936, 1, 0, 1, 1),
(39335, 13045, 0.3791, 1, 0, 1, 1),
(39335, 13047, 0.2104, 1, 0, 1, 1),
(39335, 13048, 0.3775, 1, 0, 1, 1),
(39335, 13049, 0.3711, 1, 0, 1, 1),
(39335, 13052, 0.2394, 1, 0, 1, 1),
(39335, 13054, 0.437, 1, 0, 1, 1),
(39335, 13056, 0.2217, 1, 0, 1, 1),
(39335, 13057, 0.4305, 1, 0, 1, 1),
(39335, 13059, 0.2217, 1, 0, 1, 1),
(39335, 13062, 0.3872, 1, 0, 1, 1),
(39335, 13063, 0.3679, 1, 0, 1, 1),
(39335, 13066, 0.1815, 1, 0, 1, 1),
(39335, 13067, 0.2, 1, 0, 1, 1),
(39335, 13070, 0.2265, 1, 0, 1, 1),
(39335, 13073, 0.188, 1, 0, 1, 1),
(39335, 13077, 0.1719, 1, 0, 1, 1),
(39335, 13079, 0.3904, 1, 0, 1, 1),
(39335, 13081, 0.5301, 1, 0, 1, 1),
(39335, 13084, 0.408, 1, 0, 1, 1),
(39335, 13087, 0.4177, 1, 0, 1, 1),
(39335, 13091, 0.2, 1, 0, 1, 1),
(39335, 13093, 0.3888, 1, 0, 1, 1),
(39335, 13094, 0.3727, 1, 0, 1, 1),
(39335, 13097, 0.3374, 1, 0, 1, 1),
(39335, 13099, 0.4659, 1, 0, 1, 1),
(39335, 13103, 0.4498, 1, 0, 1, 1),
(39335, 13105, 0.3968, 1, 0, 1, 1),
(39335, 13106, 0.3711, 1, 0, 1, 1),
(39335, 13108, 0.4402, 1, 0, 1, 1),
(39335, 13110, 0.4113, 1, 0, 1, 1),
(39335, 13111, 0.2394, 1, 0, 1, 1),
(39335, 13114, 0.4546, 1, 0, 1, 1),
(39335, 13119, 0.3823, 1, 0, 1, 1),
(39335, 13120, 0.1944, 1, 0, 1, 1),
(39335, 13121, 0.3823, 1, 0, 1, 1),
(39335, 13124, 0.339, 1, 0, 1, 1),
(39335, 13126, 0.1847, 1, 0, 1, 1),
(39335, 13127, 0.3004, 1, 0, 1, 1),
(39335, 13129, 0.392, 1, 0, 1, 1),
(39335, 13131, 0.4064, 1, 0, 1, 1),
(39335, 13135, 0.1815, 1, 0, 1, 1),
(39335, 13136, 0.3791, 1, 0, 1, 1),
(39335, 13137, 0.3358, 1, 0, 1, 1),
(39335, 13144, 0.196, 1, 0, 1, 1),
(39335, 13145, 0.3293, 1, 0, 1, 1),
(39335, 13146, 0.2, 1, 0, 1, 1),
(39335, 15222, 0.1526, 1, 0, 1, 1),
(39335, 15248, 0.2, 1, 0, 1, 1),
(39335, 15268, 0.2153, 1, 0, 1, 1),
(39335, 15497, 0.2, 1, 0, 1, 1),
(39335, 21929, 0.3486, 1, 0, 1, 1),
(39335, 23077, 0.3213, 1, 0, 1, 1),
(39335, 23079, 0.355, 1, 0, 1, 1),
(39335, 23107, 0.3888, 1, 0, 1, 1),
(39335, 23112, 0.3534, 1, 0, 1, 1),
(39335, 23117, 0.408, 1, 0, 1, 1),
(39335, 24222, 0.2, 1, 0, 1, 1),
(39335, 37757, 0.2, 1, 0, 1, 1),
(39335, 37758, 0.3084, 1, 0, 1, 1),
(39335, 37759, 0.392, 1, 0, 1, 1),
(39335, 37760, 0.4739, 1, 0, 1, 1),
(39335, 37761, 0.4273, 1, 0, 1, 1),
(39335, 37767, 0.3422, 1, 0, 1, 1),
(39335, 37768, 0.3582, 1, 0, 1, 1),
(39335, 37769, 0.3839, 1, 0, 1, 1),
(39335, 37770, 0.4884, 1, 0, 1, 1),
(39335, 37771, 0.3759, 1, 0, 1, 1),
(39335, 37778, 0.3422, 1, 0, 1, 1),
(39335, 37779, 0.4803, 1, 0, 1, 1),
(39335, 37780, 0.4225, 1, 0, 1, 1),
(39335, 37781, 0.5719, 1, 0, 1, 1),
(39335, 37786, 0.2, 1, 0, 1, 1),
(39335, 37789, 0.339, 1, 0, 1, 1),
(39335, 37790, 0.3936, 1, 0, 1, 1),
(39335, 37792, 0.3615, 1, 0, 1, 1),
(39335, 37793, 0.4691, 1, 0, 1, 1),
(39335, 37794, 0.3775, 1, 0, 1, 1),
(39335, 37797, 0.4578, 1, 0, 1, 1),
(39335, 37802, 0.2, 1, 0, 1, 1),
(39335, 37804, 0.347, 1, 0, 1, 1),
(39335, 37806, 0.3615, 1, 0, 1, 1),
(39335, 37808, 0.3293, 1, 0, 1, 1),
(39335, 37809, 0.3952, 1, 0, 1, 1),
(39335, 37810, 0.2651, 1, 0, 1, 1),
(39335, 37812, 0.3406, 1, 0, 1, 1),
(39335, 37822, 0.4611, 1, 0, 1, 1),
(39335, 37823, 0.4835, 1, 0, 1, 1),
(39335, 37824, 0.408, 1, 0, 1, 1),
(39335, 40211, 0.1735, 1, 0, 1, 1),
(39335, 40213, 0.1815, 1, 0, 1, 1),
(39335, 40215, 0.2, 1, 0, 1, 1),
(39335, 41777, 0.2715, 1, 0, 1, 1),
(39335, 41778, 0.1896, 1, 0, 1, 1),
(39335, 41780, 0.2104, 1, 0, 1, 1),
(39335, 41783, 0.2104, 1, 0, 1, 1),
(39335, 41784, 0.2763, 1, 0, 1, 1),
(39335, 41786, 0.2458, 1, 0, 1, 1),
(39335, 41787, 0.3422, 1, 0, 1, 1),
(39335, 41788, 0.2281, 1, 0, 1, 1),
(39335, 41789, 0.2265, 1, 0, 1, 1),
(39335, 45912, 2.0418, 1, 0, 1, 1),
(39335, 66916, 0.1, 1, 0, 1, 1),
(39335, 66976, 0.1655, 1, 0, 1, 1),
(39335, 67098, 0.1815, 1, 0, 1, 1),
(39335, 67110, 0.2362, 1, 0, 1, 1);

UPDATE `quest_template` SET `PrevQuestId`='25022' WHERE `Id`=25034;

-- Merciless Jungle Vine
SET @ENTRY := 38942;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,73155,0,0,0,0,0,11,38941,25,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Stun"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,6500,6500,60000,60000,86,46598,0,11,38941,25,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Grab Passengers"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,1,15500,15500,60000,60000,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Passengers"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,1,15500,15500,25000,25000,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");

DELETE FROM `conditions` WHERE `SourceEntry` = '73141';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 73141, 0, 0, 31, 0, 3, 38941, 0, 0, 0, '', 'Targeting -> Three Tooth');

UPDATE `creature_template` SET `VehicleId`=385 WHERE `entry`=38942;

DELETE FROM `spell_script_names` WHERE `spell_id` = '73141';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73141, 'spell_bramblestaff');

-- Three-Tooth
SET @ENTRY := 38941;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,9739,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,9739,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,9,1,100,0,0,20,9000,12000,11,12747,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Entangling Roots");

UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45 WHERE `entry`=38942;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=38942;

DELETE FROM `conditions` WHERE `SourceEntry` = '25057' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25057, 25045, 0),
(20, 8, 25057, 25043, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25057' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25057, 25045, 0),
(19, 8, 25057, 25043, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25059' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25059, 25045, 0),
(20, 8, 25059, 25043, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25059' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25059, 25045, 0),
(19, 8, 25059, 25043, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25074' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25074, 25057, 0),
(20, 8, 25074, 25059, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25074' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25074, 25057, 0),
(19, 8, 25074, 25059, 0);

UPDATE `gameobject_template` SET `data10`=70365 WHERE `entry`=201743;
UPDATE `creature_template` SET `minlevel`=32, `maxlevel`=32, `faction_A`=1802, `faction_H`=1802, `mindmg`=48, `maxdmg`=62, `attackpower`=15, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=39040;

DELETE FROM `creature_equip_template` WHERE `entry` = '39040';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(39040, 1, 1899, 1984, 0);

DELETE FROM `creature_loot_template` WHERE `item` = '52198';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3240, 52198, -45.4615, 1, 0, 1, 1);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56005';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56005, 'You\'re under arrest, follow me please.', 1, 1);

UPDATE `creature_template` SET `gossip_menu_id`=56005 WHERE `entry`=37743;

-- Taurajo Looter
SET @ENTRY := 37743;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,20,0,500,1000,60000,120000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text OOC"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,3000,9000,13000,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,8000,19000,23000,11,3583,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Deadly Poison"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,0,0,30,14000,15000,11,6434,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Slice and Dice at 30% HP"),
(@ENTRY,@SOURCETYPE,4,5,62,0,100,0,56005,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 14"),
(@ENTRY,@SOURCETYPE,6,0,7,0,100,0,0,0,0,0,2,1077,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Reset Faction");

DELETE FROM `conditions` WHERE `SourceGroup`=56005 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 56005, 0, 0, 0, 9, 0, 25057, 1, 0, 0, 0, 0, '', 'Show gossip only if quest 25057 is active');

DELETE FROM `spell_script_names` WHERE `spell_id` = '73387';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73387, 'spell_clap_em_in_irons');

-- Desolation Wind Rider
SET @ENTRY := 37974;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Players");

DELETE FROM `conditions` WHERE `SourceEntry` = '25120' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25120, 25106, 0),
(20, 8, 25120, 25108, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25120' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25120, 25106, 0),
(19, 8, 25120, 25108, 0);

UPDATE `creature_template` SET `VehicleId`=129 WHERE `entry`=39182;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '39182';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(39182, 63313, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '39182';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(39182, 39184, 1, 1, 'Marley\'s Flight Machine', 8, 0);

UPDATE `creature_template` SET `gossip_menu_id`=56006 WHERE `entry`=39155;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56006';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56006, 'I\'m ready Marley. Let\'s fly.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=56006 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 56006, 0, 0, 0, 9, 0, 25120, 1, 0, 0, 0, 0, '', 'Show gossip only if quest 25120 is active');

DELETE FROM `waypoints` WHERE `entry` = '39182';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(39182, 1, -4196.12, -2125.70, 111.77, 'Twinbraid Flying Machine WP'),
(39182, 2, -4216.63, -2198.04, 118.69, 'Twinbraid Flying Machine WP'),
(39182, 3, -4200.92, -2313.07, 148.89, 'Twinbraid Flying Machine WP'),
(39182, 4, -4143.48, -2322.49, 161.29, 'Twinbraid Flying Machine WP'),
(39182, 5, -4078.08, -2295.34, 124.80, 'Twinbraid Flying Machine WP');

UPDATE `creature_template` SET `modelid1`=22878, `name`='Marley\'s Flight Machine', `minlevel`=35, `maxlevel`=35 WHERE `entry`=39182;

DELETE FROM `creature_text` WHERE `entry`=39184;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39184,0,0,'Hold on tight back there! Seat belts are for chumps.',12,0,100,0,0,0,'Comment'),
(39184,1,0,'We\'re all very proud of Bael Modan. It was the first dwarven settlement in Kalimdor',12,0,100,0,0,0,'Comment'),
(39184,2,0,'Up ahead Bael\'dun Keep. Isn\'t she a beauty? That stronghold is indestructible!',12,0,100,0,0,0,'Comment');

-- Marley Twinbraid
SET @ENTRY := 39184;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,6000,6000,120000,120000,1,0,12000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,39184,0,0,1,1,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,39184,0,0,1,2,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2");

UPDATE `creature` SET `phaseMask`=1 WHERE `id` = '39213';

-- Bael'dun Phase 2 Effects Bunny (Large)
SET @ENTRY := 39213;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explode");

UPDATE `creature_template` SET `speed_walk`=3.14, `speed_run`=4.30 WHERE `entry`=39182;

-- Marley's Flight Machine
SET @ENTRY := 39182;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,0,39182,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,2,3,40,0,100,0,4,0,0,0,54,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - WP Pause"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,39213,150,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Triggers"),
(@ENTRY,@SOURCETYPE,4,7,61,0,100,0,0,0,0,0,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Explode"),
(@ENTRY,@SOURCETYPE,5,6,40,0,100,0,5,0,0,0,11,71495,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Explode Again"),
(@ENTRY,@SOURCETYPE,6,8,61,0,100,0,0,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Passengers"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,0,0,0,0,33,39187,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Marley Twinbraid
SET @ENTRY := 39155;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,56006,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,85,73578,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Invoker Summon Flight Machine");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=39213;
UPDATE `creature_template_addon` SET `auras`='69526 49414' WHERE `entry`=39220;
UPDATE `creature_template_addon` SET `auras`='73600 61204 49414' WHERE `entry`=39188;
UPDATE `creature_template_addon` SET `auras`='46598 49414' WHERE `entry`=39218;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25120';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 4856, 25120, 1, 66, 0),
(49416, 4872, 25120, 1, 66, 0);

DELETE FROM `spell_area` WHERE `spell` = '55858' AND `quest_start` = '25120';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(55858, 4856, 25120, 1, 66, 0),
(55858, 4872, 25120, 1, 66, 0);

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=39213;
UPDATE `creature_addon` SET `auras`='49414' WHERE `guid`=740326;
UPDATE `creature_addon` SET `auras`='69526 49414' WHERE `guid`=740327;
UPDATE `creature_addon` SET `auras`='73600 61204 49414' WHERE `guid`=740294;
UPDATE `creature_addon` SET `auras`='' WHERE `guid` IN (740328, 740323, 740324, 740349);
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=39218;

UPDATE `creature` SET `phaseMask`=4 WHERE id = '39238';
UPDATE `creature_addon` SET `auras`='73677' WHERE `auras`='52855';
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=39238;
UPDATE `creature` SET `phaseMask`=4 WHERE `id` IN (39218, 38152);
UPDATE `gameobject` SET `phaseMask`=4 WHERE `guid`=733466;
UPDATE `creature` SET `phaseMask`=4 WHERE `guid` IN (740294, 740327);
UPDATE `gameobject` SET `phaseMask`=4 WHERE `id`=202562;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=202567;

DELETE FROM `gameobject_loot_template` WHERE `item` = '52491';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(202567, 52491, -100, 1, 0, 1, 1);

UPDATE `gameobject_template` SET `data1`=202567 WHERE `entry`=202567;
UPDATE `gameobject` SET `spawntimesecs`=60 WHERE `guid`=733466;
UPDATE `creature` SET `phaseMask`=4 WHERE `id`=39227;
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=39227;

-- Emergency Fire Valve
SET @ENTRY := 202562;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,39227,6,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Triggers");

-- Bael'dun Emergency Fire System
SET @ENTRY := 39227;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,95730,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Water on Players");

DELETE FROM `creature_template` WHERE `entry` = '39202';
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(39202, 0, 0, 0, 0, 0, 328, 21072, 0, 0, 'Bael\'dun Phase 4 Effects Bunny (Medium)', '', '', 0, 1, 1, 0, 0, 190, 190, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 33555200, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 7, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 130, '', 15595);

SET @CGUID := 400950;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+84;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 39202, 1, 1, 2, 0, 0, -4094.47, -2385.21, 118.16, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+1, 39202, 1, 1, 2, 0, 0, -4065.2, -2366.46, 108.993, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+2, 39202, 1, 1, 2, 0, 0, -4053.33, -2381.03, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+3, 39202, 1, 1, 2, 0, 0, -4053.22, -2380.13, 118.16, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+4, 39202, 1, 1, 2, 0, 0, -4049.75, -2376.53, 124.826, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+5, 39202, 1, 1, 2, 0, 0, -4086.4, -2356.27, 108.992, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+6, 39202, 1, 1, 2, 0, 0, -4073.16, -2400.02, 135.939, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+7, 39202, 1, 1, 2, 0, 0, -4088.07, -2350.72, 126.214, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+8, 39202, 1, 1, 2, 0, 0, -4074.72, -2339.32, 127.603, 3.78736, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+9, 39202, 1, 1, 2, 0, 0, -4077.66, -2303.17, 127.163, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+10, 39202, 1, 1, 2, 0, 0, -4114.87, -2318.33, 127.368, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+11, 39202, 1, 1, 2, 0, 0, -4080.24, -2309.83, 129.544, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+12, 39202, 1, 1, 2, 0, 0, -4119.1, -2338.02, 133.496, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+13, 39202, 1, 1, 2, 0, 0, -4080.69, -2380.89, 118.159, 6.17846, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+14, 39202, 1, 1, 2, 0, 0, -4053.64, -2367.51, 124.826, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+15, 39202, 1, 1, 2, 0, 0, -4061.65, -2326.32, 127.603, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+16, 39202, 1, 1, 2, 0, 0, -4114.48, -2352.03, 127.603, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+17, 39202, 1, 1, 2, 0, 0, -4073.75, -2391.88, 126.214, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+18, 39202, 1, 1, 2, 0, 0, -4080.21, -2340.06, 126.214, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+19, 39202, 1, 1, 2, 0, 0, -4078.46, -2343.71, 126.214, 4.2237, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+20, 39202, 1, 1, 2, 0, 0, -4067.91, -2368.79, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+21, 39202, 1, 1, 2, 0, 0, -4057.18, -2370.45, 135.938, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+22, 39202, 1, 1, 2, 0, 0, -4049.96, -2348.1, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+23, 39202, 1, 1, 2, 0, 0, -4099.11, -2340.55, 148.464, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+24, 39202, 1, 1, 2, 0, 0, -4072.8, -2351.48, 108.992, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+25, 39202, 1, 1, 2, 0, 0, -4076.07, -2358.18, 108.992, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+26, 39202, 1, 1, 2, 0, 0, -4079.78, -2359.66, 108.992, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+27, 39202, 1, 1, 2, 0, 0, -4067.83, -2385.19, 110.381, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+28, 39202, 1, 1, 2, 0, 0, -4071.68, -2417.61, 126.216, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+29, 39202, 1, 1, 2, 0, 0, -4098.6, -2376.79, 135.939, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+30, 39202, 1, 1, 2, 0, 0, -4089.16, -2388.17, 118.16, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+31, 39202, 1, 1, 2, 0, 0, -4046.55, -2363.79, 135.94, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+32, 39202, 1, 1, 2, 0, 0, -4076.09, -2333.31, 127.603, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+33, 39202, 1, 1, 2, 0, 0, -4081.03, -2374.4, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+34, 39202, 1, 1, 2, 0, 0, -4064.93, -2316, 144.774, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+35, 39202, 1, 1, 2, 0, 0, -4119.64, -2340.97, 144.587, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+36, 39202, 1, 1, 2, 0, 0, -4064.92, -2314.12, 133.504, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+37, 39202, 1, 1, 2, 0, 0, -4109.39, -2329.33, 125.081, 2.33874, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+38, 39202, 1, 1, 2, 0, 0, -4055.55, -2366.64, 118.159, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+39, 39202, 1, 1, 2, 0, 0, -4067.16, -2392.39, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+40, 39202, 1, 1, 2, 0, 0, -4112.06, -2357.07, 127.603, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+41, 39202, 1, 1, 2, 0, 0, -4090.01, -2393, 136.616, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+42, 39202, 1, 1, 2, 0, 0, -4086.66, -2404.45, 125.382, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+43, 39202, 1, 1, 2, 0, 0, -4098.91, -2388.33, 124.826, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+44, 39202, 1, 1, 2, 0, 0, -4048.64, -2389.18, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+45, 39202, 1, 1, 2, 0, 0, -4066.56, -2359.03, 108.992, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+46, 39202, 1, 1, 2, 0, 0, -4073.33, -2411.59, 135.942, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+47, 39202, 1, 1, 2, 0, 0, -4051.99, -2352.68, 135.939, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+48, 39202, 1, 1, 2, 0, 0, -4087.48, -2398.57, 135.939, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+49, 39202, 1, 1, 2, 0, 0, -4043.29, -2386.33, 125.382, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+50, 39202, 1, 1, 2, 0, 0, -4103.69, -2373.72, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+51, 39202, 1, 1, 2, 0, 0, -4093.46, -2386.03, 135.939, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+52, 39202, 1, 1, 2, 0, 0, -4068.12, -2327.85, 127.603, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+53, 39202, 1, 1, 2, 0, 0, -4062.71, -2378.65, 126.214, 2.86234, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+54, 39202, 1, 1, 2, 0, 0, -4050.06, -2379.62, 118.622, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+55, 39202, 1, 1, 2, 0, 0, -4082.55, -2382.29, 135.938, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+56, 39202, 1, 1, 2, 0, 0, -4098.18, -2361.92, 126.695, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+57, 39202, 1, 1, 2, 0, 0, -4087.93, -2388.38, 124.826, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+58, 39202, 1, 1, 2, 0, 0, -4080.78, -2392.09, 118.16, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+59, 39202, 1, 1, 2, 0, 0, -4049.7, -2370.26, 125.627, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+60, 39202, 1, 1, 2, 0, 0, -4082.01, -2381.93, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+61, 39202, 1, 1, 2, 0, 0, -4071.54, -2338.13, 127.603, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+62, 39202, 1, 1, 2, 0, 0, -4078.99, -2372, 108.992, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+63, 39202, 1, 1, 2, 0, 0, -4097.25, -2348.51, 127.603, 2.04204, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+64, 39202, 1, 1, 2, 0, 0, -4069.72, -2363.9, 108.992, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+65, 39202, 1, 1, 2, 0, 0, -4065.97, -2379.5, 110.381, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+66, 39202, 1, 1, 2, 0, 0, -4069.15, -2422.35, 135.937, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+67, 39202, 1, 1, 2, 0, 0, -4048.6, -2362.34, 119.123, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+68, 39202, 1, 1, 2, 0, 0, -4041.05, -2374.65, 121.215, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+69, 39202, 1, 1, 2, 0, 0, -4051.56, -2379.12, 135.939, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+70, 39202, 1, 1, 2, 0, 0, -4039.14, -2379.7, 135.94, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+71, 39202, 1, 1, 2, 0, 0, -4070.45, -2385.41, 126.214, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+72, 39202, 1, 1, 2, 0, 0, -4063.58, -2344.5, 126.907, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+73, 39202, 1, 1, 2, 0, 0, -4064.9, -2417.26, 126.216, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+74, 39202, 1, 1, 2, 0, 0, -4084.44, -2385.47, 124.826, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+75, 39202, 1, 1, 2, 0, 0, -4062.98, -2368.35, 118.158, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+76, 39202, 1, 1, 2, 0, 0, -4076.57, -2395.16, 118.16, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+77, 39202, 1, 1, 2, 0, 0, -4058.53, -2389.92, 119.282, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+78, 39202, 1, 1, 2, 0, 0, -4042.77, -2374.26, 135.941, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+79, 39202, 1, 1, 2, 0, 0, -4099, -2344.23, 127.603, 5.98648, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+80, 39202, 1, 1, 2, 0, 0, -4044.84, -2369.71, 118.16, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+81, 39202, 1, 1, 2, 0, 0, -4083.9, -2369.93, 108.992, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+82, 39202, 1, 1, 2, 0, 0, -4066.43, -2371.28, 131.24, 4.93928, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+83, 39202, 1, 1, 2, 0, 0, -4074.9, -2360, 126.214, 2.86234, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+84, 39202, 1, 1, 2, 0, 0, -4090.06, -2346.2, 126.214, 5.89921, 300, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '39202';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(39202, '73671 52855');

UPDATE `creature` SET `phaseMask`=6 WHERE `id`=39202;

DELETE from `creature` WHERE `guid` IN
(740292,740314,740316,740318,740320,740322,740342,740344,740365,740367,740369,740371,740373,740421,740423,
740425,740427,740429,740431,740433,740435,740437,740439,740441,740443,740445,740447,740449,740451,740453,740455,
740457,740459);

DELETE from `creature_addon` WHERE `guid` IN
(740292,740314,740316,740318,740320,740322,740342,740344,740365,740367,740369,740371,740373,740421,740423,
740425,740427,740429,740431,740433,740435,740437,740439,740441,740443,740445,740447,740449,740451,740453,740455,
740457,740459);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '39238';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `description`, `summontype`, `summontimer`) VALUES
(39238, 39218, 'Burning Debris', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '39238';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(39238, 46598, 0, 0);

UPDATE `creature_template` SET `IconName`='Interact', `npcflag`=1, `flags_extra`=0 WHERE `entry`=39238;

DELETE FROM `creature_text` WHERE `entry`=39218;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39218,0,0,'The roof over the mess hall collapsed. So many - dead!',12,0,100,0,0,0,'Comment'),
(39218,0,1,'I thought I was done for! Thank you!',12,0,100,0,0,0,'Comment'),
(39218,0,2,'This whole keep is going to collapse!',12,0,100,0,0,0,'Comment'),
(39218,0,3,'This place is up crap creek an\' I ain\'t go no shovel.',12,0,100,0,0,0,'Comment'),
(39218,0,4,'How could they have done this?',12,0,100,0,0,0,'Comment'),
(39218,0,5,'Thank you, thank you!',12,0,100,0,0,0,'Comment'),
(39218,0,6,'How could this have happened?',12,0,100,0,0,0,'Comment');

-- Bael'dun Survivor
SET @ENTRY := 39218;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,33,39219,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=39197;
UPDATE `creature_template` SET `modelid1`=31377 WHERE `entry`=39238;
UPDATE `creature_template` SET `npcflag`=0 WHERE `entry`=39218;
UPDATE `creature` SET `npcflag`=2 WHERE `guid`=740326;

-- Burning Debris
SET @ENTRY := 39238;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,85,73679,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Invoker Cast Digging"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,39218,2,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Survivor"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,11,78609,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Smoke"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `conditions` WHERE `SourceEntry` = '25183' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25183, 25174, 0),
(20, 8, 25183, 25175, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25183' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25183, 25174, 0),
(19, 8, 25183, 25175, 0);

-- Frazzlecraz Explosives
SET @ENTRY := 202596;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,33,39315,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit");

UPDATE `gameobject` SET `phaseMask`=2 WHERE `id`=202596 AND phaseMask = '262143';
UPDATE `gameobject_template` SET `data2`=60000 WHERE `entry`=202596;

DELETE FROM `spell_script_names` WHERE `spell_id` = '73720';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73720, 'spell_frazzlecraz_cave');

-- Big Nasty Plunger
SET @ENTRY := 202598;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,25185,0,0,0,9,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Activate Object");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=38821;