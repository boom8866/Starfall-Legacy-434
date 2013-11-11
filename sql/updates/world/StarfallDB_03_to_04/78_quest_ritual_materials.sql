UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=33313;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '33313';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(33313, 62788, 2);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '84186';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(84186, 42716, 2, 'Sleep State - Add Root');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '33127';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(33127, 62512, 2);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '33978';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(33978, 64116, 2);

-- Moonstalker
SET @ENTRY := 33127;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4500,12000,17000,11,75008,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Pounce"),
(@ENTRY,@SOURCETYPE,1,5,1,0,100,0,5000,10000,20000,40000,75,84186,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Every 20-40 seconds - Sleep"),
(@ENTRY,@SOURCETYPE,3,6,1,0,100,0,15000,25000,50000,60000,28,84186,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Every 50-60 seconds - Asleep"),
(@ENTRY,@SOURCETYPE,5,8,61,0,100,0,40000,40000,40000,40000,81,16777216,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link Sleep - Set Flag Spellclick"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,55000,55000,55000,55000,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link Asleep - Remove Npc Flag Spellclick"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,2,2153,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link to Remove Npc Flag Spellclick - Set Faction 2153"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,2,31,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link to Set Flag Spellclick - Set Faction 31"),
(@ENTRY,@SOURCETYPE,9,0,31,0,100,0,62512,1,0,0,2,2153,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Aggressive"),
(@ENTRY,@SOURCETYPE,10,0,31,0,100,0,62512,1,0,0,28,84186,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Remove Sleep"),
(@ENTRY,@SOURCETYPE,11,0,31,0,100,0,62512,1,0,0,49,0,0,0,0,0,0,21,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Attack Player");

-- Hungry Thistle Bear
SET @ENTRY := 33978;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,8000,18000,22000,11,5422,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Lacerate"),
(@ENTRY,@SOURCETYPE,1,2,1,0,100,0,15000,30000,30000,50000,17,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Emote Eat"),
(@ENTRY,@SOURCETYPE,2,5,61,0,100,0,0,0,0,0,81,16777216,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link to Emote - Set Spellclick"),
(@ENTRY,@SOURCETYPE,3,4,1,0,100,0,25000,30000,25000,30000,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Emote Eat"),
(@ENTRY,@SOURCETYPE,4,6,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link to Emote Remove - Remove Spellclick"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,2,31,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link to Set Spellclick - Set Faction 31"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,2,2154,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link to Remove Spellclick - Set Faction 2154");

-- Mottled Doe
SET @ENTRY := 33313;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,31,0,100,0,62788,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,31,0,100,0,62788,1,0,0,69,0,0,0,0,0,0,11,33313,100,0,0.0,0.0,0.0,0.0,"On Spellhit - Flee");