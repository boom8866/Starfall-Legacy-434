DELETE FROM `creature` WHERE `guid` IN (5767, 775041, 775040, 775039);
DELETE FROM `creature_addon` WHERE `guid` IN (5767, 775041, 775040, 775039);

DELETE FROM `creature_text` WHERE `entry` IN (315, 43904);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(315,0,0,'I shall spill your blood, $C!',12,0,100,0,0,0,'Stalvan Mistmantle'),
(315,0,1,'Who dares disturb me?  Die $N!',12,0,100,0,0,0,'Stalvan Mistmantle'),
(315,1,0,'My ring... Who holds my family ring... Tilloa, is that you?',12,0,100,0,0,0,'Comment'),
(315,2,0,'Tobias...',12,0,100,0,0,0,'Comment'),
(315,3,0,'It\'s all true, brother. Every word. You doubted it?',12,0,100,0,0,0,'Comment'),
(315,4,0,'You know why!',12,0,100,0,0,0,'Comment'),
(315,5,0,'Surely you\'ve felt anger. Anger so foul and vicious that it makes you want to tear someone to shreds...',12,0,100,0,0,0,'Comment'),
(315,6,0,'Aren\'t you feeling it right now?',12,0,100,0,0,0,'Comment'),
(315,7,0,'You see, brother... we\'re not so different...',12,0,100,0,0,0,'Comment'),
(43904,0,0,'Brother!',12,0,100,0,0,0,'Comment'),
(43904,1,0,'Tell me it\'s not true, brother. Tell me you didn\'t die a murderer!',12,0,100,0,0,0,'Comment'),
(43904,2,0,'But why?! How could you?',12,0,100,0,0,0,'Comment'),
(43904,3,0,'No... NO! STOP IT!',14,0,100,0,0,0,'Comment'),
(43904,4,0,'No...',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '82029';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82029, 'spell_call_stalvan');

UPDATE `creature_template` SET `minlevel`=23, `maxlevel`=23, `mindmg`=23, `maxdmg`=44, `dmg_multiplier`=3, `baseattacktime`=2000, `rangeattacktime`=2000, `Health_mod`=5 WHERE `entry`=43904;

