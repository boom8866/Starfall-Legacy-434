DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_pal_shield_of_righteous';
DELETE FROM `spell_bonus_data` WHERE `entry` = '53600';
INSERT INTO `spell_bonus_data` (`entry`, `comments`) VALUES (53600, 'Paladin - Shield of the Righteous');