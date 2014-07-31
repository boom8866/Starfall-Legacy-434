DELETE FROM `spell_bonus_data` WHERE `entry` = '53301';
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(53301, 0.2730, 'Hunter - Explosive Shot');

DELETE FROM `spell_bonus_data` WHERE `entry` = '1978';
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(1978, 0.4, 'Hunter - Serpent Sting');

DELETE FROM `spell_bonus_data` WHERE `entry` = '88453';
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(88453, 0.4, 'Hunter - Serpent Sting Spread');

DELETE FROM `spell_bonus_data` WHERE `entry` = '3674';
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(3674, 0.665, 'Hunter - Black Arrow');

DELETE FROM `spell_bonus_data` WHERE `entry` = '13797';
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(13797, 0.02, 'Hunter - Immolation Trap');

DELETE FROM `spell_bonus_data` WHERE `entry` = '13812';
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(13812, 0.0545, 'Hunter - Explosive Trap');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_hun_camouflage_ignore';