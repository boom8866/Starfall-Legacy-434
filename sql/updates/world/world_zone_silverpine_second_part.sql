DELETE FROM `creature_questrelation` WHERE `id`=45315 AND `quest`=27364;
UPDATE `quest_template` SET `PrevQuestId`=27350 WHERE `Id`=27364;

-- Forsaken Warhorse
SET @ENTRY := 45041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Forsaken Warhorse (Player)"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,45041,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,39,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Start - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,20,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 20 - Dismount"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,15,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 15 Set Walk");

-- Forsaken Warhorse
SET @ENTRY := 45057;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,2000,2000,0,0,53,1,45057,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,18,1048576,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Taxi"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,8000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45051,0,0,1,1,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,45051,0,0,1,2,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45051,0,0,1,3,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45051,0,0,1,4,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,45051,0,0,1,5,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 5"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,5,45051,0,0,1,6,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 6"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,6,45051,0,0,1,7,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 7"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,7,45051,0,0,1,8,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 8"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,8,45051,0,0,1,9,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 9"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,9,45051,0,0,1,10,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 10"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,10,45051,0,0,1,11,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 11"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,11,45051,0,0,1,12,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 12"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,12,45051,0,0,1,13,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 13"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,13,45051,0,0,1,14,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 14"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,14,45051,0,0,1,15,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 15"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,15,45051,0,0,1,16,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 16"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,16,45051,0,0,1,17,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 17"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,17,45051,0,0,1,18,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 18"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,18,45051,0,0,1,19,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 19"),
(@ENTRY,@SOURCETYPE,22,0,52,0,100,0,19,45051,0,0,1,20,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 20"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,20,0,0,0,41,3000,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Dismount on WP End"),
(@ENTRY,@SOURCETYPE,24,0,58,0,100,0,0,0,0,0,33,45051,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Completed"),
(@ENTRY,@SOURCETYPE,25,0,52,0,100,0,20,45051,0,0,1,21,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk - 21"),
(@ENTRY,@SOURCETYPE,26,0,40,0,100,0,15,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 15 - Set Walk");

DELETE FROM `waypoints` WHERE `entry` = '45057';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(45057, 1, 1344.96, 1011.48, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 2, 1318.56, 1020.83, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 3, 1271.48, 1086.55, 52.33, 'Sylvanas (Lordaeron Event)'),
(45057, 4, 1229.24, 1124.89, 50.47, 'Sylvanas (Lordaeron Event)'),
(45057, 5, 1145.65, 1183.89, 47.89, 'Sylvanas (Lordaeron Event)'),
(45057, 6, 1108.21, 1205.00, 46.40, 'Sylvanas (Lordaeron Event)'),
(45057, 7, 1043.83, 1269.22, 46.03, 'Sylvanas (Lordaeron Event)'),
(45057, 8, 957.33, 1320.40, 46.54, 'Sylvanas (Lordaeron Event)'),
(45057, 9, 907.19, 1348.97, 48.92, 'Sylvanas (Lordaeron Event)'),
(45057, 10, 868.52, 1358.90, 54.70, 'Sylvanas (Lordaeron Event)'),
(45057, 11, 776.64, 1359.87, 65.12, 'Sylvanas (Lordaeron Event)'),
(45057, 12, 736.14, 1353.96, 71.88, 'Sylvanas (Lordaeron Event)'),
(45057, 13, 673.48, 1306.19, 81.39, 'Sylvanas (Lordaeron Event)'),
(45057, 14, 644.97, 1294.35, 85.60, 'Sylvanas (Lordaeron Event)'),
(45057, 15, 610.69, 1355.34, 87.32, 'Sylvanas (Lordaeron Event)'),
(45057, 16, 582.67, 1416.12, 96.24, 'Sylvanas (Lordaeron Event)'),
(45057, 17, 553.03, 1454.93, 106.07, 'Sylvanas (Lordaeron Event)'),
(45057, 18, 509.98, 1495.19, 124.92, 'Sylvanas (Lordaeron Event)'),
(45057, 19, 500.14, 1531.72, 129.62, 'Sylvanas (Lordaeron Event)'),
(45057, 20, 500.45, 1562.66, 127.63, 'Sylvanas (Lordaeron Event)');

UPDATE `creature_template` SET `unit_flags`=2 WHERE `entry`=45041;

-- Agatha
SET @ENTRY := 44951;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,75,85451,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Add Death Walk to self"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,10000,10000,11,83173,0,0,0,0,0,11,44593,10,0,0.0,0.0,0.0,0.0,"Raise Forsaken from Fallen Humans"),
(@ENTRY,@SOURCETYPE,3,0,31,0,100,0,83173,1,0,0,33,44953,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,0,0,50,0,1500,1500,1500,1500,11,84012,0,0,0,0,0,11,44987,3,0,0.0,0.0,0.0,0.0,"Cast Doomhowl"),
(@ENTRY,@SOURCETYPE,7,0,0,0,25,0,5000,5000,5000,5000,11,84013,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Cast Unholy Darkness"),
(@ENTRY,@SOURCETYPE,8,0,0,0,50,0,1500,1500,1500,1500,11,84014,0,0,0,0,0,11,44987,3,0,0.0,0.0,0.0,0.0,"Cast Unholy Smite"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,0,10000,10000,40000,40000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 0"),
(@ENTRY,@SOURCETYPE,10,0,31,0,100,0,83173,1,1500,1500,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,1,0,0,80,4495100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 Call Actionlist"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,1,2,44951,0,0,12,44989,8,120000,0,0,0,8,0,0,0,992.64,692.38,74.89,6.09,"Summon Crowley on Text 2"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,2,0,0,80,4495101,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 2 Call Actionlist"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,18,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 18 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,44987,5,0,0.0,0.0,0.0,0.0,"OOC - Attack Worgens"),
(@ENTRY,@SOURCETYPE,16,0,4,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Set Defensive"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,0,5000,5000,5000,5000,8,0,0,0,0,0,0,1,44987,5,0,0.0,0.0,0.0,0.0,"OOC - Set Passive");

-- Fenris Keep Stalker
SET @ENTRY := 45032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,1000,1000,45,0,1,0,0,0,0,11,44951,1,0,0.0,0.0,0.0,0.0,"Set data 1 to Agatha");

UPDATE `creature_template` SET `ScriptName`='npc_generic_areatrigger', `flags_extra`=128 WHERE `entry`=4;
UPDATE `creature_template_addon` SET `auras`='75511, 77559' WHERE `entry`=45345;
UPDATE `creature` SET `spawndist`=80, `MovementType`=1, `spawntimesecs`=60 WHERE `id` IN (45280, 45375);
UPDATE `creature_template` SET `rank`=80, `mindmg`=160, `dmg_multiplier`=2, `Health_mod`=5, `Armor_mod`=5 WHERE `entry`=45280;
UPDATE `creature_template` SET `rank`=10, `mindmg`=20, `dmg_multiplier`=1 WHERE `entry`=45375;

-- Worgen Rusher
SET @ENTRY := 45375;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,12000,5000,12000,11,75002,0,0,0,0,0,11,45280,45,0,0.0,0.0,0.0,0.0,"OOC - Jump on Target"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,12000,5000,12000,11,75002,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"OOC - Jump on Target");

UPDATE `creature_involvedrelation` SET `id`=45345 WHERE `id`=45315 AND `quest`=27349;
UPDATE `quest_template` SET `Flags`=3670016, `QuestStartType`=1, `SpecialFlags`=4 WHERE `Id`=27350;
UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=45345;
UPDATE `creature` SET `phaseMask`=32769 WHERE `guid`=706246;
UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=35, `MovementType`=1 WHERE `id`=45403;
UPDATE `creature_template` SET `spell1`=81087, `spell2`=86249, `ScriptName`='generic_creature', `unit_flags`=0 WHERE `entry`=45403;

DELETE FROM `creature_questrelation` WHERE `quest` = '27364';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(45389, 27364);

UPDATE `creature_template` SET `VehicleId`=686, `InhabitType`=7, `speed_walk`=3.14286, `speed_run`=3.14286 WHERE `entry`=45427;

DELETE FROM `waypoints` WHERE `entry` = '45427';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45427, 1, -1213.40, 2002.54, 20.75, 'Gilneas Camera WP'),
(45427, 2, -1217.55, 2014.67, 20.99, 'Gilneas Camera WP'),
(45427, 3, -1219.14, 2016.69, 23.35, 'Gilneas Camera WP');

-- Gilneas Camera 01
SET @ENTRY := 45427;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Caster"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,45427,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,3,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Force Despawn");

DELETE FROM `creature_template_addon` WHERE `entry` IN (45312, 45314);
DELETE FROM `creature_addon` WHERE guid IN (771389, 771390);

DELETE FROM `spell_script_names` WHERE `spell_id` = '91202';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91202, 'spell_gen_blackout_effect');

UPDATE `creature_questrelation` SET `id`=45312 WHERE `id`=45315 AND `quest`=27423;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-84943, 84943, 85036, 85039);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-84943, 84940, 'Gilneas Summon Master -> Despawn Summons'),
(84943, 84940, 'Gilneas Summon Master -> Despawn Summons'),
(84943, 84941, 'Gilneas Summon Master -> Despawn Summons'),
(84943, 84944, 'Gilneas Summon Master -> Despawn Summons'),
(85036, 84940, 'Quest Credit -> Despawn Summons'),
(85036, 85039, 'Quest Credit -> Apply Detect Quest Invis 11'),
(85039, -84941, 'Apply Detect Quest Invis 11 -> Remove Summons'),
(85039, -84944, 'Apply Detect Quest Invis 11 -> Remove Summons'),
(85039, -84943, 'Apply Detect Quest Invis 11 -> Remove Summons');

