DELETE FROM `spell_script_names` WHERE `spell_id`  IN (77700, 77701);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77700, 'spell_sha_improved_lava_lash'),
(77701, 'spell_sha_improved_lava_lash');

DELETE FROM `spell_proc_event` WHERE `entry` IN (77700, 77701);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(77701, 0, 11, 0, 0, 4, 16, 0, 0, 100, 0),
(77700, 0, 11, 0, 0, 4, 16, 0, 0, 100, 0);