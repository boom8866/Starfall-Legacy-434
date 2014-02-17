DELETE FROM `spell_script_names` WHERE `spell_id` = '78838';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(78838, 'spell_enohar_explosive_arrow');

UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=134, `attackpower`=34, `minrangedmg`=72, `maxrangedmg`=107, `rangedattackpower`=27 WHERE `entry` IN (42235, 41471);

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
(15, 11479, 0, 0, 0, 9, 0, 26168, 0, 0, 0, 0, 0, '', 'Salt-Flop - Show gossip only if quest 26168 is active'),
(15, 11479, 0, 0, 1, 9, 0, 25698, 0, 0, 0, 0, 0, '', 'Salt-Flop - Show gossip only if quest 25698 is active');

UPDATE `creature` SET `spawndist`=60, `MovementType`=1 WHERE `id` IN (6004, 6005, 6006);

-- Head of Grol
SET @ENTRY := 203230;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,92394,41200,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger");

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
(42298,0,0,'With the power within the amulets of Razelikh...',12,0,100,0,0,0,'Comment'),
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
(49416, 5086, 26170, 1, 66, 0);

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

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=41193;

DELETE FROM `spell_target_position` WHERE `id` = '77159';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(77159, -11277.20, -2547.67, 107.56, 3.10);

DELETE FROM `creature_text` WHERE `entry`=41193;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41193,0,0,'Protect Loramus\' Body until the ritual completes!',42,0,100,0,0,0,'Comment'),
(41193,1,0,'Loramus\'s Body is under attack! Protect him!',42,0,100,0,0,0,'Comment'),
(41193,2,0,'Grol!!!',14,0,100,0,0,0,'Comment'),
(41193,3,0,'You, what have you done?',14,0,100,0,0,0,'Comment'),
(41193,4,0,'I see... this is the path I must take. Meet up with me back in the cave, heroes.',14,0,100,0,0,0,'Comment');

-- Generic Bunny - PRK
SET @ENTRY := 41200;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,3000,3000,3000,3000,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 seconds) - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,4000,4000,4000,4000,12,41267,4,30000,0,0,0,8,0,0,0,-11445.2,-3800.7,-8.93,2.16,"Update (4 seconds) - Summon Grol"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,1,12000,12000,12000,12000,70,41267,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (12 seconds) - Respawn"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,1,0,2,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,7,0,60,2,100,0,3000,7500,3000,7500,11,77214,0,0,0,0,0,11,41193,200,0,0.0,0.0,0.0,0.0,"Update - Cast Beam");