UPDATE `quest_template` SET `SourceSpellId`=84943 WHERE `Id`=27406;

DELETE FROM `spell_script_names` WHERE `spell_id` = '84940';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84940, 'spell_gen_despawn_all_summons');

UPDATE `creature_template` SET `mindmg`=50, `maxdmg`=95, `attackpower`=35, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_class`=4, `spell1`=79862, `spell2`=79852, `spell3`=79864, `InhabitType`=3, `ScriptName`='generic_creature' WHERE `entry`=45474;
UPDATE `creature_template` SET `mindmg`=50, `maxdmg`=95, `attackpower`=35, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_class`=8, `spell1`=84992, `spell2`=84013, `spell3`=84014, `InhabitType`=3, `ScriptName`='generic_creature' WHERE `entry`=45473;

UPDATE `creature_involvedrelation` SET `id`=45312 WHERE `id`=45474 AND `quest`=27406;
DELETE FROM `spell_script_names` WHERE `spell_id` = '89225';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89225, 'spell_the_great_escape_init');

UPDATE `creature_template` SET `VehicleId`=1075, `speed_walk`=3.36286, `speed_run`=3.36286 WHERE `entry`=45314;

-- Arthura
SET @ENTRY := 45314;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Summoner"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,45314,0,27438,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,5,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,5,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,4,0,0,0,15,27438,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Quest Complete");

-- Deathstalker Commander Belmont
SET @ENTRY := 45312;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27438,0,0,0,85,89225,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - The Great Escape Initialize");