-- Tobias Mistmantle
SET @ENTRY := 43904;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward 5 yd"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,43904,0,0,45,0,1,0,0,0,0,11,315,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tobias"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,2,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,43904,0,0,45,0,2,0,0,0,0,11,315,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Tobias"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,2,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,43904,0,0,45,0,3,0,0,0,0,11,315,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Tobias"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,4,0,0,1,3,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,43904,0,0,11,81908,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Cast Transform Worgen"),
(@ENTRY,@SOURCETYPE,9,10,8,0,100,0,81908,1,0,0,3,0,33508,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Morph into Worgen"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,2,2173,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 1770"),
(@ENTRY,@SOURCETYPE,11,0,4,0,100,0,0,0,0,0,11,76678,2,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Jump"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,5,0,0,1,4,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 4"),
(@ENTRY,@SOURCETYPE,13,14,52,0,100,0,4,43904,0,0,69,0,0,0,0,0,0,8,0,0,0,-10355.5,-1256.69,35.3,0.05,"After Talk 4 - Move Out"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Stalvan Mistmantle
SET @ENTRY := 315;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,20,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stalvan Mistmantle - On Aggro - Say Line 0"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7800,9000,8000,16000,11,3105,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Stalvan Mistmantle - In Combat - Cast Curse of Stalvan"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Stalvan Mistmantle - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,3,4,54,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,69,2,0,0,0,0,0,8,0,0,0,-10369.6,-1254.16,35.9,5.99,"Link - Move to Pos"),
(@ENTRY,@SOURCETYPE,5,18,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,1,0,0,1,2,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,315,0,0,45,0,1,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Tobias"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,2,315,0,0,45,0,2,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Tobias"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,2,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,3,315,0,0,45,0,3,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Tobias"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,3,0,0,1,4,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,4,315,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,5,315,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,4,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 7"),
(@ENTRY,@SOURCETYPE,15,19,52,0,100,0,6,315,0,0,45,0,4,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 4 to Tobias"),
(@ENTRY,@SOURCETYPE,16,0,6,0,100,0,0,0,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 7"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,7,315,0,0,45,0,5,0,0,0,0,11,43904,200,0,0.0,0.0,0.0,0.0,"After Talk 7 - Set Data 5 to Tobias"),
(@ENTRY,@SOURCETYPE,18,0,61,0,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Unattackable"),
(@ENTRY,@SOURCETYPE,19,0,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Aggressive"),
(@ENTRY,@SOURCETYPE,20,21,4,0,100,0,0,0,0,0,19,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Make attackable"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,43904,100,0,0.0,0.0,0.0,0.0,"Link - Attack Start");

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '43915';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`) VALUES
(43862, 43915, 1, 'Stitches -> Abercrombie');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '43862';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(43862, 46598, 0);

UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (43903, 43862);
UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry`=43862;
UPDATE `creature_template` SET `mindmg`=43, `maxdmg`=63, `attackpower`=16, `dmg_multiplier`=2, `baseattacktime`=3000, `rangeattacktime`=3000, `spell1`=3106, `unit_flags`=0, `type_flags`=0, `mechanic_immune_mask`=0, `ScriptName`='generic_creature', `Armor_mod`=3 WHERE `entry`=43862;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=775039;

DELETE FROM `world_quest_phases` WHERE `QuestId` = '26727';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `ZoneId`, `AreaId`, `Comment`) VALUES
(26727, 2, 4, 10, 42, 'Quest ID: 26727 - The Embalmer\'s Revenge (ON AURA UPDATE)');

DELETE FROM `spell_area` WHERE `quest_end` = '26727';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(82071, 42, 26727, 26727, 1, 10, 10);

UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=5566;
UPDATE `creature_template` SET `flags_extra`=2 WHERE `entry`=43915;

-- Abercrombie
SET @ENTRY := 43915;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Set Passive");

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry` IN (288, 43861, 43730);
UPDATE `creature` SET `phaseMask`='1' WHERE `id` IN (288, 43861, 43730);

DELETE FROM `spell_script_names` WHERE `spell_id` = '82130';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82130, 'spell_sacred_cleansing_bane');

DELETE FROM `creature` WHERE `guid`IN (191556, 191401, 191636, 191516, 191641, 191567, 191508, 191451, 191453, 191444, 191360, 191352, 191324, 191153, 191245,
191435, 191261, 191293, 191299, 191309, 191327, 191271, 191287, 191318, 191334, 191491, 191341, 191420);
DELETE FROM `creature_addon` WHERE `guid`IN (191556, 191401, 191636, 191516, 191641, 191567, 191508, 191451, 191453, 191444, 191360, 191352, 191324, 191153, 191245,
191435, 191261, 191293, 191299, 191309, 191327, 191271, 191287, 191318, 191334, 191491, 191341, 191420);

DELETE FROM `creature` WHERE `guid`IN (191326, 191314, 191336, 191330, 191317, 191310, 191308, 191294, 191273, 191270, 191264);
DELETE FROM `creature_addon` WHERE `guid`IN (191326, 191314, 191336, 191330, 191317, 191310, 191308, 191294, 191273, 191270, 191264);

-- Plague Spreader
SET @ENTRY := 604;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Plague Spreader - Out Of Combat - Cast Birth"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,7300,420000,426000,11,3436,32,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Plague Spreader - In Combat - Cast Wandering Plague"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive");

-- Rotted One
SET @ENTRY := 948;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Rotted One - Out Of Combat - Cast Birth"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,1,0,0,0,0,11,3428,3,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Rotted One - On Death - Cast Summon Flesh Eating Worms"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive");

-- Bone Chewer
SET @ENTRY := 210;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bone Chewer - Out Of Combat - Cast Birth"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,12100,46200,66200,11,6016,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Bone Chewer - In Combat - Cast Pierce Armor"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive");

-- Soothing Incense Cloud
SET @ENTRY := 43925;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,2500,2500,6000,6000,51,0,0,0,0,0,0,11,43923,10,0,0.0,0.0,0.0,0.0,"On Just Summoned - Kill Spirit");

-- Forlorn Spirit
SET @ENTRY := 43923;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,8000,15000,21000,11,81193,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Unrelenting Anguish"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,33,43930,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=43925;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6112';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6112, 'at_addle_stead_event');

DELETE FROM `conditions` WHERE `SourceEntry` = '82058';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 82058, 0, 0, 31, 0, 3, 43814, 0, 0, 0, '', 'Harris\'s Ampule - Targeting Lurkering Worgen');

DELETE FROM `spell_script_names` WHERE `spell_id` = '82058';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82058, 'spell_harris_ampule');

DELETE FROM `creature_text` WHERE `entry`=43814;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43814,0,0,'The worgen stares and hesitates!',41,0,100,0,0,0,'Comment');

-- Lurking Worgen
SET @ENTRY := 43814;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,24,25,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 25% - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,7,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Despawn"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Remove Unit Flags");

DELETE FROM `creature` WHERE `guid`=191536;
DELETE FROM `creature_addon` WHERE `guid`=191536;

DELETE FROM `creature_text` WHERE `entry` IN (43730, 43950, 288);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43730,0,0,'Here we go...',12,0,100,0,0,0,'Comment'),
(43730,1,0,'It\'s working. Hold him still, Jitters.',12,0,100,0,0,0,'Comment'),
(43730,2,0,'Damn it, Jitters, I said HOLD!',12,0,100,0,0,0,'Comment'),
(43730,3,0,'Letting him go is the only thing that\'s going to separate you from the beasts now, my friend.',12,0,100,0,0,0,'Comment'),
(43950,0,0,'Jitters...',12,0,100,0,0,0,'Comment'),
(43950,1,0,'JITTERS!',14,0,100,0,0,0,'Comment'),
(43950,2,0,'I remember now... it\'s all your fault!',12,0,100,0,0,0,'Comment'),
(43950,3,0,'You brought the worgen to Duskwood! You led the Dark Riders to my farm, and hid while they murdered my family!',12,0,100,0,0,0,'Comment'),
(43950,4,0,'Every speck of suffering in my life is YOUR PATHETIC FAULT! I SHOULD KILL YOU!',14,0,100,0,0,0,'Comment'),
(43950,5,0,'You\'ve got a lot to make up for, Jitters. I won\'t give you the easy way out.',12,0,100,0,0,0,'Comment'),
(288,0,0,'I... I can\'t...',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` IN (288, 43730);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(288, 1, -10745.28, 332.47, 37.78, 'WP Jitters'),
(288, 2, -10745.45, 331.67, 37.82, 'WP Jitters'),
(43730, 1, -10750.63, 326.43, 37.71, 'WP Oliver Harris'),
(43730, 2, -10749.67, 329.53, 37.56, 'WP Oliver Harris');

DELETE FROM `creature_template_addon` WHERE `entry` = '43950';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(43950, '69196');

UPDATE `creature_template` SET `VehicleId`=1077 WHERE `entry`=43950;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '43950';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(43950, 82266, 0);

-- Lurking Worgen
SET @ENTRY := 43950;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,43950,0,0,45,0,1,0,0,0,0,10,191482,43730,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Oliver Harris"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,7,52,0,100,0,1,43950,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,43950,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,3,43950,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,4,43950,0,0,45,0,2,0,0,0,0,10,191482,43730,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 2 to Oliver Harris"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,28,69196,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove In Stocks"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,45,0,3,0,0,0,0,10,191522,288,0,0.0,0.0,0.0,0.0,"Link - Set Data 3 to Jitters"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,43950,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Unchoke Jitters"),
(@ENTRY,@SOURCETYPE,10,11,38,0,100,0,0,5,0,0,1,5,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 5"),
(@ENTRY,@SOURCETYPE,11,12,61,0,100,0,0,0,0,0,69,46598,0,0,0,0,0,8,0,0,0,-10766.0,334.93,37.67,2.64,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,12,13,61,0,100,0,0,0,0,0,41,12000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (12 secs)"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,33,43969,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,5,43950,0,0,70,0,0,0,0,0,0,11,0,150,0,0.0,0.0,0.0,0.0,"After Talk 5 - Reset All");

-- Jitters
SET @ENTRY := 288;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Jitters - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,0,0,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,53,1,288,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,2,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,288,0,0,45,0,1,0,0,0,0,11,43950,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Lurking Worgen"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,11,46598,2,0,0,0,0,11,43950,50,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Choked");

-- Oliver Harris
SET @ENTRY := 43730;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,19,0,100,0,26760,0,0,0,12,43950,8,0,0,0,0,8,0,0,0,-10747.4,331.95,37.73,4.48,"On Quest Accepted - Summon Lurking Worgen"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,191522,288,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Jitters"),
(@ENTRY,@SOURCETYPE,2,10,61,0,100,0,0,0,0,0,53,0,43730,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,2,0,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,43730,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,43730,0,0,45,0,2,0,0,0,0,10,191522,288,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Jitters"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,1,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,43730,0,0,45,0,2,0,0,0,0,11,43950,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Lurking Worgen"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,2,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,43730,0,0,45,0,5,0,0,0,0,11,43950,50,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 5 to Lurking Worgen"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Npc Flag 0"),
(@ENTRY,@SOURCETYPE,11,0,7,0,100,0,0,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Npc Flag 3");