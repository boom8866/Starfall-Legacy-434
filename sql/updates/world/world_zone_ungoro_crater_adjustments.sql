DELETE FROM `item_loot_template` WHERE `item` = '50238';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50238, 50236, 100, 1, 0, 1, 1);

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=9999;
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id` IN (24722, 24721, 24723);
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=727918;

-- Northern Crystal Pylon
SET @ENTRY := 164955;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,15,24722,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Complete");

-- Western Crystal Pylon
SET @ENTRY := 164956;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,15,24723,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Complete");

-- Eastern Crystal Pylon
SET @ENTRY := 164957;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,15,24721,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Complete");

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=38504;

DELETE FROM `conditions` WHERE `SourceEntry` = '24694' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 24694, 24721, 0),
(20, 8, 24694, 24722, 0),
(20, 8, 24694, 24723, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '24694' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 24694, 24721, 0),
(19, 8, 24694, 24722, 0),
(19, 8, 24694, 24723, 0);

DELETE FROM `spell_area` WHERE `spell` = '72127' AND `quest_start` IN (24721, 24722, 24723);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`) VALUES
(72127, 4882, 24721, 1),
(72127, 4882, 24722, 1),
(72127, 4882, 24723, 1);

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=24735;
UPDATE `creature_template` SET `ScriptName`='npc_ringo' WHERE `entry`=9999;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11037 AND `id`=1;

DELETE FROM `conditions` WHERE `SourceGroup`=11037 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11037, 0, 0, 0, 28, 0, 24694, 0, 0, 0, 0, 0, '', 'Ungoro Examinant - Show gossip only if quest 24694 is complete');

-- Un'Goro Examinant
SET @ENTRY := 38504;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11037,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11037,1,0,0,11,72159,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Teleport To Shaper's Terrace");

UPDATE `quest_template` SET `PrevQuestId`='13850' WHERE `Id`=13887;

DELETE FROM `creature_loot_template` WHERE `item` = '11477';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(6505, 11477, -100, 1, 0, 1, 1),
(6506, 11477, -100, 1, 0, 1, 1),
(6507, 11477, -100, 1, 0, 1, 1),
(6508, 11477, -100, 1, 0, 1, 1),
(6581, 11477, -100, 1, 0, 1, 1),
(9683, 11477, -100, 1, 0, 1, 1),
(9684, 11477, -100, 1, 0, 1, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (72168, 72179, 72187, 72197);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72168, 'spell_ever_watching_from_above'),
(72179, 'spell_ever_watching_from_above'),
(72187, 'spell_ever_watching_from_above'),
(72197, 'spell_ever_watching_from_above');

UPDATE `creature_loot_template` SET `maxcount`=6 WHERE `entry`=9165 AND `item`=11831;
UPDATE `creature_loot_template` SET `maxcount`=6 WHERE `entry`=9166 AND `item`=11831;
UPDATE `creature_loot_template` SET `maxcount`=6 WHERE `entry`=9167 AND `item`=11831;

DELETE FROM `creature_text` WHERE `entry`=38502;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38502,0,0,'I want you to pit the Bloodpetal against one another.',42,0,100,0,0,0,'Comment'),
(38502,1,0,'Challenge and defeat another Bloodpetal in one-on-one combat.',42,0,100,0,0,0,'Comment'),
(38502,2,0,'I want you to speak with the local gorillas.',42,0,100,0,0,0,'Comment'),
(38502,3,0,'Speak with one of each type - Gorilla, Stomper, and Thunderer - and learn what they have to teach you.',42,0,100,0,0,0,'Comment'),
(38502,4,0,'I want you to test the limits of your wings.',42,0,100,0,0,0,'Comment'),
(38502,5,0,'Fly high up above the jungle canopy.$b$bUse Pterrordash to temporarily increase your flight speed.$b$b|TInterface\\Icons\\ability_druid_dash.blp:32|t',42,0,100,0,0,0,'Comment'),
(38502,6,0,'I want you to test your Bite skill on the people of Marshal\'s Stand.',42,0,100,0,0,0,'Comment'),
(38502,7,0,'|TInterface\\Icons\\inv_misc_monsterfang_02.blp:32|t Use Bite on 5 humanoid targets.',42,0,100,0,0,0,'Comment'),
(38502,8,0,'|TInterface\\Icons\\inv_misc_bone_02.blp:32|t Use Bony Armor to increase your armor.',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_nablya' WHERE `entry`=38502;
UPDATE `creature_template` SET `ScriptName`='npc_ithis_moonwarden' WHERE `entry`=38263;
UPDATE `quest_template` SET `Method`=2, `Flags`=0 WHERE `Id`=24702;

DELETE FROM `gameobject_questrelation` WHERE `quest` = '24702';
INSERT INTO `gameobject_questrelation` (`id`, `quest`) VALUES
(202135, 24702);

DELETE FROM `gameobject_involvedrelation` WHERE `quest` = '24702';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(202135, 24702);

UPDATE `creature_template` SET `mindmg`=89, `maxdmg`=119, `attackpower`=218 WHERE `entry` IN (38254, 38329, 38305, 38307, 38214);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (72188, 72177);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72188, 'spell_bite_diemetradon'),
(72177, 'spell_ptherrordax_dash');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11042 WHERE `menu_id`=11043 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11042 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11040 WHERE  `menu_id`=11041 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11040 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11038 WHERE  `menu_id`=11039 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11038 AND `id`=0;

-- Un'Goro Gorilla
SET @ENTRY := 6514;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,12000,18000,11,83012,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Fling Filth"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11040,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,33,0,11040,0,0,0,85,72186,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Un'Goro Stomper
SET @ENTRY := 6513;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4500,19000,24000,11,83378,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Stomp"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11042,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,33,0,11042,0,0,0,85,72186,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Un'Goro Thunderer
SET @ENTRY := 6516;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5500,15000,21000,11,12553,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shock"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11038,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,33,0,11038,0,0,0,85,72186,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");