UPDATE `creature_addon` SET `auras`='' WHERE `guid` IN (771338, 771340);
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (771268, 771269, 771261, 771263, 771267, 771264, 771265, 771262, 771405, 771573, 771290);
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=771290;
DELETE FROM `creature_addon` WHERE `guid` IN (771268, 771269, 771261, 771263, 771267, 771264, 771265, 771262, 771405, 771573, 771290);
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry` IN (45585, 45576);
UPDATE `creature_template_addon` SET `auras`='29266' WHERE `entry` = '45576';

DELETE FROM `creature_text` WHERE `entry`=45525;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45525,0,0,'Rise, Lord Vincent Godfrey. Be reborn as an instrument of my vengeance!',12,0,100,0,0,0,'Comment'),
(45525,1,0,'You live to serve me, Godfrey. Together we will crush the worgen uprising and retake Gilneas for the Forsaken.',12,0,100,0,0,0,'Comment'),
(45525,2,0,'Yes, of course...',12,0,100,0,0,0,'Comment'),
(45525,3,0,'Prepare your men. The Gilneas Liberation Front amasses at the Greymane Wall. Soon their reinforcements from Stormwind will arrive. We haven\'t a minute to waste.',12,0,100,0,0,0,'Comment'),
(45525,4,0,'Once again you have impressed me. Without your aid, we would have not made it this far. Walk with me...',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (85200, 85201, 85198);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(85200, -29266, 'Transformation -> Remove Dead Aura'),
(85201, -29266, 'Transformation -> Remove Dead Aura'),
(85198, -29266, 'Transformation -> Remove Dead Aura');

DELETE FROM `conditions` WHERE `SourceEntry` = '85197';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85197, 0, 0, 31, 0, 3, 45578, 0, 0, 0, '', 'Raise Forsaken Agatha'),
(13, 2, 85197, 1, 0, 31, 0, 3, 45577, 0, 0, 0, '', 'Raise Forsaken Agatha'),
(13, 3, 85197, 2, 0, 31, 0, 3, 45576, 0, 0, 0, '', 'Raise Forsaken Agatha');

UPDATE `creature` SET `position_x`=-196.47, `position_y`=1282.64, `position_z`=42.95, `orientation`=4.63 WHERE `guid`=771263;
UPDATE `creature_template` SET `scale`=1.3 WHERE `entry`=45583;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85197';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85197, 'spell_raise_forsaken_agatha');

UPDATE `creature_template_addon` SET `auras`='75511' WHERE `entry` IN (45576, 45577, 45578);

DELETE FROM `waypoints` WHERE `entry` = '45525';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45525, 1, -152.31, 1270.22, 51.56, 'Sylvanas WP (Godfrey)'),
(45525, 2, -182.36, 1275.85, 46.44, 'Sylvanas WP (Godfrey)');

DELETE FROM `creature_text` WHERE `entry`=45593;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45593,0,0,'For the Horde...',12,0,100,0,0,0,'Comment');

DELETE FROM `world_quest_phases` WHERE `QuestId` = '27472';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `Comment`) VALUES
(27472, 32768, 3, 'Quest ID: 27472 - Rise, Godfrey (ON QUEST COMPLETE)');

UPDATE `creature_template_addon` SET `auras`='0' WHERE `entry` IN (45627, 45626, 45624, 45622, 45623);
UPDATE `creature` SET `position_z`=55.50 WHERE `guid` IN (771285, 771284);
UPDATE `creature` SET `position_z`=43.95 WHERE `guid`=771263;
UPDATE `creature` SET `position_z`=46.1189 WHERE  `guid`=771269;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (45584, 45583, 45626, 45625);
UPDATE `creature` SET `phaseMask`=32769 WHERE `guid` IN (195601, 195619);

-- Lady Sylvanas Windrunner
SET @ENTRY := 45525;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,10,19,0,100,0,27472,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45525,0,0,45,0,5,0,0,0,0,10,771263,45583,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 5 to Agatha"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45525,0,0,45,0,1,0,0,0,0,10,771261,45593,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Cromush"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45525,0,0,45,0,2,0,0,0,0,10,771262,45576,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Godfrey"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,3,0,0,1,3,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,45525,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,45525,0,0,53,0,45525,0,27472,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Start WP"),
(@ENTRY,@SOURCETYPE,9,11,40,0,100,0,1,0,0,0,33,45617,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Quest Credit"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Quest Flag (Temp)"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,1,0,0,0,0,70,0,0,0,0,0,0,11,0,250,0,0.0,0.0,0.0,0.0,"Link - Respawn Actors"),
(@ENTRY,@SOURCETYPE,12,0,40,0,100,0,2,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Reset Quest Flag");

-- High Warlord Cromush
SET @ENTRY := 45593;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45593,0,0,45,0,2,0,0,0,0,10,771268,45525,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 2 to Sylvanas");

-- Lord Godfrey
SET @ENTRY := 45576;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45576,0,0,45,0,1,0,0,0,0,10,771268,45525,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Sylvanas"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45576,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,45576,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,3,45576,0,0,45,0,3,0,0,0,0,10,771268,45525,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Sylvanas");

-- Agatha
SET @ENTRY := 45583;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,5,0,0,11,85197,0,0,0,0,0,11,45576,20,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Cast Raise Forsaken");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (773145, 773133);

DELETE FROM `spell_target_position` WHERE `id` IN (85317, 85318);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(85317, 291.74, 379.52, -65.90, 2.37),
(85318, 454.23, 1468.64, 125.02, 1.05);

DELETE FROM `spell_area` WHERE `quest_start` IN (27483, 27478);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85320, 279, 27483, 27483, 1, 10, 10),
(85320, 279, 27478, 27483, 1, 10, 10);

-- Dalar Dawnweaver
SET @ENTRY := 1938;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27483,0,0,0,85,85320,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Add Phase Aura"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27478,0,0,0,85,85320,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Add Phase Aura");

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=10.67 WHERE `entry`=45728 AND `item`=61310;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12054';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12054, 'Use the Ambermill dimensional Portal', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=12054;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12054, 0, 0, 0, 9, 0, 27513, 0, 0, 0, 0, 0, '', 'Ambermill Dimensional Portal - Show gossip only if quest 27513 is active');

-- Ambermill Dimensional Portal
SET @ENTRY := 45752;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12054,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12054,0,0,0,85,85360,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Invoker Teleport");

UPDATE `creature` SET `phaseMask`=2, `spawndist`=20, `MovementType`=1 WHERE `id` IN (1888, 1913, 1914, 1889) AND `MovementType`=0;

DELETE FROM `spell_area` WHERE `quest_start` IN (27513, 27518);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85361, 233, 27513, 27513, 1, 10, 10),
(85361, 233, 27518, 27518, 1, 10, 10);

DELETE FROM `spell_target_position` WHERE `id` = '85360';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(85360, -132.22, 897.85, 65.95, 4.73);

DELETE FROM `creature_text` WHERE `entry`=2120;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2120,0,0,'Minions, destroy the interloper! The shield must not come down!',14,0,100,0,0,0,'Comment'),
(2120,1,0,'Destroy Arcane Fiends near Archmage Ataeric to Overload the shield!',41,0,100,0,0,0,'Comment'),
(2120,2,0,'You will not succeed, monster!',14,0,100,0,0,0,'Comment'),
(2120,3,0,'We will... never... give up!',14,0,100,0,0,0,'Comment'),
(2120,4,0,'The armies of the Alliance will march upon your bones!',14,0,100,0,0,0,'Comment'),
(2120,5,0,'Lordaeron belongs to the Alliance. You only delay the inevitable...',14,0,100,0,0,0,'Comment'),
(2120,6,0,'The power...is too much...I cannot hold...any longer...',14,0,100,0,0,0,'Comment'),
(2120,7,0,'RUN! DO NOT LET THEM TURN YOU!',14,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (2120, 45761, 45763, 45762);
UPDATE `creature` SET `phaseMask`=4 WHERE `id` IN (45777, 45775, 45778, 45779);
UPDATE `creature` SET `phaseMask`=6 WHERE `id`=45790;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (45761, 45775);
UPDATE `creature` SET `position_z`=70.8305 WHERE `guid` IN (773163, 773473);

UPDATE `creature_template` SET `minlevel`=19, `maxlevel`=19, `faction_A`=76, `faction_H`=76, `mindmg`=19, `maxdmg`=27, `baseattacktime`=2000, `Health_mod`=1 WHERE `entry`=45766;
UPDATE `creature_template` SET `maxdmg`=19, `dmgschool`=27, `attackpower`=7, `dmg_multiplier`=1.1 WHERE `entry`=45711;
UPDATE `creature_template_addon` SET `auras`='87251 87239 85379 70634' WHERE `entry`=2120;
UPDATE `creature_template` SET `flags_extra`=128, `ScriptName`='npc_ambermill_event_generator' WHERE `entry`=45790;
UPDATE `creature` SET `position_x`=-136.02, `position_y`=1067.66, `position_z`=66.29, `orientation`=1.57 WHERE `guid`=773507;

DELETE FROM `world_quest_phases` WHERE `QuestId` = '27518';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `Comment`) VALUES
(27518, 4, 3, 'Quest ID: 27518 - Transdimensional Warfare: Chapter III (ON QUEST COMPLETE)');

DELETE FROM `creature_text` WHERE `entry`=45775;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45775,0,0,'The dimensional barrier is broken! TAKE THEM NOW! FOR THE BANSHEE QUEEN!',14,0,100,0,0,0,'Comment'),
(45775,1,0,'Rise, magi! Be reborn as a Forsaken!',14,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceEntry` = '85411';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85411, 0, 0, 31, 0, 3, 45779, 0, 0, 0, '', 'Raise Forsaken Dashla');

DELETE FROM `spell_script_names` WHERE `spell_id` = '85411';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85411, 'spell_raise_forsaken_dashla');

DELETE FROM `creature` WHERE `guid`=773266;
DELETE FROM `creature_addon` WHERE `guid`=773266;

-- Archmage Ataeric
SET @ENTRY := 45803;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,8000,8000,8000,8000,70,0,0,0,0,0,0,11,0,500,0,0.0,0.0,0.0,0.0,"On Just Summoned - Reset Event"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,5000,5000,5000,5000,75,91202,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Blackout");

