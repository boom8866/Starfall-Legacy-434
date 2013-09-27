--  Item - Death Knight T13 Blood 2P Bonus
DELETE FROM `spell_proc_event` WHERE `entry` = 105552;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('105552', '0', '15', '0', '0', '0', '666280', '0', '0', '0', '45');