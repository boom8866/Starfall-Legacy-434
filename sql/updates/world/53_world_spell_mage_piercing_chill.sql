DELETE FROM `spell_script_names` WHERE `spell_id` = '83154';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(83154, 'spell_mage_piercing_chill');

DELETE FROM `spell_proc_event` WHERE `entry` IN (83156, 83157);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(83156, 16, 3, 32, 0, 0, 65536, 2, 0, 100, 0),
(83157, 16, 3, 32, 0, 0, 65536, 2, 0, 100, 0);