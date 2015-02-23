DELETE FROM `spell_script_names` WHERE `spell_id` = '64801';
DELETE FROM `spell_script_names` WHERE `spell_id` = '774';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(774, 'spell_dru_rejuvenation');

DELETE FROM `spell_bonus_data` WHERE `entry` = '64801';
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(64801, 0.13477, 0, 0, 0, 'Druid - Instant Rejuvenation');