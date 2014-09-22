DELETE FROM `creature_text` WHERE `entry`=34571;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34571,0,0,'Welcome back, $n. You were fortunate. Krennan\'s treatment doesn\'t always work this well on people who\'ve had the Curse as long as you.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36132;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36132,0,0,'Do exercise caution. Don\'t expect anyone to invite you to their homes just yet. But at least they won\'t shoot you outright.',12,0,100,0,0,0,'Comment');

-- Krennan Aranas
SET @ENTRY := 36132;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,14313,0,0,0,1,0,8000,0,0,0,0,10,798902,34571,0,0.0,0.0,0.0,0.0,"On Quest Reward - Talk 0 Gwen"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,34571,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 0");

UPDATE `creature_template` SET `flags_extra`=0, `ScriptName`='npc_forsaken_invader' WHERE `entry`=34511;
UPDATE `creature_template` SET `ScriptName`='npc_duskhaven_watchman' WHERE `entry`=36211;

-- Prince Liam Greymane
SET @ENTRY := 36140;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,1032,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Immune"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,6000,4000,6500,11,68552,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Throw Bottle");

UPDATE `creature_template` SET `ScriptName`='npc_dh_forsaken_catapult' WHERE `entry`=36283;
UPDATE `creature` SET `spawntimesecs`=120 WHERE `id`='36283';

DELETE FROM `conditions` WHERE `SourceEntry` = '68591' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 68591, 0, 0, 31, 0, 3, 36286, 0, 0, 0, '', 'Targeting -> Catapult Triggers');

DELETE FROM `spell_script_names` WHERE `spell_id` = '68591';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(68591, 'spell_catapult_boulder');

UPDATE `creature_template` SET `npcflag`=0 WHERE `entry`=36283;
UPDATE `npc_spellclick_spells` SET `spell_id`=46598 WHERE `npc_entry`=36283 AND `spell_id`=69434;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56007';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56007, 'Your mother\'s in the basement next door. Get to her now!', 1, 1);

UPDATE `creature_template` SET `gossip_menu_id`=56007 WHERE `entry`=36289;
UPDATE `creature` SET `spawndist`=8, `MovementType`=1, `spawntimesecs`=60 WHERE `guid`=799075;

DELETE FROM `conditions` WHERE `SourceGroup`=56007 AND `SourceEntry` = '0';

DELETE FROM `creature_text` WHERE `entry`=36289;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36289,0,0,'Don\'t hurt me! I was just looking for my sister! I think Ashley\'s inside that house!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_dh_james' WHERE `entry`=36289;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_dh_ashley' WHERE `entry`=36288;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_dh_cynthia' WHERE `entry`=36287;

DELETE FROM `conditions` WHERE `SourceEntry` = '68659' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 68659, 0, 0, 31, 0, 3, 36286, 0, 0, 0, '', 'Targeting -> Catapult Triggers');

DELETE FROM `creature_text` WHERE `entry`=36288;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36288,0,0,'Are you one of the good worgen, mister? Did you see Cynthia hinding in the sheds outside?',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36287;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36287,0,0,'You are scary! I just want my mommy!',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `spawntimesecs`=120 WHERE `map`='654' AND `spawntimesecs` >= '120';
UPDATE `creature` SET `phaseMask`=4096 WHERE `id`=36211;
UPDATE `creature_template` SET `ScriptName`='npc_forsaken_footsoldier' WHERE `entry`=36236;
UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `id`='36236';
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `id`='36211';
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=36211;

DELETE FROM `conditions` WHERE `SourceEntry` = '68659' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 68659, 0, 0, 31, 0, 3, 36286, 0, 0, 0, '', 'Targeting -> Catapult Triggers');

DELETE FROM `spell_script_names` WHERE `spell_id` = '68659';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(68659, 'spell_load_catapult_boulder');

DELETE FROM `conditions` WHERE `SourceEntry` = '14386' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 14386, 14382, 0),
(20, 8, 14386, 14369, 0),
(20, 8, 14386, 14368, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '14386' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 14386, 14382, 0),
(19, 8, 14386, 14369, 0),
(19, 8, 14386, 14368, 0);