-- Loramus' Body
SET @ENTRY := 41193;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,41200,200,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 2 to Bunny"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,5000,10000,30000,60000,12,41191,4,30000,0,0,0,8,0,0,0,-11295.8,-2559.71,97.03,1.03,"Update - Summon Obstructor (1)"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,20000,30000,30000,60000,12,41191,4,30000,0,0,0,8,0,0,0,-11296.9,-2538.74,97.09,5.77,"Update - Summon Obstructor (2)"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,20000,30000,30000,60000,12,41191,4,30000,0,0,0,8,0,0,0,-11276.0,-2529.44,97.16,4.6,"Update - Summon Obstructor (3)"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,0,15500,25500,30000,60000,12,41191,4,30000,0,0,0,8,0,0,0,-11262.2,-2546.12,97.05,3.26,"Update - Summon Obstructor (4)"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,5000,10000,30000,60000,12,41191,4,30000,0,0,0,8,0,0,0,-11272.9,-2565.48,97.06,2.01,"Update - Summon Obstructor (5)"),
(@ENTRY,@SOURCETYPE,7,0,54,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,8,0,60,1,100,1,120000,120000,120000,120000,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (120 seconds) - Set Phase 2"),
(@ENTRY,@SOURCETYPE,9,0,60,2,100,1,3000,3000,3000,3000,1,2,5000,0,0,0,0,8,0,0,0,-11295.8,-2559.71,97.03,1.03,"Update (3 seconds) - Talk 2"),
(@ENTRY,@SOURCETYPE,10,0,52,2,100,1,2,41193,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,11,0,52,2,100,1,3,41193,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,12,0,52,2,100,1,4,41193,0,0,33,41193,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Quest Complete"),
(@ENTRY,@SOURCETYPE,13,0,52,2,100,1,4,41193,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Force Despawn"),
(@ENTRY,@SOURCETYPE,14,0,8,0,100,1,77129,36,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Spellhit - Talk 1");

-- Shadowsworn Obstructor
SET @ENTRY := 41191;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-11282.5,-2548.41,99.33,0.09,"On Just Summoned - Move to Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,11,77129,0,0,0,0,0,11,41193,200,0,0.0,0.0,0.0,0.0,"On Just Summoned - Disrupt Ritual"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

DELETE FROM `creature` WHERE `guid` = '400495';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(400495, 7783, 0, 1, 1, 0, 1, -11219.4, -3475.61, 9.81452, 4.27267, 300, 0, 0, 3758, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '400495';
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(400495, 0, 0, 0, 0, 0, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '26162';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 1440, 26162, 26162, 1, 2, 11);

DELETE FROM `creature_template_addon` WHERE `entry` = '42334';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(42334, '78986');

DELETE FROM `creature_text` WHERE `entry`=42334;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42334,0,0,'What are you doing? You threaten my work! The Tainted Scar\'s revival is all thanks to me!',14,0,100,0,0,0,'Comment'),
(42334,1,0,'I only wanted to... do something... good...',14,0,100,0,0,0,'Comment');

-- Marl Wormthorn
SET @ENTRY := 42334;
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
(@ENTRY,@SOURCETYPE,10,0,1,0,100,0,500,1000,600000,600000,11,79833,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Mark of the Wild on Spawn"),
(@ENTRY,@SOURCETYPE,11,0,0,1,100,0,7000,9000,14000,20000,11,33844,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Entangling Roots"),
(@ENTRY,@SOURCETYPE,12,0,2,1,100,0,0,40,19000,27000,11,12160,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rejuvenation at 40% HP"),
(@ENTRY,@SOURCETYPE,13,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,14,0,6,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 1");

-- Illycor
SET @ENTRY := 41163;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,14000,22000,11,84297,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Corrosive Saliva"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7000,9000,18000,27000,11,84298,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Optic Link");

UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=134, `attackpower`=34 WHERE `entry` IN
(41163, 41171, 41162, 41173, 41386, 41387, 41404, 41405, 41423, 41422, 45119, 41470, 45125, 42336, 42337, 42338);
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=762634;
UPDATE `creature_template` SET `modelid1`=31378, `VehicleId`=887 WHERE `entry`=41174;
UPDATE `gameobject_template` SET `data10`=77052, `data5`=1 WHERE `entry`=203192;

-- Inconspicuous Box
SET @ENTRY := 203192;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,85,77052,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Box");

DELETE FROM `creature_text` WHERE `entry`=5998;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(5998,0,0,'Hmm...',12,0,100,0,0,0,'Comment'),
(5998,0,1,'Get back to work! Oh wait... you\'re just a box, never mind.',12,0,100,0,0,0,'Comment'),
(5998,0,2,'What in tarnation?',12,0,100,0,0,0,'Comment'),
(5998,0,3,'How peculiar.',12,0,100,0,0,0,'Comment'),
(5998,0,4,'A box that walks? I should ask Hondo about this... nah, maybe later.',12,0,100,0,0,0,'Comment'),
(5998,0,5,'I do declare... a moving box. The engineers have really done it this time!',12,0,100,0,0,0,'Comment'),
(5998,0,6,'Oh my.',12,0,100,0,0,0,'Comment'),
(5998,0,7,'Was that box there a second ago?',12,0,100,0,0,0,'Comment');

-- Nethergarde Engineer
SET @ENTRY := 5997;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,1,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - Out Of Combat - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - Out Of Combat - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,2,3,4,0,100,0,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - On Aggro - Cast Shoot"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - On Aggro - Increment Phase"),
(@ENTRY,@SOURCETYPE,4,5,9,0,100,0,5,30,2300,3900,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 5 - 30 Range - Cast Shoot"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 5 - 30 Range - Display ranged weapon"),
(@ENTRY,@SOURCETYPE,6,7,9,0,100,0,25,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 25 - 80 Range - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 25 - 80 Range - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,8,9,9,0,100,0,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 0 - 5 Range - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,9,10,9,0,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 0 - 5 Range - Display melee weapon"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 0 - 5 Range - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,11,12,9,0,100,0,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 5 - 15 Range - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,12,0,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 5 - 15 Range - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,13,0,0,0,100,0,8000,11000,12000,16000,11,8858,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - In Combat - Cast Bomb"),
(@ENTRY,@SOURCETYPE,14,0,2,0,100,1,0,15,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 15% HP - Increment Phase"),
(@ENTRY,@SOURCETYPE,15,16,2,0,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 15% HP - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,16,0,61,0,100,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,18,0,7,0,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Engineer - On Evade - Display melee weapon"),
(@ENTRY,@SOURCETYPE,19,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=5997;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(5997,0,0,'%s attempts to run away in fear!',16,0,100,0,0,0,'combat Flee'),
(5997,1,0,'Hmm...',12,0,100,0,0,0,'Comment'),
(5997,1,1,'Hey! Somebody\'s ambulatory cube is escaping!',12,0,100,0,0,0,'Comment'),
(5997,1,2,'Heavens to Betsy!',12,0,100,0,0,0,'Comment'),
(5997,1,3,'Looks like somebody\'s getting a special delivery.',12,0,100,0,0,0,'Comment'),
(5997,1,4,'I think I\'ve been down in this mine too long.',12,0,100,0,0,0,'Comment'),
(5997,1,5,'Look out! It\'s a box-demon!"',12,0,100,0,0,0,'Comment'),
(5997,1,6,'Gadzooks! Would ya look at that?"',12,0,100,0,0,0,'Comment');

-- Nethergarde Foreman
SET @ENTRY := 5998;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,3000,12000,16000,11,5115,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Foreman - In Combat - Cast Battle Command"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Nethergarde Foreman - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,2,0,38,0,35,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=41173;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41173,0,0,'Is that box walking on its own? Am I going mad? Quick, someone check the canary!',12,0,100,0,0,0,'Comment');

-- Chief Prospector Hondo
SET @ENTRY := 41173;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,52,0,100,0,0,41173,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Attack Start Invoker"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,41173,0,0,45,0,1,0,0,0,0,11,41174,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Box"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,12000,12000,12000,12000,11,80382,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Dirt Toss"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,2000,15000,15000,11,6016,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Pierce Armor"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,8500,8500,14500,20000,11,79726,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Ticking Time Bomb"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

-- Inconspicuous Box
SET @ENTRY := 41174;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Unattackable"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,5000,5000,5000,5000,45,0,1,0,0,0,0,11,0,15,0,0.0,0.0,0.0,0.0,"Update - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,5000,5000,5000,5000,45,0,2,0,0,0,0,11,0,15,0,0.0,0.0,0.0,0.0,"Update - Set Data 2 to Creatures"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,37,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Die");

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` IN (25688, 25700);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5086, 25688, 1, 66, 0),
(49416, 5086, 25700, 1, 66, 0);

DELETE FROM `conditions` WHERE `SourceEntry`=25674;

UPDATE `gameobject_template` SET `data5`=1, `flags`=0 WHERE `entry`=203289;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=762629;

DELETE FROM `creature` WHERE `guid` IN (774735, 776721, 774734, 774736);
DELETE FROM `creature_addon` WHERE `guid` IN (774735, 776721, 774734, 774736);
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=722303;

UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=134, `attackpower`=34, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (41290, 41280, 41292);
UPDATE `creature_template` SET `mindmg`=235, `maxdmg`=356, `attackpower`=80, `baseattacktime`=1500, `rangeattacktime`=1500 WHERE `entry` = '41279';
UPDATE `creature_template` SET `minlevel`=57, `maxlevel`=57, `Health_mod`=5.5 WHERE `entry`=41292;
UPDATE `creature_template` SET `Health_mod`=10.5 WHERE `entry`=41279;
UPDATE `creature_template` SET `Health_mod`=2.5 WHERE `entry`=41292;
UPDATE `creature_template` SET `ScriptName`='npc_loramus_thalipedes' WHERE `entry`=41279;
UPDATE `creature_template` SET `ScriptName`='npc_loramus_the_defiled' WHERE `entry`=41292;
UPDATE `creature_template` SET `ScriptName`='npc_razelikh_the_defiler' WHERE `entry`=41280;

-- Defiled Felhound
SET @ENTRY := 41290;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,7741,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Effect"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,49,7741,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player");

DELETE FROM `creature_text` WHERE `entry`=41279;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41279,0,0,'Demon! I have returned from beyond the grave to destroy you!',12,0,100,0,0,0,'Comment'),
(41279,1,0,'Death has not erased my memory. I still know your name...',12,0,100,0,0,0,'Comment'),
(41279,2,0,'RAKH\'LIKH! Come, and know demise!',14,0,100,0,0,0,'Comment'),
(41279,3,0,'Hold on!',14,0,100,0,0,0,'Comment'),
(41279,3,1,'Return to me!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41280;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41280,0,0,'Fool of a demon hunter. How many pieces must I cut you into this time?',14,0,100,0,0,0,'Comment'),
(41280,1,0,'Enough games!',14,0,100,0,0,0,'Comment'),
(41280,2,0,'What\'s this? Loramus... I see, they used the Altar of Storms, didn\'t they?',12,0,100,0,0,0,'Comment'),
(41280,3,0,'You must feel it already then... the demonic energy entering your heart, your lungs, your soul...',12,0,100,0,0,0,'Comment'),
(41280,4,0,'Allow me to speed up the process a bit!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41292;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41292,0,0,'Now, heroes! Finish me, while Rakh\'likh possesses my body!',12,0,100,0,0,0,'Comment'),
(41292,1,0,'[Demonic] Lok zenn Za enkil refir mordanas lok zenn',14,0,100,0,0,0,'Comment'),
(41292,2,0,'Quickly! Use the knife on me! Time runs short!',12,0,100,0,0,0,'Comment'),
(41292,3,0,'It is done. Leave me here, then, while I wrestle with Rakh\'likh in the next world. Your job here is done, heroes.',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_area` WHERE `spell` = '60191' AND `quest_start` IN (26171, 25701);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(60191, 2517, 26171, 26171, 1, 10),
(60191, 2517, 25701, 25701, 1, 10);

DELETE FROM `spell_script_names` WHERE `spell_id` = '77372';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77372, 'spell_loramus_demon_grip');

DELETE FROM `spell_script_names` WHERE `spell_id` = '77380';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77380, 'spell_stone_knife');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '1446';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(1446, 'at_rise_of_the_defiler');

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=727385;