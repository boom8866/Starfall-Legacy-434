DELETE FROM `spell_proc_event` WHERE `entry` = '78228';
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (78228, 0, 6, 8421376, 1024, 0, 0, 2, 0, 0, 0);
UPDATE `spell_proc_event` SET `procEx`=2 WHERE `entry`=33191 LIMIT 1;