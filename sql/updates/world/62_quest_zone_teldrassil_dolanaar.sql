UPDATE `quest_template` SET `PrevQuestId`=0, `NextQuestId`=933 WHERE `Id`=7383;
UPDATE `quest_template` SET `PrevQuestId`=7383 WHERE `Id`=933;

DELETE FROM `spell_area` WHERE `quest_start` IN (919, 918);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84777, 186, 919, 919, 0, 0, 2, 1, 64, 64),
(84777, 186, 918, 918, 0, 0, 2, 1, 64, 64);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735143;
UPDATE `quest_template` SET `SourceSpellId`=65602 WHERE `Id`=14005;

DELETE FROM `spell_script_names` WHERE `spell_id` = '66166';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66166, 'spell_cancel_vengeance_of_elune');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '65455';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(65455, 68295, 2, 'Nature Fury -> Effect Visual');

UPDATE `creature_template` SET `ScriptName`='npc_grellkin' WHERE `entry`=1989;