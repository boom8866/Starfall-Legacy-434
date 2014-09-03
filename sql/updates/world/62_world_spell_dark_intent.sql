DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_dark_intent';
DELETE FROM `spell_proc_event` WHERE `entry` IN (85767, 85768);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(85767, 0, 0, 0, 0, 0, 262144, 2, 0, 100, 0),
(85768, 0, 5, 0, 0, 0, 262144, 2, 0, 100, 0);