-- Archmage Ataeric
SET @ENTRY := 2120;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Rooted"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,2120,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,2120,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,0,1,100,0,3000,20000,12500,25000,11,87253,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - Summon Arcane Fiend"),
(@ENTRY,@SOURCETYPE,5,7,6,0,100,0,0,0,0,0,1,7,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 7"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,33,45769,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Daschla
SET @ENTRY := 45775;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,52,0,100,0,0,45775,0,0,45,0,2,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 2 to Creatures"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-135.9,1071.06,68.83,4.8,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,1,1,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,45775,0,0,11,85411,0,0,0,0,0,10,773507,45779,0,0.0,0.0,0.0,0.0,"After Talk 1 - Raise Forsaken");

-- Forsaken Vanguard
SET @ENTRY := 45777;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,2,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,46,150,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Aggressive");

-- Forsaken Catapult
SET @ENTRY := 45778;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,2,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,46,200,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Move Forward");

DELETE FROM `spell_script_names` WHERE `spell_id` = '85515';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85515, 'spell_battlefront_broadcast');

UPDATE `quest_template` SET `RewardSpellCast`=85516 WHERE `Id`=27542;
UPDATE `creature_template` SET `flags_extra`=128, `scale`=8 WHERE `entry` IN (45939, 45938, 45937);
UPDATE `creature_template_addon` SET `auras`='44025' WHERE `entry` IN (45939, 45938, 45937);
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (45882, 45883, 45910);
UPDATE `creature` SET `phaseMask`=3 WHERE `id` IN (45939, 45938, 45937);
UPDATE `creature` SET `spawntimesecs`=120, `spawndist`=10, `MovementType`=1 WHERE `id`=45883;
UPDATE `creature_template_addon` SET `auras`='85514' WHERE `entry` IN (45939, 45938, 45937, 45883, 45910);
UPDATE `creature_template_addon` SET `auras`='29266 85514' WHERE `entry`=45882;
UPDATE `creature_template_addon` SET `emote`=431 WHERE `entry`=45910;

DELETE FROM `creature_addon` WHERE `guid` IN
(773403,773411,773412,773413,773414,773415,773418,773419,773420,773438,773442,773443,773444,773446,773453,773524,773527,773528,773530,773531,
773532,773533,773534,773535,773536,773537,773538,773539,773568,773569,773571,773572,773573,773574,773575,773576,773579,773582,773587,773588,
773589,773590,773591,773592,773593,773594,773596,773597,773598,773599,773600,773601,773602,773603,773604,773606,773607,773608,773609,773610,
773611,773614,773616,773617,773619,773620,773621,773623,773624,773625,773626,773632,773636);

DELETE FROM `spell_area` WHERE `quest_start` IN (27547, 27548, 27550);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85513, 204, 27547, 27547, 1, 10, 10),
(85513, 204, 27548, 27548, 1, 10, 10),
(85513, 204, 27550, 27550, 1, 10, 10),
(85513, 5478, 27547, 27547, 1, 10, 10),
(85513, 5478, 27548, 27548, 1, 10, 10),
(85513, 5478, 27550, 27550, 1, 10, 10),
(85513, 5477, 27547, 27547, 1, 10, 10),
(85513, 5477, 27548, 27548, 1, 10, 10),
(85513, 5477, 27550, 27550, 1, 10, 10),
(85513, 5476, 27547, 27547, 1, 10, 10),
(85513, 5476, 27548, 27548, 1, 10, 10),
(85513, 5476, 27550, 27550, 1, 10, 10);

DELETE FROM `conditions` WHERE `SourceEntry` = '85600';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85600, 1, 0, 31, 0, 3, 45937, 0, 0, 0, '', 'Toss Torch'),
(13, 1, 85600, 2, 0, 31, 0, 3, 45938, 0, 0, 0, '', 'Toss Torch'),
(13, 1, 85600, 3, 0, 31, 0, 3, 45939, 0, 0, 0, '', 'Toss Torch');

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=45910;
UPDATE `creature_template` SET `npcflag`=1, `unit_flags`=4, `flags_extra`=2 WHERE `entry`=45910;

-- Cowering Trooper
SET @ENTRY := 45910;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,64,0,100,0,0,0,0,0,33,45910,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip");

DELETE FROM `creature_template_addon` WHERE `entry` = '45879';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(45879, 1, '82123');

UPDATE `creature_template_addon` SET `bytes2`=1 WHERE `bytes2` = '0' and `auras` > '0';
UPDATE `creature_addon` SET `bytes2`=1 WHERE `bytes2` = '0' and `auras` > '0';

