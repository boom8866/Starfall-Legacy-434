DELETE FROM `spell_proc_event` WHERE `entry` IN (91003, 90998);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(91003, 0, 0, 0, 0, 0, 0, 0, 0, 100, 45),
(90998, 0, 0, 0, 0, 0, 0, 0, 0, 100, 45);