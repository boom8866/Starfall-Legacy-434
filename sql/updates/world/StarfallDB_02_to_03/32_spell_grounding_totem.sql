DELETE FROM `spell_proc_event` WHERE `entry` = '89523';
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (89523, 126, 0, 0, 0, 0, 131072, 0, 0, 0, 0);
UPDATE `creature_template` SET `spell1`=0, `spell2`=0 WHERE  `entry`=5925;
UPDATE `creature_template` SET `ScriptName`='npc_grounding_totem' WHERE  `entry`=5925;