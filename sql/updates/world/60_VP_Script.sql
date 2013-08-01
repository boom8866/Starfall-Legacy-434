-- Script Texts
DELETE FROM `creature_text` WHERE `entry` = 43875;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
('43875', '0', '0', 'YOU tread upon the sacrosanct! Mortals have no place amidst the clouds.', '14', '0', '100', '0', '0', '20867', 'Asaad'),
('43875', '1', '0', 'Al\'Akir, your servant calls for aid!', '14', '0', '100', '0', '0', '20869', 'Asaad'),
('43875', '2', '0', '%s conjure a temporary grounding field!', '41', '0', '100', '0', '0', '', 'Asaad'),
('43875', '3', '0', 'The winds take me!', '14', '0', '100', '0', '0', '20870', 'Asaad'),
('43875', '4', '0', 'BACK to the earth with you!', '14', '0', '100', '0', '0', '20868', 'Asaad');

DELETE FROM `conditions` WHERE `SourceEntry` IN(87517,86911);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('13', '7', '87517', '0', '0', '31', '0', '3', '47085', '0', '0', '0', '0', '', 'Grounding Field Visual Beams - target World Trigger'),
('13', '7', '86911', '0', '0', '31', '0', '3', '46492', '0', '0', '0', '0', '', 'Unstable Grounding Field - target World Trigger');

-- Grounding Field
UPDATE `creature_template` SET `HoverHeight`='1', `flags_extra`='130',`faction_A`='14', `faction_H`='14', `npcflag`='256', `InhabitType` = 4 WHERE `entry`='47085';
-- Unstable Grounding Field
UPDATE `creature_template` SET `HoverHeight`='1', `flags_extra`='130',`faction_A`='114',`VehicleId`='192' , `faction_H`='114', `npcflag`='256', `InhabitType` = 4, `ScriptName`='npc_field_walker' WHERE `entry`='46492';
-- Assad
UPDATE `creature_template` SET `HoverHeight`='10', `flags_extra`='1', `InhabitType` = 4,`ScriptName`='boss_asaad' WHERE `entry`='43875';

-- Slipstream
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_slipstream' WHERE `entry` = 45455;

-- Spell Script Names
DELETE FROM `spell_script_names` WHERE `spell_id` IN (85063,87726,87474,87553,93994);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('85063', 'spell_slipstream'),
('87726', 'spell_grounding_field_pulse'),
('87474', 'spell_grounding_field_pulse'),
('87553', 'spell_supremacy_of_the_storm_damage'),
('93994', 'spell_supremacy_of_the_storm_damage');
