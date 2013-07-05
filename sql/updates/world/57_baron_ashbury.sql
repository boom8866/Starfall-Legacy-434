
/*
12:36:46.857 -- aggro

12:37:06.919 -- asphyxiate 1
12:37:14.158 -- execution delay

12:36:52.442 -- pain and suffering 1
12:37:18.978 -- pain and suffering 2

12:37:00.882 -- wracking pain 1
12:37:27.418 -- wracking pain 2
*/


UPDATE `creature_template` SET `scriptname`= 'boss_baron_ashbury' WHERE `entry`= 46962;
UPDATE `creature_template` SET `flags_extra`= 128 WHERE `entry`= 50604;
DELETE FROM `creature` WHERE `id`= 50604;
DELETE FROM `creature_template_addon` WHERE `entry`= 50604;

DELETE FROM `spell_script_names` WHERE `spell_id`= 93424;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93424, 'spell_sfk_asphyxiate_damage');

DELETE FROM `creature_text` WHERE `entry`= 46962;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(46962, 1, 0, 'Tally ho! The hunt begins!', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 2, 0, 'This is just too easy...', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 3, 0, '|TInterface\\Icons\\spell_holy_healingaura.blp:20|tBaron Ashbury begins to channel |cFFFF0000|Hspell:93468|h''Stay of Execution''|h|r !', 41, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 4, 0, 'HA! Let\'s at least keep it interesting.', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 5, 0, 'I grow tired of this hunt... Time to die!', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 6, 0, 'Killed by lowly commoners, how droll...', 14, 0, 100, 0, 0, 0, 'Baron Ashbury');

DELETE FROM `conditions` WHERE `SourceEntry`= 93766;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 93766, 0, 0, 31, 0, 3, 50604, 0, 0, 0, '', 'Dark Archangel - Wings Aura');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (93757);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
('93757', '93766', '0', 'Baron Ashbury Wings - Apply Aura'),
('93757', '93812', '0', 'Baron Ashbury - Archangel Damage Aura');
