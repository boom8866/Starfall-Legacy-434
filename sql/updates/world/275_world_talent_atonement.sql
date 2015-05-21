DELETE FROM `spell_proc_event` WHERE `entry` IN (14523, 81749);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(14523, 0, 6, 1048704, 0, 0, 65536, 0, 0, 100, 0),
(81749, 0, 6, 1048704, 0, 0, 65536, 0, 0, 100, 0);