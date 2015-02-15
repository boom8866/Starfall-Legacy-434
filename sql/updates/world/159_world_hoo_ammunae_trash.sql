DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40668';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `description`) VALUES
(40668, 40669, 'Budding Spore');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40668';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40668, 46598, 0);

UPDATE `creature_template` SET `ScriptName`='npc_hoo_seed_pod_trash' WHERE `entry`=40716;

-- Seedling Pod
SET @ENTRY := 40716;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

-- Budding Spore
SET @ENTRY := 40669;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,11,75701,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Spore Cloud");

UPDATE `creature_template` SET `ScriptName`='npc_hoo_lifewarden_nynph' WHERE `entry`=40715;

-- Lifewarden Nymph
SET @ENTRY := 40715;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218712';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(218712, 218712, 0, 0, 2),
(218712, 218722, 0, 0, 2),
(218712, 218721, 0, 0, 2),
(218712, 218714, 0, 0, 2),
(218712, 218718, 0, 0, 2),
(218712, 218717, 0, 0, 2),
(218712, 218414, 0, 0, 2),
(218712, 218715, 0, 0, 2);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218711';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(218711, 218711, 0, 0, 2),
(218711, 218719, 0, 0, 2),
(218711, 218716, 0, 0, 2),
(218711, 218725, 0, 0, 2),
(218711, 218720, 0, 0, 2),
(218711, 218729, 0, 0, 2),
(218711, 218713, 0, 0, 2),
(218711, 218724, 0, 0, 2),
(218711, 218723, 0, 0, 2),
(218711, 218413, 0, 0, 2);