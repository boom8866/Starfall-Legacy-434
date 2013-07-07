DELETE FROM `spell_proc_event` WHERE `entry` = '33881';
DELETE FROM `spell_proc_event` WHERE `entry` = '33882';
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (33881, 0, 0, 0, 0, 0, 1048576, 0, 0, 0, 0);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (33882, 0, 0, 0, 0, 0, 1048576, 0, 0, 0, 0);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (45281, 774, 'Nature\'s Ward -> Cast Rejuvenation');