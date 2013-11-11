-- Blackrock Caverns
-- 39665 Rom'ogg Bonecrusher
-- Race	Ogre lord (Humanoid)
-- Level	 82 - 87 Elite
-- Health	 893,580 - 4,564,670 (Heroic)

DELETE FROM `creature_text` WHERE `entry` = 39665;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39665', '0', '0', 'Boss Cho\'gall not gonna be happy \'bout dis!', '14', '0', '0', '0', '0', '18925', 'SAY_AGGRO'), 
('39665', '1', '0', 'Stand still! Rom\'ogg crack your skulls!', '14', '0', '0', '0', '0', '18927', 'SKULLCRACKER'),
('39665', '2', '0', 'That what you get! Nothing!', '14', '0', '0', '0', '0', '18926', 'SAY_KILL'),
('39665', '3', '0', 'Rom\'ogg...sorry...', '14', '0', '0', '0', '0', '18928', 'SAY_DEATH');

-- Quake 
UPDATE `creature_template` SET `flags_extra` = 1, `ScriptName` = 'npc_quake' WHERE  `entry` IN (40401,51406);

-- Chains of Woe
-- Race	Human (Humanoid)
-- Level	 82 - 87 Elite
-- Health	 40,906 - 46,494 (Heroic)
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`='51407';
UPDATE `creature_template` SET `unit_flags`='1', `InhabitType` = 4, `HoverHeight` = 1.5 WHERE `entry`IN ('51407','50379');
UPDATE `creature_template` SET `flags_extra`=1, `ScriptName` = 'npc_chains_of_woe' WHERE `entry` = 40447;

-- spells
-- 76336 Fire Strike
DELETE FROM `spell_script_names` WHERE `spell_id` IN(75272, 95317,75464);
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`)
VALUES
(75272,'spell_quake_summon_target'),
(95317,'spell_quake_summon_target'),
(75464,'spell_chains_of_woe');

-- Crushing Bones and Cracking Skulls achievement
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` = 5281;
INSERT INTO `achievement_criteria_data` VALUES 
(5281, 11, 0, 0, 'achievement_crushing_bones_and_cracking_skulls');