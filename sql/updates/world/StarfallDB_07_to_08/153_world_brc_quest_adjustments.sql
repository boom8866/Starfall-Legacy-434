UPDATE `quest_template` SET `QuestStartType`=1 WHERE `Id` IN (28740, 28738);

DELETE FROM `areatrigger_queststart` WHERE `quest_id` IN (28740, 28738);
INSERT INTO `areatrigger_queststart` (`trigger_id`, `quest_id`) VALUES
(6597, 28740),
(6594, 28738);

UPDATE `quest_template` SET `PrevQuestId`='28735' WHERE `Id`=28737;
UPDATE `quest_template` SET `PrevQuestId`='28737' WHERE `Id`=28738;
UPDATE `quest_template` SET `PrevQuestId`='28738' WHERE `Id`=28740;
UPDATE `quest_template` SET `PrevQuestId`='28740' WHERE `Id`=28741;

UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (49445, 49444);

DELETE FROM `creature_template_addon` WHERE `entry` IN (49445, 49444);
DELETE FROM `creature_questrelation` WHERE `id`=49476 AND `quest` IN (28740, 28738, 28737);

-- Finkle Einhorn
SET @ENTRY := 49476;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,3000,3000,3000,3000,15,28732,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"OOC - Complete Quest");

UPDATE `creature_template` SET `speed_walk`=2, `speed_run`=2.42857 WHERE `entry`=39670;