UPDATE `creature_template` SET `ScriptName`='npc_pyrewood_trigger' WHERE `entry` IN (45937, 45938, 45939);
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id`=205578;
UPDATE `creature_template` SET `unit_class`=8 WHERE `entry` IN (45880, 45879, 45878);
UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27550, 27548, 27547);

-- Fire
SET @ENTRY := 205578;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,60000,120000,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Set Phase 2");

DELETE FROM `creature_template_addon` WHERE `entry` = '45878';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(45878, 1, '79849');

DELETE FROM `creature_template_addon` WHERE `entry` = '45880';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(45880, 1, '16592');

-- Lord Godfrey
SET @ENTRY := 45878;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,0,0,50,0,5000,10000,5000,10000,11,79857,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blast Wave"),
(@ENTRY,@SOURCETYPE,2,0,0,0,25,0,5000,10000,5000,10000,11,79855,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Blast"),
(@ENTRY,@SOURCETYPE,3,0,0,0,25,0,5000,10000,5000,10000,11,79854,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball"),
(@ENTRY,@SOURCETYPE,4,0,0,0,30,0,5000,10000,5000,10000,11,79854,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flamestrike"),
(@ENTRY,@SOURCETYPE,5,0,27,0,100,0,0,0,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 4"),
(@ENTRY,@SOURCETYPE,6,0,27,0,100,0,0,0,0,0,33,46002,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Quest Credit");

-- Lord Walden
SET @ENTRY := 45879;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,0,0,15,0,5000,10000,5000,10000,11,17137,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flash Heal (Self)"),
(@ENTRY,@SOURCETYPE,2,0,0,0,15,0,5000,10000,5000,10000,11,17137,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flash Heal (Friendly)"),
(@ENTRY,@SOURCETYPE,3,0,0,0,15,0,5000,10000,5000,10000,11,85965,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Holy Nova"),
(@ENTRY,@SOURCETYPE,4,0,0,0,15,0,5000,10000,5000,10000,11,9734,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Holy Smite"),
(@ENTRY,@SOURCETYPE,5,0,0,0,15,0,5000,10000,5000,10000,11,54520,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Penance"),
(@ENTRY,@SOURCETYPE,6,0,0,0,15,0,5000,10000,5000,10000,11,54520,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Penance (Heal)"),
(@ENTRY,@SOURCETYPE,7,0,4,0,100,0,0,0,0,0,11,11974,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Power Word Shield"),
(@ENTRY,@SOURCETYPE,8,0,0,0,15,0,5000,10000,5000,10000,11,11974,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Power Word: Shield");

-- Baron Ashbury
SET @ENTRY := 45880;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,0,0,25,0,5000,10000,5000,10000,11,13860,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mind Blast"),
(@ENTRY,@SOURCETYPE,2,0,0,0,25,0,5000,10000,5000,10000,11,16568,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mind Flay"),
(@ENTRY,@SOURCETYPE,3,0,0,0,5,0,5000,10000,5000,10000,11,22884,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Psychic Scream"),
(@ENTRY,@SOURCETYPE,4,0,0,0,25,0,5000,10000,5000,10000,11,11639,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Word: Pain"),
(@ENTRY,@SOURCETYPE,5,0,0,0,2,0,5000,10000,5000,10000,11,79811,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Dispersion");

-- 7th Legion Scout
SET @ENTRY := 45883;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,5000,5000,11,84442,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Stealth"),
(@ENTRY,@SOURCETYPE,1,0,0,0,20,0,5000,10000,5000,10000,11,79584,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fan of Knives"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,3,0,0,0,55,0,5000,10000,5000,10000,11,79862,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Backstab"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,84442,1,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Spellhit - Set Defensive");

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=6.005 WHERE  `entry`=45896 AND `item`=61505;

DELETE FROM `creature_involvedrelation` WHERE `quest` IN (27574, 27575);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(45622, 27574),
(45878, 27574),
(45622, 27575),
(45878, 27575);

DELETE FROM `creature_questrelation` WHERE `quest`=27575;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(45622, 27575),
(45878, 27575);

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60, `spawndist`=10, `MovementType`=1 WHERE `id`=45855;
DELETE FROM `creature` WHERE `guid`=773648;
DELETE FROM `creature_addon` WHERE `guid`=773648;
UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60 WHERE `guid`=773618;
UPDATE `creature_template_addon` SET `auras`='85599' WHERE `entry` IN (45995, 45855);
UPDATE `quest_template` SET `Flags`=0 WHERE  `Id`=27575;
UPDATE `creature_template` SET `maxdmg`=40, `dmgschool`=78, `baseattacktime`=2000 WHERE `entry` IN (45878, 45879, 45880, 45883, 45995, 45855, 45896);

DELETE FROM `spell_area` WHERE `quest_start` IN (27577, 27580);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85598, 5481, 27577, 27577, 1, 10, 10),
(85598, 5481, 27580, 27580, 1, 10, 10),
(85598, 5456, 27577, 27577, 1, 10, 10),
(85598, 5456, 27580, 27580, 1, 10, 10);

DELETE FROM `creature_addon` WHERE `guid` IN
(773280,773281,773344,773407,773455,773456,773540,773541,773542,773543,773612,773613,773615,773622,773631,773633,773634,773635,773637,773639,773640,773641,773647,773649);

DELETE FROM `creature_text` WHERE `entry` IN (45997, 45878);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45997,0,0,'So the Banshee Queen has sent assassins? ',12,0,100,0,0,0,'Comment'),
(45997,1,0,'Godfrey? So the rumors are true.',12,0,100,0,0,0,'Comment'),
(45997,2,0,'You would betray your kingdom out of spite?',12,0,100,0,0,0,'Comment'),
(45997,3,0,'HAH! You\'ll have to kill me! DIE!',12,0,100,0,0,0,'Comment'),
(45878,0,0,'Lorna, is that how you greet old friends? ',12,0,100,0,0,0,'Comment'),
(45878,1,0,'My kingdom? My kingdom is no more.',12,0,100,0,0,0,'Comment'),
(45878,2,0,'Your father and Greymane saw to that... No, Gilneas died when they allowed murderous beasts to reign free. Unchecked.',12,0,100,0,0,0,'Comment'),
(45878,3,0,'Now lay down your arms and surrender. We are not here to kill you. Not yet.',12,0,100,0,0,0,'Comment'),
(45878,4,0,'Quickly! We must head back to the Forsaken Front before we are discovered!',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=773651;
UPDATE `creature_template` SET `VehicleId`=1170 WHERE `entry`=45878;
UPDATE `quest_template` SET `RewardSpellCast`=84940 WHERE `Id`=27594;

DELETE FROM `creature_template_addon` WHERE `entry` = '46027';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(46027, 1, '87259');

-- Commander Lorna Crowley
SET @ENTRY := 45997;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,1,1,100,1,47000,47000,47000,47000,49,0,0,0,0,0,0,11,45878,50,0,0.0,0.0,0.0,0.0,"On Phase 1 - Attack Godfrey"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,0,0,0,0,0,18,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Remove Pacified"),
(@ENTRY,@SOURCETYPE,3,0,0,1,35,0,5000,10000,5000,10000,11,81140,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Thunderclap"),
(@ENTRY,@SOURCETYPE,4,0,0,1,55,0,5000,10000,5000,10000,11,85240,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sundering Cleave"),
(@ENTRY,@SOURCETYPE,5,0,4,1,100,0,0,0,0,0,11,80983,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Commanding Shout"),
(@ENTRY,@SOURCETYPE,6,0,6,1,100,0,0,0,0,0,12,46027,8,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Captured Lorna"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Force Despawn");

-- Commander Lorna Crowley
SET @ENTRY := 46027;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,45878,30,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Godfrey"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,300000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn (5 mins)"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,46028,30,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Godfrey (2)");

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60, `spawndist`=25, `MovementType`=1 WHERE `id` IN (46063, 45860, 46054);
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (46070, 46052);
UPDATE `quest_template` SET `SourceSpellId`=85872 WHERE `Id`=27601;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85872';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85872, 'spell_silverpine_finale_master');

DELETE FROM `waypoints` WHERE `entry` = '46032';
DELETE FROM `creature_text` WHERE `entry`= '46032';

UPDATE `quest_template` SET `SourceSpellId`=84941 WHERE `Id`=27290;
UPDATE `creature_template` SET `VehicleId`=1075 WHERE `entry`=45473;
UPDATE `creature_template` SET `speed_walk`=3, `speed_run`=3, `InhabitType`=4, `HoverHeight`=2.4, `spell1`=0, `spell2`=0, `spell3`=0, `ScriptName`='' WHERE `entry`=45473;

DELETE FROM `waypoints` WHERE `entry` = '45473';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(45473, 1, 480.35, 1541.18, 158.89, 'Arthura to Gilneas'),
(45473, 2, 255.29, 1453.40, 164.76, 'Arthura to Gilneas'),
(45473, 3, -372.69, 1430.74, 180.49, 'Arthura to Gilneas'),
(45473, 4, -732.05, 1547.03, 72.42, 'Arthura to Gilneas'),
(45473, 5, -887.05, 1580.53, 76.02, 'Arthura to Gilneas'),
(45473, 6, -932.12, 1632.24, 73.00, 'Arthura to Gilneas');

DELETE FROM `creature_text` WHERE `entry`=45473;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45473,0,0,'Do not be afraid. I will not let you fall.',12,0,100,0,0,0,'Comment');

-- Arthura
SET @ENTRY := 45473;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Grab Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,45473,0,27290,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 1 Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,6,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Last WP Reached - Leave Vehicle");

-- Arthura
SET @ENTRY := 46032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.14286, `VehicleId`=0, `ScriptName`='npc_arthura_final' WHERE `entry`=46032;

DELETE FROM `creature_template_addon` WHERE `entry` = '46026';
INSERT INTO `creature_template_addon` (`entry`, `mount`, `auras`) VALUES
(46026, 29257, '85874');

DELETE FROM `creature_template_addon` WHERE `entry` IN (46032, 46034, 46033);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(46032, 0, 0, 50397184, 1, 0, ''),
(46033, 0, 0, 50397184, 1, 0, ''),
(46034, 0, 0, 50397184, 1, 0, '');

UPDATE `creature_template` SET `ScriptName`='npc_daschla_final' WHERE `entry`=46033;
UPDATE `creature_template` SET `ScriptName`='npc_agatha_final' WHERE `entry`=46034;
UPDATE `creature_template` SET `InhabitType`=3, `HoverHeight`=2, `flags_extra`=2 WHERE `entry` IN (46033, 46032, 46034);
UPDATE `creature_template` SET `speed_walk`=1.98, `speed_run`=1.98 WHERE `entry` IN (46033, 46032, 46034, 46031);
UPDATE `creature_template` SET `speed_walk`=1.65, `speed_run`=1.65 WHERE `entry`=46026;

DELETE FROM `waypoints` WHERE `entry` = '46026';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(46026, 1, -352.25, 1306.9, 40.66, 'Sylvanas Final WP'),
(46026, 2, -535.42, 1373.94, 32.52, 'Sylvanas Final WP'),
(46026, 3, -636.65, 1441.94, 28.38, 'Sylvanas Final WP'),
(46026, 4, -700.73, 1548.33, 27.98, 'Sylvanas Final WP');

DELETE FROM `creature` WHERE `guid` = '706302';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(706302, 4, 0, 1, 32770, 0, 0, -707.401, 1549.1, 28.007, 3.06809, 300, 0, 0, 30951, 0, 0, 0, 0, 0);

DELETE FROM `spell_target_position` WHERE `id` IN (85877, 85878, 85925, 85926, 85927);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(85877, -769.59, 1549.27, 28.01, 6.27),
(85878, -769.55, 1546.96, 28.01, 0.01),
(85925, -678.55, 1518.47, 29.85, 2.51),
(85926, -681.43, 1514.50, 29.82, 2.51),
(85927, -677.48, 1519.95, 29.76, 2.51);

DELETE FROM `creature_text` WHERE `entry` IN (46036, 46035, 46026, 46028, 46031, 46032, 46033, 46034);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46036,0,0,'It\'s not over, Sylvanas. Not yet.',12,0,100,0,0,0,'Comment'),
(46036,1,0,'We will die trying! ',12,0,100,0,0,0,'Comment'),
(46036,2,0,'LORNA? What... Where is she!? What have you done to her!?',12,0,100,0,0,0,'Comment'),
(46036,3,0,'GODFREY! You deceitful maggot!',12,0,100,0,0,0,'Comment'),
(46036,4,0,'Lorna... I... Release her. I will sound the retreat.',12,0,100,0,0,0,'Comment'),
(46036,5,0,'Forgive me, daughter...',12,0,100,0,0,0,'Comment'),
(46035,0,0,'You can\'t be serious, Crowley. You miserable bastard!',12,0,100,0,0,0,'Comment'),
(46026,0,0,'Onward, $n! We will beat back the Alliance dogs and secure Lordaeron for the Forsaken! For the Horde! ',12,0,100,0,0,0,'Comment'),
(46026,1,0,'Accompany Lady Sylvanas Windrunner across the Battlefront.',41,0,100,0,0,0,'Comment'),
(46026,2,0,'Lay down your arms and surrender!',14,0,100,0,0,0,'Comment'),
(46026,3,0,'I will leave your cities in dust and your lives in ruin!',14,0,100,0,0,0,'Comment'),
(46026,4,0,'Look at them... They scurry like rats, veering headlong to their doom. Surely Crowley and Bloodfang can see the futility in this!',12,0,100,0,0,0,'Comment'),
(46026,5,0,'To the Greymane Wall! We will force their hand.',12,0,100,0,0,0,'Comment'),
(46026,6,0,'Crowley, your forces have fallen before my mighty army. You have lost!',14,0,100,0,0,0,'Comment'),
(46026,7,0,'You frivolously throw away the lives of your people while your own king sits atop his throne of lies, nary lifting a finger to help.',12,0,100,0,0,0,'Comment'),
(46026,8,0,'Is Gilneas worth the lives that have been lost? The lives that will be lost? You cannot win. ',12,0,100,0,0,0,'Comment'),
(46026,9,0,'And your daughter? You could have saved her... You could have offered her your blood, yet you did not. Why?',12,0,100,0,0,0,'Comment'),
(46026,10,0,'Nothing, yet...',12,0,100,0,0,0,'Comment'),
(46026,11,0,'I now present you with a choice - a choice that I was never given.',12,0,100,0,0,0,'Comment'),
(46026,12,0,'I offer you the life of Lorna for your unconditional surrender.',12,0,100,0,0,0,'Comment'),
(46026,13,0,'Choose your next words wisely, Crowley.',12,0,100,0,0,0,'Comment'),
(46026,14,0,'Bring her, Godfrey!',14,0,100,0,0,0,'Comment'),
(46026,15,0,'Release her, Godfrey.',12,0,100,0,0,0,'Comment'),
(46026,16,0,'Now leave here, Crowley, and never return. ',12,0,100,0,0,0,'Comment'),
(46026,17,0,'Lordaeron belongs to the Forsaken.',12,0,100,0,0,0,'Comment'),
(46026,18,0,'SOLDIERS OF THE HORDE! WE ARE VICTORIOUS! LORDAERON IS W...',14,0,100,0,0,0,'Comment'),
(46026,19,0,'Lady Sylvanas Windrunner dies.',41,0,100,0,0,0,'Comment'),
(46026,20,0,'I saw... only darkness.',12,0,100,0,0,0,'Comment'),
(46026,21,0,'And as I drifted towards nothingness, a brilliant light appeared, then another, and another... My dear val\'kyr.',12,0,100,0,0,0,'Comment'),
(46026,22,0,'I know now - beyond a shadow of a doubt - that the val\'kyr are our future.',12,0,100,0,0,0,'Comment'),
(46026,23,0,'We will never stop fighting for Lordaeron. Never...',12,0,100,0,0,0,'Comment'),
(46028,0,0,'Hello, old friend!',12,0,100,0,0,0,'Comment'),
(46028,1,0,'Of course, mistress.',12,0,100,0,0,0,'Comment'),
(46028,2,0,'Something that should have been done a long time ago, you filthy animal.',12,0,100,0,0,0,'Comment'),
(46028,3,0,'Gilneas belongs to me, and so soon will the rest of Lordaeron!',12,0,100,0,0,0,'Comment'),
(46028,4,0,'NOW JOIN YOUR MISTRESS IN DEATH!',12,0,100,0,0,0,'Comment'),
(46028,5,0,'FALL BACK, BROTHERS! TO SHADOWFANG!',14,0,100,0,0,0,'Comment'),
(46028,6,0,'This land will quiver and shake in the wake of our destruction!',14,0,100,0,0,0,'Comment'),
(46031,0,0,'WHAT HAVE YOU DONE, GODFREY!',12,0,100,0,0,0,'Comment'),
(46031,1,0,'Fix her... FIX HER!',12,0,100,0,0,0,'Comment'),
(46032,0,0,'It will destroy us, sister... ',12,0,100,0,0,0,'Comment'),
(46032,1,0,'Then let it be done.',12,0,100,0,0,0,'Comment'),
(46033,0,0,'It is our sacred duty. The pact was sealed, the bargain made...',12,0,100,0,0,0,'Comment'),
(46034,0,0,'We are bound to her, sisters...',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `VehicleId`=1170 WHERE `entry`=46028;

-- Commander Lorna Crowley
SET @ENTRY := 46001;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,0,0,5,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-713.62,1547.21,28.0,2.93,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,5,68,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Kneel"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,0,8,0,0,0,45,0,6,0,0,0,0,11,46026,35,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Data 6 to Sylvanas"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,6,0,0,69,0,0,0,0,0,0,8,0,0,0,-766.38,1546.82,28.01,3.08,"On Get Data 6 - Move To Pos"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,6,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Force Despawn");

UPDATE `creature_template` SET `minlevel`=20, `maxlevel`=20, `faction_A`=68, `faction_H`=68, `flags_extra`=0 WHERE `entry` IN (46031, 46032, 46033, 46034);

DELETE FROM `conditions` WHERE `SourceEntry` = '85950';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85950, 0, 0, 31, 0, 3, 46026, 0, 0, 0, '', 'Raise Forsaken On Sylvanas');

DELETE FROM `spell_script_names` WHERE `spell_id` = '85950';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85950, 'spell_raise_forsaken_arthura');

DELETE FROM `creature` WHERE `guid` IN (773242, 773243);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(773242, 46124, 0, 1, 1, 0, 1, -698.391, 1546.57, 28.0851, 0, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(773243, 46125, 0, 1, 1, 0, 1, -694.822, 1545.62, 28.0851, 2.87979, 300, 0, 0, 1, 0, 0, 0, 0, 0);

-- Lady Sylvanas Windrunner
SET @ENTRY := 46026;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Rooted"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,3,52,0,100,0,0,46026,0,0,19,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Remove Root"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,53,1,46026,0,27601,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Link - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,5,9,40,0,100,0,1,0,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,46026,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,46026,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,46026,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5 "),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,54,22500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Wp Paused"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,4,0,0,0,0,6,2500,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Talk 6 (NONE)"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,46026,0,0,0,85877,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Summon Crowley (NONE)"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,6,46026,0,0,0,85878,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Summon Bloodfang (NONE)"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,2,0,0,1,7,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 7"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,7,46026,0,0,1,8,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8 "),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,8,46026,0,0,45,0,1,0,0,0,0,11,46036,40,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 1 to Crowley"),
(@ENTRY,@SOURCETYPE,16,0,38,0,100,0,0,3,0,0,1,9,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 9"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,9,46026,0,0,45,0,2,0,0,0,0,11,46036,40,0,0.0,0.0,0.0,0.0,"After Talk 9 - Set Data 2 to Crowley"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,4,0,0,1,10,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 10"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,10,46026,0,0,1,11,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 10 - Talk 11"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,11,46026,0,0,1,12,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 11 - Talk 12"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,12,46026,0,0,1,13,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 12 - Talk 13"),
(@ENTRY,@SOURCETYPE,22,0,52,0,100,0,13,46026,0,0,1,14,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 13 - Talk 14"),
(@ENTRY,@SOURCETYPE,23,0,52,0,100,0,14,46026,0,0,11,85925,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 14 - Summon Godfrey"),
(@ENTRY,@SOURCETYPE,24,0,52,0,100,0,14,46026,0,0,11,85926,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 14 - Summon Walden"),
(@ENTRY,@SOURCETYPE,25,0,52,0,100,0,14,46026,0,0,11,85927,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 14 - Summon Ashbury"),
(@ENTRY,@SOURCETYPE,26,0,38,0,100,0,0,5,0,0,1,15,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 15"),
(@ENTRY,@SOURCETYPE,27,0,52,0,100,0,15,46026,0,0,45,0,2,0,0,0,0,11,46028,95,0,0.0,0.0,0.0,0.0,"After Talk 15 - Set Data 2 to Godfrey"),
(@ENTRY,@SOURCETYPE,28,0,38,0,100,0,0,6,0,0,1,16,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 16"),
(@ENTRY,@SOURCETYPE,29,0,52,0,100,0,16,46026,0,0,1,17,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 16 - Talk 17"),
(@ENTRY,@SOURCETYPE,30,0,52,0,100,0,17,46026,0,0,45,0,5,0,0,0,0,11,46036,25,0,0.0,0.0,0.0,0.0,"After Talk 17 - Set Data 5 to Crowley"),
(@ENTRY,@SOURCETYPE,31,0,38,0,100,0,0,7,0,0,1,18,4500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Talk 18"),
(@ENTRY,@SOURCETYPE,32,0,52,0,100,0,18,46026,0,0,45,0,25,0,0,0,0,11,46028,70,0,0.0,0.0,0.0,0.0,"After Talk 18 - Set Data 25 to Godfrey"),
(@ENTRY,@SOURCETYPE,33,0,38,0,100,0,0,8,0,0,1,19,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 8 - Talk 19"),
(@ENTRY,@SOURCETYPE,34,0,52,0,100,0,19,46026,0,0,45,0,2,0,0,0,0,11,46031,100,0,0.0,0.0,0.0,0.0,"After Talk 19 - Set Data 2 to Cromush"),
(@ENTRY,@SOURCETYPE,35,0,52,0,100,0,19,46026,0,0,11,90359,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 19 - Die (Fake)"),
(@ENTRY,@SOURCETYPE,36,0,52,0,100,0,19,46026,0,0,43,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 19 - Dismount");

-- Commander Lorna Crowley
SET @ENTRY := 46027;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,45878,30,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Godfrey"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,300000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn (5 mins)"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,46028,30,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Godfrey (2)"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,5,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Lord Godfrey
SET @ENTRY := 46028;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,46,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,12,46027,8,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Lorna"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,45,0,3,0,0,0,0,11,46036,100,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 3 to Crowley"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,46028,0,0,12,46001,8,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Summon Lorna"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,46028,0,0,45,0,4,0,0,0,0,11,46036,100,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 4 to Crowley"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,46028,0,0,45,0,5,0,0,0,0,11,46027,15,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 5 to Lorna (On back)"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,20,0,0,69,0,0,0,0,0,0,8,0,0,0,-701.63,1544.31,27.98,2.42,"On Get Data 20 - Move To Pos"),
(@ENTRY,@SOURCETYPE,9,10,38,0,100,0,0,25,0,0,11,101877,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 25 - Shoot Sylvanas"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,45,0,8,0,0,0,0,11,46026,70,0,0.0,0.0,0.0,0.0,"Link - Set Data 8 to Sylvanas"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,4,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 2"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,2,46028,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,3,46028,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,4,46028,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Faction Enemy"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,4,46028,0,0,49,0,0,0,0,0,0,11,46031,70,0,0.0,0.0,0.0,0.0,"After Talk 4 - Attack Cromush"),
(@ENTRY,@SOURCETYPE,16,0,4,0,100,0,0,0,0,0,45,0,30,0,0,0,0,11,46029,50,0,0.0,0.0,0.0,0.0,"On Aggro Set Data 30 to Walden"),
(@ENTRY,@SOURCETYPE,17,0,4,0,100,0,0,0,0,0,45,0,30,0,0,0,0,11,46030,50,0,0.0,0.0,0.0,0.0,"On Aggro Set Data 30 to Ashbury"),
(@ENTRY,@SOURCETYPE,18,19,2,0,100,1,10,45,0,0,42,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"HP - 20% Immunity"),
(@ENTRY,@SOURCETYPE,19,0,61,0,100,0,0,0,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 5"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,5,46028,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,6,46028,0,0,11,52096,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Cast Teleport"),
(@ENTRY,@SOURCETYPE,22,0,8,0,100,0,52096,1,0,0,45,0,50,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Data 50 to Creatures"),
(@ENTRY,@SOURCETYPE,23,0,8,0,100,0,52096,1,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn");

-- Lord Walden
SET @ENTRY := 46029;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,46,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,20,0,0,69,0,0,0,0,0,0,8,0,0,0,-701.0,1542.51,28.02,1.44,"On Get Data 20 - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,30,0,0,2,14,0,0,0,0,0,1,0,0,0,-701.0,1542.51,28.02,1.44,"On Get Data 30 - Set Faction 14"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,30,0,0,49,0,0,0,0,0,0,11,46031,50,0,0.0,0.0,0.0,0.0,"On Get Data 30 - Attack Cromush"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,50,0,0,41,1,0,0,0,0,0,1,0,0,0,-701.0,1542.51,28.02,1.44,"On Get Data 50 - Force Despawn");

-- Baron Ashbury
SET @ENTRY := 46030;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,46,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,20,0,0,69,0,0,0,0,0,0,8,0,0,0,-705.84,1544.32,28.0,0.62,"On Get Data 20 - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,30,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 30 - Set Faction Enemy"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,30,0,0,49,0,0,0,0,0,0,11,46031,50,0,0.0,0.0,0.0,0.0,"On Get Data 30 - Active Start"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,50,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 50 - Force Despawn");

-- High Warlord Cromush
SET @ENTRY := 46031;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,2,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46031,0,0,45,0,4,0,0,0,0,11,46028,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 4 to Godfrey"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,50,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 50 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,46031,0,0,45,0,60,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 60 to Creatures");

-- Arthura
SET @ENTRY := 46032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,61,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 61 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46032,0,0,45,0,61,0,0,0,0,11,46033,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 61 to Daschla"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,62,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 62 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,46032,0,0,11,85950,0,0,0,0,0,11,46026,100,0,0.0,0.0,0.0,0.0,"After Talk 1 - Cast Resurrection"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,33,46019,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,46032,0,0,45,0,65,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 65 to Creatures");

-- Daschla
SET @ENTRY := 46033;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,61,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 61 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46033,0,0,45,0,62,0,0,0,0,11,46032,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 62 to Arthura"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,65,0,0,11,85950,0,0,0,0,0,11,46026,100,0,0.0,0.0,0.0,0.0,"On Get Data 65 - Cast Resurrection");

-- Agatha
SET @ENTRY := 46034;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,60,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 60 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46034,0,0,45,0,61,0,0,0,0,11,46032,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 61 to Arthura"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,65,0,0,11,85950,0,0,0,0,0,11,46026,100,0,0.0,0.0,0.0,0.0,"On Get Data 65 - Cast Resurrection");

-- Packleader Ivar Bloodfang
SET @ENTRY := 46035;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-718.15,1545.64,28.01,0.03,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,46035,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,46035,0,0,69,0,0,0,0,0,0,8,0,0,0,-786.62,1547.89,28.0,3.13,"After Talk 0 - Move to Pos"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,46035,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,46035,0,0,45,0,5,0,0,0,0,11,46026,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 5 to Sylvanas");

-- Lord Darius Crowley
SET @ENTRY := 46036;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-718.23,1548.09,28.01,0.33,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,46036,0,0,45,0,2,0,0,0,0,11,46026,40,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 2 to Sylvanas"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,1,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,46036,0,0,45,0,3,0,0,0,0,11,46026,25,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 3 to Sylvanas"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,46036,0,0,45,0,4,0,0,0,0,11,46026,25,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 4 to Sylvanas"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,4,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,46036,0,0,45,0,1,0,0,0,0,11,46028,150,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 1 to Godfrey"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,4,46036,0,0,45,0,1,0,0,0,0,11,46035,15,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 1 to Bloodfang"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,5,0,0,1,5,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 5"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,5,46036,0,0,45,0,6,0,0,0,0,11,46001,35,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 6 to Lorna"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,5,46036,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Run"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,5,46036,0,0,69,0,0,0,0,0,0,8,0,0,0,-757.46,1547.32,28.0,3.13,"After Talk 5 - Move To Pos"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,5,46036,0,0,41,4000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Force Despawn"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,5,46036,0,0,45,0,7,0,0,0,0,11,46026,60,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 7 to Sylvanas"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,5,46036,0,0,45,0,20,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 20 to Godfrey and Party");

-- Commander Lorna Crowley
SET @ENTRY := 46001;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,5,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-713.62,1547.21,28.0,2.93,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,17,68,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Kneel"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,0,8,0,0,0,45,0,6,0,0,0,0,11,46026,35,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Data 6 to Sylvanas"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,6,0,0,69,0,0,0,0,0,0,8,0,0,0,-766.38,1546.82,28.01,3.08,"On Get Data 6 - Move To Pos"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,6,0,0,41,4000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Force Despawn");

SET @CGUID := 798524;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+4;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 46033, 0, 1, 32768, 0, 0, -703.521, 1552.16, 33.0162, 3.46816, 300, 0, 0, 1260, 0, 0, 0, 0, 0),
(@CGUID+1, 46032, 0, 1, 32768, 0, 0, -703.537, 1542.54, 33.1821, 2.71184, 300, 0, 0, 1260, 0, 0, 0, 0, 0),
(@CGUID+2, 46034, 0, 1, 32768, 0, 0, -702.363, 1547.37, 36.9966, 3.05741, 300, 0, 0, 1260, 0, 0, 0, 0, 0),
(@CGUID+3, 46031, 0, 1, 32768, 0, 1, -704.026, 1550.31, 28.0043, 3.09275, 300, 0, 0, 630, 0, 0, 0, 0, 0),
(@CGUID+4, 46026, 0, 1, 32768, 0, 1, -704.916, 1547.49, 28.003, 3.09275, 300, 0, 0, 21800, 0, 0, 0, 134217728, 0);

DELETE FROM `creature_involvedrelation` WHERE `id` = '46026' AND `quest` = '27601';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46026, 27601);

DELETE FROM `creature_questrelation` WHERE `id` = '46026' AND `quest` = '27746';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(46026, 27746);

UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `id` IN (54372, 42407, 54371, 54373);
UPDATE `creature_template` SET `mindmg`=5, `maxdmg`=8 WHERE `entry`=42407;
UPDATE `creature` SET `spawndist`=10, `phaseMask`=1, `MovementType`=1 WHERE `id` IN (594, 589, 449);