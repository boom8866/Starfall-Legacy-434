DELETE FROM `spell_script_names` WHERE `spell_id` = '64801';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(64801, 'spell_dru_instant_rejuvenation');

DELETE FROM `spell_bonus_data` WHERE `entry` = '64801';
INSERT INTO `spell_bonus_data` (`entry`, `comments`) VALUES
(64801, 'Druid - Instant Rejuvenation');