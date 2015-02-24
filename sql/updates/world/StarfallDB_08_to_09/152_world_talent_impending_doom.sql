DELETE FROM `spell_proc_event` WHERE `entry` IN (85106, 85107, 85108);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(85106, 36, 5, 2097153, 192, 0, 65536, 0, 0, 5, 0),
(85107, 36, 5, 2097153, 192, 0, 65536, 0, 0, 10, 0),
(85108, 36, 5, 2097153, 192, 0, 65536, 0, 0, 15, 0);