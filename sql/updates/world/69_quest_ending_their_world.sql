-- TODO: Get better waypoints and sniff retail creature_text!

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '7538';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(7538, 'I\'m ready to fight Sironas!', 1, 1);

DELETE FROM `waypoints` WHERE `entry` = '17982';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(17982, 1, -1811.75, -11123.03, 64.19, 'Legoso WP'),
(17982, 2, -1827.95, -11094.94, 63.80, 'Legoso WP'),
(17982, 3, -1867.21, -11077.34, 60.78, 'Legoso WP'),
(17982, 4, -1885.31, -11048.42, 59.43, 'Legoso WP'),
(17982, 5, -1879.23, -10990.85, 60.74, 'Legoso WP'),
(17982, 6, -1933.92, -10893.70, 63.32, 'Legoso WP'),
(17982, 7, -1901.38, -10947.50, 61.48, 'Legoso WP'),
(17982, 8, -1880.84, -10744.31, 109.83, 'Legoso WP'),
(17982, 9, -1929.58, -10567.61, 176.96, 'Legoso WP');

UPDATE `quest_template` SET `RequiredNpcOrGo1`=17678, `RequiredNpcOrGoCount1`=1 WHERE  `Id`=9759;
UPDATE `quest_template` SET `EndText`='' WHERE  `Id`=9759;
UPDATE `creature_template` SET `ScriptName`='npc_sironas' WHERE `entry`= '17678';

-- Sironas
SET @ENTRY := 17678;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,17678,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2500,6300,2000,5000,11,8282,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Curse of Blood"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,4000,6500,11,12742,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Immolate"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,500,500,2000,10000,11,10966,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Uppercut"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,17982,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Legoso");

-- Demolitionist Legoso
SET @ENTRY := 17982;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,7538,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,7538,0,0,0,12,17982,8,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Self"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,53,1,17982,0,9759,0,2,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Gossip"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,9,0,0,0,49,0,0,0,0,0,0,10,63402,17678,0,0.0,0.0,0.0,0.0,"On WP Reached - Attack Sironas"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,1500,1500,20000,20000,11,38116,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Searing Totem"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,1500,1500,20000,20000,11,31633,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Strength of Earth Totem"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,1500,1500,20000,20000,11,8004,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Healing Surge"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,2500,3500,2500,2500,11,8056,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frost Shock"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,1,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Get 1 - Force Despawn ");