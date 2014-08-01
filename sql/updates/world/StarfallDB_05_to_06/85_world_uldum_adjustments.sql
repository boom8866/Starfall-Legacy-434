UPDATE `spell_area` SET `quest_start_status`=66 WHERE `spell`=94566 AND `area`=440 AND `quest_start`=28558 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
UPDATE `spell_area` SET `quest_start_status`=66 WHERE `spell`=94566 AND `area`=440 AND `quest_start`=28557 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
UPDATE `spell_area` SET `quest_start_status`=66 WHERE `spell`=94566 AND `area`=440 AND `quest_start`=28296 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
UPDATE `spell_area` SET `quest_start_status`=66 WHERE `spell`=94566 AND `area`=440 AND `quest_start`=28295 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=45715;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=48991;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid`=77465;

-- Fusion Core
SET @ENTRY := 46750;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27779,0,0,0,85,86418,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Fusion Core");

DELETE FROM `spell_script_names` WHERE `spell_id` = '85188';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85188, 'spell_move_champions');

-- Ramkahen Prisoner
SET @ENTRY := 46425;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=49281;
UPDATE `spell_area` SET `quest_start_status`=66 WHERE `spell`=94566 AND `area`=5602 AND `quest_start`=28267 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27926';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 5602, 27926, 27926, 1, 10);