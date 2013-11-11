
-- Whack a gnoll!
UPDATE `creature_template` SET `scriptname`= '' WHERE `entry`= 54601;

-- 102022 whack!
DELETE FROM conditions WHERE SourceEntry IN (102022);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 102022, 0, 0, 31, 0, 3, 54444, 0, 0, 0, '', 'Whack! - Target Gnoll'),
(13, 1, 102022, 1, 0, 31, 0, 3, 54466, 0, 0, 0, '', 'Whack! - Target Gnoll Baby'),
(13, 1, 102022, 2, 0, 31, 0, 3, 54549, 0, 0, 0, '', 'Whack! - Target Hogger');

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (13018, 13065);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES (13018, 0, 0, 'How do I play Whack-a-Gnoll?', 1, 1, 13065, 0, 0, 0, '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES (13018, 1, 0, 'Ready to whack! |cFF0008E8(Darkmoon Game Token)|r', 1, 1, 0, 0, 0, 0, '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES (13065, 0, 0, 'I understand.', 1, 1, 13018, 0, 0, 0, '');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 54601;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 1, 54601, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play'),
(22, 2, 54601, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play'),
(22, 3, 54601, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play');

-- Mola
SET @ENTRY := 54601;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,13018,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,13018,1,0,0,75,101612,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Add Aura 101612"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,13018,1,0,0,57,71083,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Token"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,60000,60000,60000,120000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"1-2min - Talk");

DELETE FROM `creature_text` WHERE `entry` = 54601;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(54601, 0, 0, 'Hammer swingin\' fun! Who wants to swing a hammer?', 12, 0, 100, 0, 0, 0, ''),
(54601, 0, 1, 'Hammer time!', 12, 0, 100, 0, 0, 0, ''),
(54601, 0, 2, 'Swing a hammer, win a prize!', 12, 0, 100, 0, 0, 0, ''),
(54601, 0, 3, 'Whack some gnolls! Step right up and whack some gnolls!', 12, 0, 100, 0, 0, 0, '');

REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(101612, 110230, 2, ''),
(-101612, 110966, 0, '');

DELETE FROM `areatrigger_scripts` WHERE entry = 7344;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(7344, 'at_whack_a_gnoll');

-- Darkmoon Death Match Pit
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(108941, 'spell_darkmoon_deathmatch');
