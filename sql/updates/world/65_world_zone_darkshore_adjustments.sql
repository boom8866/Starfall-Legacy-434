-- Decomposing Thistle Bear
SET @ENTRY := 32975;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,44911,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Carcass"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Despawn");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=32975;

-- Foolhardy Adventurer
SET @ENTRY := 34207;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,62684,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,34207,0,0,1,1,4500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,34207,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Die");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10431';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(10431, 0, 0, 'I am ready. Begin the attack.', 1, 1, 0, 0, 0, 0, NULL);

-- Huntress Sandrya Moonfall
SET @ENTRY := 33178;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,13515,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,10431,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,33178,0,0,45,0,1,0,0,0,0,11,32969,35,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Sentinels"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,33178,0,0,53,0,33178,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Move WP"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,1,0,0,0,11,64550,0,0,0,0,0,10,187729,32862,0,0.0,0.0,0.0,0.0,"On WP Reached - Cast Shattershield Arrow"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,1,0,0,0,1,2,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,10431,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,0,60000,60000,60000,60000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Evade"),
(@ENTRY,@SOURCETYPE,8,0,7,0,100,0,0,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Npc Flags"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,0,10431,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove NPC Flags");

DELETE FROM `conditions` WHERE `SourceEntry` = '64550';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 64550, 0, 0, 31, 0, 3, 32862, 0, 0, 0, '', 'Targeting -> Soulripper');

-- Lor'danel Sentinel
SET @ENTRY := 32969;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,9,1,100,0,0,20,9000,13000,11,31290,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Net on Close"),
(@ENTRY,@SOURCETYPE,17,0,9,1,100,0,11,24,15000,18000,11,81253,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Glaive on Close"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,1,0,0,69,0,0,0,0,0,0,8,0,0,0,7436.23,-1684.68,195.15,5.49,"On Get Data 1 - Attack"),
(@ENTRY,@SOURCETYPE,19,0,38,0,100,0,0,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data 1 - Set Run");

DELETE FROM `spell_script_names` WHERE `spell_id` = '62430';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62430, 'spell_absorb_fire_soothing_totem');

-- Unbound Fire Elemental
SET @ENTRY := 32999;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,75025,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rush of Flame on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,4500,9000,15000,11,13729,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Shock"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,11,65348,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Fire Aura");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=34401;

-- Thessera
SET @ENTRY := 34243;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,75,73446,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Spee Up");

SET @CGUID := 840794;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+1, 34282, 1, 1, 1, 0, 1, 5905.89, 218.815, 368.646, 4.22241, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+2, 34282, 1, 1, 1, 0, 1, 5922.57, 185.053, 362.91, 2.56129, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+3, 34282, 1, 1, 1, 0, 1, 5915.21, 246.823, 519.021, 5.53794, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+4, 34282, 1, 1, 1, 0, 1, 5881.24, 238.699, 466.712, 1.76803, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+5, 34282, 1, 1, 1, 0, 1, 5889.79, 139.007, 432.98, 3.08436, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+6, 34282, 1, 1, 1, 0, 1, 5956.67, 167.761, 466.584, 4.22869, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+7, 34282, 1, 1, 1, 0, 1, 5983.69, 245.407, 481.454, 3.10164, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+8, 34282, 1, 1, 1, 0, 1, 6039.22, 243.187, 378.915, 3.78101, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+9, 34282, 1, 1, 1, 0, 1, 5963.5, 167.884, 381.018, 0.368454, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+10, 34282, 1, 1, 1, 0, 1, 5888.07, 160.183, 382.194, 6.0461, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+11, 34282, 1, 1, 1, 0, 1, 5820.92, 183.446, 383.261, 5.4759, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+12, 34282, 1, 1, 1, 0, 1, 5856.9, 231.741, 364.77, 2.9964, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+13, 34282, 1, 1, 1, 0, 1, 5926.96, 200.119, 296.495, 2.67517, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0),
(@CGUID+14, 34282, 1, 1, 1, 0, 1, 5977.65, 146.156, 246.652, 2.97048, 60, 12, 0, 875, 1950, 1, 16777216, 0, 0);

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=189102;
UPDATE `creature_template` SET `VehicleId`=156 WHERE `entry`=34243;
UPDATE `creature_template` SET `VehicleId`=161 WHERE `entry`=33166;

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60, `spawndist`=12, `MovementType`=1 WHERE `id`=34282;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10490';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(10490, 0, 0, 'Ancient Onu, where may I find a Seed of the Earth?', 1, 1, 0, 0, 0, 0, NULL);

-- Onu
SET @ENTRY := 33072;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10490,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip "),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,86,65154,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Onu - Cast");

DELETE FROM `conditions` WHERE `SourceGroup`=10490 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10490, 0, 0, 0, 9, 0, 13882, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 13882 is active');

DELETE FROM `spell_script_names` WHERE `spell_id` = '62092';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62092, 'spell_blessed_herb_bundle_furbolg');

-- Spirit of Corruption
SET @ENTRY := 33000;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Invoker");

UPDATE `quest_template` SET `PrevQuestId`='13582' WHERE `Id`=13583;
UPDATE `gameobject` SET `spawntimesecs`=30 WHERE `id`=194150;

DELETE FROM `spell_area` WHERE `spell` = '84761' AND `quest_start` IN (26383, 26385);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84761, 4659, 26383, 1, 74, 0),
(84761, 4659, 26385, 1, 74, 0);

UPDATE `creature_template` SET `mindmg`=15, `maxdmg`=20, `attackpower`=5 WHERE `entry` IN
(32935, 32928, 32899,32888,33179,33180,32861,32863,32869,32860,34046,34033,33009,32859
,34248,33277,7015,33262,33021,33022,33020,33980,33127,33311,33978,32989,32988,32990,33206
,33207,34304,33083,32999,33057,33058,34399,34398,33043,33044,34302,32996,32997,40271,34339
,34350,34413,33079,34414,34423,34415);