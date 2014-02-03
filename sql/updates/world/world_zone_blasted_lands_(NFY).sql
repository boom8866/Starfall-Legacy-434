DELETE FROM `spell_script_names` WHERE `spell_id` = '78838';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(78838, 'spell_enohar_explosive_arrow');

UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=134, `attackpower`=34, `minrangedmg`=72, `maxrangedmg`=107, `rangedattackpower`=27 WHERE `entry`=42235;

DELETE FROM `spell_target_position` WHERE `id` IN (78923, 78924);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(78923, -11213.82, -3509.54, 8.11, 1.88),
(78924, -11315.19, -3442.09, 7.46, 1.84);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11479 AND `id`=0;

-- Salt-Flop
SET @ENTRY := 41265;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11479,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11479,0,0,0,56,10754,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Add Quest Item");

DELETE FROM `conditions` WHERE `SourceGroup`=11479;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11479, 0, 0, 0, 9, 0, 26168, 0, 0, 0, 0, 0, '', 'Salt-Flop - Show gossip only if quest 26168 is active');

UPDATE `creature` SET `spawndist`=60, `MovementType`=1 WHERE `id` IN (6004, 6005, 6006);

-- Head of Grol
SET @ENTRY := 203230;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,92394,41200,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger");

-- Generic Bunny - PRK
SET @ENTRY := 41200;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,3000,3000,3000,3000,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 seconds) - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,4000,4000,4000,4000,12,41267,4,30000,0,0,0,8,0,0,0,-11445.2,-3800.7,-8.93,2.16,"Update (4 seconds) - Summon Grol"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,1,12000,12000,12000,12000,70,41267,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (12 seconds) - Respawn");

-- Spirit of Grol
SET @ENTRY := 41267;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Unattackable"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,1,3000,3000,3000,3000,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 secs) - Set Aggressive"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,3000,3000,3000,3000,19,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 secs) - Set Attackable"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,11,84310,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Bloodlust"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,1500,1500,15000,15000,11,16555,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Drowning Death"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,3500,3500,9500,15000,11,80182,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Uppercut");

UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=134, `attackpower`=34, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=41267;

DELETE FROM `creature_text` WHERE `entry`=41200;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41200,0,0,'You hear a noise behind you.',41,0,100,0,0,0,'Comment');

DELETE FROM `creature` WHERE `guid`=774732;
DELETE FROM `creature_addon` WHERE `guid`=774732;

UPDATE `creature_template` SET `modelid1`=32425 WHERE `entry`=41402;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=25707;

-- Abandoned Bloodwash Crate
SET @ENTRY := 41402;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,0,0,0,0,85,77549,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Start Event"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,2,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

UPDATE `creature_template` SET `ScriptName`='npc_abandoned_bloodwash_trigger' WHERE `entry`=41454;
UPDATE `creature_template` SET `scale`=5, `modelid1`=32425, `InhabitType`=4 WHERE `entry`=41454;

DELETE FROM `creature_text` WHERE `entry`=42298;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42298,0,0,'With the power within the amulets of Razelikh...',12,0,100,0,0,0,'Comment');
(42298,1,0,'... I bind you to his lair!',12,0,100,0,0,0,'Comment');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11613';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11613, 'I would like to start the Amulet Ritual, Kasim.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=11613;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11613, 0, 0, 0, 9, 0, 26170, 0, 0, 0, 0, 0, '', 'Kasim Sharim - Show gossip only if quest 26170 is active');

UPDATE `quest_template` SET `SpecialFlags`=2, `Flags`=0 WHERE `Id`=26170;

-- Kasim Sharim
SET @ENTRY := 42298;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11613,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11613,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-11221.7,-3476.83,9.29,0.35,"On Gossip Select - Move to Pos"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11613,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Quest Flag"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,0,8,0,0,0,11,77581,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Cast Amulet Ritual"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,42298,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,42298,0,0,70,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Respawn Self"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset NPC Flag");

DELETE FROM `spell_script_names` WHERE `spell_id` = '77581';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77581, 'spell_amulet_ritual');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '26170';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5086, 26170, 1, 2, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=774022;

DELETE FROM `gameobject_loot_template` WHERE `item` = '55837';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(29583, 55837, -100);

DELETE FROM `gameobject_loot_template` WHERE `item` = '55829';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(29581, 55829, -100);

DELETE FROM `gameobject_loot_template` WHERE `item` = '55836';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(29582, 55836, -100);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=727384;

-- OP EVENT!
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=762627;

DELETE FROM `spell_target_position` WHERE `id`=12885;
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(12885, -11228.09, -2834.85, 158.29, 3.66);