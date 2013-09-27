DELETE FROM `spell_script_names` WHERE `spell_id` = '46832';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (46832, 'spell_dru_pvpset_4p_balance');

DELETE FROM `spell_proc_event` WHERE `entry` = '46832';
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (46832, 0, 7, 0, 0, 0, 1048576, 0, 0, 0, 0);